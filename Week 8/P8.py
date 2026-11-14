import re

s = input("Enter a binary string: ")

pattern = r'^(1|01*0)*$'

if re.fullmatch(pattern, s):
    print("The string has an even number of 0s and matches the pattern.")
else:
    print("The string does not match the pattern.")
