fname = input("Enter filename: ")
f = open(fname, "r")
text = f.read()
f.close()

freq = {}
for ch in text:
    if ch.isalpha():
        ch = ch.lower()
        if ch in freq:
            freq[ch] += 1
        else:
            freq[ch] = 1

max_count = max(freq.values())
print("Maximum frequency:", max_count)
print("Alphabet(s) with maximum instances:")
for letter, count in freq.items():
    if count == max_count:
        print(letter, "-", count, "times")
