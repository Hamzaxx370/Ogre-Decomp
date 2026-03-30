#!/usr/bin/env python3
"""
Generates the helper functions + config.libs block for configure.py
by scanning splat-generated asm files and grouping them by library.

Run from repo root:
    python tools/gen_libs.py > libs_section.py

Then review libs_section.py and paste into configure.py, replacing
the existing helper functions and `config.libs = [...]` block.
"""

from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).parent.parent
ASM_DIR = ROOT / "build" / "SLUS-21642-PROTO-070901" / "asm"

# These stay as .s (pure assembly, never compiled to C/C++)
ASM_ONLY = {
    "usr/local/sce/ee/lib/crt0.s",
}


def src_path(rel: Path) -> str:
    """Map an asm-relative Path to the source path used in Object()."""
    s = str(rel).replace("\\", "/")
    if s in ASM_ONLY:
        return s
    ext = ".cpp" if rel.parts[0] == "Develop" else ".c"
    return str(rel.with_suffix(ext)).replace("\\", "/")


def group_key(rel: Path) -> str:
    """Return a logical group key for the given asm-relative path."""
    p = rel.parts

    if p[0] == "Develop":
        # Develop/Projects/SR2/pgm/{src|lib}/...
        area = p[4] if len(p) > 4 else "misc"
        if area == "src":
            # p[5] is either a subdir name ("Object") or a file ("Main.s")
            subdir = p[5] if len(p) > 5 else None
            if subdir is None or "." in subdir:
                return "game_src_root"
            return f"game_src_{subdir}"
        if area == "lib" and len(p) > 5 and p[5] == "OO":
            return f"oo_{p[6]}" if len(p) > 6 else "oo_root"
        return "develop_misc"

    if p[0] == "usr" and len(p) >= 3:
        vendor = p[2]
        if vendor == "metrowerks":
            return "mw_support"
        if vendor == "sce" and len(p) >= 5:
            area = p[4]  # "lib" or "gcc"
            if area == "lib":
                # p[5] is a subdir (e.g. "libcdvd") or a file (e.g. "crt0.s")
                if len(p) <= 5 or "." in p[5]:
                    return "sce_runtime"
                return f"sce_{p[5]}"
            if area == "gcc" and len(p) >= 8:
                return f"sce_{p[7]}"  # libc / libgcc / libm
            return "sce_misc"
        if vendor == "sega" and len(p) >= 4:
            return f"sega_{p[3]}"   # nn / nvs / px
        if vendor == "cri":
            return "cri"
        return f"usr_{vendor}"

    return "misc"


# ── Collect & group ───────────────────────────────────────────────────────────

groups: dict[str, list[str]] = defaultdict(list)
for asm_file in sorted(ASM_DIR.rglob("*.s")):
    rel = asm_file.relative_to(ASM_DIR)
    if rel.parts[0] not in ("Develop", "usr"):
        continue
    groups[group_key(rel)].append(src_path(rel))


# ── Emit helpers ──────────────────────────────────────────────────────────────

HELPERS = '''\
# ============================================================
# Helper functions
# ============================================================

def GameSrc(subdir: str, objects: List[Object]) -> Dict[str, Any]:
    """Game source code under pgm/src/<subdir>/"""
    return {
        "lib": subdir,
        "mw_version": config.linker_version,
        "cflags": cflags_base,
        "progress_category": "game",
        "objects": objects,
    }


def OOLib(subdir: str, objects: List[Object]) -> Dict[str, Any]:
    """OO framework library under pgm/lib/OO/<subdir>/"""
    return {
        "lib": f"OO_{subdir}",
        "mw_version": config.linker_version,
        "cflags": cflags_base,
        "progress_category": "game",
        "objects": objects,
    }


def MWSupport(objects: List[Object]) -> Dict[str, Any]:
    """Metrowerks PS2 runtime support"""
    return {
        "lib": "PS2_Support",
        "mw_version": config.linker_version,
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": objects,
    }


def SCELib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    """Sony PS2 SDK library"""
    return {
        "lib": lib_name,
        "mw_version": config.linker_version,
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": objects,
    }


def SegaLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    """Sega middleware library (nn / nvs / px)"""
    return {
        "lib": lib_name,
        "mw_version": config.linker_version,
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": objects,
    }


def CRILib(objects: List[Object]) -> Dict[str, Any]:
    """CRI middleware library"""
    return {
        "lib": "CRI",
        "mw_version": config.linker_version,
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": objects,
    }

'''

# ── Ordered sections ──────────────────────────────────────────────────────────
# Each entry: (group_key, helper_name, arg_or_None)

SECTION_ORDER = [
    # --- Runtime (must link first) ---
    ("sce_runtime",  "SCELib",    '"PS2_Runtime"'),
    ("mw_support",   "MWSupport", None),
    # --- Game source ---
    ("game_src_root", "GameSrc", '"root"'),
    *[(f"game_src_{d}", "GameSrc", f'"{d}"') for d in [
        "2D", "Advertise", "Camera", "Data", "Debug", "Effect",
        "Game", "Havok", "Misc", "Object", "SaveLoad", "Script",
        "Stage", "System", "Task",
    ]],
    # --- OO framework ---
    *[(f"oo_{d}", "OOLib", f'"{d}"') for d in [
        "CRI", "PS2", "PS2_CRI", "PS2_nn", "core", "nn",
    ]],
    # --- SCE PS2 SDK ---
    *[(f"sce_{lib}", "SCELib", f'"{lib}"') for lib in [
        "libcdvd", "libdma", "libgraph", "libipu", "libkernl",
        "libmc",   "libmpeg", "libmrpc", "libmtap", "libnet",
        "libpad",  "libscf",  "libsdr",
        "libc", "libgcc", "libm",
    ]],
    # --- Sega ---
    *[(f"sega_{lib}", "SegaLib", f'"{lib}"') for lib in ["nn", "nvs", "px"]],
    # --- CRI ---
    ("cri", "CRILib", None),
]


def emit_group(key: str, helper: str, arg) -> str | None:
    files = groups.get(key)
    if not files:
        return None
    obj_lines = "\n".join(f'        Object(NonMatching, "{f}"),' for f in files)
    open_paren = f"{helper}(" + (f"{arg}, [\n" if arg else "[\n")
    return f"    {open_paren}{obj_lines}\n    ]),\n"


# ── Print output ──────────────────────────────────────────────────────────────

print("# fmt: off")
print(HELPERS)
print("# ============================================================")
print("# config.libs")
print("# ============================================================")
print()
print("config.libs = [")

emitted: set[str] = set()

for key, helper, arg in SECTION_ORDER:
    block = emit_group(key, helper, arg)
    if block:
        emitted.add(key)
        print(block, end="")

# Catch-all for anything not covered by SECTION_ORDER
for key in sorted(set(groups) - emitted):
    block = emit_group(key, "SCELib", f'"{key}"')
    if block:
        print(f"    # NOTE: ungrouped — review this section ({key})")
        print(block, end="")

print("]")
print("# fmt: on")
