//----------------------------------------------------------------------------------------
/* 
Table of Contents
1. Implement Pow(double, int n), where n can be (-), 0 , (+)  T(n) = O(logN), S(n) = O(logN)
2. Euclid's Algorithm: Calculate GCD, T(n) = O(n), S(n) = O(1)
3. Binomial Coefficient = Number of ways to choose k out of n objects, T(n,k) = O(nk), S(n,k) = O(k)
4. SquareRoot(int x), where x > 0, T(n) = O(logn), S(n) = O(1)
5. Replace every # x with # y given an integer, T(n) = O(n), S(n) = O(1)
//-----------------------------------
TODO:
0. Calculate pow(double, int n), where n can be (-), 0 , (+)  T(n) = O(logN), S(n) = O(1) Hint: Dynamic Programming
1. Create rand()
2. Create 16by 9 => 16by10 or 16 by 8 cannot, 17by9 or 15by 9 cannot, returns true if 16b9 and false otherwise
3. Generate prime numbers up to N efficiently: Sieve of Eratosthenes
4. Look up sorting integers in O(logN) time on some Youtube MIT video on advanced data structures
5. Given numbers 0,1,2,...,N inserted into an array. Now exactly 1 number is removed from this array. Find that one number. 
6. Given numbers 0,1,2,...,N inserted into an array. Now exactly 2 numbers are removed from this array. Find these two number. 
    Hint: Linear equation and quadratic eqn. 
7. Given numbers 0,1,2,...,N inserted into an array. Now exactly k numbers are removed from this array. Find these k numbers, k <= n 
8. Given a value N, find the minimum number perfect squares sums to reach n. e.g. f(13) = 2 (2*2 + 3*3 = 4 + 9)
hint: Dynamic Programming/BFS/Math theorem can be used to solve
9. Reverse Integer 
    -321 => -123
    T(n) = O(n) S(n) = O(1)
10. Determine whether an integer is a palindrome 
    12321 => True
    -12321 => False
    T(n) = O(n) S(n) = O(1)
11. Add 'x' between 10^k,  (Bloomberg Round 1)
    e.g. k = 3 , x = ',', input = 12300987 (int) => output 12,300,987 (string)
//-----------------------------------
// Hint
//-----------------------------------
When working with % and / operators:
   - if handling (-) numbers, convert to (+) and solve, then multiply final result by (-)
   - make sure to account for appending "0"s if converting number to strings
// */
//----------------------------------------------------------------------------------------
// 1 Implement Pow(double, int n), where n can be (-), 0 , (+)  T(n) = O(logN), S(n) = O(logN)
// Time Complexity: O(logN)
// Space Complexity: O(1)
//-----------------------------------
/*
Questions:
    1. Integers only or double? 
    2. Can k be (-)? 
    3. Any limit to the number for k or num?  

Function Prototype: 
    double powers(double num,int k); 

Test Cases
    2^0 = 1
    2^3 = 8
    2^(-3) = 1/8

Algorithm: 
    2^4 = 2^2 * 2^2 
    2^5 = 2^2 * 2^2 * 2
// */
//-----------------------------------
/* //
#include <cmath>
#include <iostream>
using namespace std;

double power(double num, int k)
{
    if (k == 0 || num == 1) return 1; 
    if (k == 1) return num; 
    if (k == -1) return 1/num;
    double result = 1; 
    result = power(num, k/2);
    result *= result; 
    if (k&0x1)
    {
        if (k > 0)
            result *= num;
        else 
            result *= 1/num;
    }
    return result; 
}

int main(void)
{
    double num = 2; 
    double result = power(num, 3); 
    cout << result << endl;
    result = power(num, -3); 
    cout << result << endl;
    return 0; 
}
double power(double a, int n);

// */
//----------------------------------------------------------------------------------------
// 2 Euclid's Algorithm: Calculate GCD  
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
//-----------------------------------
/* //
#include <iostream>
using namespace std;

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}
// Based on Euclid's algorithm
int gcd(int a, int b)
{
    int temp;
    if (a > b)
    {
        swap(&a, &b);
    }
    // assume a <= b always
    while (a != 0)
    {
        temp = a; // save the current lowest
        a = b%a;  // get the new lowest
        b = temp; // restore the previous lowest
    }
    return b; // return the lowest that resulted in the mod to be 0
}

int main(void)
{
    int T, N;
    cin >> T;
    int i = 0;
    for(i = 0; i < T; i++)
    {
        cin >> N;
        int values[N];
        int j = 0 ;
        cin >> values[0];
        int gcdValue = values[0];
        for (j = 1; j < N; j++)
        {
            cin >> values[j];
            gcdValue = gcd(values[j],gcdValue);
            if (gcdValue == 1)
            {
                cout << "YES" << endl;
                // flush everything on current line
                // Note: Need to add j++ at beginning of for loop to iterate to next iteration.
                for (j++ ; j < N; j++)
                {
                    cin >> values[j];
                    // will break here
                }
            }
        }
        if (gcdValue != 1)
        {
            cout << "NO" << endl;
        }
    }
    return 0;
}
// */
//----------------------------------------------------------------------------------------
// 3 Binomial Coefficient = Number of ways to choose k out of n objects
// Time Complexity, T(n,k) = O(nk)
// Space Complexity, S(n,k) = O(k)
//-----------------------------------
/* 
#include <vector>
#include<iostream> 
using namespace std; 

// T(n,k) = O(n + k) , S(n,k) = O(1)
// Problem with this solution is that you are multiplying a number by itself to be very huge, so may have overflow.
// Thus, use dynamic programming instead
int binomialCoeffOverflow(int n, int k)
{
    if (k > n || k < 0 || n < 0) return 0; 
    if(k == 0 || k == n) return 1;
    int nFact = 1; 
    int kFact = 1;
    for(int i = 1; i <= n; i++)
        nFact *= i;
    for(int i = 1; i <= k; i++)
        kFact *= i;
    for(int i = 1; i <= n-k; i++)
        kFact *= i;
    return nFact/kFact;
}

// Note: f(n,k) = f(n-1,k-1) + f(n-1,k)
int binomialCoeffDynamic(int n, int k)
{
    if(k > n || k < 0 || n < 0 ) return 0;
    if(k == 0 || k == n) return 1;
    vector<int> arr(k+1, 1); // n = 1 => 1 way to choose 0 objects out of n, so initialize all to 1
    for(int i = 1; i <= n; i++)
    {
        // k cannot exceed n
        for(int j = min(k,i); j >= 0; j--) // j == 0 => 1 way which is already initialize
        {
            if(j == i || j == 0)
                arr[j] = 1;
            else
                // arr[j-1] => f(n, k-1)
                // arr[j] => f(n-1,k-1)
                arr[j] = arr[j-1] + arr[j];
        }
    }
    return arr[k];
}

int main(void)
{
    int n = 5;
    int k  = 3; 
    int result = binomialCoeffOverflow(n,k);  // 10
    cout << result << endl;
    result = binomialCoeffDynamic(n,k);  // 10
    cout << result << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------
// 4 SquareRoot(int x), where x > 0 
// Time Complexity, T(n) = O(logn)
// Space Complexity, S(n) = O(1)
//-----------------------------------
/* //
Questions: 
    1. Do I need to return both (+) and (-) solutions ? 
    2. Do I return a double or integer? If integer, then x = 8 should return 2 or 3? 
    3. For double, what is the precision needed
Function Prototype: 
    double SquareRoot(int x);
Test_case: 
    9 => 3,-3
    144 => 12, -12
    8 => 2.828
Algorithm: 
    a*a = a^2, thus, do binary search to search for the solution 
    Solved!=D 
    T(n)= O(lgn), S(n) = O(1) , lgN only if  final result is integer, otherwise, depends on precision needed
Implement!
Test!
*/
//-----------------------------------
/* //
#include <cmath> // for abs()
#include <iostream> 
using namespace std;
double SquareRoot(int x)
{
    double low = 0; 
    double high = x; 
    double mid = (low+high)/2;
    double midSqr = mid*mid; 
    while ( abs((midSqr) - x) >= 0.001)
    {
        if(midSqr > x)
        {
            high = mid; 
        }
        else
        {
            low = mid;
        }
        mid = (low+high)/2;
        midSqr = mid*mid; 
    }
    return mid; 
}

int main(void)
{
    int x = 9; 
    double result = SquareRoot(x); 
    cout << "Square Root of " << x << " is: " << result << endl; // 3
    x = 144; 
    result = SquareRoot(x); 
    cout << "Square Root of " << x << " is: " << result << endl; // 12
    x = 8;
    result = SquareRoot(x); 
    cout << "Square Root of " << x << " is: " << result << endl; // 
    return 0;
}
// */
//----------------------------------------------------------------------------------------
// 5 Replace every # x with # y given an integer
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
//-----------------------------------
/*
Questions: 
    1. Can integer be (-) ? 
Function Prototype:
    int replaceNum(int input, int x, int y); 
TestCases:
    input = 1003405, x = 0, y = 6 => output = 1663465
    input = 0, x = 0, y = 6 => 6;
*/
//-----------------------------------
/* //
#include <iostream> 
using namespace std; 

int replaceNum(int input, int x, int y)
{
    // Base Case
    if(input == 0 && input == x) return y; 
    int copyInput = input;
    int output = 0;
    int multiple = 1;
    if(input < 0) input *= -1; // MISTAKE: Must always convert to (+) in order to use % operator properly
    while(input)
    {
        int curr = input%10; 
        if(curr == x) curr = y;
        output += curr * multiple;
        input /= 10;
        multiple *= 10;
    }
    if (copyInput < 0) output *= -1;
    return output;
}

int main(void)
{
    int input = -1003405; 
    int x = 0; 
    int y = 6; 
    int result = replaceNum(input, x, y);
    cout << result << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------
