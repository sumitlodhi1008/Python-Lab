#!/bin/bash
# Problem 2: Display inode information using ls -i and interpret the results

touch sample.txt

# Display inode number of the file
# An inode is a data structure storing file metadata (permissions, owner, size, timestamps)
echo "=== File inode number using ls -i ==="
ls -i sample.txt

# Detailed listing showing inode number in first column
echo "=== Detailed listing with inode using ls -li ==="
ls -li sample.txt

# Cleanup
rm -f sample.txt
