s = input("Enter a string containing alphabets and numbers: ")

L1 = []
L2 = []

for ch in s:
    if ch.isdigit():
        L1.append(ch)
    elif ch.isalpha():
        L2.append(ch)

print("L1 (Numbers):", L1)
print("L2 (Alphabets):", L2)
