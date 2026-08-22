#!/usr/bin/env python3
import subprocess
import sys
import os

def build():
    os.makedirs("build", exist_ok=True)
    
    print("Compiling...")
    result = subprocess.run(
        ["g++", "-Iinclude", "-std=c++20", "main.cpp", "-o", "build/minijson"],
        capture_output=True,
        text=True
    )
    
    if result.returncode != 0:
        print("Compilation failed:")
        print(result.stderr)
        return False
    
    print("Compilation successful!")
    return True

if __name__ == "__main__":
    sys.exit(0 if build() else 1)
