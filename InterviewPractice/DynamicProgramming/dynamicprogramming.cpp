Table of Contents

1. Fibonacci Sequence (Bottom Up)

2. Rod Cutting Problem (Top Down with Memoization)

3. Rod Cutting Problem (Bottom Up)

4. Longest Common Subsequence Between Two Strings (Bottom Up)

/*
TODO: 
5.Maximum Subarray() (using dynamic instead of kadane's algorithm)

6.Longest Common Substring Between Two Strings (Bottom Up)

7.Josephus Problem

8. Triangle Problem
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
        - Identify optimal substructure (Subproblems can be solved optimally as well)
        - Use divide and conquer approach (Top - Down)
        - Start from solving each element individually and combine answers (Down -> Up) , normally saves space of not needing the cache compared to previous (top down)
        - Start cases either from individual to group (bottom up) of tree  OR from left to right (One element to all N elements) and try to form an equation
        - How does including your new individual change the equation? Think in that way. 
        - When moving from left to right, each step i is the solution for the same problem at i. Then at step(n), that is the solution to the problem n given
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
    

Given Knapsack Problem 
I(0), ... I(n-1), I(0) = (V(0), W(0)) with constraint C = Weight. Calculate maximum value that can be gain. 
Note: can pick duplicates of I(i) for any i. So like 3I(0) + 2I(i)
*/

//----------------------------------------------------------------------------------------------------
/* //
// 1 Fibonacci Sequence (Bottom Up)
// Time Complexity: O(n)
// Space Complexity, S(n) = O(n)

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
/* //
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
/* //
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
//-----------------------------------------------------------------------------------------------
/*
// 4 Longest Common Subsequence Between Two Strings
// Approach 1: Dynamic Programming (Bottom Up)
// Time Complexity, T(n,m) = O(nm)
// Space Complexity, S(n,m) = O(nm)

#include <cstdlib>
#include <iostream>
using namespace std;

void printLCS(int** C, char** direction, int* x,  int i , int j);

int main(void)
{
    int N, M;
    cin >> N >> M;
    int x[N];
    int y[M];
    // Create a 2D array to store values
    int** C;
    char** direction; // for backtracing which path was taken later
        // '0' => backtrack [i-1][j]
        // '1' => backtrack [i][j-1]
        // '2' => backtrack [i-1][j-1]
    C = (int **) malloc(sizeof(int *) * (N+1));
    direction = (char **) malloc(sizeof(char *) * (N+1));

    for (int i = 0; i <= N; i++)
    {
        C[i] = (int *) malloc(sizeof(int) * (M+1));
        direction[i] = (char *) malloc(sizeof(char) * (M+1));
    }

    for(int i = 0; i <= N; i++)
    {
        if(i != N)
        {
            cin >> x[i];
        }
        C[i][0] = 0;
        direction[i][0] = '0';
    }

    for(int i = 0; i <= M; i++)
    {
        if(i != M)
        {
            cin >> y[i];
        }
        C[0][i] = 0;
    }

    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            if(x[i-1] == y[j-1])
            {
                C[i][j] = C[i-1][j-1] + 1;// add one to number of common subsequence in this path
                direction[i][j] = '2';
            }
            else
            {
                if(C[i-1][j] >= C[i][j-1])
                {
                    C[i][j] = C[i-1][j];
                    direction[i][j] = '0';
                }
                else
                {
                    C[i][j] = C[i][j-1];
                    direction[i][j] = '1';
                }
            }
        }
    }

    printLCS(C, direction, x, N, M);
    cout << endl;
    // Done finding longest subsequence
    // now print out solution recursively
}

void printLCS(int** C, char** direction, int* x,  int i , int j)
{
    if(i == 0 || j == 0)
    {
        return;
    }
    if (direction[i][j] == '2')
    {
        printLCS(C, direction, x, i-1, j-1);
        cout << x[i-1] << " ";
    }
    else if(direction[i][j] == '0')
    {
        printLCS(C, direction, x, i-1, j);
    }
    else
    {
        printLCS(C, direction, x, i, j-1);
    }
    return;
}
// */
//-----------------------------------------------------------------------------------------------
