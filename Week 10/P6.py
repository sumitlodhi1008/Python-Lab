emp_file = open("employee.txt", "r")
dept_file = open("department.txt", "r")

employees = []
for line in emp_file:
    parts = line.strip().split(",")
    employees.append(parts)
emp_file.close()

departments = {}
for line in dept_file:
    parts = line.strip().split(",")
    departments[parts[0]] = (parts[1], parts[2])
dept_file.close()

out = open("Emp_Dep.txt", "w")
out.write("Ename,Eid,Esalary,EDID,DName,Dlocation\n")

for emp in employees:
    name, eid, salary, did = emp[0], emp[1], emp[2], emp[3]
    if did in departments:
        dname, dloc = departments[did]
        out.write(name + "," + eid + "," + salary + "," + did + "," + dname + "," + dloc + "\n")

out.close()
print("Merged file Emp_Dep.txt created successfully.")
