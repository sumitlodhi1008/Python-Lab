#!/bin/bash
# Problem 1: Display detailed information about files using ls -l and other options

# 1. Long listing format showing permissions, links, owner, group, size, date
echo "=== Long Listing (ls -l) ==="
ls -l

# 2. List all files including hidden files (files starting with dot)
echo "=== All Files Including Hidden (ls -a) ==="
ls -a

# 3. Long listing with human readable file sizes (KB, MB, GB)
echo "=== Human Readable Sizes (ls -lh) ==="
ls -lh

# 4. Sort files by modification time, newest files first
echo "=== Sorted by Modification Time (ls -lt) ==="
ls -lt

# 5. Recursively list directory contents and subdirectories
echo "=== Recursive Directory Listing (ls -lR) ==="
ls -lR
