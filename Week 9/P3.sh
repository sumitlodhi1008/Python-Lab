#!/bin/bash
# Problem 3: Create and delete files and directories, and observe changes in inode numbers

# 1. Create first file and observe its allocated inode
touch f1.txt
echo "f1.txt inode:"
ls -i f1.txt

# 2. Create second file; OS assigns a new available inode
touch f2.txt
echo "f2.txt inode:"
ls -i f2.txt

# 3. Delete f1.txt; its inode is released back to the free inode table
echo "Deleting f1.txt..."
rm f1.txt

# 4. Create f3.txt; observe the operating system reuses the freed inode
touch f3.txt
echo "f3.txt inode (notice freed inode reuse):"
ls -i f3.txt

# Cleanup
rm -f f2.txt f3.txt
