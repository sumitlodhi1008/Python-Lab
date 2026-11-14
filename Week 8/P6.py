fname = input("Enter the filename: ")

f = open(fname, "r")
text = f.read()
f.close()

vowels = "aeiouAEIOU"
count = {}

for ch in text:
    if ch in vowels:
        lower = ch.lower()
        if lower in count:
            count[lower] += 1
        else:
            count[lower] = 0 + 1

max_vowel = None
max_count = 0

for v in count:
    if count[v] > max_count:
        max_count = count[v]
        max_vowel = v

if max_vowel:
    print("Vowel with maximum instances:", max_vowel)
    print("Number of instances:", max_count)
else:
    print("No vowels found in the file.")
