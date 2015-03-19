//
//----------------------------------------------------------------------------------------
/* //
Table of Contents
1. Maximum Subarray Problem using Kadane's Algorithm

// TODO: Sorted Shifted Array, find the amount array is shifted by
// TODO:  Sorted shifted array, search for an element
// TODO: Find the only singular integer in an array of pairs of integers
// TODO: Array with n distinct elements and local minimums, find one local min in O(logN)
e.g. 10, 6, 4, 3, 12, 19, 18, 20, 17 has 3 local mins at : 3, 18, 17
Easy, just prove that if A[n-1] < A[n] , there must exist local min in A[1] -> A[n-1]
Similarly for A[n-1] < A[n-2] => There must exist local min in A[n-1] -> A[n]
note: Always check for A[n-1] itself being local min as base case cause
 you must always set top or bottom to not include it. If not may end up with infinite
 loop in certain cases. basically must always exclude the middle element that you checked itself
 so that don't end up checking it again in any way.

// TODO: 2. Merge two equally sized integer arrays, the first one   having the capacity to accommodate the result.
            Hint: Merge from end to first so won't overwrite non-merge values

// TODO 3.   Implement a method for a Fibonacci sequence where instead of adding the last 2 elemenT's you add the last n elements. For n=3. 1 1 1 3 5 9...
// */
//----------------------------------------------------------------------------------------
/* //
// 1 Maximum Subarray Problem using Kadane's Algorithm
// Time Complexity = O(n)
// Space Complexity = O(1)
#include <stdlib.h> // for rand()
#include <time.h>
#include <limits.h> // INT_MAX
#include <iostream>
using namespace std;

int maxSubArray(int* a, int N, int &startIndex, int &endIndex);
int maxSubArrayDynamic(int* a, int N);
int main(void)
{
    int N = 10;
    int * a;
    a = (int*) malloc(sizeof(int) * N);
    int i = 0;
    srand (time(NULL));
    for(i = 0; i < N; i++)
    {
        a[i] = rand()%20;
        if((rand()%20) > 10)
        {
            a[i] *= -1;
        }
    }
    for(i = 0; i < N; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    int k,l;
    int maximum = maxSubArray(a, N, k, l);
    int maximum2 = maxSubArrayDynamic(a, N);
    cout<<"Start: "<< k<<" to End: " << l <<" is maximum: "<< maximum << endl;
    cout<<"maximum: "<< maximum2 << endl;
    int b[5] = { -4, -2, -3, -1, -5};
    maximum = maxSubArray(b, 5, k, l);
    maximum2 = maxSubArrayDynamic(b, 5);
    cout<<"Start: "<< k<<" to End: " << l <<" is maximum: "<< maximum << endl;
    cout<<"maximum: "<< maximum2 << endl;
    return 0;
}

int maxSubArray(int* a, int N, int &startIndex, int &endIndex)
{
    startIndex = 0;
    endIndex = 0;
    int currStartIndex = 0;
    int currEndIndex = 0;
    int i = 0;
    int cumulativeSum = -1*INT_MAX;
    int maxSum = cumulativeSum;
    for(i = 0; i < N; i++)
    {
        if(cumulativeSum < 0)
        {
            cumulativeSum = a[i];
            currStartIndex = i;
            currEndIndex = i;
        }
        else
        {
            cumulativeSum += a[i];
            currEndIndex = i;
        }
        if (cumulativeSum >= maxSum)
        {
            maxSum = cumulativeSum;
            startIndex = currStartIndex;
            endIndex = currEndIndex;
        }
    }
    return maxSum;
}

// or another implementation which is easier to understand
// Note: You solved this yourself! Kadane's algorithm is basically a dynamic programming solution that can easily be solved!=) 


// Basically 2 cases: 
// Case 1: There is a positive number in the array
//      Then, you just output your dynamic programming solution
// Case 2: There is no positive number at all in the array
//      Then, you output the minimum value of the array 

// Time Complexity, T(n) = O(n) // one pass only 
// Space Complexity, S(n) = O(1) 
// Note: Haven't accounted for start and end index yet
int maxSubArrayDynamic(int* a, int N)
{
    bool notAllNegative = false; // initialize to all are negative
    int minNegative = a[0]; // initialize minNegative to first element assuming there exist a first element
    int maxSum = a[0]; // initialize maximumSum to be first element
    int currSum = 0; // initialize to 0 for a[-1] 
    for(int i = 0; i <N; i++)
    {
        currSum = max(0, currSum + a[i]);
        if(currSum > maxSum) 
        {
            maxSum = currSum; 
        }
        if(!notAllNegative)
        {
            if(a[i] >= 0)
            {
                notAllNegative = true; // there is a positive value, so don't need to evaluate this anymore 
            }
            else 
            {
                if(minNegative < a[i])
                {
                    minNegative = a[i]; 
                }
            }
        }

    }
    // If special case where all negative numbers
    if(!notAllNegative) return minNegative;
    // Otherwise, return the maximumSum from dynamic programming solution 
    else return maxSum; 
}
// */


