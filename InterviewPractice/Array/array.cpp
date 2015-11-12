//----------------------------------------------------------------------------------------------------------------------------------
/* //
Table of Contents
1. Maximum Contiguous Sum Subarray using Kadane's Algorithm, T(n) = O(n), S(n) = O(1)
2. Rotate Array : Rotate an array of n elements to the right by k units, T(n,k) = O(n), S(n,k) = O(1) 
3. Sorted Shifted Array with only distinct elements, find if a value exist in the sorted shifted array, T(n) = O(logn) = S(n)
4. Given an array of integers, find two numbers such that they add up to a specific target number. T(n) = O(nlogn), S(n) = O(1)
5. Maximum Contiguous Product Subarray, T(n) = O(n), S(n) = O(1)
6. Buy and sell stocks as many times. Max profit?, T(n) = O(n), S(n) = O(1)
7. Buy and sell stock one time. Max Profit? T(n) = O(n), S(n) = O(1)
//-------------------------
TODO:
    (e.g. Product of entire array except itself without using division(/) operator)  Leetcode: O(2n) time and O(1) space (not counting output array)
        Done in LeetCode
    (e.g. Sum of entire array except itself without using deduct (-) operator)  Leetcode: O(2n) time and O(1) space (not counting output array) 
        Done in LeetCode
// Sorted Shifted Array with DUPLICATE elements, find the amount array is shifted by 
// Sorted shifted array with DUPLICATE elements, search for an element
// CIRCULAR ARRAY: 
    HouseRobberIIFromLeetCode: Find the maximum sum of non-adjacent elements in a circular array. 
    e.g. [2,6,5,7,8] = 6+8 = 14 (can't pick both 2 and 8 in the sum as it is circular array and so 2 and 8 will be adjacent)
    Time Complexity, T(n) = O(n) single pass, Space Complexity, S(n) = O(1)
    Hint: Use dynamic programming
// Find the only singular integer in an array of pairs of integers (done in leetcode)
// Array with n distinct elements and local minimums, find one local min in O(logN)
e.g. 10, 6, 4, 3, 12, 19, 18, 20, 17 has 3 local mins at : 3, 18, 17
    Easy, just prove that if A[n-1] < A[n] , there must exist local min in A[1] -> A[n-1]
    Similarly for A[n-1] < A[n-2] => There must exist local min in A[n-1] -> A[n]
    note: Always check for A[n-1] itself being local min as base case cause
     you must always set top or bottom to not include it. If not may end up with infinite
     loop in certain cases. basically must always exclude the middle element that you checked itself
     so that don't end up checking it again in any way.
// ADD Array questions implemented in RandomDecision folder for ECE345 assignments here, where you find intersection of 2 different arrays etc. 
// Given circular array with reference indexing, return if it is a complete circular array.T(n) = O(n), S(n) = O(1) , (Google Practice Interview) note: Use a single pass only
        // hint: Just check if nth element is the starting element. If it is not, then error, if you reach starting element before n, then error
// TODO: 2. Merge two equally sized integer arrays, the first one   having the capacity to accommodate the result.
            Hint: Merge from end to first so won't overwrite non-merge values
// TODO 3.   Implement a method for a Fibonacci sequence where instead of adding the last 2 elemenT's you add the last n elements. For n=3. 1 1 1 3 5 9...
Determine if there is a number in a sorted array that may contain duplicates that is duplicated at least N/4 times. (G Interview) 
//----------------------------------------------------------------------------------------------------------------------------------
// Common Hints
//-------------------------
- Have 2 pointers, one at each end and move towards the middle 
- Sort and use binary search 
- Counting sort and Radix sort 
- Solve for 1, then recursively solve the remainders  
- Have 2 pointers, one at each end, have third pointer moving from one end to another and swapping elements in and out from both end pointers. 
- Partition values to left and right of middle element (quicksort) 
- If a number isn't in the array, and -1 is a valid number, you need to create a new Integer class and return NULL instead. 
- Greatest Common Divisor might be helpful
- First find number of rotation, but do a binary seach, creating a mapping from rotation index to 0->n-1 index
//-------------------------
// Common Questions
//-------------------------
- (-) index? 
- resizable or fixed size? 
- the type the array is holding? 
- circular or straight array? 
- Traverse from left to right, then traverse from right to left. 
    (e.g. Product of entire array except itself without using division(/) operator) 
    (e.g. Sum of entire array except itself without using deduct (-) operator) 
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Maximum Contiguous Sum Subarray using Kadane's Algorithm, T(n) = O(n), S(n) = O(1)
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
//---------------------------------
/*
Questions:
*/
//---------------------------------
/* //
#include <climits> // INT_MAX
#include <vector>
#include <iostream>
using namespace std;

int maxSubArray(vector<int>& arr, int& startIndex, int& endIndex)
{
    startIndex = 0;
    endIndex = 0;
    int currStartIndex = 0; int currEndIndex = 0;
    int cumulativeSum= -1*INT_MAX;  
    int tempSum = 0;
    int n = arr.size(); 
    for(int i = 0; i < arr.size(); i++)
    {
        currStartIndex = tempSum < 0 ? i : currStartIndex;
        tempSum = tempSum < 0 ? arr[i] : tempSum + arr[i];
        if (tempSum > cumulativeSum)  // Mistake: Did if statement at beginning of for loop which is wrong as the last index wasn't checked
        {
            cumulativeSum= tempSum; 
            startIndex = currStartIndex;
            endIndex = i;
        }
    }
    return cumulativeSum;
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
int maxSubArrayDynamic(vector<int>& arr)
{
    int N = arr.size();
    bool notAllNegative = false; // initialize to all are negative
    int minNegative = arr[0]; // initialize minNegative to first element assuming there exist a first element
    int maxSum = arr[0]; // initialize maximumSum to be first element
    int currSum = 0; // initialize to 0 for a[-1] 
    for(int i = 0; i <N; i++)
    {
        currSum = max(0, currSum + arr[i]);
        if(currSum > maxSum) 
        {
            maxSum = currSum; 
        }
        if(!notAllNegative)
        {
            if(arr[i] >= 0)
            {
                notAllNegative = true; // there is a positive value, so don't need to evaluate this anymore 
            }
            else 
            {
                if(minNegative < arr[i])
                {
                    minNegative = arr[i]; 
                }
            }
        }

    }
    // If special case where all negative numbers
    if(!notAllNegative) return minNegative;
    // Otherwise, return the maximumSum from dynamic programming solution 
    else return maxSum; 
}

int main(void)
{
    vector<int> arr = {1, 3, -3, 4, -5, 3};  // Test normal: 5
    int startIndex, endIndex;
    int maximum = maxSubArray(arr, startIndex, endIndex);
    int maximum2 = maxSubArrayDynamic(arr);
    cout<<"Start: "<< startIndex <<" to End: " << endIndex <<" is maximum: "<< maximum << endl;
    cout<<"maximum: "<< maximum2 << endl;
    vector<int> arr2 = { -4, -2, -3, -1, -5}; // Test All Negative: -1
    maximum = maxSubArray(arr2, startIndex, endIndex);
    maximum2 = maxSubArrayDynamic(arr2);
    cout<<"Start: "<< startIndex <<" to End: " << endIndex <<" is maximum: "<< maximum << endl;
    cout<<"maximum: "<< maximum2 << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 2 Rotate Array : Rotate an array of n elements to the right by k units
// Time Complexity, T(n,k) = O(n)
// Space Complexity, S(n,k) = O(1) 
//---------------------------------
/*
Questions: 
    1. What if k is < 0 ? Is allowed and just means go more
    2. What if k is > n ? Is allowed and just means go more 
    3. Rotate left (clockwise) or right (counterclockwise) by k ?
Function Prototype
	void RotateArray(vector<int>& arr, int k); 
Test case: 
	1 2 3 4 , k=2 => 3 4 1 2
	1 2 3 4 5, k = -3 => 4 5 1 2 3
	1 , k=anything => 1
Algorithm: 
    1. Worst case: Shift by O(nk) time, O(1) space, just shift by 1 for all n elements, k times. It doesnt work when n%k = 0, 2*3*4*5 = 120 => if k = 4, 
    2. Put it all in new array. then put back O(2n) time and O(n) space
    3. O(n) => Must shift a constant number of times only 
    Let d = gcd(n,k)
    Juggling Algorithm: Shift by k until find original from start point, move to next point and repeat. Do this d times!  O(n) since only touch each element once 
        arr[(i+k)%n] = arr[i]
Notes:
can’t simply deduct and shift by (k-1) and later shift by (1) as well. cause if
Failed: 1. Shift by (k-1), then shift by 1
    Counter Example n = 2*3*4*5 = 120, k = 4, then shift by k and shift by k-1 will both end up not covering everything. 
Failed: 2.  Shift by k steps till reach original, then move to next element and repeat. Do this for k times
    If n%(k)> 0 => just shift by k till original 
    If n%(k) == 0 => Just shift by k till original, then move next and shift by k till original, and do this (k) times, at each time, you’ll cover n/k . 
    therefore, as a total, you will only cover n times! thus, O(n)
    Counter Example: n = 10, k = 6
    From
    1 2 3 4 5 6 7 8 9 10
    Output will be:
    5 2 7 4 9 6 1 8 3 10 which is wrong!
    Fix by using gcd(n,k) instead of n%(k) 
Implement!
*/
//---------------------------------
/* //
#include <cstdlib> 
#include <vector> 
#include <iostream> 
using namespace std; 

// assumes n >= k
int gcd(int n, int k)
{
    int temp = k; 
    while (n != k)
    {
        temp = k; 
        n -= k;
        k = n; 
        n = temp;
    }
    return n;

}

void rotateCounterClockwise(vector<int>& arr, int k)
{
    bool negative = false;
    if (k < 0) negative = true;
    int n = arr.size();
    if (n <= 1) return;
    int divisor = abs(k)/n;
    if (negative) k += (divisor * n) + n; // add n more to make it rotate right instead of left
    else  k %= n; 
    int d = gcd(n, k);
    for(int i = 0; i < d; i++)
    {
        int prevVal = arr[i]; 
        int currIndex = i ; 
        currIndex = (currIndex + k)%n ; 
        while (currIndex != i) // while not equal to starting point for this iteration
        {
            int temp = arr[currIndex]; // needed for swap
            arr[currIndex] = prevVal;
            prevVal = temp; 
            currIndex = (currIndex + k)%n ; 
        }
        arr[currIndex] = prevVal;
    }
    return; 
}

int main(void)
{   
    vector<int> arr (10, 0); // n1 = 10
    for(int i = 0; i < arr.size(); i++) arr[i] = i+1; 
    vector<int> arr2 (6, 0); // n2 = 6
    for(int i = 0; i < arr2.size(); i++) arr2[i] = i+1; 
    rotateCounterClockwise(arr,6); // k1 = 6
    rotateCounterClockwise(arr2,10); // k2 = 10
    // After rotating n1 = 10 by k1 = 6
    for(int i = 0; i < arr.size(); i++) cout << arr[i] << " ";
    cout << endl;
    // after rotating n2 = 6 by k2 = 10
    for(int i = 0; i < arr2.size(); i++) cout << arr2[i] << " ";
    cout << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 3 Sorted Shifted Array with only distinct elements, find if a value exist in the sorted shifted array, T(n) = O(logn) = S(n)
// Time Complexity, T(n) = O(logn)
// Space Complexity, S(n) = O(logn)
//------------------------
/*
Questions: 
Can duplicates exist?  NO
Can the values be (-)? can the integer be any values? 
what is maximum length of array ?
Does [-1] indexing work on this rotated array? 
What if array is empty?  return -1 
Do i output the minimum value or its index?  // this is for finding shift that has been updated to find minimum as it depends on shift

Function Prototype 

int getPivot(vector<int>& nums); 

TEST_CASE: 
	4567012 => return 4 (indexof 0) 
	1 => return 0 
	1,2=> return 0
	2,1 => return 1
	2,1,3 
	3,3,1,3 => returns 2 (CODE DOESNT WORK FOR THIS CASE!) 

ALGORITHM: 
	Binary search. 
	// base case
	If nums[mid] < nums[mid-1] return mid  
	if (nums[mid] > nums[end])
		begin = mid+1
		end = end 
		Search 
	else 
		begin = begin
		end = mid-1
		search 

Implementation: 
TEST!
*/
//------------------------
/* //
#include <vector> 
#include <iostream> 
using namespace std; 

int binarySearchGetPivot(vector<int>& nums, int begin, int end)
{
    int mid = ((end + begin)/2); 
    // Base cases
    if((mid > begin && nums[mid] < nums[mid-1]) || (mid == begin && nums[mid] <= nums[end]))     
        return mid; 
    // General case 
    if (nums[mid] > nums[end]) 
    {
        begin = mid + 1; 
        return binarySearchGetPivot(nums, begin, end); 
    }
    else
    {
        end = mid - 1; 
        return binarySearchGetPivot(nums, begin, end); 
    }	
} 

int getPivot(vector<int>& nums)
{
    if( nums.size() == 0) return -1; 
    int result = binarySearchGetPivot(nums, 0, nums.size()-1); 
    return result; 
}

int binarySearchSearch(vector<int>& nums, int begin, int end, int target, int pivot)
{
    if (begin > end) return -1; 
    int mid = (begin+end)/2;
    int n = nums.size();  
    if (n <= 0) return -1; 
    while(begin <= end)
    {
        mid = (begin+end)/2; 
        int midFix = (mid+pivot) % n; 
        if(nums[midFix] == target) 
        {
            return midFix; 
        }
        else if (nums[midFix] < target)
        {
            begin = mid+1; 
        }
        else
        {
            end = mid - 1; 
        }
    }
    return -1; 
}

int search(vector<int>& nums, int target) 
{
    int pivot = getPivot(nums); 
    int begin = 0; 
    int end = nums.size() - 1; 
    int result = binarySearchSearch(nums, begin, end, target, pivot); 
    return result; 
}

int main(void)
{
	vector<int> nums = {4,5,6,7,0,1,2}; // C++ 11 compiler required 
	int result = getPivot(nums); 
	cout << result << endl; 
	cout << nums[result] << endl; 
    int target = 6;
    result = search(nums, target); 
    cout << result << endl;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 4 Given an array of integers, find two numbers such that they add up to a specific target number.
// Time Complexity, T(n) = O(nlgn + n) = O(nlgn)
// Space Complexity, S(n) = O(1)
//---------------------------------
/* //
Questions:
1. 	Is the array of integers sorted?  
2. 	Can the numbers be (-) 
3.  	Can array contain repeated elements? 
4. 	Can I modify the array? 
Test Case: 
	-3, -2 -8 7 5
// */
//---------------------------------
/* // 
#include <vector> 
#include <cstdlib> // bool 
#include <algorithm> // sort()
#include <iostream> 
using namespace std; 
bool targetNumber(vector<int>& vec , int sum, int& first, int& second)
{
	sort(vec.begin(), vec.end()); 	
	int i = 0; 
	int j = vec.size()-1; 
	while(i != j)
	{
		if (vec[i] + vec[j] == sum)
		{
			first = vec[i]; 
			second = vec[j]; 
			return true; 
        }
        else if (vec[i] + vec[j] < sum)
        {
            i++; 
        }
        else 
        {
            j--;  
        }
    }
    return false; 
}
int main(void)
{
    vector<int> vec(4, 0);
    vec[0] = -2; 
    vec[1] = -8; 
    vec[2] = 7; 
    vec[3] = 5; 
    int first = 0; 
    int second = 0; 
    if(targetNumber( vec , -3,  first,second))
    {
        cout << "Numbers found are: " << first << " , " << second; 
    }
    else
    {
        cout << "No numbers found" << endl; 
    }
    return 0; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 5 Maximum Contiguous Product Subarray
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
//-------------------------
/*  
Questions: 
    1. Is array filled with integers or doubles? 
    2. Can there be (-) values ? 
    3. Can there be a 0 in the array? 
    4. What to return when it is only 1 element and (-) ? 
    5. What to return if array is empty? 
Function Prototype: 
    int maxProductSubArray(vector<int> arr);
Test_Case:
    [2,3,0,3,4] = 12
    [2,-3,0,3,-2] = 3
    [-3,2,-2,3] = 36
    [-3,-2,-4,5] = 40
    [-3] = -3
    [2] = 2
    [0,-2] = 0
Algorithm: 
    Initialize to 1 
    Everytime see a 0, re-initialize to 1, and restart algorithm, but don't reset maxProduct. Check maxProduct even for case of 0
    Initialize maxProduct to INT_MIN
    Keep track of : 
        1. Max product for current iteration
    At each iteration, calculate:
        i) MaxCurrent * curr 
        ii) MinCurrent * curr
        iii) curr
       Then assign maxCurrent to max of the 3 choices .  
       Then assign minCurrent to min of the 3 choices .  
       Update MaxProduct if possible from maxCurrent
    T(n) = O(n), S(n) = O(1)
    Solved!!=D

*/
//-------------------------
/* //
#include <climits> // INT_MIN
#include <vector> 
#include <iostream> 
using namespace std;
int maxProductSubArray(vector<int> arr)
{
    int n = arr.size();
    if (n <= 0) return 0;
    int maxProduct = INT_MIN;
    int maxCurr = 1; // initialize to 1
    int minCurr = 1; // initialize to 1
    int curr = arr[0]; // 
    for(int i = 0; i < n; i++)
    {
        // Base case to reinitialize
        if(arr[i] == 0)
        {
            if(maxProduct < arr[i]) maxProduct = arr[i]; // to handle case where 0 is the maximum you can get
            maxCurr = 1; 
            minCurr = 1;
            curr = arr[i];
        }
        else
        {
            // Calculate all possible 3 choices
            curr = arr[i]; 
            int a = curr*maxCurr;  
            int b = curr*minCurr; 
            // Get the max of all 3 elements
            maxCurr = max(a,b); 
            maxCurr = max(maxCurr, curr);
            // Get the min of all 3 elements
            minCurr = min(a,b); 
            minCurr = min(minCurr, curr);
            if (maxProduct < maxCurr) maxProduct = maxCurr; 
        }
    }
    return maxProduct;
}

int main(void)
{
    vector<int> arr1 = {2,3,0,3,4}; // 12 , C++ 11 Feature
    int result = maxProductSubArray(arr1);
    cout << result << endl;
    vector<int> arr2 = {2,-3,0,3,-2}; // 3
    result = maxProductSubArray(arr2);
    cout << result << endl;
    vector<int> arr3 = {-3, 2, -2,3}; // 36
    result = maxProductSubArray(arr3);
    cout << result << endl;
    vector<int> arr4 = {-3, -2, -4, 5}; // 40
    result = maxProductSubArray(arr4);
    cout << result << endl;
    vector<int> arr5 = {-3}; // -3
    result = maxProductSubArray(arr5);
    cout << result << endl;
    vector<int> arr6 = {0,-2}; // 0 
    result = maxProductSubArray(arr6);
    cout << result << endl;
    return 0; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 6 Buy and sell stocks as many times. Max profit?
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
//----------------------------------------------------------------------------------------------------------------------------------
/*
Buy and sell stock many times. But only 1 transaction at a time. (buy, and sell before can buy again)
k = 1 
Questions: 
What does 1 transaction at a time mean? 
How do I buy and sell a stock? 
How are the stock data stored? 
Allowed to sell then buy on the same day? 
Yes 
Function Prototype: 
	int maxProfit(int * arr, int n) 
	int maxProfit(vector<int>& arr) 
Test_Cases 
	1 5 -3 2 9 7 5  => 12 + 4 + 0 = 16
	1->5 
	-3->2 
	2->9 
	O(n)  = 9 + 7 = 16
	-1 3 
Algorithm: 
    1.
	For k = 1, one time. 
	Loop through array, keep track of maxDiff. 
	Each time update maxDiff, I update minIndex and maxIndex
    To do many times, 
    Loop through once and solve in O(n) 
    2.
   Max profit? buy and sell stock at most k times. Max profit? (k's base case is 1, k = 1)
    - For many times, just do it recursively. Solve for k = 1, then divide left and right to 2 recursions 
    - For k times, do similarly as many times, but use O(n) space by returning linked list of all the components of many times in sorted order
    - Sorting takes O(n) since it's the merge step in merge sort at each recursion. 
    - Then just pick the first k. 
IMPLEMENT: `	
*/
//---------------------------------
/*
#include <cstdlib> 
#include <vector> 
#include<iostream> 
using namespace std; 

int maxProfit(int * arr, int n) 
{
	if(n <= 1) return 0; 
	unsigned int maxProfit = 0; 
	int curr = arr[0]; // 1
	for(int i = 1; i < n; i++) 
	{
		if (arr[i] > curr) 
		{
			maxProfit += (arr[i] - curr); 
			curr = arr[i]; // buy back on same day 
		}
		else 
		{
			curr = arr[i]; // update smaller value 
		}
	}
	return maxProfit; 
}

int main(void) 
{
	int a[7] = {1, 5, -3, 2, 9, 7, 5};
	int profit = maxProfit(a, 7); 
	cout << profit << endl;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 7 Buy and sell stock one time. Max Profit? 
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
//----------------------------------------------------------------------------------------------------------------------------------
/* // 
#include <cstdlib> 
#include <iostream> 
using namespace std; 
int oneTransactionMaxProfit(int * arr, int n)
{
    if (n <= 0) return 0; 
    int maxDiff = 0; // initialize to don’t buy or sell at all 
    int currMin = arr[0]; 
    for(int i = 1; i < n; i++)
    {
        maxDiff = max(maxDiff, arr[i] - currMin ); 
        currMin = min(currMin , arr[i]); 
    }
    return maxDiff; 
}

int main(void)
{
    int a[10] = {2, 5, 1, 5, 2, 8, 9, 1, 3, 2}; 
    int maxProfit = oneTransactionMaxProfit(a, 10); 
    cout << maxProfit << endl; 
    return 0; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
