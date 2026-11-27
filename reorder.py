#!/usr/bin/env python3
"""Auto-reorder numbered section folders and cheatsheet files in ./source.

Supports:
- Closing gaps after removing items (e.g. 01, 02, 03, 05 -> 01, 02, 03, 04)
- Inserting items in the middle via decimal or letter suffixes
  (e.g. 03a_Foo.cpp or 03.5_Foo.cpp -> placed after 03_, then renumbered)
- Adding unnumbered items at the end (e.g. Foo.cpp -> assigned next number)
"""

import argparse
import os
import re
import sys
import uuid
from pathlib import Path

SUPPORTED_EXTENSIONS = {".cpp", ".tex", ".txt"}
PREFIX_RE = re.compile(r"^(\d+(?:\.\d+)?)([A-Za-z]*)_(.*)$")


def parse_sort_key(name: str):
    """Return (sort_key, clean_title) for a folder name or file stem."""
    match = PREFIX_RE.match(name)
    if match:
        num = float(match.group(1))
        suffix = match.group(2).lower()
        title = match.group(3)
        return (0, num, suffix, title.lower()), title
    return (1, float("inf"), "", name.lower()), name


def plan_renames(entries, is_file: bool):
    """Compute list of (old_path, new_path) pairs needed to normalize numbering."""
    parsed = []
    for path in entries:
        if is_file:
            stem = path.stem
            ext = path.suffix
        else:
            stem = path.name
            ext = ""
        sort_key, title = parse_sort_key(stem)
        parsed.append((sort_key, path, title, ext))

    parsed.sort(key=lambda item: item[0])

    width = max(2, len(str(len(parsed)))) if parsed else 2
    renames = []
    for idx, (_, old_path, title, ext) in enumerate(parsed, start=1):
        new_name = f"{idx:0{width}d}_{title}{ext}"
        new_path = old_path.with_name(new_name)
        if old_path.name != new_name:
            renames.append((old_path, new_path))
    return renames, parsed


def apply_renames(renames, dry_run: bool, label: str) -> int:
    """Apply two-phase safe renames to prevent filename collisions."""
    if not renames:
        return 0

    if dry_run:
        print(f"[DRY-RUN] {label}:")
        for old_path, new_path in renames:
            print(f"  {old_path.name} -> {new_path.name}")
        return len(renames)

    temp_pairs = []
    token = uuid.uuid4().hex[:8]
    for idx, (old_path, new_path) in enumerate(renames):
        tmp_path = old_path.with_name(f"__reorder_tmp_{token}_{idx}_{old_path.name}")
        os.rename(old_path, tmp_path)
        temp_pairs.append((tmp_path, new_path, old_path.name))

    for tmp_path, new_path, old_name in temp_pairs:
        os.rename(tmp_path, new_path)
        print(f"[REORDER] {label}: {old_name} -> {new_path.name}")

    return len(renames)


def reorder_source(source_dir: Path, dry_run: bool = False) -> int:
    if not source_dir.is_dir():
        print(f"Error: source directory not found: {source_dir}", file=sys.stderr)
        return -1

    total_changes = 0

    # 1. Reorder section directories inside source/
    section_dirs = [
        p for p in source_dir.iterdir()
        if p.is_dir() and not p.name.startswith(".")
    ]
    section_renames, sorted_sections = plan_renames(section_dirs, is_file=False)
    total_changes += apply_renames(section_renames, dry_run, "source")

    # Map old section path -> current path on disk (unchanged if dry_run)
    rename_map = {old: new for old, new in section_renames}

    # 2. Reorder cheatsheet files inside each section directory
    for _, orig_section_path, _, _ in sorted_sections:
        target_section_path = rename_map.get(orig_section_path, orig_section_path)
        disk_section_path = orig_section_path if dry_run else target_section_path

        files = [
            p for p in disk_section_path.iterdir()
            if p.is_file()
            and not p.name.startswith(".")
            and p.suffix.lower() in SUPPORTED_EXTENSIONS
        ]
        file_renames, _ = plan_renames(files, is_file=True)
        total_changes += apply_renames(
            file_renames, dry_run, f"source/{target_section_path.name}"
        )

    if total_changes == 0:
        print("[REORDER] Already in order. No changes needed.")
    elif dry_run:
        print(f"\n[DRY-RUN] {total_changes} rename(s) planned. No files were modified.")
    else:
        print(f"[REORDER] Completed {total_changes} rename(s).")

    return total_changes


def main():
    parser = argparse.ArgumentParser(
        description="Auto-reorder numbered folders and files in ./source."
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Preview planned renames without modifying any files.",
    )
    parser.add_argument(
        "--source",
        type=Path,
        default=Path(__file__).resolve().parent / "source",
        help="Path to the source directory (default: ./source).",
    )
    args = parser.parse_args()

    result = reorder_source(args.source, dry_run=args.dry_run)
    if result < 0:
        sys.exit(1)


if __name__ == "__main__":
    main()
