#----------------------------------------------------------------------------------------------------------------------------------
'''
Table of Contents
1. Implement flatten operation to convert multidimensional numpy array to single dimension
'''
#---------------------------------
'''
'''
#----------------------------------------------------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------------------------------------------------
# 1 Implement flatten operation to convert multidimensional numpy array to single dimension
# Time Complexity, T(n) = O(n1*n2*...*nm) , ni = number of elements in dimension i 
# Space Complexity, S(n) = O(n1*n2*...*nm)
#---------------------------------
# TestCases:
# Input: [[[1,2,3],[4,5,6]]] => Shape = (1, 2, 3)
# Output: [1,2,3,4,5,6] => Shape = (6)
#---------------------------------
'''
import numpy as np

# Generate permutation code copied from backtracking.py
def generatePermutationWithSlice(arr):
    result = list()
    currTuple = tuple() # need to use tuple to index into numpy arrays
    generatePermutationWithSliceHelper(arr, result, currTuple)
    return result

def generatePermutationWithSliceHelper(arr, result, currTuple):
    if arr.size == 0:
        result.append(currTuple)
        return
    for nextInt in range(arr[0]):
        generatePermutationWithSliceHelper(arr[1:], result, currTuple + (nextInt,))

def flatten(multiArr):
    arr = np.zeros(multiArr.size)
    allMultiIndices = generatePermutationWithSlice(np.array(multiArr.shape))
    for multiDimIndex in allMultiIndices:
        singleDimIndex = multiIndexToSingleIndex(multiArr.shape, multiDimIndex)
        arr[singleDimIndex] = multiArr[multiDimIndex]
    return arr

def multiIndexToSingleIndex(multiArrShape, multiDimIndex):
    singleIndex = 0
    for i in range(len(multiArrShape)):
        singleIndex = singleIndex * multiArrShape[i] + multiDimIndex[i]
    return singleIndex

if __name__ == '__main__':
    multiArr = np.array([[[1,2,3],[4,5,6]]])
    print("Input Multi Array:\n", multiArr)
    print("Input Multi Array Shape:\n", multiArr.shape)
    arr = flatten(multiArr)
    print("Output Single Array:\n", arr)
    print("Output Single Array Shape:\n", arr.shape)
# '''
