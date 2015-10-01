//----------------------------------------------------------------------------------------
/*
Table of Contents
1. Given an array of integers, every element appears twice except for two. Output both elements . T(n) = O(n), S(n) = O(1)


//----------------------------------------------------------------------------------------
TODO: 
10. Count first occurence of leading 1 in a variable (Qualcomm interview) // (done in leetcode)

2.Check if a number is a power of 2
// Hint: ((n&1 == 0) only tells you it is even, use (n&(n-1))to find if it is power of 2 (done in leecode)

3. Write function to determine number of bit swap required to convert integer A to integer B

4. Write program to swap odd and even bits in an interger with the fewest instructions (O(1))
// e.g. bit 0 and bit 1 swapped, bit 2 and bit 3 swapped

HARD: 6. SingleNumberII: Given an array of 3n + 1 elements, where n of elements are repeated thrice each, and 1 element is different from the rest. Identify that one element.
7. SingleNumberIII: Given an array of kn + 1 elements, where n of elements are repeated k times each, k > 1, and 1 element is different from the rest. Identify that one element.
    Create an array of 32/64 slots. 
    Add each 1 bit separately in each array slots. 
    Then mod each array slot by k. If remainder is NOT 0, then that bit has to be a 1 in the special element. 
    Then, output that special element from the arrays. 
8. 
The gray code is a binary numeral system where two successive values differ in only one bit.
Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.
For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
00 - 0
01 - 1
11 - 3
10 - 2
    hint: Go forwards, then when end, append a 1, and go backwards, all the way, needs some form of recursion. 
    betterHint: BinaryToGrey => (num>>1 ^ num)
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Given an array of integers, every element appears twice except for two. Output both elements . T(n) = O(n), S(n) = O(1)
/*
Questions:
    Can the original vector be modified? 
    Is there a limit to the number of integers given? No
    Can the integers be (-) ? Yes
    How large can the integers be? (use counting sort and then can do a pass with O(n) timing.)
        As large as can be represented in memory 
    Can the same number appear 2z times instead of twice? where z is an integer > 0	
        Yes
    Are the inputs sorted already? 
        No 
Test cases: 
    232536
    37
*/
//---------------------------------
/* //
#include <vector> 
#include <iostream> 
using namespace std;
 
int firstLeadingOne(int x)
{
int shift = 0; 
	int remain = x; 
	int leadOne = remain & 1; 
	if(leadOne) return shift;
	while(remain)
	{
		shift++; 
		remain = remain >> 1; 
		int leadOne = remain & 1; 
		if(leadOne) return shift;
	}
}

void outputBothUnique(vector<int>& a)
{
    int both = 0; 
    for(int i = 0; i < a.size(); i++)
    {
        both = both ^ a[i]; 
    }
    // Here, as long as both numbers are different, 
    // it will xor them separately
    int shift = firstLeadingOne(both); 
    int first = 0; 
    int second = 0; 
    int andValue = 1 << shift; 
    for(int i = 0; i < a.size(); i++)
    {
        if(a[i] & andValue)
        {
            first = first ^ a[i]; 
        }
        else
        {
            second = second ^ a[i]; 
        }
    }
    cout << first << " " << second << endl;
}
int main(void)
{
    vector<int> vec(2, 0); 
    vec[0] = 2;
    vec[1] = 4;
    outputBothUnique(vec);
    
    return 0; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
