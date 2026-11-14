#!/bin/bash
# Problem 3: Modify file and directory permissions using chmod

touch testfile.txt

# 1. Numeric (Octal) Mode:
# Permissions: r=4, w=2, x=1
# 755 = User: rwx(7), Group: r-x(5), Others: r-x(5)
echo "=== Setting 755 (rwxr-xr-x) ==="
chmod 755 testfile.txt
ls -l testfile.txt

# 644 = User: rw-(6), Group: r--(4), Others: r--(4)
echo "=== Setting 644 (rw-r--r--) ==="
chmod 644 testfile.txt
ls -l testfile.txt

# 2. Symbolic Mode:
# u=user, g=group, o=others, a=all; +=add, -=remove, ==exact
# Add execute permission for owner, remove write for group, remove read for others
echo "=== Symbolic mode: u+x, g-w, o-r ==="
chmod u+x,g-w,o-r testfile.txt
ls -l testfile.txt

# Cleanup temporary file
rm -f testfile.txt
