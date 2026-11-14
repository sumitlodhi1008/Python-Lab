fname = input("Enter filename: ")
f = open(fname, "r")
lines = f.readlines()
f.close()

print("Name\t\tId\tSalary\tDname\t\tHRA")
print("-" * 60)

output_lines = []
for line in lines:
    line = line.strip()
    if line == "":
        continue
    parts = line.split(",")
    name = parts[0].strip()
    emp_id = parts[1].strip()
    salary = float(parts[2].strip())
    dname = parts[3].strip()
    hra = salary * 0.18
    output_lines.append(name + "," + emp_id + "," + str(salary) + "," + dname + "," + str(round(hra, 2)))
    print(name + "\t\t" + emp_id + "\t" + str(salary) + "\t" + dname + "\t\t" + str(round(hra, 2)))

out_fname = input("Enter output filename: ")
f = open(out_fname, "w")
for ol in output_lines:
    f.write(ol + "\n")
f.close()
print("Output written to", out_fname)
