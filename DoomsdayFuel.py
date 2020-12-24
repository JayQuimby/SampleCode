'''
this is a code representation of an absorbing markov chain
the implementation takes advantage of the standard form that absorbing markov chains have
_         _
|  R |  Q |   I - Identity matrix, but its just zeros for this implementation
|____|____|   0 - zero matrix 
|    |    |   Q - repeat cycle probabilities
|  I |  0 |   R - terminal state probabilities
-         -

by utilizing this form we can get the probabilities by calculating F = (I - Q)^-1
and then use that for FxR to get the probabilities of going from one place and ending at another
we then just take the first row since it is the S0 block and all the ore starts in that form.
'''
from __future__ import division
import fractions
import numpy as np
from __builtin__ import True, False


def solution(m):
    m = np.matrix(m)
    if len(m) <= 2:
        return [1,1]
    else:
        sort(m)
        print m
        r = R(m)
        print("r:"+ str(r))
        f = F(m)
        print("f"+str(f))
        result = f*r
        print("res"+str(result))
        result = final(result, len(m) - numUnstable(m))
        return result
    
def sort(m):
    stables = stableOre(m)
    index = 0
    for x in range(len(stables)):
        if stables[x] == False:
            m = swapr(m, x, index)
            m = swapc(m, x, index)
            index += 1
    return m

def swapr(m, a, b):
    tmp = m[a]
    m[a] = m[b]
    m[b] = tmp
    return m

def swapc(m, a, b):
        m[:, [a,b]] = m[:,[b,a]]
        return m
             

def stableOre(m):
    tst = [0] * len(m)
    stable = []
    for row in range(len(m)):
        if (m[row] == tst).all(1):
            stable.append(True)
        else:
            stable.append(False)
    return stable

def numUnstable(m):
    a = stableOre(m)
    ct = 0
    for x in range(len(a)):
        if a[x] == False:
            ct += 1
    return ct

def I(m):
    ident = []
    for row in range(len(m)):
        ident.append([0 for col in range(len(m))])
        ident[row][row] = 1
    return ident
    
def R(m):
    n = numUnstable(m)
    l = len(m)
    q = l - n
    result = np.matrix([[0]*q]*n)
    denom = 1
    for row in range(n):
        denom = sum(m[row])
        for col in range(q):
            
            result.itemset((row, col), m[row, col] / denom)
    return result
    
def Q(m):
    n = numUnstable(m)
    l = len(m)
    q = l - n
    result = [[0 for x in range(n)] for y in range(n)]
    denom = 1
    for row in range(n):
        denom = sum(m[row])
        for col in range(q,l):
            result[row][col - q] = m[row][col] / denom
    return result
    
def F(m):
    result = np.matrix(Q(m))
    id = np.matrix(I(result))
    result = id - result
    return result.I

def final(m, s):
    result = []
    for i in range(s):
        result.append(fractions.Fraction(str(m[0, i])).limit_denominator())
    return result


        

example1 = [[1,1,1,0,3],
            [1,6,3,2,0],
            [0,0,0,0,0],
            [0,0,0,0,0],
            [0,0,0,0,0]]

example2 = [[1,1,1,0,3],
            [1,6,3,2,0],
            [1,1,1,1,1],
            [0,0,0,0,0],
            [0,0,0,0,0]]

example3 = [[1,1,1,0,3],
            [1,6,3,2,0],
            [1,1,1,1,1],
            [1,1,1,1,1],
            [0,0,0,0,0]]

example4 = [[0,0,0,0,0],
            [1,6,3,2,0],
            [0,0,0,0,0],
            [1,1,1,1,1],
            [0,0,0,0,0]]

example5 = [[0,2,1,0,0], 
            [0,0,0,3,4], 
            [0,0,0,0,0], 
            [0,0,0,0,0], 
            [0,0,0,0,0]]

#print(stableOre(example1))
#print(numUnstable(example1))
#print(np.matrix(example1))
#print(Q(example3))
#print(Q(example2))
#print(Q(example1))

print(solution(example5))






