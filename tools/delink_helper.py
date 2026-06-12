"""
delink_helper.py
Assembles splat-output .s files and partial-links them into relocatable .o files.
Object list is driven by config.json (dtk objdiff format) so it stays in sync
with compile_mwcc.py and objdiff automatically.
"""

import json
import subprocess
import sys
from pathlib import Path, PurePosixPath

# ---------------------------------------------------------------------------
# WSL path helper (Windows only — on Linux just use the real path)
# ---------------------------------------------------------------------------

def to_tool_path(p: Path) -> str:
    """Return a path string suitable for passing to WSL-hosted binaries."""
    if sys.platform != "win32":
        return str(p)
    p = p.resolve()
    drive = p.drive.rstrip(":").lower()
    rest  = PurePosixPath(*p.parts[1:])
    return f"/mnt/{drive}/{rest}"

# ---------------------------------------------------------------------------
# Paths
# ---------------------------------------------------------------------------

ROOT       = Path(__file__).resolve().parent.parent
CONFIG     = ROOT / "objdiff.json"
ASM_DIR    = ROOT / "asm"
INC_DIR    = ROOT / "include"
OUT_SECTION = ROOT / "build" / "section"
OUT_OBJ    = ROOT / "build" / "obj"

# ---------------------------------------------------------------------------
# Toolchain
# ---------------------------------------------------------------------------

AS       = "mips-linux-gnu-as"
LD       = "mips-linux-gnu-ld"
AS_FLAGS = ["-march=r5900", "-mabi=eabi", "-EL", "-I", to_tool_path(INC_DIR)]
LD_FLAGS = ["-EL"]

# (file suffix, subdirectory inside asm/)
SECTIONS = [
    (".s",        ""),
    (".data.s",   "data/"),
    (".rodata.s", "data/"),
#    (".sbss.s",   "data/"),
#    (".bss.s",    "data/"),
]

def run_cmd(cmd: list[str]) -> bool:
    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print(result.stderr.strip(), file=sys.stderr)
        return False
    return True

def wsl(cmd: list[str]) -> list[str]:
    """Prepend 'wsl' on Windows."""
    return (["wsl"] + cmd) if sys.platform == "win32" else cmd

# ---------------------------------------------------------------------------
# Object list from config.json
# ---------------------------------------------------------------------------

def load_objects() -> list[str]:
    """
    Returns a list of bare object names (no extension) derived from
    the 'target_path' field of each unit in config.json.
    e.g. "build/obj/StartMain.o"  ->  "Main/StartMain"
    We reconstruct the subpath from 'name' (SRC/Foo/Bar.cpp -> Foo/Bar).
    """
    with open(CONFIG) as f:
        cfg = json.load(f)
    objects = []
    for unit in cfg.get("units", []):
        name = unit["name"]                       # e.g. "SRC/Main/StartMain.cpp"
        rel  = Path(name).with_suffix("")         # SRC/Main/StartMain
        parts = rel.parts
        # Strip leading "SRC" if present
        if parts[0].upper() == "SRC":
            parts = parts[1:]
        objects.append("/".join(parts))           # "Main/StartMain"
    return objects

# ---------------------------------------------------------------------------
# Build steps
# ---------------------------------------------------------------------------

def assemble_sections(obj: str) -> list[Path] | None:
    """Assemble all .s sections for obj. Returns list of .o paths or None on error."""
    section_objs: list[Path] = []

    for suffix, subdir in SECTIONS:
        s_file = ASM_DIR / f"{subdir}{obj}{suffix}"
        if not s_file.exists():
            continue                              # missing sections are fine (warn only)

        o_file = OUT_SECTION / f"{Path(obj).name}{suffix}.o"
        o_file.parent.mkdir(parents=True, exist_ok=True)

        cmd = wsl([AS, *AS_FLAGS, "-o", to_tool_path(o_file), to_tool_path(s_file)])
        print(f"  AS    {s_file.name} -> {o_file.name}")

        if not run_cmd(cmd):
            print(f"  ERROR assembling {s_file.name}", file=sys.stderr)
            return None

        section_objs.append(o_file)

    if not section_objs:
        print(f"  WARN  no .s files found for {obj}, skipping")

    return section_objs

def partial_link(obj: str, section_objs: list[Path]) -> Path | None:
    """Partial-link section .o files into one relocatable .o for this object."""
    out = OUT_OBJ / f"{Path(obj).name}.o"
    cmd = wsl([
        LD, *LD_FLAGS, "-r",
        "-o", to_tool_path(out),
        *[to_tool_path(o) for o in section_objs],
    ])
    print(f"  LD -r {out.name}")

    if not run_cmd(cmd):
        print(f"  ERROR partial linking {obj}", file=sys.stderr)
        return None

    return out

# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------

def main():
    OUT_SECTION.mkdir(parents=True, exist_ok=True)
    OUT_OBJ.mkdir(parents=True, exist_ok=True)

    objects = load_objects()
    if not objects:
        print("No units found in config.json", file=sys.stderr)
        sys.exit(1)

    ok = warn = err = 0

    for obj in objects:
        print(f"\n[{obj}]")

        section_objs = assemble_sections(obj)
        if section_objs is None:
            err += 1
            continue

        if not section_objs:
            warn += 1
            continue

        if partial_link(obj, section_objs) is None:
            err += 1
            continue

        ok += 1

    print(f"\n{ok} objects built, {warn} skipped (no .s), {err} failed")
    if err:
        sys.exit(1)

if __name__ == "__main__":
    main()
