"""
delink_helper.py
Assembles a single combined .s file per TU into a relocatable .o.
The .s file contains explicit .section directives for .text/.data/.rodata etc.
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

ROOT    = Path(__file__).resolve().parent.parent
CONFIG  = ROOT / "objdiff.json"
ASM_DIR = ROOT / "asm"
INC_DIR = ROOT / "include"
OUT_OBJ = ROOT / "build" / "obj"

# ---------------------------------------------------------------------------
# Toolchain
# ---------------------------------------------------------------------------

AS       = "mips-linux-gnu-as"
AS_FLAGS = ["-march=r5900", "-mabi=eabi", "-EL", "-I", to_tool_path(INC_DIR)]

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
    the 'name' field of each unit in config.json.
    e.g. "SRC/Main/StartMain.cpp"  ->  "Main/StartMain"
    """
    with open(CONFIG) as f:
        cfg = json.load(f)
    objects = []
    for unit in cfg.get("units", []):
        name = unit["name"]                       # e.g. "SRC/Main/StartMain.cpp"
        rel  = Path(name).with_suffix("")         # SRC/Main/StartMain
        parts = rel.parts
        if parts[0].upper() == "SRC":
            parts = parts[1:]
        objects.append("/".join(parts))           # "Main/StartMain"
    return objects

# ---------------------------------------------------------------------------
# Build step
# ---------------------------------------------------------------------------

def assemble(obj: str) -> Path | None:
    """Assemble the single combined .s for obj into a .o. Returns output path or None."""
    s_file = ASM_DIR / f"{obj}.s"
    if not s_file.exists():
        print(f"  WARN  {s_file} not found, skipping")
        return None

    out = OUT_OBJ / f"{Path(obj).name}.o"
    out.parent.mkdir(parents=True, exist_ok=True)

    cmd = wsl([AS, *AS_FLAGS, "-o", to_tool_path(out), to_tool_path(s_file)])
    print(f"  AS    {s_file.name} -> {out.name}")

    if not run_cmd(cmd):
        print(f"  ERROR assembling {s_file.name}", file=sys.stderr)
        return None

    return out

# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------

def main():
    OUT_OBJ.mkdir(parents=True, exist_ok=True)

    objects = load_objects()
    if not objects:
        print("No units found in config.json", file=sys.stderr)
        sys.exit(1)

    ok = warn = err = 0

    for obj in objects:
        print(f"\n[{obj}]")
        result = assemble(obj)
        if result is None:
            # distinguish warn (no file) from error (AS failed)
            warn += 1
        else:
            ok += 1

    print(f"\n{ok} objects built, {warn} skipped, {err} failed")
    if err:
        sys.exit(1)

if __name__ == "__main__":
    main()
