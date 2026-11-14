#!/bin/bash
# Problem 4: Demonstrate how to set and remove directory permissions

mkdir -p testdir
touch testdir/sample.txt

# 1. Removing execute (x) permission on directory prevents entering (cd)
echo "Removing execute permission on directory:"
chmod -x testdir
cd testdir 2>&1 || echo "Cannot enter testdir: Permission denied"

# 2. Removing write (w) permission prevents creating or deleting files inside
echo "Restoring execute, removing write permission:"
chmod +x testdir
chmod -w testdir
touch testdir/newfile.txt 2>&1 || echo "Cannot create file inside testdir: Permission denied"

# 3. Removing read (r) permission prevents listing directory contents
echo "Removing read permission:"
chmod -r testdir
ls testdir 2>&1 || echo "Cannot list testdir: Permission denied"

# 4. Restoring standard directory permissions (rwxr-xr-x)
chmod 755 testdir
echo "Permissions restored successfully."

# Cleanup test directory
rm -rf testdir
