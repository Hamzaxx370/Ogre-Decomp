#!/usr/bin/env python3

###
# Converts Splat-generated GNU ld linker scripts to MWLD LCF format.
# Adapted for Sonic Riders: Zero Gravity PS2 decompilation.
###

import os
import argparse
from pathlib import Path


def get_linker_file_lines(splat_linker_file_lines):
    """Parse Splat generated .ld linker file and grab lines to convert"""
    text_o_lines = []
    data_o_lines = []
    sdata_o_lines = []
    bss_o_lines = []
    sbss_o_lines = []
    rodata_o_lines = []

    for line in splat_linker_file_lines:
        # Skip .bin and other non-assembly/non-code files
        if ".s.o" not in line and ".c.o" not in line and ".cpp.o" not in line:
            continue

        # Include only the .o lines and organize them by section type
        if "(.text);" in line:
            text_o_lines.append(line)
            continue
        if "(.rodata);" in line:
            rodata_o_lines.append(line)
            continue
        if "(.data);" in line:
            data_o_lines.append(line)
            continue
        if "(.sdata);" in line:
            sdata_o_lines.append(line)
            continue
        if "(.bss);" in line:
            bss_o_lines.append(line)
            continue
        if "(.sbss);" in line:
            sbss_o_lines.append(line)
            continue
    
    return text_o_lines, data_o_lines, sdata_o_lines, bss_o_lines, sbss_o_lines, rodata_o_lines


def convert_ld_text_to_lcf(text_o_lines):
    lcf_text_lines = []
    ld_text_pattern = "(.text);"
    for line in text_o_lines:
        if ld_text_pattern not in line:
            raise Exception(f"ERROR: Unexpected line in ld linker text: {line}")
        lcf_text_lines.append(line.replace(ld_text_pattern, " (.text)"))
    return lcf_text_lines


def convert_ld_data_to_lcf(data_o_lines):
    lcf_data_lines = []
    ld_data_pattern = "(.data);"
    for line in data_o_lines:
        if ld_data_pattern not in line:
            raise Exception(f"ERROR: Unexpected line in ld linker data: {line}")
        lcf_data_lines.append(line.replace(ld_data_pattern, " (.data)"))
    return lcf_data_lines


def convert_ld_sdata_to_lcf(sdata_o_lines):
    lcf_sdata_lines = []
    ld_sdata_pattern = "(.sdata);"
    for line in sdata_o_lines:
        if ld_sdata_pattern not in line:
            raise Exception(f"ERROR: Unexpected line in ld linker sdata: {line}")
        lcf_sdata_lines.append(line.replace(ld_sdata_pattern, " (.sdata)"))
    return lcf_sdata_lines


def convert_ld_rodata_to_lcf(rodata_o_lines):
    lcf_rodata_lines = []
    ld_rodata_pattern = "(.rodata);"
    for i, line in enumerate(rodata_o_lines):
        if ld_rodata_pattern not in line:
            raise Exception(f"ERROR: Unexpected line in ld linker rodata: {line}")
        # Add alignment before each rodata entry
        alignall_indentation = "" if i == 0 else "\t\t"
        lcf_rodata_lines.append(f"{alignall_indentation}ALIGNALL(0x8);\n") # TODO: Figure out how to calculate each time, setting to 8 as a default for now
        lcf_rodata_lines.append(line.replace(ld_rodata_pattern, " (.rodata)"))
    return lcf_rodata_lines


def convert_ld_bss_to_lcf(bss_o_lines):
    lcf_bss_lines = []
    ld_bss_pattern = "(.bss);"
    for line in bss_o_lines:
        if ld_bss_pattern not in line:
            raise Exception(f"ERROR: Unexpected line in ld linker bss: {line}")
        lcf_bss_lines.append(line.replace(ld_bss_pattern, " (.bss)"))
    return lcf_bss_lines


def convert_ld_sbss_to_lcf(sbss_o_lines):
    lcf_sbss_lines = []
    ld_sbss_pattern = "(.sbss);"
    for line in sbss_o_lines:
        if ld_sbss_pattern not in line:
            raise Exception(f"ERROR: Unexpected line in ld linker sbss: {line}")
        lcf_sbss_lines.append(line.replace(ld_sbss_pattern, " (.sbss)"))
    return lcf_sbss_lines


def lcf_files_to_string(lcf_files) -> str:
    lcf_string = ""
    for i, lcf_file_line in enumerate(lcf_files):
        # Fix the first line having double indentation
        spacing_corrected_line = (
            lcf_file_line.replace("        ", "") if i == 0 else lcf_file_line
        )
        lcf_string += spacing_corrected_line
    return lcf_string


def main():
    parser = argparse.ArgumentParser(description="Convert Splat .ld to MWLD .lcf linker script.")
    parser.add_argument(
        "--splat-ld",
        type=Path,
        required=True,
        help="Path to Splat-generated .ld linker file",
    )
    parser.add_argument(
        "--template",
        type=Path,
        required=True,
        help="Path to LCF template file",
    )
    parser.add_argument(
        "--output",
        type=Path,
        required=True,
        help="Output path for generated .lcf file",
    )
    parser.add_argument(
        "--build-dir",
        type=Path,
        default=Path("build"),
        help="Build directory path (for path adjustments)",
    )
    args = parser.parse_args()

    print(f"Converting {args.splat_ld} to {args.output}")
    print(f"Using template: {args.template}")

    # Read splat linker file
    with open(args.splat_ld, "r") as splat_linker_file:
        splat_linker_file_lines = splat_linker_file.readlines()

        # Convert file paths to relative paths (trim extended paths)
        # Adjust these based on your actual directory structure
        splat_linker_file_lines = [
            line.replace("asm/", "") for line in splat_linker_file_lines
        ]
        splat_linker_file_lines = [
            line.replace("src/", "") for line in splat_linker_file_lines
        ]
        splat_linker_file_lines = [
            line.replace(f"{args.build_dir}/", "") for line in splat_linker_file_lines
        ]

        # Remove folder structure from linker files entirely (flatten to basename)
        splat_linker_file_lines = [
            f"\t\t{os.path.basename(line)}" for line in splat_linker_file_lines
        ]

        # Filter out crt0 segments as they're handled in template
        splat_linker_file_lines = [
            line for line in splat_linker_file_lines if "crt0" not in line
        ]

        # Parse and convert sections
        (
            text_o_lines,
            data_o_lines,
            sdata_o_lines,
            bss_o_lines,
            sbss_o_lines,
            rodata_o_lines,
        ) = get_linker_file_lines(splat_linker_file_lines)

        lcf_text_lines = convert_ld_text_to_lcf(text_o_lines)
        lcf_data_lines = convert_ld_data_to_lcf(data_o_lines)
        lcf_sdata_lines = convert_ld_sdata_to_lcf(sdata_o_lines)
        lcf_bss_lines = convert_ld_bss_to_lcf(bss_o_lines)
        lcf_sbss_lines = convert_ld_sbss_to_lcf(sbss_o_lines)
        lcf_rodata_lines = convert_ld_rodata_to_lcf(rodata_o_lines)

        # Filter bss lines (keep only .bss. entries)
        lcf_bss_lines = [line for line in lcf_bss_lines if ".bss." in line]

        # Convert to strings
        lcf_text_files_string = lcf_files_to_string(lcf_text_lines)
        lcf_data_files_string = lcf_files_to_string(lcf_data_lines)
        lcf_rodata_files_string = lcf_files_to_string(lcf_rodata_lines)
        lcf_sdata_files_string = lcf_files_to_string(lcf_sdata_lines)
        lcf_bss_files_string = lcf_files_to_string(lcf_bss_lines)
        lcf_sbss_files_string = lcf_files_to_string(lcf_sbss_lines)

        # Read template and replace placeholders
        with open(args.template, "r") as template_linker_file:
            template_lines = template_linker_file.readlines()

            updated_lines = [
                line.replace("#<REPLACE_W_TEXT_FILES>", lcf_text_files_string)
                for line in template_lines
            ]
            updated_lines = [
                line.replace("#<REPLACE_W_DATA_FILES>", lcf_data_files_string)
                for line in updated_lines
            ]
            updated_lines = [
                line.replace("#<REPLACE_W_RODATA_FILES>", lcf_rodata_files_string)
                for line in updated_lines
            ]
            updated_lines = [
                line.replace("#<REPLACE_W_SDATA_FILES>", lcf_sdata_files_string)
                for line in updated_lines
            ]
            updated_lines = [
                line.replace("#<REPLACE_W_BSS_FILES>", lcf_bss_files_string)
                for line in updated_lines
            ]
            updated_lines = [
                line.replace("#<REPLACE_W_SBSS_FILES>", lcf_sbss_files_string)
                for line in updated_lines
            ]

            # Write output LCF file
            args.output.parent.mkdir(parents=True, exist_ok=True)
            with open(args.output, "w") as output_linker_file:
                output_linker_file.writelines(updated_lines)

    print(f"Successfully generated {args.output}")


if __name__ == "__main__":
    main()