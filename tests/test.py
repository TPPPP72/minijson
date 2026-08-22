#!/usr/bin/env python3
import subprocess
import sys
import os
import platform
import glob

def test(exe, input_file, expected_file, test_num):
    with open(input_file, 'r', encoding='utf-8') as f:
        arg = f.read().strip()
    
    with open(expected_file, 'r', encoding='utf-8') as f:
        expected = f.read()

    out = subprocess.run([exe, arg], capture_output=True, text=True)
    ok = out.stdout == expected and out.returncode == 0
    
    print(f"------TEST {test_num} {'OK' if ok else 'FAIL'}------")
    
    if not ok:
        print(f"\nexpected:\n{expected}\n")
        print(f"actual:\n{out.stdout}")
    
    return ok

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    project_root = os.path.dirname(script_dir)
    
    if platform.system() == "Windows":
        exe_name = os.path.join(project_root, "build", "minijson.exe")
    else:
        exe_name = os.path.join(project_root, "build", "minijson")
    
    exe = sys.argv[1] if len(sys.argv) > 1 else exe_name

    if not os.path.exists(exe):
        print(f"Error: {exe} not found. Please build first.")
        sys.exit(1)

    os.chdir(script_dir)
    
    test_files = []
    input_files = sorted(glob.glob("input*.txt"))

    for input_file in input_files:
        num = ''.join(filter(str.isdigit, input_file))
        expected_file = f"expected{num}.txt"

        if os.path.exists(expected_file):
            test_files.append((input_file, expected_file))
    
    if not test_files:
        print("Error: No test files found in test directory")
        sys.exit(1)
    
    print(f"Found {len(test_files)} test(s)")
    ok = all(test(exe, inp, exp, i+1) for i, (inp, exp) in enumerate(test_files))
    sys.exit(0 if ok else 1)
