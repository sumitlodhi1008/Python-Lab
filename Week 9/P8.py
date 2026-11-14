def dfa_accepts(s):
    state = "q0"
    for ch in s:
        if ch not in ('0', '1'):
            return False
        if state == "q0":
            if ch == '0':
                state = "q1"
            else:
                state = "q0"
        elif state == "q1":
            if ch == '0':
                state = "q1"
            else:
                state = "q2"
        elif state == "q2":
            if ch == '0':
                state = "q1"
            else:
                state = "q0"
    return state == "q2"

s = input("Enter a string over {0,1}: ")
if dfa_accepts(s):
    print("Accepted - string ends with 01")
else:
    print("Rejected - string does not end with 01")
