"""
compile_mwcc.py
Compiles SRC/**/*.cpp with mwccps2 into build/match/*.o.
Object list is driven by config.json so it stays in sync with delink_helper.py.

Called by dtk objdiff as the custom_make target, and also usable standalone.
"""

import json
import os
import subprocess
import sys
from pathlib import Path

# ---------------------------------------------------------------------------
# Paths
# ---------------------------------------------------------------------------

ROOT    = Path(__file__).resolve().parent.parent
CONFIG  = ROOT / "objdiff.json"
SRC_DIR = ROOT / "src"
OUT_DIR = ROOT / "build" / "match"

# ---------------------------------------------------------------------------
# Compiler — resolve from env var first, then fall back to config.json,
# then fall back to the hardcoded default.
# Set MWCC_PS2 in your environment (or .env) to override.
# ---------------------------------------------------------------------------

_MWCC_DEFAULT = r"D:\Decomp\Compilers\PS2\mwcps2-3.0.1b145-050209\mwccps2.exe"
MWCC = os.environ.get("MWCC_PS2", _MWCC_DEFAULT)

MWCC_FLAGS = [
    "-lang=c++",
    "-O4,p",
    "-str",  "readonly",
    "-enum", "min",
    "-RTTI", "off",
    "-sym",  "on",
    "-Cpp_exceptions", "off",
    "-D__GNUC__",
    "-I-",
    f"-I{ROOT / 'include' / 'mw'  / 'headers'}",
    f"-IC:/usr/local/sce/common/include",
    f"-IC:/usr/local/sce/ee/include",
    f"-IC:/usr/local/sce/ee/gcc/lib/gcc-lib/ee/2.95.3/include",
    f"-IC:/usr/local/sce/ee/gcc/ee/include",
    f"-I{SRC_DIR / 'Ogre' / 'SRC'}",
    #f"-I{SRC_DIR}",
]

# ---------------------------------------------------------------------------
# Object list from config.json
# ---------------------------------------------------------------------------

def load_units() -> list[dict]:
    """
    Returns units from config.json that have a 'base_path' (i.e. need compiling).
    Each unit: { name, base_path, target_path }
    """
    with open(CONFIG) as f:
        cfg = json.load(f)
    return cfg.get("units", [])

# ---------------------------------------------------------------------------
# Compile
# ---------------------------------------------------------------------------

def check_compiler() -> bool:
    if not Path(MWCC).exists():
        print(
            f"\n  ERROR  Compiler not found: {MWCC}\n"
            f"         Set the MWCC_PS2 environment variable to your mwccps2.exe path.\n"
            f"         Example (PowerShell):\n"
            f"           $env:MWCC_PS2 = 'C:\\path\\to\\mwccps2.exe'\n",
            file=sys.stderr,
        )
        return False
    return True

def compile_unit(unit: dict) -> bool:
    """Compile one unit. Returns True on success or skip, False on error."""
    # 'name' is e.g. "SRC/Main/StartMain.cpp"
    src_rel  = Path(unit["name"])
    src_file = ROOT / src_rel
    out_file = ROOT / unit["base_path"]

    if not src_file.exists():
        print(f"  WARN  {src_rel} not found, skipping")
        return True                               # soft skip — don't fail the whole build

    out_file.parent.mkdir(parents=True, exist_ok=True)

    cmd = [MWCC, "-c", *MWCC_FLAGS, "-o", str(out_file), str(src_file)]
    print(f"  MWCC  {src_rel} -> {out_file.relative_to(ROOT)}")

    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        output = (result.stdout + result.stderr).strip()
        print(f"  ERROR {src_rel}:\n{output}", file=sys.stderr)
        return False

    return True

# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------

def main():
    if not check_compiler():
        sys.exit(1)

    OUT_DIR.mkdir(parents=True, exist_ok=True)

    units = load_units()
    if not units:
        print("No units found in config.json", file=sys.stderr)
        sys.exit(1)

    ok = warn = err = 0

    for unit in units:
        print(f"\n[{unit['name']}]")
        result = compile_unit(unit)
        if result:
            ok += 1
        else:
            err += 1

    print(f"\n{ok} compiled, {err} failed")
    if err:
        sys.exit(1)

if __name__ == "__main__":
    main()
