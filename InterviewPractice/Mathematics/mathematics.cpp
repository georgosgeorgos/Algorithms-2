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
/* //
// 1. Implement pow(double, int)
// Time Complexity: O(logN)
// Space Complexity: O(1)
// Calculate pow(double, int n), where n can be (-), 0 , (+)  T(n) = O(logN), S(n) = O(logN)
#include <math.h>
#include <iostream>
using namespace std;

double power(double a, int n);

int main(void)
{
    int k = 3;
    double m = 4.0;
    double result = power(m, k);
    cout << result << endl;
    k = -3;
    m = 2.0;
    result = power(m, k);
    cout << result << endl;
}

double power(double a, int n)
{
    if ((n == 0) || (a == 1))
        return 1;
    if (n > 0)
    {
        double b = power(a, floor(n/2));
        if (n%2 == 0)
        {
            return b*b;
        }
        else
        {
            return b*b*a;
        }
    }
    else
    {
        double b = power(a, -floor(n/2));
        if (n%2 == 0)
        {
            return 1.0/(b*b);
        }
        else
        {
            return 1.0/(b*b*a);
        }
    }
}
// */
//----------------------------------------------------------------------------------------
// 2 Euclid's Algorithm: Calculate GCD  
//----------------------------------------------------------------------------------------
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
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
