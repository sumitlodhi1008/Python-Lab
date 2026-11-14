#!/bin/bash
# Problem 2: Change file ownership using chown and group ownership using chgrp

# Create a test file for demonstration
touch testfile.txt
echo "Initial file details:"
ls -l testfile.txt

# chown: Changes the owner of the file to the current user
# Syntax: chown [user] [filename] or chown [user]:[group] [filename]
sudo chown $USER testfile.txt
echo "After changing owner with chown:"
ls -l testfile.txt

# chgrp: Changes only the group ownership of the file
# Syntax: chgrp [group] [filename]
sudo chgrp $(id -gn) testfile.txt
echo "After changing group with chgrp:"
ls -l testfile.txt

# Cleanup temporary file
rm -f testfile.txt
