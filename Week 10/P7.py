def parse(s):
    if len(s) < 2:
        return False
    if s[0] != '0' or s[-1] != '1':
        return False
    if len(s) == 2:
        return s == "01"
    return parse(s[1:-1])

string = input("Enter the string: ")
if parse(string):
    print("The string belongs to the language of the CFG S -> 0S1 | 01")
else:
    print("The string does NOT belong to the language")
