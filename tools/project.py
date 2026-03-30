###
# PS2 project generator adapted from decomp-toolkit template
# Generates build.ninja and objdiff.json for PS2/MWCCPS2 projects.
#
# This is specifically adapted for Sonic Riders: Zero Gravity (PS2)
# and maintains compatibility with splat-based workflows.
###

import io
import json
import os
import platform
import sys
import re
from pathlib import Path
from typing import Any, Dict, List, Optional, Set, Tuple

from . import ninja_syntax
from .ninja_syntax import serialize_path

if sys.platform == "cygwin":
    sys.exit(
        f"Cygwin/MSYS2 is not supported."
        f"\nPlease use native Windows Python instead."
        f"\n(Current path: {sys.executable})"
    )

Library = Dict[str, Any]


class Object:
    def __init__(self, completed: bool, name: str, **options: Any) -> None:
        self.name = name
        self.completed = completed
        self.options: Dict[str, Any] = {
            "add_to_all": None,
            "asflags": None,
            "asm_dir": None,
            "cflags": None,
            "extra_asflags": [],
            "extra_cflags": [],
            "lib": None,
            "mw_version": None,
            "progress_category": None,
            "scratch_preset_id": None,
            "source": name,
            "src_dir": None,
        }
        self.options.update(options)

        # Internal
        self.src_path: Optional[Path] = None
        self.asm_path: Optional[Path] = None
        self.src_obj_path: Optional[Path] = None
        self.asm_obj_path: Optional[Path] = None
        self.ctx_path: Optional[Path] = None

    def resolve(self, config: "ProjectConfig", lib: Library) -> "Object":
        # Use object options, then library options
        obj = Object(self.completed, self.name, **lib)
        for key, value in self.options.items():
            if value is not None or key not in obj.options:
                obj.options[key] = value

        # Use default options from config
        def set_default(key: str, value: Any) -> None:
            if obj.options[key] is None:
                obj.options[key] = value

        set_default("add_to_all", True)
        set_default("asflags", config.asflags)
        set_default("asm_dir", config.asm_dir)
        set_default("mw_version", config.linker_version)
        set_default("src_dir", config.src_dir)

        # Validate progress categories
        def check_category(category: str):
            if not any(category == c.id for c in config.progress_categories):
                sys.exit(
                    f"Progress category '{category}' missing from config.progress_categories"
                )

        progress_category = obj.options["progress_category"]
        if isinstance(progress_category, list):
            for category in progress_category:
                check_category(category)
        elif progress_category is not None:
            check_category(progress_category)

        # Resolve paths
        build_dir = config.out_path()
        obj.src_path = Path(obj.options["src_dir"]) / obj.options["source"]
        if obj.options["asm_dir"] is not None:
            obj.asm_path = (
                Path(obj.options["asm_dir"]) / obj.options["source"]
            ).with_suffix(".s")
        base_name = Path(self.name).with_suffix("")
        obj.src_obj_path = build_dir / "src" / f"{base_name}.o"
        obj.asm_obj_path = build_dir / "obj" / f"{base_name}.o"
        obj.ctx_path = build_dir / "src" / f"{base_name}.ctx"
        return obj


class ProgressCategory:
    def __init__(self, id: str, name: str) -> None:
        self.id = id
        self.name = name


class ProjectConfig:
    def __init__(self) -> None:
        # Paths
        self.build_dir: Path = Path("build")
        self.src_dir: Path = Path("src")
        self.tools_dir: Path = Path("tools")
        self.asm_dir: Optional[Path] = None

        # Tooling
        self.binutils_tag: Optional[str] = None
        self.binutils_path: Optional[Path] = None
        self.compilers_tag: Optional[str] = None
        self.compilers_path: Optional[Path] = None
        self.mwccps2_tag: Optional[str] = None
        self.wibo_tag: Optional[str] = None
        self.wrapper: Optional[Path] = None
        self.ninja_path: Optional[Path] = None
        self.objdiff_tag: Optional[str] = None
        self.objdiff_path: Optional[Path] = None

        # Project config
        self.non_matching: bool = False
        self.check_sha_path: Optional[Path] = None
        self.config_path: Optional[Path] = None
        self.symbol_addrs_path: Optional[Path] = None
        self.generate_map: bool = False
        self.asflags: Optional[List[str]] = None
        self.ldflags: Optional[List[str]] = None
        self.libs: Optional[List[Library]] = None
        self.linker_version: Optional[str] = None
        self.version: Optional[str] = None
        self.warn_missing_config: bool = False
        self.warn_missing_source: bool = False
        self.reconfig_deps: Optional[List[Path]] = None
        self.short_loop_workaround: bool = True

        # decomp.me scratch settings
        self.scratch_preset_id: Optional[int] = None
        self.scratch_platform: str = "ps2"
        # Include dirs passed to decompctx.py (e.g. ["include"])
        self.ctx_include_dirs: List[str] = ["include"]

        # Progress output
        self.progress = True
        self.progress_each_module: bool = False
        self.progress_categories: List[ProgressCategory] = []

    def validate(self) -> None:
        required_attrs = [
            "build_dir",
            "src_dir",
            "tools_dir",
            "check_sha_path",
            "config_path",
            "ldflags",
            "linker_version",
            "libs",
            "version",
        ]
        for attr in required_attrs:
            if getattr(self, attr) is None:
                sys.exit(f"ProjectConfig.{attr} missing")

    def objects(self) -> Dict[str, Object]:
        out = {}
        for lib in self.libs or {}:
            objects: List[Object] = lib["objects"]
            for obj in objects:
                if obj.name in out:
                    sys.exit(f"Duplicate object name {obj.name}")
                out[obj.name] = obj.resolve(self, lib)
        return out

    def out_path(self) -> Path:
        return self.build_dir / str(self.version)

    def compilers(self) -> Path:
        if self.compilers_path:
            return self.compilers_path
        elif self.compilers_tag:
            return self.build_dir / "compilers"
        else:
            sys.exit("ProjectConfig.compilers_tag missing")

    def compiler_wrapper(self) -> Optional[Path]:
        wrapper = self.wrapper

        if self.use_wibo():
            wrapper = self.build_dir / "tools" / "wibo"
        if not is_windows() and wrapper is None:
            wrapper = Path("wine")

        return wrapper

    def use_wibo(self) -> bool:
        return (
            self.wibo_tag is not None
            and (sys.platform == "linux" or sys.platform == "darwin")
            and platform.machine() in ("i386", "x86_64", "aarch64", "arm64")
            and self.wrapper is None
        )


def is_windows() -> bool:
    return os.name == "nt"


# On Windows, we need this to use && in commands
CHAIN = "cmd /c " if is_windows() else ""
# Native executable extension
EXE = ".exe" if is_windows() else ""


def file_is_asm(path: Path) -> bool:
    return path.suffix.lower() == ".s"


def file_is_c(path: Path) -> bool:
    return path.suffix.lower() == ".c"


def file_is_cpp(path: Path) -> bool:
    return path.suffix.lower() in (".cc", ".cp", ".cpp", ".cxx")


def file_is_c_cpp(path: Path) -> bool:
    return file_is_c(path) or file_is_cpp(path)


def make_flags_str(flags: Optional[List[str]]) -> str:
    if flags is None:
        return ""
    return " ".join(flags)


# Short loop workaround for MWCCPS2
COMMENT_PART = r"\/\* (.+) ([0-9A-Z]{2})([0-9A-Z]{2})([0-9A-Z]{2})([0-9A-Z]{2}) \*\/"
INSTRUCTION_PART = r"(\b(bne|bnel|beq|beql|bnez|bnezl|beqzl|bgez|bgezl|bgtz|bgtzl|blez|blezl|bltz|bltzl|b)\b.*)"
OPCODE_PATTERN = re.compile(f"{COMMENT_PART}  {INSTRUCTION_PART}")

PROBLEMATIC_FUNCS = set([
    "UpdateJtActive__FP2JTP3JOYf",
    "AddMatrix4Matrix4__FP7MATRIX4N20",
    "FInvertMatrix__FiPfT1",
    "PwarpFromOid__F3OIDT0",
    "RenderMsGlobset__FP2MSP2CMP2RO",
    "ProjectBlipgTransform__FP5BLIPGfi",
    "DrawTvBands__FP2TVR4GIFS",
    "LoadShadersFromBrx__FP18CBinaryInputStream",
    "FillShaders__Fi",
    "FUN_001aea70",
    "ApplyDzg__FP3DZGiPiPPP2SOff",
    "BounceRipgRips__FP4RIPG",
    "UpdateStepPhys__FP4STEP",
    "PredictAsegEffect__FP4ASEGffP3ALOT3iP6VECTORP7MATRIX3T6T6",
    "ExplodeExplsExplso__FP5EXPLSP6EXPLSO",
    "UpdateShadow__FP6SHADOWf"
])


def replace_instructions_with_opcodes(asm_folder: Path) -> None:
    """Replace branch instructions with raw opcodes for functions that trigger the short loop bug."""
    nm_folder = asm_folder / "nonmatchings"
    if not nm_folder.exists():
        return

    for p in nm_folder.rglob("*.s"):
        if p.stem not in PROBLEMATIC_FUNCS:
            continue

        with p.open("r") as file:
            content = file.read()

        if re.search(OPCODE_PATTERN, content):
            content = re.sub(
                OPCODE_PATTERN,
                r"/* \1 \2\3\4\5 */  .word      0x\5\4\3\2 /* \6 */",
                content,
            )

            with p.open("w") as file:
                file.write(content)


# Generate build.ninja and objdiff.json
def generate_build(config: ProjectConfig) -> None:
    config.validate()
    objects = config.objects()
    
    # Run splat to generate asm and linker script
    print("Running splat to split binary...")
    import splat.scripts.split as split
    split.main([config.config_path], modes="all", verbose=False)
    
    # Convert GNU ld script to MWLD LCF format
    print("Converting linker script to LCF format...")
    splat_ld = config.out_path() / "SLUS_216.42.splat.ld"
    template_lcf = Path("include") / "template.lcf"
    output_lcf = config.out_path() / "SLUS_216.42.lcf"
    
    import subprocess
    subprocess.run([
        sys.executable,
        config.tools_dir / "convert_ld_to_lcf.py",
        "--splat-ld", str(splat_ld),
        "--template", str(template_lcf),
        "--output", str(output_lcf),
        "--build-dir", str(config.out_path()),
    ], check=True)
    
    # Apply short loop workaround if enabled
    if config.short_loop_workaround:
        asm_path = config.out_path() / "asm"
        if asm_path.exists():
            print("Applying short loop workaround...")
            replace_instructions_with_opcodes(asm_path)
    
    generate_build_ninja(config, objects)
    generate_objdiff_config(config, objects)


# Generate build.ninja
def generate_build_ninja(
    config: ProjectConfig,
    objects: Dict[str, Object],
) -> None:
    out = io.StringIO()
    n = ninja_syntax.Writer(out)
    n.variable("ninja_required_version", "1.3")
    n.newline()

    configure_script = Path(os.path.relpath(os.path.abspath(sys.argv[0])))
    python_lib = Path(os.path.relpath(__file__))
    python_lib_dir = python_lib.parent
    n.comment("The arguments passed to configure.py, for rerunning it.")
    n.variable("configure_args", sys.argv[1:])
    n.variable("python", f'"{sys.executable}"')
    n.newline()

    ###
    # Variables
    ###
    n.comment("Variables")
    n.variable("ldflags", make_flags_str(config.ldflags))
    if config.linker_version is None:
        sys.exit("ProjectConfig.linker_version missing")
    n.variable("mw_version", Path(config.linker_version))
    n.newline()

    ###
    # Tooling
    ###
    n.comment("Tooling")

    build_path = config.out_path()
    report_path = build_path / "report.json"
    build_tools_path = config.build_dir / "tools"
    download_tool = config.tools_dir / "download_tool.py"
    n.rule(
        name="download_tool",
        command=f"$python {download_tool} $tool $out --tag $tag",
        description="TOOL $out",
    )

    # objdiff-cli
    if config.objdiff_path is not None and config.objdiff_path.is_file():
        objdiff = config.objdiff_path
    elif config.objdiff_tag:
        objdiff = build_tools_path / f"objdiff-cli{EXE}"
        n.build(
            outputs=objdiff,
            rule="download_tool",
            implicit=download_tool,
            variables={
                "tool": "objdiff-cli",
                "tag": config.objdiff_tag,
            },
        )
    else:
        sys.exit("ProjectConfig.objdiff_tag missing")

    # wibo or wine wrapper
    wrapper = config.compiler_wrapper()
    wrapper_implicit: Optional[Path] = None
    if wrapper is not None and config.use_wibo():
        n.build(
            outputs=wrapper,
            rule="download_tool",
            implicit=download_tool,
            variables={
                "tool": "wibo",
                "tag": config.wibo_tag,
            },
        )
        wrapper_implicit = wrapper

    wrapper_cmd = f"{wrapper} " if wrapper else ""

    # Compilers
    compilers = config.compilers()
    compilers_implicit: Optional[Path] = None
    if config.compilers_path is None and config.compilers_tag is not None:
        compilers_implicit = compilers
        n.build(
            outputs=compilers,
            rule="download_tool",
            implicit=download_tool,
            variables={
                "tool": "compilers",
                "tag": config.compilers_tag,
            },
        )

    # PS2 compiler (downloaded separately)
    mwccps2_implicit: Optional[Path] = None
    if config.mwccps2_tag is not None:
        mwccps2_dir = compilers / "PS2" / f"mwcps2-{config.mwccps2_tag}"
        mwccps2_implicit = mwccps2_dir
        n.build(
            outputs=mwccps2_dir,
            rule="download_tool",
            implicit=download_tool,
            variables={
                "tool": "mwccps2",
                "tag": config.mwccps2_tag,
            },
        )
    else:
        sys.exit("ProjectConfig.mwccps2_tag missing")

    # Binutils
    binutils_implicit = None
    if config.binutils_path:
        binutils = config.binutils_path
    elif config.binutils_tag:
        binutils = config.build_dir / "binutils"
        binutils_implicit = binutils
        n.build(
            outputs=binutils,
            rule="download_tool",
            implicit=download_tool,
            variables={
                "tool": "binutils",
                "tag": config.binutils_tag,
            },
        )
    else:
        sys.exit("ProjectConfig.binutils_tag missing")

    n.newline()

    ###
    # Helper rule for downloading all tools
    ###
    n.comment("Download all tools")
    n.build(
        outputs="tools",
        rule="phony",
        inputs=[wrapper, compilers, mwccps2_dir, binutils, objdiff],
    )
    n.newline()

    ###
    # Build rules
    ###
    compiler_path = compilers / "$mw_version"

    # MWCCPS2
    mwcc = compiler_path / "mwccps2.exe"
    mwcc_cmd = f"{wrapper_cmd}{mwcc} $cflags -c $in -o $out"
    mwcc_implicit: List[Optional[Path]] = [compilers_implicit or mwcc, wrapper_implicit]

    # Patch MWCCPS2 compiler DLLs (done after download)
    n.comment("Patch MWCCPS2 compiler DLLs")

    patch_script = config.tools_dir / "patch_compiler.py"
    n.rule(
        name="patch_compiler",
        command=f"$python {patch_script} $gc_dll_path $ps2_compiler_path $out",
        description="PATCH $ps2_compiler_path",
    )
    gc_dll_path = compilers / "GC" / "3.0a5"
    ps2_compiler_path = mwccps2_dir
    patch_marker = ps2_compiler_path / ".patched"
    n.build(
        outputs=patch_marker,
        rule="patch_compiler",
        implicit=[compilers_implicit, mwccps2_implicit, patch_script],
        variables={
            "gc_dll_path": gc_dll_path,
            "ps2_compiler_path": ps2_compiler_path,
        },
    )
    mwcc_implicit.append(patch_marker)
    n.newline()

    # MWLD (linker)
    mwld = compiler_path / "mwldps2.exe"
    mwld_cmd = f"{wrapper_cmd}{mwld} $ldflags -o $out $in"
    mwld_implicit: List[Optional[Path]] = [compilers_implicit or mwld, wrapper_implicit]

    # GNU as (MIPS assembler)
    gnu_as = binutils / f"mips-linux-gnu-as{EXE}"
    gnu_as_cmd = f"{gnu_as} $asflags -o $out $in"
    gnu_as_implicit = [binutils_implicit or gnu_as]

    # Transform dependency files on non-Windows
    if os.name != "nt":
        transform_dep = config.tools_dir / "transform_dep.py"
        mwcc_cmd += f" -MMD && $python {transform_dep} $out.d $out.d"
        mwcc_implicit.append(transform_dep)

    n.comment("Link ELF file")
    n.rule(
        name="link",
        command=mwld_cmd,
        description="LINK $out",
    )
    n.newline()

    n.comment("MWCC build")
    n.rule(
        name="mwcc",
        command=mwcc_cmd,
        description="MWCC $out",
        depfile="$out.d",
        deps="gcc",
    )
    n.newline()

    n.comment("Assemble asm")
    n.rule(
        name="as",
        command=gnu_as_cmd,
        description="AS $out",
    )
    n.newline()

    n.comment("Generate decomp.me context")
    decompctx = config.tools_dir / "decompctx.py"
    ctx_include_flags = " ".join(f"-I {d}" for d in config.ctx_include_dirs)
    n.rule(
        name="ctx",
        command=f"$python {decompctx} $in -o $out -d $out.d {ctx_include_flags}",
        description="CTX $in",
        depfile="$out.d",
        deps="gcc",
    )
    n.newline()

    ###
    # Source files
    ###
    n.comment("Source files")
    source_inputs: List[Path] = []
    source_added: Set[Path] = set()

    def c_build(obj: Object, src_path: Path) -> Optional[Path]:
        if obj.src_obj_path is None or obj.src_obj_path in source_added:
            return obj.src_obj_path
        source_added.add(obj.src_obj_path)

        cflags = obj.options["cflags"]
        extra_cflags = obj.options["extra_cflags"]
        all_cflags = cflags + extra_cflags
        cflags_str = make_flags_str(all_cflags)

        lib_name = obj.options["lib"]
        n.comment(f"{obj.name}: {lib_name} (linked {obj.completed})")
        n.build(
            outputs=obj.src_obj_path,
            rule="mwcc",
            inputs=src_path,
            variables={
                "mw_version": Path(obj.options["mw_version"]),
                "cflags": cflags_str,
            },
            implicit=mwcc_implicit,
        )
        n.newline()

        if obj.ctx_path is not None:
            n.build(
                outputs=obj.ctx_path,
                rule="ctx",
                inputs=src_path,
            )
            n.newline()

        if obj.options["add_to_all"]:
            source_inputs.append(obj.src_obj_path)

        return obj.src_obj_path

    def asm_build(obj: Object, src_path: Path, obj_path: Optional[Path]) -> Optional[Path]:
        if obj.options["asflags"] is None:
            sys.exit("ProjectConfig.asflags missing")
        asflags_str = make_flags_str(obj.options["asflags"])
        if len(obj.options["extra_asflags"]) > 0:
            extra_asflags_str = make_flags_str(obj.options["extra_asflags"])
            asflags_str += " " + extra_asflags_str

        if obj_path is None or obj_path in source_added:
            return obj_path
        source_added.add(obj_path)

        lib_name = obj.options["lib"]
        n.comment(f"{obj.name}: {lib_name} (linked {obj.completed})")
        n.build(
            outputs=obj_path,
            rule="as",
            inputs=src_path,
            variables={"asflags": asflags_str},
            implicit=gnu_as_implicit,
        )
        n.newline()

        if obj.options["add_to_all"]:
            source_inputs.append(obj_path)

        return obj_path

    # Build all objects
    link_inputs: List[Path] = []
    for obj in objects.values():
        link_built_obj = obj.completed
        built_obj_path: Optional[Path] = None

        if obj.src_path is not None and obj.src_path.exists():
            if file_is_c_cpp(obj.src_path):
                built_obj_path = c_build(obj, obj.src_path)
            elif file_is_asm(obj.src_path):
                built_obj_path = asm_build(obj, obj.src_path, obj.src_obj_path)
            else:
                sys.exit(f"Unknown source file type {obj.src_path}")
        else:
            if config.warn_missing_source or obj.completed:
                print(f"Missing source file {obj.src_path}")
            link_built_obj = False

        # Assembly overrides
        asm_obj_path: Optional[Path] = None
        if obj.asm_path is not None and obj.asm_path.exists():
            asm_obj_path = asm_build(obj, obj.asm_path, obj.asm_obj_path)
            # Only use for linking if source doesn't match
            if not link_built_obj:
                link_built_obj = True
                built_obj_path = asm_obj_path

        if link_built_obj and built_obj_path is not None:
            link_inputs.append(built_obj_path)

    n.newline()

    ###
    # Helper rule for building all source files
    ###
    n.comment("Build all source files")
    n.build(
        outputs="all_source",
        rule="phony",
        inputs=source_inputs,
    )
    n.newline()

    ###
    # Link
    ###
    elf_path = build_path / f"{config.version}.elf"
    lcf_script = build_path / "SLUS_216.42.lcf"  # Generated LCF file
    
    n.comment("Link ELF")
    elf_ldflags = f"$ldflags {serialize_path(lcf_script)}"
    if config.generate_map:
        elf_map = elf_path.with_suffix(".map")
        elf_ldflags += f" -map {serialize_path(elf_map)}"
    else:
        elf_map = None
    
    n.build(
        outputs=elf_path,
        rule="link",
        inputs=link_inputs,
        implicit=[lcf_script, binutils, *mwld_implicit],
        implicit_outputs=elf_map,
        variables={"ldflags": elf_ldflags},
    )
    n.newline()

    ###
    # Check hash
    ###
    n.comment("Check hash")
    ok_path = build_path / "ok"
    n.rule(
        name="check",
        command=f"sha1sum -c $in && touch $out",
        description="CHECK $in",
    )
    n.build(
        outputs=ok_path,
        rule="check",
        inputs=config.check_sha_path,
        implicit=[elf_path],
    )
    n.newline()

    ###
    # Calculate progress
    ###
    if config.progress:
        n.comment("Calculate progress")
        n.rule(
            name="progress",
            command=f"$python {configure_script} $configure_args progress",
            description="PROGRESS",
        )
        n.build(
            outputs="progress",
            rule="progress",
            implicit=[report_path, configure_script, python_lib],
        )

        ###
        # Generate progress report
        ###
        n.comment("Generate progress report")
        n.rule(
            name="report",
            command=f"{objdiff} report generate -o $out",
            description="REPORT",
        )
        n.build(
            outputs=report_path,
            rule="report",
            implicit=[objdiff, "objdiff.json", "all_source"],
        )

    ###
    # Regenerate on change
    ###
    n.comment("Reconfigure on change")
    n.rule(
        name="configure",
        command=f"$python {configure_script} $configure_args",
        generator=True,
        description=f"RUN {configure_script}",
    )
    n.build(
        outputs=["build.ninja", "objdiff.json"],
        rule="configure",
        implicit=[
            configure_script,
            python_lib,
            python_lib_dir / "ninja_syntax.py",
            config.config_path,
            *(config.reconfig_deps or []),
        ],
    )
    n.newline()

    ###
    # Default rule
    ###
    n.comment("Default rule")
    if config.non_matching:
        n.default(elf_path)
    elif config.progress:
        n.default("progress")
    else:
        n.default(ok_path)

    # Write build.ninja
    with open("build.ninja", "w", encoding="utf-8") as f:
        f.write(out.getvalue())
    out.close()


# Generate objdiff.json
def generate_objdiff_config(
    config: ProjectConfig,
    objects: Dict[str, Object],
) -> None:
    # Load existing objdiff.json
    existing_units: Dict[str, Any] = {}
    if Path("objdiff.json").is_file():
        with open("objdiff.json", "r", encoding="utf-8") as r:
            existing_config = json.load(r)
            existing_units = {
                unit["name"]: unit for unit in existing_config.get("units", [])
            }

    if config.ninja_path:
        ninja = str(config.ninja_path.absolute())
    else:
        ninja = "ninja"

    objdiff_config: Dict[str, Any] = {
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "min_version": "2.0.0-beta.5",
        "custom_make": ninja,
        "build_target": False,
        "watch_patterns": [
            "*.c",
            "*.cc",
            "*.cp",
            "*.cpp",
            "*.cxx",
            "*.c++",
            "*.h",
            "*.hh",
            "*.hp",
            "*.hpp",
            "*.hxx",
            "*.h++",
            "*.pch",
            "*.pch++",
            "*.inc",
            "*.py",
            "*.yml",
            "*.txt",
            "*.json",
        ],
        "units": [],
        "progress_categories": [],
    }

    # decomp.me compiler name mapping for PS2
    PS2_COMPILER_MAP = {
        "PS2/mwcps2-3.0.1b198-051011": "mwcps2-3.0.1b198-051011",
    }

    for obj in objects.values():
        unit_config: Dict[str, Any] = {
            "name": obj.name,
            "target_path": obj.asm_obj_path,
            "base_path": None,
            "scratch": None,
            "metadata": {
                "complete": None,
                "reverse_fn_order": None,
                "source_path": None,
                "progress_categories": (
                    [obj.options["progress_category"]]
                    if obj.options["progress_category"]
                    else []
                ),
                "auto_generated": False,
            },
            "symbol_mappings": None,
        }

        # Preserve existing symbol mappings
        existing_unit = existing_units.get(obj.name)
        if existing_unit is not None:
            unit_config["symbol_mappings"] = existing_unit.get("symbol_mappings")

        src_exists = obj.src_path is not None and obj.src_path.exists()
        if src_exists:
            unit_config["base_path"] = obj.src_obj_path
            unit_config["metadata"]["source_path"] = obj.src_path

        # Only generate scratch block for C/C++ source files
        if obj.src_path is not None and file_is_c_cpp(obj.src_path):
            def keep_flag(flag: str) -> bool:
                return not any(
                    flag.startswith(prefix)
                    for prefix in ("-i ", "-i-", "-I ", "-I+", "-I-")
                )

            all_cflags = list(
                filter(
                    keep_flag,
                    (obj.options["cflags"] or []) + (obj.options["extra_cflags"] or []),
                )
            )

            # Check for reverse_fn_order (-inline deferred)
            reverse_fn_order = False
            for flag in all_cflags:
                if not flag.startswith("-inline "):
                    continue
                for value in flag.split(" ")[1].split(","):
                    if value == "deferred":
                        reverse_fn_order = True
                    elif value == "nodeferred":
                        reverse_fn_order = False

            compiler_version = PS2_COMPILER_MAP.get(obj.options["mw_version"])
            if compiler_version is None:
                print(
                    f"Missing scratch compiler mapping for {obj.options['mw_version']}"
                )
            else:
                cflags_str = make_flags_str(all_cflags)
                preset_id = obj.options["scratch_preset_id"] or config.scratch_preset_id
                unit_config["scratch"] = {
                    "platform": config.scratch_platform,
                    "compiler": compiler_version,
                    "c_flags": cflags_str,
                    "preset_id": preset_id,
                }
                if src_exists:
                    unit_config["scratch"].update(
                        {
                            "ctx_path": obj.ctx_path,
                            "build_ctx": True,
                        }
                    )

            unit_config["metadata"].update(
                {
                    "complete": obj.completed if src_exists else None,
                    "reverse_fn_order": reverse_fn_order,
                }
            )

        objdiff_config["units"].append(unit_config)

    # Add progress categories
    for category in config.progress_categories:
        objdiff_config["progress_categories"].append(
            {
                "id": category.id,
                "name": category.name,
            }
        )

    def cleandict(d: Any) -> Any:
        if isinstance(d, dict):
            return {k: cleandict(v) for k, v in d.items() if v is not None}
        elif isinstance(d, list):
            return [cleandict(v) for v in d]
        return d

    def unix_path(input: Any) -> str:
        return str(input).replace(os.sep, "/") if input else ""

    with open("objdiff.json", "w", encoding="utf-8") as w:
        json.dump(cleandict(objdiff_config), w, indent=2, default=unix_path)


# Print progress information
def calculate_progress(config: ProjectConfig) -> None:
    config.validate()
    out_path = config.out_path()
    report_path = out_path / "report.json"
    if not report_path.is_file():
        sys.exit(f"Report file {report_path} does not exist")

    with open(report_path, "r", encoding="utf-8") as f:
        report_data = json.load(f)

    # Convert string numbers to int
    def convert_numbers(data: Dict[str, Any]) -> None:
        for key, value in data.items():
            if isinstance(value, str) and value.isdigit():
                data[key] = int(value)

    convert_numbers(report_data["measures"])
    for category in report_data.get("categories", []):
        convert_numbers(category["measures"])

    # Print progress
    print("Progress:")

    def print_category(name: str, measures: Dict[str, Any]) -> None:
        total_code = measures.get("total_code", 0)
        matched_code = measures.get("matched_code", 0)
        matched_code_percent = measures.get("matched_code_percent", 0)
        total_data = measures.get("total_data", 0)
        matched_data = measures.get("matched_data", 0)
        matched_data_percent = measures.get("matched_data_percent", 0)
        total_functions = measures.get("total_functions", 0)
        matched_functions = measures.get("matched_functions", 0)
        complete_code_percent = measures.get("complete_code_percent", 0)
        total_units = measures.get("total_units", 0)
        complete_units = measures.get("complete_units", 0)

        print(f"  {name}: {matched_code_percent:.2f}% matched, {complete_code_percent:.2f}% linked ({complete_units} / {total_units} files)")
        print(f"    Code: {matched_code} / {total_code} bytes ({matched_functions} / {total_functions} functions)")
        print(f"    Data: {matched_data} / {total_data} bytes ({matched_data_percent:.2f}%)")

    print_category("All", report_data["measures"])
    for category in report_data.get("categories", []):
        print_category(category["name"], category["measures"])
