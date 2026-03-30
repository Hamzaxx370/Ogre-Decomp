#!/usr/bin/env python3

###
# Patches MWCCPS2 compiler by copying DLLs from GC compiler.
# This is required because PS2 compiler DLLs are incompatible.
#
# Usage:
#   python3 tools/patch_compiler.py <gc_dll_path> <ps2_compiler_path> <marker_file>
###

import sys
import shutil
from pathlib import Path


def main():
    if len(sys.argv) != 4:
        print("Usage: patch_compiler.py <gc_dll_path> <ps2_compiler_path> <marker_file>")
        sys.exit(1)

    gc_dll_path = Path(sys.argv[1])
    ps2_compiler_path = Path(sys.argv[2])
    marker_file = Path(sys.argv[3])

    # Check if GC DLLs exist
    lmgr8c = gc_dll_path / "lmgr8c.dll"
    lmgr326b = gc_dll_path / "lmgr326b.dll"

    if not lmgr8c.exists():
        print(f"Error: {lmgr8c} not found")
        sys.exit(1)
    if not lmgr326b.exists():
        print(f"Error: {lmgr326b} not found")
        sys.exit(1)

    # Create PS2 compiler directory if it doesn't exist
    ps2_compiler_path.mkdir(parents=True, exist_ok=True)

    # Copy DLLs
    print(f"Copying {lmgr8c} to {ps2_compiler_path}")
    shutil.copy(lmgr8c, ps2_compiler_path / "lmgr8c.dll")
    
    print(f"Copying {lmgr326b} to {ps2_compiler_path}")
    shutil.copy(lmgr326b, ps2_compiler_path / "lmgr326b.dll")

    # Create marker file
    marker_file.parent.mkdir(parents=True, exist_ok=True)
    marker_file.touch()
    
    print(f"Successfully patched PS2 compiler at {ps2_compiler_path}")


if __name__ == "__main__":
    main()
