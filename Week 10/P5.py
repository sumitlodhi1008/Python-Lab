filename = input("Enter the filename: ")

f = open(filename, "r")
text = f.read()
f.close()

words = text.split()
freq = {}
for w in words:
    if w in freq:
        freq[w] += 1
    else:
        freq[w] = 1

max_count = max(freq.values())
max_words = [w for w in freq if freq[w] == max_count]

print("Word(s) with maximum occurrences:", max_words)
print("Frequency:", max_count)

for word in max_words:
    text = text.replace(word, "Aligarh")

f = open(filename, "w")
f.write(text)
f.close()

print("Replaced all occurrences. Updated file saved.")
