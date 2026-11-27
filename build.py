#!/usr/bin/env python3
import os
import shutil

SOURCE = './source'
STAGING = './build/src'
SUPPORTED_EXTS = {'.tex', '.txt', '.cpp'}


def get_name(filename):
    parts = filename.split('_', 1)
    return parts[1] if len(parts) > 1 else parts[0]


def normalize_indent(text):
    """Convert 4-space or leading-tab indentation to 2 spaces without altering
    blank lines or any other whitespace/formatting."""
    lines = text.splitlines(keepends=True)
    space_indents = []
    has_leading_tab = False

    for line in lines:
        if not line.strip():
            continue
        lead_len = len(line) - len(line.lstrip(' \t'))
        lead = line[:lead_len]
        if '\t' in lead:
            has_leading_tab = True
        elif lead:
            space_indents.append(lead_len)

    if has_leading_tab:
        out = []
        for line in lines:
            if not line.strip():
                out.append(line)
                continue
            lead_len = len(line) - len(line.lstrip(' \t'))
            out.append(line[:lead_len].replace('\t', '  ') + line[lead_len:])
        return ''.join(out)

    if space_indents and min(space_indents) >= 4:
        out = []
        for line in lines:
            if not line.strip():
                out.append(line)
                continue
            lead_len = len(line) - len(line.lstrip(' '))
            new_len = (lead_len // 4) * 2 + (lead_len % 4)
            out.append(' ' * new_len + line[lead_len:])
        return ''.join(out)

    return text


def stage_cpp(section, filename):
    src_path = os.path.join(SOURCE, section, filename)
    dst_dir = os.path.join(STAGING, section)
    os.makedirs(dst_dir, exist_ok=True)
    dst_path = os.path.join(dst_dir, filename)

    with open(src_path, 'r', encoding='utf-8', errors='replace', newline='') as f:
        content = f.read()

    converted = normalize_indent(content)
    with open(dst_path, 'w', encoding='utf-8', newline='') as f:
        f.write(converted)

    return f"{STAGING}/{section}/{filename}"


if __name__ == '__main__':
    if os.path.exists(STAGING):
        shutil.rmtree(STAGING)

    sections = sorted(
        entry for entry in os.listdir(SOURCE)
        if not entry.startswith('.') and os.path.isdir(os.path.join(SOURCE, entry))
    )
    for section in sections:
        path = SOURCE + '/' + section
        print("\\section{%s}" % get_name(section))
        files = sorted(
            entry for entry in os.listdir(path)
            if not entry.startswith('.') and os.path.isfile(os.path.join(path, entry))
        )
        for file in files:
            full_path = path + '/' + file
            name, ext = os.path.splitext(file)
            ext_lower = ext.lower()
            if ext_lower not in SUPPORTED_EXTS:
                continue
            print("\\subsection{%s}" % get_name(name))
            if ext_lower == '.tex':
                print("\\input{%s}" % full_path)
            elif ext_lower == '.txt':
                print("\\lstinputlisting{%s}" % full_path)
            elif ext_lower == '.cpp':
                staged_path = stage_cpp(section, file)
                print("\\lstinputlisting[language=c++]{%s}" % staged_path)
