//----------------------------------------------------------------------------------------------------------------------------------
/*
1. Given an array of integers, every element appears twice except for one. Find that single one. T(n) = O(n), S(n) = O(1)
2. Given an array of integers, every element appears twice except for two. Output both elements . T(n) = O(n), S(n) = O(1)
3. Given an array of integers, find two numbers such that they add up to a specific target number. T(n) = O(nlogn), S(n) = O(1)
//---------------------------------
TODO: 
note: 
The difference with using LeetCode is you also practice:
    Asking questions about the problem. Can there be (-) index
    What exactly does reference indexing mean? 
ALWAYS: 
    Questions:  Clarify problem, check assumptions, int(limit? (-)? number of integers? can modify array?, repeated? )
        -
        -
        -
    Test Case: Give a simple test case that covers edge cases (so fewer numbers but covers enough), give the basic test case , n = 1
        - 
        -
        -
    Algorithms: Discuss the different methods to solve and complexity. 
        Sort(nlgn), ... 
        Heap().... 
        HashTable()... 
    Check algorithm by running input over it and finding error code. 
*/
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Given an array of integers, every element appears twice except for one. Find that single one. T(n) = O(n), S(n) = O(1)
/*
Questions:
    Is there a limit to the number of integers given? No
    Can the integers be (-) ? Yes
    How large can the integers be? (use counting sort and then can do a pass with O(n) timing. 
        As large as can be represented in memory 
    Can the same number appear 2z times instead of twice? where z is an integer > 0	
        Yes
    Are the inputs sorted already? 
        No 
Test cases: 
    23253
    1
*/
//---------------------------------
/*
#include <iostream> 
#include <cstdlib> 
#include <cstdio> 
#include <vector>
#include <algorithm> 
using namespace std;

int returnSingle(vector<int>& nums)
{
    int single = 0; 
    for(int i = 0; i < nums.size(); i++)
    {
        single = single ^ nums[i];
    }
    return single; 
}
int main(void)
{
	vector<int> a(5,0); 
	a[0] = 2; 
	a[1] = 3; 
	a[2] = 2; 
	a[3] = 5; 
	a[4] = 3; 
	int result = returnSingle(a); 
	cout << result << endl;
	return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 2 Given an array of integers, every element appears twice except for two. Output both elements . T(n) = O(n), S(n) = O(1)
/*
Questions:
    Can the original vector be modified? 
    Is there a limit to the number of integers given? No
    Can the integers be (-) ? Yes
    How large can the integers be? (use counting sort and then can do a pass with O(n) timing. 
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
// 3 Given an array of integers, find two numbers such that they add up to a specific target number.
// Time Complexity, T(n) = O(nlgn + n) = O(nlgn) , S(n) = O(1)
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
 // 
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
