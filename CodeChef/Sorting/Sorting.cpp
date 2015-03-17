/* 
 * Table of Contents
 * 1. OrderingTheSoliders, T(n) = O(n), S(n) = O(n) 
 *
 *
 * Time Complexity, T(n) = O(n)
 * Space Complexity, S(n) = O(n) 
 *
 */


//------------------------------------------------------------
// 1 OrderingTheSoldiers

// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(n) 
// Note: Not passing all test cases, may need to use trees to get O(nlgn) solution
// Firstly, create a bunch of test cases and test your program below! 

#include <iostream> 
using namespace std; 

int main(void)
{
    long long int T;
    long long int N;
    cin >> T; // get number of testcases
    for(long long int i = 0; i < T; i++)
    {
        // get number of values 
        cin >> N;
        long long int sortedArray[N];
        long long int position[N];
        long long int finalArray[N]; 
        for(long long int j = 0; j < N; j++)
        {
            cin >> sortedArray[j];
            position[j] = j;// initialize to respective positions 
            finalArray[j] = 0; // initialiaze all to 0
        }
        // now update the array, O(n)
        for(long long int j = N-1; j >= 0; j--)
        {
            long long int newPos = j-sortedArray[j]; 
            finalArray[position[newPos]] = j+1; // add 1 since rank is 1-based not 0 based 
            position[newPos]++; // update so that next time something comes here, it moves 1 to the right 
        }
        for(long long int j = 0; j < N; j++)
        {
            // Output the answer 
            cout << finalArray[j] <<" ";
        }
        cout << endl; 
    }
}







