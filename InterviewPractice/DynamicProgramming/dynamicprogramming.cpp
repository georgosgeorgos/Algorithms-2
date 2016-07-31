//----------------------------------------------------------------------------------------------------
/*
Table of Contents
1. Fibonacci Sequence (Bottom Up), T(n) = O(n), S(n) = O(n)
2. Rod Cutting: Given a rod of length n, and a price for each length of rod, find ways to cut the rod to have maximum value, T(n) = O(n^2), S(n) = O(n)
3. Maximum Sum Increasing Subsequence, T(n) = O(n^2), S(n) = O(n)
4. Longest Common Subsequence Between Two Strings, T(n,m) = O(nm), S(n,m) = O(nm)
5. Longest Increasing Subsequence, T(n) = O(n^2), S(n) = O(n)
6. Edit Distance, given 2 strings that are different, find min. number of changes to convert 1 to another, T(n,m) = O(nm), S(n,m) = O(nm)
7. Minimum Cost Path from [0][0] to [m-1][n-1] in a matrix, T(n,m) = O(mn), S(n,m) = O(mn)
8. Coin Change: Find # of combinations to make a change for value N given infinite supply of a given CoinType = [C1, C2, ... , Cm], T(n,m) = O(nm), S(n,m) = O(n)
9. Matrix Chain Multiplication: Find most efficient way to multiply a chain of matrices together, T(n) = O(n^3), S(n) = O(n^2) 
10. Knapsack 0-1: Find max value from items with weights >= 0 and values, for weight capacity, W, T(W,n) = O(nW), S(W,n) = O(nW)
11. Egg Dropping: Given n eggs and k floors, find minimum number of attempts to determine level at which egg starts to break, T(n,k) = O(n(k^2)), S(n,k) = O(nk)
12. Longest Palindrome Subsequence, T(n) = O(n^2), S(n) = O(n^2) 
13. Unique Paths: Number of unique paths from [0][0] to [n-1][m-1], only move (down,right) at any time, T(n,m) = O(nm), S(n,m) = O(min(n,m)) 
14. Minimum Number Coin Change: Find min. number of coins from a set of coin values to get a particular value, T(V,n) = O(Vn), S(V,n) = O(V)
//----------------------------------------------------------------------------------------------------
TODO:
15. Palindrome Partitioning (Solved on paper, not implemented yet)
16. SubsetSum Problem: Given an array and a sum, figure out if a subset of the array has value equal to that sum.  (solved on paper, not implemented yet) 
17. Partitioning Problem
    Hint: Subset Sum Problem
25.Longest Common Substring Between Two Strings (Bottom Up)
    Easy! Just go diagonal upwards and no vertical horizontal, since no subsequence, iterate properly and keep track of max, once done iterating will have optimal solution
26. Longest Palindromic Substring 
    Note: Optimal solution is not dynamic programming but try dynamic programming for learning, similar to maxContiguousSumSubArray
    Note: Must pass this case: str = abacdfgdcaba
    There are 4 solutions:  (refer to LeetCode textbook)
    1. Brute Force O(n^3) & O(1)
    2. Dynamic O(n^2) & O(n)
    3. Array  O(n^2) & O(1) (hint: There are only (2n-1) centers and expanding takes O(n)
    4. Manacher Algorithm O(n) & O(n)
TODO MUST DO: Unbounded Knapsack (Easy, just your solution for 0-1 knapsack but with O(n) space cause can add itself many times) 
23. Unique Paths with Obstacles given 
27.Josephus Problem
28. Triangle Problem
    This is really a great problem. Easy enough. Note: In this problem, the direction you traverse have different complexities. 
    One has O(n^2 + n), the other has O(n^2) 
    Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.
    For example, given the following triangle
    [
         [2],
        [3,4],
       [6,5,7],
      [4,1,8,3]
    ]
    Question: 1. what does adjacent mean? It means if you look at the triangle in a diagonal way, it can either go left or right, (NOT array way where its left, right, or middle)
40.Maximum Contiguous Sum Subarray() (using dynamic instead of kadane's algorithm) (noting that dynamic isn't the optimal solution)
//-------------------
notes: 
//-------------------
0. To know when dynamic programming should be tried: 
    - Repeated computation
    - At each level, you can either move:
        1D: to left or right by 1 step.
        2D: To left, or up or diagonal leftUp for 2D array by 1 step.
            curr = (m,n) => Cost/Benefit can be 1 or 0.
            currCost + maxOrMin(subProblem(m-1,n), subProblem(m,n-1), subProblem(m-1,n-1)
                left = (m-1, n)
                up = (m, n-1)
                diagonal leftUp = (m-1, n-1)
    - Can solve sub-problems optimally
1. Remove useless arguments from function, the different combinations of arguments are the states of the function. Repeat Step 1
2. Find out equation and create recursive function.  (Really, what you are doing is trial and error until you find a solution that works from these approaches)
    - Start by figuring out the base cases
    - Identify optimal substructure (Subproblems can be solved optimally as well)
    - When moving from left to right, each step i is the solution for the same problem at i. Then at step(n), that is the solution to the problem n given
    - Note: The optimal substructure may not be the optimal solution to that sub-problem. The optimal substructure may contain restriction such as: 
        - Longest Increasing Subsequence, the optimal Substructure L[i] requires the optimal solution to i to contain item 'i' itself. 
            However, the actual optimal solution will need to be iterated from L[0] to L[i] to find the actual optimal solution as 
            the optimal solution may not contain i
        - Coin Change, optimal substructure must contain coin [i] 
    - Use divide and conquer approach (Top - Down)
    - Start from solving each element individually and combine answers (Down -> Up) , normally saves space of not needing the cache compared to previous (top down)
    - Start cases either from individual to group (bottom up) of tree  OR from left to right (One element to all N elements) and try to form an equation
    - How does including your new individual change the equation? Think in that way. 
    - Find out what base cases are, try out every variable combination. (Knapsack => W, w[i], v[i]) => arr[W] = (v[i], w[i])
    - Dimensions are prolly the values that can only contain positive integers since thats how you build your array. 
        - if (-) integers are allowed, just add everything with the abs(lowest (-) integer) and now all you have is (+) integers
        - if the values aren't (-), you can always build the array by indexing into it. 
    - An NP-Hard problem may have a pseudo-polynomial solution 
3. If subproblems overlap, memoize them: Save results into cache[n][n] (2 arguments, each can span n different values => n^2 different computations only) 
   - To optimize for space: figure out the solution first, then learn to see what you depend on the get the solution. 
     Note: Normally can save more space if depend on a fixed number of previous elements:
     i) If any number of arbitrary previous elements => Prolly can't save space, but need correct iteration for correct computation
     ii) If only 1 or a constant number of previous elements => can use that constant number of space to keep track of previous contant number of elements
        e.g. (Binomial Coefficient only needs previous (-1) row of elements, so constant space (only 1 row needed) O(n)
             On other hand, (Knapsack 0-1) needs anywhere from 0->k previous rows of elements, so need all m rows O(nm)
     Change the order of computation that covers what you depend on with as little space as possible as well as correct computation.
       - Swap the 2 inner and outer for loops and see if that works.  (e.g. Coin Change from S(n,m) = O(nm) to O(n)
       - Make the for loop go from 1->N elements or from N->1 elements
       - there are prolly 2 different iterations depending on what current element depends on in matrix
            - Depends on (top and left) of matrix 
                - Loop from (left to right and diagonaltopLeft) downwards
                - Loop from (up to down) rightwards
            - Depends on (top and right and diagonaltopRight) of matrix  (can easily change to top and left by changing for loop iteration order)
                - Loop from (right to left) downwards
                - Loop from (up to down) leftwards
            - The order of looping can change the space complexity of the algorithm. E.g. (Coin Change)
            - NOTE: This is only true if you always want to get the latest changes, sometimes, you want the older changes instead of latest changes
                    Then, this Loop order doesn't hold.     
                    e.g. Binomial Coefficient Problem (Refer to Mathematics Folder) 
                    Depends on (top and diagonalTopLeft) of matrix
                        Loop from right to left downwards so that you don't (replace older changes if looping from left to right)
   - If your function only depends on the last k results, where k is a constant (doesnt change depending on value of n) 
       Then, you can make temporary variables and swap them as necessary instead of making an entire array to store the results. 
       e.g. if k = 2, instead of doing a[i] = max(a[i-1], a[i-2]) 
       you can do,   currMax = max(prev, prevprev), prevprev = prev, prev = currMax; 
4. The solution is not always O(n^2)!! Sometimes, it can be O(n^3)! Thus, try every possible n within the for loops. 
    - If question asks to find minimum of a worst case, use minimax. Iterate through all possibilities 
    and get the minimum of the worst case. 
    - Ask yourself, what can you control at each iteration? That's picking the best case. Now after you pick something, 
    what is the worst case for picking it? thats the worst case. 
    Thus, you pick the best cases among all the worst cases. 
    e.g. Egg Dropping Problem
Number of subsets from n elements is (2^n), since you can think of it as 1=> in subset, and 0 => Not in subset and so if you have n elements, 
you can binary count from 00000 to 11111 and there's 2^n total number of them
//-------------------
e.g. Pasted from comments at: https://www.quora.com/Are-there-any-good-resources-or-tutorials-for-dynamic-programming-besides-the-TopCoder-tutorial
    Imagine you have a collection of N wines placed next to each other on a shelf. For simplicity, let's number the wines from left to right as they are standing 
    on the shelf with integers from 1 to N, respectively. 
    The price of the i-th wine is pi (prices of different wines can be different).
    Because the wines get better every year, supposing today is the year 1, on year y
    the price of the i-th wine will be y*pi, i.e. y-times the value that current year.You want to sell all the wines you have, but you want to sell exactly one wine per year, starting 
    on this year. One more constraint - on each year you are allowed to sell only either the leftmost or the rightmost wine on the shelf and you are not allowed 
    to reorder the wines.
    (i.e. they must stay in the same order as they are in the beginning).
    If the prices of the wines are: p1=2, p2=3, p3=5, p4=1, p5=4
    The greedy strategy would sell them in the order p1, p2, p5, p4, p3 for a total profit 2*1 + 3*2 + 4*3 + 1*4 + 5*5 = 49
    But we can do better if we sell the wines in the order p1, p5, p4, p2, p3 for a total profit 2*1 + 4*2 + 1*3 + 3*4 + 5*5 = 50
    Up Down: 
        int N; // read-only number of wines in the beginning
        int p[N]; // read-only array of wine prices
        int cache[N][N]; // all values initialized to -1 (or anything you choose)

        int profit(int be, int en) {
          if (be > en)
            return 0;

          // these two lines save the day
          if (cache[be][en] != -1)
            return cache[be][en];

          int year = N - (en-be+1) + 1;
          // when calculating the new answer, don't forget to cache it
          return cache[be][en] = max(
            profit(be+1, en) + year * p[be],
            profit(be, en-1) + year * p[en]);
        }
    Down Up: 
    public int getMaxProfitDP() {
        // initialize such that each sale is maximized
        for (int i = 0; i < N; i++) {
            cache[i][i] = p[i] * N;
        }

        for (int y = 1; y < N; y++) {
            for (int x = 0; x < N - y; x++) {
                int be = x;
                int en = x + y;
                int year = N - (en - be);

                cache[be][en] = max(cache[be + 1][en] + year * p[be],
                                    cache[be][en - 1] + year * p[en]);
            }
        }
        return cache[0][N - 1];
    }
    
Unbounded Knapsack Problem
    Given Knapsack Problem 
    I(0), ... I(n-1), I(0) = (V(0), W(0)) with constraint C = Weight. Calculate maximum value that can be gain. 
    Note: can pick duplicates of I(i) for any i. So like 3I(0) + 2I(i)
    w[i] > 0 for every i
    w[i] = Integer, W = integer
*/
//----------------------------------------------------------------------------------------------------
// 1 Fibonacci Sequence (Bottom Up)
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(n)
//-------------------------------------
/* //
#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;

int fibonacci(int n);
int main(void)
{
    int i = 0;
    int n = 10;
    for (i = 0; i <= n; i++)
    {
        int j = fibonacci(i);
        cout << "Fibonacci for " << i << " is: " << j << endl;
    }
}

int fibonacci(int n)
{
    if (n <= 1)
        return 1;
    vector<int> cache(n+1, 0);
    cache[0] = 1;
    cache[1] = 1;
    for (int i = 2; i <= n; i++)
        cache[i] = cache[i-1] + cache[i-2];
    return cache[n] ;
}
// */
//----------------------------------------------------------------------------------------------------
// 2 Rod Cutting: Given a rod of length n, and a price for each length of rod, find ways to cut the rod to have maximum value
// Time Complexity, T(n) = O(n^2)
// Space Complexity, S(n) = O(n)
//-------------------------------------
/*
Questions
    1. 
*/
//-------------------------------------
/* //
#include <vector> 
#include <iostream> 
using namespace std; 

int RodCutting(vector<int> rodPrices)
{
    int n = rodPrices.size();
    if (n <= 0) return 0;
    vector<int> L (n, 0);
    // Initialize base case for all rod of length 1
    for (int i = 0; i < n; i++)
    {
        L[i] = rodPrices[i];
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j <= i/2; j++)
        {
            L[i] = max(L[i], L[j] + L[i-j-1]);
        }
    }
    return L[n-1];
}

void printSolution(vector<int>& rodPrices) 
{
    int maxValue = RodCutting(rodPrices); 
    cout << maxValue << endl;
}

int main(void)
{
    vector<int> single = {5}; // 5
    vector<int> normal = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 23}; // 25
    printSolution(single);
    printSolution(normal);
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------
// 3 Maximum Sum Increasing Subsequence
// Time Complexity, T(n) = O(n^2)
// Space Complexity, S(n) = O(n)
//-------------------------------------
/* 
Questions:
    1. If I have {1,2,2} is the max sum 5 or 3? does same value count as increasing? yes
    2. Can there be (-) numbers? 
    3. What if all numbers are negative? 
*/
//-------------------------------------
/* //
#include <vector> 
#include <iostream> 
using namespace std;

int MaxSumIncreaseSubsequence(vector<int>& arr)
{
    if (arr.empty()) return 0;
    int n = arr.size();
    vector<int> L (n, 0);
    for (int i = 0; i < n; i++)
        L[i] = arr[i];
    for (int i = 0; i < n; i ++)
    {
        for (int j = 0; j < i; j++)
        {
            // if the value is less than current value
            if ((arr[j] <= arr[i]) && (L[j] + arr[i] > L[i]))
            {
                L[i] = L[j] + arr[i];
            }
        }
    }
    // TODO: Use single pass by putting the logic below into the logic above instead of 2 passes. 
    // Now get the maximum sum
    int maxSum = L[0];
    for (int i = 0; i < n; i++)
    {
        if (L[i] > maxSum)
            maxSum = L[i];
    }
    return maxSum;
}

int main(void)
{
    vector<int> arr = { 5, 1, 2, 1, 3, 2}; // 6 = 1 + 2 + 3
    int maxSum = MaxSumIncreaseSubsequence(arr); 
    cout << maxSum << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------
// 4 Longest Common Subsequence Between Two Strings
// Time Complexity, T(n,m) = O(nm)  
// Space Complexity, S(n,m) = O(nm)
//-------------------------------------
/*
Questions
    1. Maximum length of both strings? 
    2. Are both strings same length? 
    3. Can string contain duplicates? 
    4. If any string is NULL or empty? Return 0? 
    5. Print length only or sequence as well? 
Function Prototype 
    int LCS(char* str1, char* str2);
Test Case: 
    "abbc", "abc" = 3 "abc"
    "aghbklc, "hgalbck" = 3 "abc"
    "aghbklc", "hgalbckzzyw";
Algorithm: 
    initialize a[n][m]; a[i][j] => maximum longest common subsequence that includes str[i] and str[j] 
    if str[i] == str[j] => and i!=0 or j != 0 => a[i][j] = 1 + LCS[i-1][j-1]
    else        => a[i][j] = max(LCS[i-1][j], LCS[i][j-1])
    otherwise, a[i][j] = 0
Implementation:
Test!
// */
//-------------------------------------
/* //
#include <string> 
#include <vector> 
#include <iostream> 
using namespace std; 

void printLCS(vector<vector<int>>& dir, string s1, int i, int j)
{
    if (i < 0 || j < 0) return; 
    if (dir[i][j] == 2)
    {
        printLCS(dir, s1, i-1, j-1);
        cout << s1[i] << " ";
    }
    else if (dir[i][j] == 1)
    {
        printLCS(dir, s1, i-1, j);
    } 
    else  // dir[i][j] == 0
    {
        printLCS(dir, s1, i, j-1);
    }
}

int LCS(const string& s1, const string& s2)
{
    if (s1.empty() || s2.empty()) return 0;
    int s1Len = s1.length();
    int s2Len = s2.length();
    if (s1Len == 0 || s2Len == 0) return 0;
    vector<vector<int>> arr(s1Len, vector<int> (s2Len, 0));
    vector<vector<int>> dir(s1Len, vector<int> (s2Len, 0));
    int maxSoFar = 0; 
    for (int s1Index = 0; s1Index < s1Len; s1Index++)
    {
        for (int s2Index = 0; s2Index < s2Len; s2Index++)
        {
            if (s1[s1Index] == s2[s2Index]) // matches
            {
                dir[s1Index][s2Index] = 2; 
                arr[s1Index][s2Index] = 1; 
                if (s1Index != 0 && s2Index != 0) // MISTAKE!! USED || instead of &&
                {
                    arr[s1Index][s2Index] += arr[s1Index-1][s2Index-1]; 
                }
            }
            else // not match
            {
                if (s1Index != 0)
                {
                    dir[s1Index][s2Index] = 1; 
                    arr[s1Index][s2Index] = arr[s1Index-1][s2Index]; 
                }
                if (s2Index!=0)
                {
                    if (arr[s1Index][s2Index-1] > arr[s1Index][s2Index])
                    {
                        arr[s1Index][s2Index] = arr[s1Index][s2Index-1];
                        dir[s1Index][s2Index] = 0; 
                    }
                }
            }
            if (arr[s1Index][s2Index] > maxSoFar) maxSoFar = arr[s1Index][s2Index]; 
        }
    }
    printLCS(dir, s1, s1Len-1, s2Len-1);
    cout << endl;
    return arr[s1Len-1][s2Len-1];
}

int main(void)
{
    string s1 = "aghbklc";
    string s2 = "hgalbcdzzyw";
    int maxLCS = LCS(s1, s2); // 3 => "abc"
    cout << maxLCS << endl;
    return 0; 
}
// */
//----------------------------------------------------------------------------------------------------
// 5 Longest Increasing Subsequence
// Time Complexity, T(n) = O(n^2)
// Space Complexity, S(n) = O(n)
//-------------------------------------
/* //  
Questions
    1. What does the array contain? Integer? Double? 
    2. Can the integers be any value? Can it be (-) ? 
    3. What to return if array is empty?  0 
    4. Do I return the array of longest increasing subsequence or just length 
    5. Can array have duplicates? Does maintaining on the same number counts as increasing? YES. 
Function Prototype 
    int LIS(vector<int>& arr); 
Test Cases
    [] = 0
    [1,-1,3] = 2
    [1,-1] = 1 
    [15, 16, 9, 17, 10, 11, 12] = 4 
Algorithm
    1. Brute Force => O(2^n) 
        NOT O(n^2) cause can't simply loop through array once to find out if it works for each element. Need try all possible permutations. 
    2. Dynamic Programming 
        Let L[i] = longest increasing subsequence from 0->i but including 'i' with i in the LIS. 
        L[0] = 1 
        L[i] = 1, L[i] = max(L[i], L[j] + 1) for every j < i where arr[j] < arr[i]
        O(n^2), Space O(n)
TEST!  
// */ 
//-------------------------------------
/* //
#include <cmath> 
#include <cstdlib>
#include <vector> 
#include <iostream> 
using namespace std; 

int LIS(vector<int>& arr)
{
    int n = arr.size(); 
    if ( n <= 0) return 0;
    vector<int> L(n, 1); // initialize all to 1
    for (int i = 1; i < n; i++)
    {
        for (int j = i-1; j >= 0; j--)
        {
            if (arr[j] <= arr[i])
            {
                L[i] = max(1 + L[j], L[i]);
            }
        }
    }
    int maximum = L[0];
    for (int i = 1; i < n; i++)
    {
        maximum = max(maximum, L[i]);
    }
    return maximum;
}

int main(void)
{
    vector<int> arr = {15, 16, 9, 17, 10, 11, 12}; // C++ 11
    int result = LIS(arr); 
    cout << result << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------
// 6 Edit Distance 
// Given 2 strings that are different, find min. number of changes to convert 1 to another
// Operations are equal cost: Replace, Insert, Delete             
// Time Complexity, T(n,m) = O(nm)
// Space Complexity, S(n,m) = O(nm)
//-------------------------------------
/* 
Questions
    1. Can I Replace,Insert,Delete anywhere in string or at end of string
    2. Do I have to print the operations? If yes, must I only modify 1 string or can I modify any of the string at any given operation? 
Applications: Auto-correct
OMG YOU SOLVED IT YOURSELF, it is a totally different solution that what's available online, so understand those in future
Online solution is actually simpler but the fact that you solved it yourself from Longest Common Subsequence is cool! 
You can actually solve it directly. But your motivation was from LCS. 
BUT your solution takes O(2nm) time whereas best way to do it only takes O(nm) time. 
// */
//-------------------------------------
/*
#include <cstring> 
#include <string> 
#include <vector> 
#include <iostream> 
using namespace std; 

int getEdit(vector < vector<int> >& dir,vector < vector<int> >& arr, const char* s1, int i, int j)
{
    if (i < 0 || j < 0) return 0;  // no need to count out of bounds

    // Pick the direction that results in largest
    int direc = -1; // initialize to nowhere
    int currMax = 0;

    // Then just skip to diagonal
    if (dir[i][j] == 2)
    {
        // Check that i and j are both not = 0
        if (i != 0 && j != 0)
            return (0 + getEdit(dir, arr, s1, i-1, j-1));
        else if (i != 0)
            return (0 + getEdit(dir, arr, s1, i-1, j));
        else if (j != 0)
            return (0 + getEdit(dir, arr, s1, i, j-1));
        else 
            return 0;
    }
    else 
    {
        if (i!= 0 && j != 0)
        {
            direc = 2;
            currMax = arr[i-1][j-1];
        }
        if (i!= 0)
        {
            if (arr[i-1][j] > currMax) 
            {
                direc = 1; 
                currMax = arr[i-1][j];
            }

        }
        if (j != 0)
        {
            if (arr[i][j-1] > currMax)
            {
                direc = 0;
                currMax = arr[i][j-1];
            }
        }
        // If you didn't update direction
        if (direc == -1)
            return 1;  // return 1 for accounting for this node
        else if (direc == 2)
            return (1 + getEdit(dir, arr, s1, i-1, j-1));
        else if (direc == 1)
            return (1 + getEdit(dir, arr, s1, i-1, j));
        else
            return (1 + getEdit(dir, arr, s1, i, j-1));
    }
}

int LCSThenEdit(const char* s1, const char* s2)
{
    if (!s1 || !s2) return 0;
    int n = strlen(s1); 
    int m = strlen(s2);
    if (n == 0 || m == 0) return 0;
    vector < vector <int> > arr(n, vector<int> (m, 0));
    vector < vector <int> > dir(n, vector<int> (m, 0));
    int maxSoFar = 0; 
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (s1[i] == s2[j])
            {
                dir[i][j] = 2; 
                arr[i][j] = 1; 
                if (i != 0 && j != 0) // MISTAKE!! USED || instead of &&
                {
                    arr[i][j] += arr[i-1][j-1]; 
                }
            }
            else 
            {
                if (i!=0)
                {
                    dir[i][j] = 1; 
                    arr[i][j] = arr[i-1][j]; 
                }
                if (j!=0)
                {
                    if (arr[i][j-1] > arr[i][j])
                    {
                        arr[i][j] = arr[i][j-1];
                        dir[i][j] = 0; 
                    }
                }
            }
            if (arr[i][j] > maxSoFar) maxSoFar = arr[i][j]; 
        }
    }
    maxSoFar = getEdit(dir, arr, s1, n-1, m-1);
    // Need to know direction to know how far back to go
    cout << endl;
    return maxSoFar; 
}

int main(void)
{
    string a1 = "iaebgch";
    string b1 = "afbcg";
    //string a1 = "abbc";
    //string b1 = "abc";
    const char* s1 = a1.c_str();
    const char* s2 = b1.c_str();
    int maxEdit = LCSThenEdit(s1, s2); // 3 => "abc"
    cout << maxEdit << endl;
    cout << "OMG, YOU SOLVED IT YOURSELF!" << endl;
    return 0; 
}
// */
//----------------------------------------------------------------------------------------------------
// 7 Minimum Cost Path from [0][0] to [m-1][n-1] in a matrix 
// Time Complexity, T(n,m) = O(mn)
// Space Complexity, S(n,m) = O(mn)
//-------------------------------------
/* 
Questions: 
    1. What does the matrix contain? Integers or doubles? 
    2. Can the values be <= 0? 
    3. Is it inclusive of starting and ending points? 
    4. Which direction can I move ? Right, Down, Diagonal Down. 
    5. Any limitations on the values? Or the size of matrix? 
    6. Can I modify original matrix passed in to save space? No!
    7. What to return if array size is empty? 
Function Prototype:
    int minCostPath(vector < vector <int> >& arr);
Test Case:
    1 2 2
    2 1 2  => 3
    2 2 1 
Algorithm: 
    Start from top and go from left to right row by row and fill it up with minimum to come from adding its own value
    Then at the end, you'll get the min cost path.
    minimum[i][j] = minimum cost to go from [0][0] to [i][j]
Implementation
TEST!
*/
//-------------------------------------
/* //
#include <climits> // for INT_MAX
#include <vector>
#include <iostream>
using namespace std; 

int minCostPath(vector < vector <int> >& arr)
{
    int N = arr.size();
    if (N <= 0) return 0;
    int M = arr[0].size();
    if (M <= 0) return 0;
    vector < vector <int> > minimum(N, vector<int> (M, 0)); 
    // minimum[i][j] = minimum cost to go from [0][0] to [i][j]
    minimum[0][0] = arr[0][0]; 
    int j = 1;
    for (int i = 0; i < N; i++)
    {
        for (; j < M; j++)
        {
            int prev = INT_MAX;  // initialize to 0 if no previous since guaranteed all values are > 0. 
            if (i > 0 && j > 0 && (minimum[i-1][j-1] < prev)) // MISTAKE: USED '<' instead of '>'
            {
                prev = minimum[i-1][j-1];
            }
            if ( i > 0 && (minimum[i-1][j] < prev))
            {
                prev = minimum[i-1][j];
            }
            if ( j > 0 && (minimum[i][j-1] < prev))
            {
                prev = minimum[i][j-1];
            }
            // previous will always be updated except the very first occurence which only occurs once
            minimum[i][j] = prev + arr[i][j];
        }
        // Initialize j, the reason you do this is so you don't have to do the if statement everytime to check if its (i == 0 && j == 0)
        // beautiful =) , learnt this problem from engineer at bloomberg where if statement only executes once
        j = 0;
    }
    return minimum[N-1][M-1];
}

int main(void)
{
    int N = 3; 
    int M = 3;
    vector < vector <int> > arr(N, vector<int> (M, 0));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            arr[i][j]  = (i+1) * (j+1);
            cout << arr[i][j] << " "; 
        }
        cout << endl;
    }
    int minimum = minCostPath(arr);
    cout << minimum << endl;
    return 0; 
}
// */
//----------------------------------------------------------------------------------------------------
// 8 Coin Change: Find # of combinations to make a change for value N given infinite supply of a given CoinType = [C1, C2, ... , Cm]
// Time Complexity, T(n,m) = O(nm), Space Complexity, S(n,m) = O(n)
//-------------------------------------
/*
Questions
    1. Are the coins integers or can they be floats? 
    2. Is N an integer or can be floats? 
    3. Can the values of the coins be (-)
    4. Are the coins sorted? 
    5. Is it min. number of combination of coins or min. number of coins needed to get value N? 
Test Case: 
    {1,2,3}, N = 1 => 1 = [(1)]
    {1,2,3}, N = 3 => 3 = [(1,1,1), (1,2), (3)] 
    {1,2,3}, N = 6 => 7 = [(1,...,1), (2,2,2), (2,2,1,1), (2,1,..,1), (3,3), (3,2,1), (3,1,1,1)]
// */
//-------------------------------------
/* //
#include <vector> 
#include <iostream> 
using namespace std; 

int CoinChange(int N, vector<int>& Coins)
{
    vector<int> currSolution (N+1, 0); // C++ 11 feature
    // currSolution[0] = 1 always
    currSolution[0] = 1;
    // Loop through each coin and include them in the solution
    for (int i = 0; i < Coins.size(); i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (j - Coins[i] >= 0)
            {
                // Get the 1*numCombinationAfterDeducting + originalTotalSum for this value of N without this coin
                currSolution[j] = currSolution[j - Coins[i]] + currSolution[j];
            }
            // else, don't do anything as it's just 0*numCombinationAfterDeducting + originalTotalSum for this value of N without this coin, which remains the same
        }
    }
    return currSolution[N]; 
}

int main(void)
{
    int N = 6; 
    vector<int> Coins = {3,1,2}; // to show coin doesn't need to be sorted 
    int numCombinations = CoinChange(N, Coins); 
    cout << numCombinations << endl;
    return 0; 
}
// */
//----------------------------------------------------------------------------------------------------
// 9 Matrix Chain Multiplication: Find most efficient way to multiply a chain of matrices together. 
// Time Complexity, T(n) = O(n^3), Space Complexity, S(n) = O(n^2) 
/*
Questions: 
    1. Return order of multiplication of number of multiplication? 
    2. How is the matrix given to me? Is matrix guaranteed to be multiplicable ? (row * column)
    3. What happens if matrix size is less than 3? 
Function Prototype: 
    int MatrixChainMultiplication(vector<int>& matrix);
TestCases:
    [10,30,5,60] = 10*30*5  + 10*5*60 = 1500 + 3000 = 4500
    [10,10] = 0
    [10] = 0
// */
//-------------------------------------
/* // 
#include <cstdlib> // for min()
#include <climits> // for INT_MAX
#include <vector> 
#include <iostream> 
using namespace std; 

int MatrixChainMultiplication(vector<int>& matrix)
{
    int N = matrix.size(); 
    // Initialize a matrix of N^2 with value 0 
    vector< vector<int> > orders(N, vector<int>(N, INT_MAX));
    // Let orders[i][j] = matrixChainMultiplication from matrix[i] to matrix[j] inclusive
    if (N <= 2) return 0;
    // Compute base cases
    orders[N-1][N-1] = 0; // extra case outside for loop
    for (int i = 0; i+1 < N; i++) // O(n)
    {
        orders[i][i] = 0;
        orders[i][i+1] = 0;
    }
    for (int i = 0; i+2 < N; i++) // O(n)
    {
        orders[i][i+2] = matrix[i] * matrix[i+1] * matrix[i+2];
    }
    // Done computing base cases
    // O(n^3)
    for (int i = 2; i < N; i++)
    {
        for (int j = 0; j+i < N; j++)
        {
            // Start from k = 1 since k = 0 does not make sense as you can't have a matrix with rows and no columns
            for (int k = 1; k < i; k++)
            {
                // get value of splitting at current k value
                int temp = orders[j][j+k] + orders[j+k][j+i] + matrix[j]*matrix[j+k]*matrix[j+i];
                orders[j][j+i] = min(orders[j][j+i], temp); // update to minimum value found // MISTAKE: Did maximum instead of minimum
            }
        }
    }
    return orders[0][N-1];
}

int main(void)
{
    vector<int> matrix = {10, 30, 5, 60}; // C++ 11 feature
    int minMultiplication = MatrixChainMultiplication(matrix);
    cout << minMultiplication << endl;
    return 0; 
}
// */
//----------------------------------------------------------------------------------------------------
// 10 Knapsack 0-1: Find max value from items with weights >= 0 and values, for weight capacity, W.
// Time Complexity, T(W,n) = O(nW), Space Complexity, S(W,n) = O(nW)
//-------------------------------------
/* 
Questions:
    1. Is there unlimited number of each item? 
    2. Can weights be < 0 ? Are weights double or integers? 
    3. How about weight capacity? 
    4. Can values be < 0 ?  No
Function Prototype:
    int Knapsack01(vector<int>& weights, vector<int>& values, int capacity); 
Test:
    W=5, [Wi,Vi] = [2,3], [3,1] => 4
    W=4, [Wi,Vi] = [2,3], [3,1] => 3 
    W=11, [Wi,Vi] = [2,3], [6,6], [3,1] => 10
        // To make sure [3,1] doesn't overwrite [5,6] after deciding can overwrite [2,3]
    W=9, [Wi,Vi] = [2,3], [3,1], [6,6] => 9 
    W=12, [Wi,Vi] = [2,3], [6,6] => 9 
        // to make sure do not add same item twice, so in this case, don't add item 5 twice to get 12 
// */
//-------------------------------------
/* //
#include <vector>
#include <iostream> 
using namespace std;

int Knapsack01(vector<int>& weights, vector<int>& values, int capacity)
{
    if (capacity < 0) return 0; 
    int N = values.size();
    if ( N != weights.size()) return 0; // error in inputs given
    if (N <= 0) return 0; // if no item given, return 0
    vector< vector<int> > matrix(capacity + 1, vector<int> (N, 0));
    // matrix[weight,itemIndex] => total value obtainable for this weight capacity with items up to and including itemIndex 
    // but not necessarily including item at itemIndex itself
    // Initialize first item
    for (int i = 0; i <= capacity; i++)
    {
        matrix[i][0] =  i >= weights[0] ? values[0] : 0;
    }
    // Go through each item other item
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j <= capacity; j++)
        {
            // Initialize to not adding current item
            matrix[j][i] = matrix[j][i-1];
            // only if current item weight is less than current total capacity
            if (j >= weights[i])
            {
                // Decide if better to include new item or not include it
                if ((matrix[j-weights[i]][i-1] + values[i]) > matrix[j][i-1])
                {
                    // Include this item instead 
                    matrix[j][i] = matrix[j-weights[i]][i-1] + values[i];
                }
            }
        }
    }
    return matrix[capacity][N-1];
}

int main(void)
{
    int W = 12; 
    vector<int> weights = {2,3,6}; // C++11 Feature
    vector<int> values = {3,1,6}; 
    int totalValue = Knapsack01(weights, values, W); // totalValue should be 10
    cout << totalValue << endl; 
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------
// 11 Egg Dropping: Given n eggs and k floors, find minimum number of attempts to determine level at which egg starts to break. 
// Time Complexity, T(n,k) = O(n(k^2)), Space Complexity, S(n,k) = O(nk)
//-------------------------------------
/*
Questions
    1. Is there a limit for value of k? 
// */
//-------------------------------------
/* //
#include <climits> // INT_MAX
#include <cstdlib> // min() and max()
#include <vector> 
#include <iostream> 
using namespace std;

int EggDrop(int n, int k)
{
    vector< vector<int> > arr(n+1, vector<int> (k + 1,INT_MAX));
    for (int i = 1; i <= k; i++)
    {
        // Can't try anymore if 0 eggs left
        arr[0][i] = 0;
        // Need try all k floors if only have 1 
        arr[1][i] = i; // MISTAKE: Wrote k instead of i here which is wrong!
    }
    for (int i = 1; i <= n; i++)
    {
        arr[i][0] = 0; // no floors left to try
        arr[i][1] = 1; // 1 floor left to try
    }
    for (int i = 2; i <= n; i++)
    {
        for (int j = 2; j <= k;j++)
        {
            for (int x = 1; x <= j; x++)
            {
                arr[i][j] = min(arr[i][j],1 + max(arr[i][j-x], arr[i-1][x-1]));
            }
        }
    }
    return arr[n][k];
}

int main(void)
{
    int n = 2;
    int k = 36;
    int minTries = EggDrop(n, k); 
    cout << minTries << endl; // 8 
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------
// 12 Longest Palindrome Subsequence 
// Time Complexity, T(n) = O(n^2), Space Complexity, S(n) = O(n^2) 
//-------------------------------------
// note: Possible to change S(n) = O(2n) but complicated, do later. 
/*
Questions
    1. Is it any character  or integers? 
    2. Can there be duplicates in the Longest Palindrome Subsequence? 
    3. Do I return the palindrome or do I return the length? 
    4. What happens if string is now? or string is ""? 
Function Prototype: 
    int LongestPalindromeSubsequence(char* str);
Test Cases: 
    1. "agbdbha" => 5 ("abdba")
    2. "abc" => 1 ("a")
    3. "aa" => 2 ( "aa")
Algorithms: 
    1.  T(n) = O(n^2) , S(n) = O(n^2) 
        Loop from down to up, add 2 if equal but not same exist, add 1 if equal but same index
        move diagonal downwards if equal, move max (horizontal,vertical) if not equal
        Only use half the matrix, but complicated logic. In fact, better to just reduce to O(2n)
        Can possible reduce S(n) = O(2n) = O(n) if want to but complicated logic, possible cause only depend on latest 2 rows 
    2.  T(n) = O(n^2 + n) , S(n) = O(n^2 + n) 
        Create a new string as the reversed of the original string. 
        Return the longest common subsequence of the original string and its reversed string.
*/
//-------------------------------------
/* //
#include <cstring> 
#include <string> 
#include <vector> 
#include <iostream> 
using namespace std; 

int LongestPalindromeSubsequence(const char* str)
{
    if (!str) return 0; 
    int n = strlen(str);
    if (n <= 0) return 0;
    vector< vector<int> > arr(n, vector<int> (n,0)); //initialize all elements to be 0
    // arr[i][j] => Longest palindrome subsequence from substring[i][j] inclusive
    // the case where j < i is always 0 so ignore
    for (int j = 0; j < n; j++) // first string to compare
    {
        for (int i = j; i >= 0; i--)
        {
            if (i == j)
                arr[i][j] = 1; 
            else if (str[i] == str[j]) // MISTAKE: used 'if' instead of 'else if', also used arr[i] INSTEAD OF str[i]
                arr[i][j] = 2 + arr[i+1][j-1];
            else
                arr[i][j] = max(arr[i+1][j], arr[i][j-1]);
        }
    }
    return arr[0][n-1];
}
int main(void)
{
    string ab = "agbdbha";
    const char * str = ab.c_str();
    int length = LongestPalindromeSubsequence(str); // "abdba" => 5
    cout << length << endl;
    string ba = "aa";
    const char * str2 = ba.c_str();
    length = LongestPalindromeSubsequence(str2); // "aa" => 2
    cout << length << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------
// 13 Unique Paths: Number of unique paths from [0][0] to [n-1][m-1], only move (down,right) at any time
// Time Complexity, T(n,m) = O(nm) 
// Space Complexity, S(n,m) = O(min(n,m)) 
//-------------------------------------
/* 
Questions: 
    1.  What happens if n || m <= 0 ? 
Function Prototype: 
    int uniquePaths(int n, int m);
Test_Cases: 
    (1,1) = 1
    (2,3) = 3
    (5,3) = 15
Algorithm: 
    Dynamic programming O(nm)
    Each element depends only on top or left by 1 step => Can use  S(n,m) = O(min(n,m)) space instead of O(nm) 
    Move from up to down from left to right. Can skip first element at each column since it remains the same always (1 way only to move horizontal)
    T(n,m)  = O(mn) time 
Implement!
// */
//-------------------------------------
/* //
#include <vector> 
#include <iostream> 
using namespace std; 

int uniquePaths(int n, int m)
{
    if ( n <= 0 || m <= 0) return 0;
    // Make n1 <= m1
    int n1 = min(n,m);
    int m1 = max(n,m); 
    // Initialize all to 1
    vector<int> arr(n1, 1);
    for (int i = 1; i < m1; i++) // can skip the first column since will always be 1
    {
        // Inner loop is n1 so that space required is only n1
        for (int j = 1; j < n1; j++) // can skip the first row of every column since will always be 1
        {
            arr[j] = arr[j] + arr[j-1];
        }
    }
    return arr[n1-1];
}

int main(void)
{
    int n = 1; 
    int m = 1; 
    int result = uniquePaths(n,m); // 1
    cout << n << ", " << m <<": " << result << endl;
    n = 2; m = 3; 
    result = uniquePaths(n,m); // 3
    cout << n << ", " << m <<": " << result << endl;
    n = 5; m = 3;  // 15
    result = uniquePaths(n,m);
    cout << n << ", " << m <<": " << result << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------
// 14 Minimum Number Coin Change: Find min. number of coins from a set of coin values to get a particular value
// Time Complexity, T(V,n) = O(Vn)
// Space Complexity, S(V,n) = O(V)
//-------------------------------------
/*
Questions: 
    1. Output the actual coins used or just min. number of coins? 
    2. What happens if no way to get the values?  Return INT_MAX
Function Prototype: 
    int minimumNumCoins(vector<int>& coins, int V);
Test Case: 
    [7,3,6,1], V = 9 => 2 (6,3) 
Implement!
*/
//-------------------------------------
/* //
#include <climits> // INT_MAX
#include <vector>
#include <iostream> 
using namespace std; 

int minimumNumCoins(vector<int>& coins, int V)
{
    int n = coins.size(); 
    vector<int> arr(V+1, INT_MAX);
    arr[0] = 0; // V = 0 => 0 coins needed
    // Loop through each coin
    for (int i = 0; i < n; i++)
    {
        // Loop through each value for coin from 1 to V
        for (int j = 1; j <= V; j++)
        {
            int currMin = INT_MAX; // initialize currMin to INT_MAX
            // If there may be possible ways to get this coin
            if ((j - coins[i] >= 0) && (arr[j-coins[i]] != INT_MAX))
            {
                currMin = 1 + arr[j-coins[i]];
            }
            // current array value is minimum of the coin itself + previous combinations, or without using the coin itself from previous coins
            arr[j] = min(currMin, arr[j]);
        }
    }
    return arr[V];
}

int main(void)
{
    int V = 9;
    vector<int> arr = {7, 3, 6, 1};
    int result = minimumNumCoins(arr, V); 
    cout << result << endl;
    vector<int> arr2 = {1, 6, 3, 7};
    result = minimumNumCoins(arr2, V); 
    cout << result << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------
