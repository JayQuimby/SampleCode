def solution(x, y):
    return solutionh(int(x), int(y), 0)

def solutionh(M, F, C):
    if M == 1 and F ==1:
        return str(C)
    elif M == 0 or F == 0 or M == F:
        return "impossible"
    else:
        if M > F:
            if F == 1:
                return str(C+M-F)
            elif M > F*2:
                return solutionh(F, M-int(M/F)*F, C+int(M/F))
            else:
                return solutionh(F, M-F, C+1)
        else:
            return solutionh(F, M, C)


x = input("\nenter x: ")
y = input("enter y: ")
print(solution(x,y))
