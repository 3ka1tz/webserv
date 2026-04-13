#!/usr/bin/env python3

import os
import sys

print("Content-Type: text/plain")
print()

print("Hello from Python CGI!")
print()

print("Environment variables:")
for key, value in os.environ.items():
    print(f"{key} = {value}")

print("\nPOST body:")
body = sys.stdin.read()
print(body)
