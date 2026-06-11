"""
build.py  —  one command to rule them all
Usage:
    py build.py            # split + delink + compile
    py build.py split      # splat split only
    py build.py delink     # assemble .s -> build/obj/*.o only
    py build.py compile    # mwcc compile -> build/match/*.o only
"""

import subprocess
import sys

STEPS = {
    "split":   ["py", "-m", "splat", "split", "configs/elf.yaml"],
    "delink":  ["py", "tools/delink_helper.py"],
    "compile": ["py", "tools/compile_mwcc.py"],
}

def run(name: str, cmd: list[str]) -> bool:
    print(f"\n{'='*60}")
    print(f"  {name.upper()}")
    print(f"{'='*60}")
    result = subprocess.run(cmd)
    if result.returncode != 0:
        print(f"\n  FAILED: {name}", file=sys.stderr)
        return False
    return True

def main():
    args = sys.argv[1:]

    if args:
        # Run only the requested step(s)
        requested = args
    else:
        # Default: full pipeline
        requested = ["split", "delink", "compile"]

    for step in requested:
        if step not in STEPS:
            print(f"Unknown step '{step}'. Valid: {', '.join(STEPS)}", file=sys.stderr)
            sys.exit(1)
        if not run(step, STEPS[step]):
            sys.exit(1)

    print("\n  Done.")

if __name__ == "__main__":
    main()
