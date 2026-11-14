#!/bin/bash
# Problem 4: Explain the significance of inodes in file management with demonstration

# Demonstration 1: Renaming a file does not change its inode number
# In Linux, file names are just directory entries pointing to an inode.
touch fileA.txt
echo "Original fileA.txt inode:"
ls -i fileA.txt

mv fileA.txt fileB.txt
echo "After renaming to fileB.txt, inode remains identical:"
ls -i fileB.txt

# Demonstration 2: Hard links share the same inode number and link count increments
ln fileB.txt hardlink.txt
echo "Hard link shares the exact same inode number:"
ls -li fileB.txt hardlink.txt

# Cleanup
rm -f fileB.txt hardlink.txt
