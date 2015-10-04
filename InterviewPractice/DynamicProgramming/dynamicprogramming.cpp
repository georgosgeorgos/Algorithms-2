//----------------------------------------------------------------------------------------------------
/*
Table of Contents
1. Fibonacci Sequence (Bottom Up)
2. Rod Cutting Problem (Top Down with Memoization)
3. Rod Cutting Problem (Bottom Up)
4. Longest Common Subsequence Between Two Strings
5. Longest Increasing Subsequence, T(n) = O(n^2), S(n) = O(n)
//----------------------------------------------------------------------------------------------------
TODO: 
15.Maximum Subarray() (using dynamic instead of kadane's algorithm)

16.Longest Common Substring Between Two Strings (Bottom Up)

17.Josephus Problem

18. Triangle Problem
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
notes: 
When question says, at each level, you can either move to left or right => Big hint you should try dynamic programming
    1. Find out equation and create recursive function. 
        - Start by figuring out the base cases
        - Identify optimal substructure (Subproblems can be solved optimally as well)
        - Note: The optimal substructure may not be the optimal solution to that sub-problem. The optimal substructure may contain restriction such as: 
            For Longest Increasing Subsequence, the optimal Substructure L[i] requires the optimal solution to i to contain item 'i' itself. 
            However, the actual optimal solution will need to be iterated from L[0] to L[i] to find the actual optimal solution as 
            the optimal solution may not contain i
        - Use divide and conquer approach (Top - Down)
        - Start from solving each element individually and combine answers (Down -> Up) , normally saves space of not needing the cache compared to previous (top down)
        - Start cases either from individual to group (bottom up) of tree  OR from left to right (One element to all N elements) and try to form an equation
        - How does including your new individual change the equation? Think in that way. 
        - When moving from left to right, each step i is the solution for the same problem at i. Then at step(n), that is the solution to the problem n given
        - Find out what base cases are, try out every variable combination. (Knapsack => W, w[i], v[i]) => arr[W] = (v[i], w[i])
        - Dimensions are prolly the values that can only contain positive integers since thats how you build your array. 
            - if (-) integers are allowed, just add everything with the abs(lowest (-) integer) and now all you have is (+) integers
            - if the values aren't (-), you can always build the array by indexing into it. 
        - An NP-Hard problem may have a pseudo-polynomial solution 
    2. Remove useless arguments from function, the different combinations of arguments are the states of the function. 
    3. If subproblems overlap, memoize them: Save results into cache[n][n] (2 arguments, each can span n different values => n^2 different computations only) 
       - If your function only depends on the last k results, where k is a constant (doesnt change depending on value of n) 
       Then, you can make temporary variables and swap them as necessary instead of making an entire array to store the results. 
       e.g. if k = 2, instead of doing a[i] = max(a[i-1], a[i-2]) 
       you can do,   currMax = max(prev, prevprev), prevprev = prev, prev = currMax; 
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
// Time Complexity: O(n)
// Space Complexity, S(n) = O(n)
//-------------------------------------
/* //
#include <iostream>
#include <stdlib.h>

using namespace std;

int fibonacci(int n, int* p);
int main(void)
{
    int i = 0;
    int n = 10;
    int *p;
    p = (int *) malloc(sizeof(int) * (n+1));
    for (i = 0; i < n; i++)
    {
        p[i] = -1; // initialize with negative numbers
    }
    for(i = 0; i < n; i++)
    {
        int j = fibonacci(i, p);
        cout << "Fibonacci for " << i << " is: " << j << endl;
    }
}

int fibonacci(int n, int* p)
{
    p[0] = 1;
    p[1] = 1;
    if (n <= 1)
    {
        return 1;
    }
    int i = 0;
    for(i = 2; i <= n; i++)
    {
        p[i] = p[i-1] + p[i-2];
    }
    return p[n] ;
}
// */

//----------------------------------------------------------------------------------------------------
// 2 Rod Cutting Problem ( Dynamic Programming)
// Top-Down with memoization
// Given a rod of length n, and a price for rod of length 1, 2, ... n.
// Determine how to cut the rod to maximize total price.
// Note: There are 2^n - 1 combinations of possible answers since
//       For every i > 1, you can decide if you wanna cut, or not cut.
//  Which means trying everything out will be an exponential time
// Method 1: Top-Down with memoization
// Time Complexity: O(n^2) , using dynamic programming
// Space Complexity: O(n)
// Note: Use dynamic programming and print the final solution, not just the optimal value
// TODO: Have not printed the final solution
//-------------------------------------
/* //
#include <iostream>
#include <stdlib.h>
#include <limits.h>

using namespace std;
int cut_rod(int *p , int n, int *s, int *r);
int main(void)
{
    int *p; // prices
    int *s; // list of cuts for printing
    int *r; // current list from solution
    int n = 10;
    p = (int *) malloc(sizeof(int) * (n+1));
    s = (int *) malloc(sizeof(int) * (n+1));
    r = (int *) malloc(sizeof(int) * (n+1));
    p[0] = 0;
    p[1] = 1;
    p[2] = 5;
    p[3] = 8;
    p[4] = 9;
    p[5] = 10;
    p[6] = 17;
    p[7] = 17;
    p[8] = 20;
    p[9] = 24;
    p[10]= 30;
    int  i = 0;
    for ( i = 0; i <= n; i++)
    {
        r[i] = -1;
    }
    for (i =0 ; i <= n; i++)
    {
        int k = cut_rod(p, i, s, r);
        cout << "Optimal value for " << i << " is " << k << endl;
    }

    return 0;
}

int cut_rod(int *p , int n, int *s, int *r)
{
    if (n == 0)
    {
        r[0] = 0;// COMMENT THIS OUT FOR PURELY RECURSIVE WITHOUT MEMOIZATION
        p[0] = 0;
        return 0;
    }
    if (r[n] >= 0) return r[n];// COMMENT THIS OUT FOR PURELY RECURSIVE WITHOUT MEMOIZATION
    int i = 0;
    int q = INT_MIN;
    for (i = 1; i <= n; i++)
    {
                // max(whatever stored before, p[i] + r[n-i]
                // You can use p[i] cause you know that you are accounting for all cases of
                // the piece of each length from 1 all the way up to n.
                // this means you would have accounted for all cases.
        // Refer to pg 362/1292 of actual textbook from CLRS 3rd ed, it doesn't provide the proof
        // but it says you can prove it.
        q = max(q, p[i] + cut_rod(p, n-i, s, r));
    //    q = max(q, cut_rod(p, i, s, r) + cut_rod(p, n-i, s, r)); // NOTE: This is wrong and causes segfault.
    //    cout << "q is " << q << endl;
    }
    r[n] = q;  // COMMENT THIS OUT FOR PURELY RECURSIVE WITHOUT MEMOIZATION
    return q;
}
// */
//----------------------------------------------------------------------------------------------------
// 3 Rod Cutting Problem ( Dynamic Programming)
// Bottom Up Approach
// Given a rod of length n, and a price for rod of length 1, 2, ... n.
// Determine how to cut the rod to maximize total price.
// Note: There are 2^n - 1 combinations of possible answers since
//       For every i > 1, you can decide if you wanna cut, or not cut.
//  Which means trying everything out will be an exponential time
// Method 2: Bottom Up Approach
// Time Complexity: O(n^2) , using dynamic programming
// Space Complexity: O(n)
// Note: Use dynamic programming and print the final solution, not just the optimal value
//-------------------------------------
/* //
#include <iostream>
#include <stdlib.h>
#include <limits.h>

using namespace std;
int cut_rod(int *p , int n, int *s, int *r);
int main(void)
{
    int *p; // prices
    int *s; // list of cuts for printing
    int *r; // current list from solution
    int n = 10;
    p = (int *) malloc(sizeof(int) * (n+1));
    s = (int *) malloc(sizeof(int) * (n+1));
    r = (int *) malloc(sizeof(int) * (n+1));
    p[0] = 0;
    p[1] = 1;
    p[2] = 5;
    p[3] = 8;
    p[4] = 9;
    p[5] = 10;
    p[6] = 17;
    p[7] = 17;
    p[8] = 20;
    p[9] = 24;
    p[10]= 30;
    int  i = 0;
    for ( i = 0; i <= n; i++)
    {
        r[i] = -1;
    }
    for (i =0 ; i <= n; i++)
    {
        int k = cut_rod(p, i, s, r);
        cout << "Optimal value for " << i << " is " << k << endl;
    }

    return 0;
}

int cut_rod(int *p , int n, int *s, int *r)
{
    r[0] = 0;
    p[0] = 0;
    if (n == 0)
    {
        return 0;
    }
    int i = 0;
    int j = 0;
    for (i = 1; i <= n; i++)
    {
        int q = INT_MIN;
        for (j = 1; j <= i; j++)
        {
            // max(whatever stored before, p[i] + r[n-i]
            // You can use p[i] cause you know that you are accounting for all cases of
            // the piece of each length from 1 all the way up to n.
            // this means you would have accounted for all cases.
            // Refer to pg 362/1292 of actual textbook from CLRS 3rd ed, it doesn't provide the proof
            // but it says you can prove it.
            int oldq = q;
            q = max(q, p[j] + r[i-j]); // note: NO recursion
            if (oldq != q)
            {
                s[i] = j;
            }
        }
        r[i] = q;

    //    q = max(q, cut_rod(p, i, s, r) + cut_rod(p, n-i, s, r)); // NOTE: This is wrong and causes segfault.
    //    cout << "q is " << q << endl;
    }
    int l = n;
    cout <<"Arrangement for " << n << " is: " <<endl;
    while ( l > 0)
    {
        cout << "r[" << s[l] << "] ";
        l = l - s[l];
    }
    cout << endl;
    return r[n];
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
#include <cstring> 
#include <string> 
#include <vector> 
#include <iostream> 
using namespace std; 

void printLCS(vector < vector<int> >& dir, const char* s1, int i, int j)
{
    if(i < 0 || j < 0) return; 
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

int LCS(const char* s1, const char* s2)
{
    if (!s1 || !s2) return 0;
    int n = strlen(s1); 
    int m = strlen(s2);
    if (n == 0 || m == 0) return 0;
    vector < vector <int> > arr(n, vector<int> (m, 0));
    vector < vector <int> > dir(n, vector<int> (m, 0));
    int maxSoFar = 0; 
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
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
                    if(arr[i][j-1] > arr[i][j])
                    {
                        arr[i][j] = arr[i][j-1];
                        dir[i][j] = 0; 
                    }
                }
            }
            if (arr[i][j] > maxSoFar) maxSoFar = arr[i][j]; 
        }
    }
    printLCS( dir, s1, n-1, m-1);
    cout << endl;
    return maxSoFar; 
}

int main(void)
{
    string a1 = "aghbklc";
    string b1 = "hgalbckzzyw";
    const char* s1 = a1.c_str();
    const char* s2 = b1.c_str();
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
    for(int i = 1; i < n; i++)
    {
        for(int j = i-1; j >= 0; j--)
        {
            if(arr[j] <= arr[i])
            {
                L[i] = max(1 + L[j], L[i]);
            }
        }
    }
    int maximum = L[0];
    for(int i = 1; i < n; i++)
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
//-----------------------------------------------------------------------------------------------
