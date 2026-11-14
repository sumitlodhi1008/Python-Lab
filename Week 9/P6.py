fname = input("Enter filename: ")
f = open(fname, "r")
lines = f.readlines()
f.close()

course_count = {}
for line in lines:
    line = line.strip()
    if line == "":
        continue
    parts = line.split(",")
    program = parts[0].strip()
    if program in course_count:
        course_count[program] += 1
    else:
        course_count[program] = 1

print("Program-wise course count:")
for program, count in course_count.items():
    print(program, "-", str(count).zfill(2))
