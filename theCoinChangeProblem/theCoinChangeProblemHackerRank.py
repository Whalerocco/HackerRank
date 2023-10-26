# https://www.hackerrank.com/challenges/coin-change/problem?isFullScreen=true

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'getWays' function below.
#
# The function is expected to return a LONG_INTEGER.
# The function accepts following parameters:
#  1. INTEGER n
#  2. LONG_INTEGER_ARRAY c
#

def getWays(n, c):
    # GENERALIZED FORMULA
    # a1 < a2 < a3
    # ways(n, [a1, a2, a3]) = ways(n-a3, [a1, a2, a3]) + ways(n-a2, [a1, a2]) + ways(n-a1, [a1])

    # Example: ways(6, [5,3,1]) = ways(1, [5,3,1]) + ways(3, [3,1]) + ways(5, [1]) = 1+2+1 = 4
    # ways(5, [1]) = 1 (all problems with 1 (or 0) coins are either 0 or 1 ways), depends on the modulus 5%1 = 0 -> 1 ways
    # ways(3, [3,1]) = ways(0, [3,1]) + ways(2, [1]) = 1 (base case) + 1 (other base case)
    
    # Example: ways(11, [5,3,1]) = ways(6, [5,3,1]) + ways(8, [3,1]) + ways(10, [1]) 
    # ways(6, [5,3,1]) = 4 (prior example)
    # ways(8, [3,1]) = ways(5, [3,1]) + ways(7, [1])
    # ways(5, [3,1]) = ways(2, [3,1]) + ways(4, [1])
    # ways(2, [3,1]) = ways(-1, [3,1]) + ways(2, [1]) = 0 + 1

    c.sort() # a1, a2, a3 ...
    # print(c)
    # First loop for ways of a1 up to n-a1, save all results in vector 1 coin on the fly - results might be needed by further cases
    # Then loop for ways of [a1, a2] up to n-a2, save all results in vector 2 coin on the fly
    # Then loop for ways of [a1, a2, a3] up to n-a3, save all results in vector 3 coin on the fly
    # Then calculate result with generalized formula

    # totalWays = [[0]*n]*len(c)
    totalWays = [[0 for _ in range(n+1)] for _ in range(len(c))]
 
    # row 0 is ways(n-a1, [a1]) 1 coin
    # row 1 is ways(n-a2, [a1,a2]) 2 coins
    # row 2 is ways(n-a3, [a1,a2,a3]) 3 coins


    # Degenerate case
    if len(c) == 0 or c[0] == 0: 
        if n == 0:
            return 1
        else:
            return 0
    if c[0] > n:
        return 0  
    
    # to calc a new ways, a value with lesser value and 
    # lesser coins used is needed -> for loops can be nested either way
    for value in range(n+1): 
        
        ways = 0
        for i in range(len(c)): # each row represents the nrWays for 1 smallest coin, 2 smallest coins etc..
        
            # which coins are relevant?
            if i == 0: # Base case, if there's only one coin (the smallest)
                if value%c[i] == 0: 
                    ways = 1 
            
            elif value == 0: # Base case, can always give back 0 change in 1 way
                ways = 1

            else: # General case - Calculate the ways based on prior results
                ways = 0
                for j in range(i+1):    
                    if (value-c[j]) >= 0: # Otherwise there are 0 ways to give back the change
                        ways += totalWays[j][value-c[j]] # Example: ways(11, [5,3,1]) = ways(6, [5,3,1]) + ways(8, [3,1]) + ways(10, [1]) 
                    
            totalWays[i][value] = ways

    # print('\n'.join(['\t'.join([str(cell) for cell in row]) for row in totalWays]))

    return totalWays[-1][n]

    



if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    m = int(first_multiple_input[1])

    c = list(map(int, input().rstrip().split()))

    # Print the number of ways of making change for 'n' units using coins having the values given by 'c'

    ways = getWays(n, c)

    fptr.write(str(ways) + '\n')

    fptr.close()
