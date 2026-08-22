#!/usr/bin/env python3
import subprocess
import sys
import os
import platform
import glob

def test(exe, input_file, expected_file, test_num, extra_args=None):
    if extra_args is None:
        extra_args = []

    with open(expected_file, 'r', encoding='utf-8') as f:
        expected_content = f.read()

    cmd = [exe, input_file] + extra_args
    out = subprocess.run(cmd, capture_output=True, text=True)
    
    ok = out.stdout == expected_content and out.returncode == 0
    
    print(f"------TEST {test_num} {'OK' if ok else 'FAIL'}------")
    
    if not ok:
        print(f"\nexpected:\n{expected_content}\n")
        print(f"actual:\n{out.stdout}")
        if out.stderr:
            print(f"stderr:\n{out.stderr}")
    
    return ok

def run_tests_in_dir(exe, test_dir, extra_args=None):
    if extra_args is None:
        extra_args = []
    
    original_cwd = os.getcwd()
    os.chdir(test_dir)
    
    test_files = []
    input_files = sorted(glob.glob("input*.txt"))
    
    for input_file in input_files:
        num = ''.join(filter(str.isdigit, input_file))
        expected_file = f"expected{num}.txt"
        
        if os.path.exists(expected_file):
            test_files.append((input_file, expected_file))
    
    os.chdir(original_cwd)
    
    if not test_files:
        print(f"Error: No test files found in {test_dir}")
        return False
    
    print(f"Found {len(test_files)} test(s) in {os.path.basename(test_dir)}")
    
    ok = all(test(exe, 
                  os.path.join(test_dir, inp), 
                  os.path.join(test_dir, exp), 
                  i+1, 
                  extra_args) 
             for i, (inp, exp) in enumerate(test_files))
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
    
    lexer_dir = os.path.join(script_dir, "lexer")
    if os.path.exists(lexer_dir):
        print("\n=== Running Lexer Tests ===")
        lexer_ok = run_tests_in_dir(exe, lexer_dir, ["--dump-tokens"])
    else:
        print("Warning: lexer directory not found")
        lexer_ok = True
    
    parser_dir = os.path.join(script_dir, "parser")
    if os.path.exists(parser_dir):
        print("\n=== Running Parser Tests ===")
        parser_ok = run_tests_in_dir(exe, parser_dir, ["--dump-ast"])
    else:
        print("Warning: parser directory not found, skipping...")
        parser_ok = True
    
    sys.exit(0 if (lexer_ok and parser_ok) else 1)
