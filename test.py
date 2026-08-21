#!/usr/bin/env python3
import subprocess
import sys
import os
import platform

def test(exe, arg, expected, test_num):
    out = subprocess.run([exe, arg], capture_output=True, text=True)
    ok = out.stdout == expected and out.returncode == 0
    
    print(f"------TEST {test_num} {'OK' if ok else 'FAIL'}------")
    
    if not ok:
        print(f"\nexpected:\n{expected}\n")
        print(f"actual:\n{out.stdout}")
    
    return ok

if __name__ == "__main__":
    if platform.system() == "Windows":
        exe_name = "./build/minijson.exe"
    else:
        exe_name = "./build/minijson"
    
    exe = sys.argv[1] if len(sys.argv) > 1 else exe_name
    
    if not os.path.exists(exe):
        print(f"Error: {exe} not found. Please build first.")
        sys.exit(1)
    
    tests = []
    
    ok = all(test(exe, arg, exp, i+1) for i, (arg, exp) in enumerate(tests))
    sys.exit(0 if ok else 1)
