//
//----------------------------------------------------------------------------------------
/*  //
Table of Contents

1. Calculate pow(double, int n), where n can be (-), 0 , (+)  T(n) = O(logN), S(n) = O(logN)

2. Euclid's Algorithm: Calculate GCD, T(n) = O(n), S(n) = O(1)

//----------------------------------------------------------------------------------------
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

10. Determine whether an integer is a paindrome 
    12321 => True
    -12321 => False
    T(n) = O(n) S(n) = O(1)

11. 


// */
//----------------------------------------------------------------------------------------
// 1. Calculate pow(double, int n), where n can be (-), 0 , (+)
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
//----------------------------------------------------------------------------------------
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
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
//----------------------------------------------------------------------
