n = int(input("Enter how many distinct integers (must be even): "))

if n % 2 != 0:
    print("Number of elements must be even.")
else:
    lst = []
    print("Enter", n, "distinct integers:")
    for i in range(n):
        while True:
            val = int(input())
            if val not in lst:
                lst.append(val)
                break
            else:
                print("Duplicate! Enter a different integer:")

    lst.sort()

    half = n // 2
    list1 = lst[:half]
    list2 = lst[half:]

    print("Original sorted list:", lst)
    print("First list (smaller elements):", list1)
    print("Second list (larger elements):", list2)
