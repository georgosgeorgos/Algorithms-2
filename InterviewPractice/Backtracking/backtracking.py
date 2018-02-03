#----------------------------------------------------------------------------------------------------------------------------------
'''
Table of Contents
1. Generate Indices for Arbitrary Dimension Numpy Array
'''
#---------------------------------
'''
Implementing Variable Elimination (Recursively restrict, recursively marginalize, recursively product)
is an awesome exercise for practicing backtracking. Refer to CSC384 Winter 2015 Bayes Net. 

'''
#----------------------------------------------------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------------------------------------------------
# 1 Generate Indices for Arbitrary Dimension Numpy Array
# Time Complexity, T(n) = O(n1*n2*...*nm) , ni = number of elements in dimension i 
# Space Complexity, S(n) = O(n1*n2*...*nm)
#---------------------------------
# TestCases:
# [2,3] => [[0,0], [0,1], [0,2], [1,0], [1,1], [1,2], [2,0], [2,1], [2,2]
#---------------------------------
'''
import numpy as np

def generatePermutationWithDepth(arr):
    result = list()
    currTuple = tuple() # need to use tuple to index into numpy arrays
    result, currTuple = generatePermutationWithDepthHelper(arr, result, currTuple, 0)
    return result

# Python must return multiple values instead of by reference
def generatePermutationWithDepthHelper(arr, result, currTuple, depth):
    if depth == arr.size:
        result.append(currTuple)
        return result, currTuple
    for nextInt in range(arr[depth]):
        # Add next move
        currTuple = currTuple + (nextInt,)
        # Go deeper
        result, currTuple = generatePermutationWithDepthHelper(arr, result, currTuple, depth + 1)
        # Backtrack
        currTuple = currTuple[:-1]
    return result, currTuple

def generatePermutationWithSlice(arr):
    result = list()
    currTuple = tuple() # need to use tuple to index into numpy arrays
    generatePermutationWithSliceHelper(arr, result, currTuple)
    return result

# In python, can get rid of depth parameter by slicing the array
def generatePermutationWithSliceHelper(arr, result, currTuple):
    if arr.size == 0:
        result.append(currTuple)
        return
    # Always use the 0th index of array since slicing
    for nextInt in range(arr[0]):
        # Add next move in function parameter so dont have to remove move after call, since copy by value
        generatePermutationWithSliceHelper(arr[1:], result, currTuple + (nextInt,))

if __name__ == '__main__':
    arr = np.array([2,3])
    print(generatePermutationWithDepth(arr))
    print(generatePermutationWithSlice(arr))
# '''
