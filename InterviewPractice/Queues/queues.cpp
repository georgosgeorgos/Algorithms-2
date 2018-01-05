//
//----------------------------------------------------------------------------------------
/* //
Table of Contents
1. Find Maximum of Every Contiguous k Subarray Elements in An Array, T(n,k) = O(2n), S(n,k) = O(k)

TODO: Implement LRU Cache
// */
//----------------------------------------------------------------------------------------
/* //
note: QUEUE PUSHES TO BACK AND POPS FROM FRONT!
#include <queue>
    // q.empty()
    // q.size()
    // q.push(value) // push to end(back) of queue
    // q.pop() // pop from front of queue, returns void
    // q.front() // returns reference to the front element
    // q.back() // returns reference to the back element (last element added
#include <string>
#include <iostream>
using namespace std;
int main(void)
{
    queue<string> q;
    string temp = "hahaha";
    string temp2 = "baba";
    q.push(temp);
    if(!q.empty())
    {
        cout << q.front() << endl;
        cout << q.back() << endl;
    }
    q.pop();
    if(q.empty())
    {
        cout << "queue is now empty" << endl;
    }
    q.push(temp);
    q.push(temp2);
    cout << "number of elements in queue is " << q.size() << endl;
    return 0;
}
//-------------------------------------------
#include <deque>
   deque.push_front(2); 
   deque.push_back(3); 
   int three = deque.back();  // returns reference to back element
   int two = deque.front();  // returns reference to front element
   deque.pop_front(); 
   deque.pop_back(); 
Deque = Double Ended Queue => Queue + Stack 
//-------------------------------------------
// Common Hints
//-------------------------------------------
    Instead of storing the values, try storing the indices. 
    Instead of strong everything, only store the values you need.
//-------------------------------------------
// Common Questions
//-------------------------------------------
    Is it a double ended queue or single ended queue? 
// */
//----------------------------------------------------------------------------------------
// 1 Find Maximum of Every Contiguous k Subarray Elements in An Array
// Time Complexity, T(n,k) = O(2n)
// Space Complexity, S(n,k) = O(k)
//-------------------------------------------
/*
Questions:
    What does it store? int
    Are the values sorted? No
    Can the values be repeated? Yes
    What if k bigger than array? Then, just list biggest element in array
    Can k be <= 0? No
Function Prototype:
    vector<int> MaxContiguousSubarrayElements(const vector<int>& arr, int numContiguousElements);
TestCases:
    [], k = anything => []
    [1], k >= 1 => [1]
    [1, 3, 2, 4], k = 2 => [3, 3, 4]
                  k = 3 => [3, 4]
                  k = 10 => [4]
    [8, 2, 5, 4, 3], k = 4 => [8, 5] // next largest is in middle, which is 5
Algorithm:
    Solution 1a: Push and pop from queue, checking queue each iteration, T(n,k) = O(nk), S(n,k) = O(k)
        (n iteration), each iteration need O(k) to check max)
    Solution 1b:
        Don't even need a queue, just double loop through array brute force,T(n,k) = O(nk) S(n,k) = O(1)
    Solution 2: Use a balanced BST, T(n,k) = O(nlogk), S(n,k) = O(k)
        Assuming k <= n;
        Insert k elements => T(n,k) = O(klogk), S(n,k) = O(k)
            for(int i = 0; i < k; i++)
                BalancedBST.insert(arr[i]);
        For every new element
            Get max T(n,k) = O(1)
                solution.push_back(BalancedBST.getRoot());
            Delete k elements before BST & insert new element
                for(int i = k; i < n; i++) 
                 BalancedBST.delete(arr[i-k]);
                 BalancedBST.insert(arr[i]);
    Solution 3: Dequeue (can push or pop from both ends) 
        Time Complexity, T(n, k) = O(n), Space Complexity, S(n,k) = O(k)
        Hint: Store the indices!
        Can always pop whatever that is smaller than current window
        But must always keep track whatever smaller than later window
        Get rid by popping the larger elements that have lower indices than (current iteration - k)
        Note: The time complexity is at worst 2n since for each element 
        you will at most add them once and pop them once, so 2n is worst case, T(2n) = T(n) 
Implement!
Test!
*/
//-------------------------------------------
/* //
#include <deque>
#include <queue>
#include <algorithm> // std::min()
#include <vector>
#include <iostream>
using namespace std;

vector<int> MaxContiguousSubarrayElements(const vector<int>& arr, int numContiguousElement)
{
    vector<int> solution; 
    if (arr.empty() || numContiguousElement <= 0) return solution;
    // Ensure we do not loop pass the array's size
    numContiguousElement = min(numContiguousElement, (int) arr.size());
    // A queue that stores the current maximum at the end of the queue 
    // end is the front of the queue in C++ STL's #include <queue>
    queue<int> currMaxSoFarAtEnd; 
    // Initialize the queue for the first interval
    for (int i = 0; i < numContiguousElement; i++)
    {
        currMaxSoFarAtEnd.push(arr[i]); // pushes to back of queue
        // note: Add duplicates if they exist, use '<' instead of '<='
        while(currMaxSoFarAtEnd.front() < arr[i])
        {
            currMaxSoFarAtEnd.pop(); // pops from front of queue
        }
    }

    // Append the current maximum of the first interval
    solution.push_back(currMaxSoFarAtEnd.front());

    // For every remaining intervals
    for (int currStartIndex = 1; currStartIndex + numContiguousElement - 1 < arr.size(); currStartIndex++) 
    {
        int deletedIndex = currStartIndex - 1;
        // Get rid of outdated maximum
        if (currMaxSoFarAtEnd.front() == arr[deletedIndex]) currMaxSoFarAtEnd.pop();
        // Add the new item
        int currLatestItemIndex = currStartIndex +  numContiguousElement - 1;
        currMaxSoFarAtEnd.push(arr[currLatestItemIndex]);
        // Get rid of non-maximum 
        // note: Add duplicates if they exist, so use '<' instead of '<='
        while(currMaxSoFarAtEnd.front() < arr[currLatestItemIndex])
        {
            currMaxSoFarAtEnd.pop();
        }
        // Append the current maximum of the interval
        solution.push_back(currMaxSoFarAtEnd.front());
    }
    return solution;
}

// Gets rid of the smaller values from older indexes from back
void getRidOfOlderSmallerFromBack(const vector<int>& arr, const int& currentVal, deque<int>& maxOfInterval)
{
    while ((!maxOfInterval.empty()) && (arr[maxOfInterval.back()] <= currentVal))
        maxOfInterval.pop_back();
}

void getRidOfOutdatedFromFront(const int& oldestIndex, deque<int>& maxOfInterval)
{
    while (!maxOfInterval.empty() && maxOfInterval.front() < oldestIndex)
        maxOfInterval.pop_front();
} 

vector<int> MaxContiguousSubarrayElementsWrong(const vector<int>& arr, int numContiguousElement)
{
    // LOL, this is WRONG! It fails the test case below
    // vector<int> nextLargestInMiddle = {8, 2, 5, 4, 3} with numContiguousElement = 4
    // should return 8, 5. 
    // You fixed it with the latest implementation that is much better than this.
    vector<int> solution;
    if (arr.empty() || numContiguousElement <= 0) return solution;
    // Front stores the largest element in current interval, back stores the smallest element in current interval
    // It doesn't store the actual value, but the indices of the values from the arr
    // Thus, to get the current maximum, do arr[maxOfInterval.front()];
    deque<int> maxOfInterval;
    int i = 0;
    int sizeInInt = arr.size();
    for (; i < min(numContiguousElement, sizeInInt); i++) // Error! min(numContiguousElement, arr.size()) doesn't work because comparing (int, unsigned long)
    {
        getRidOfOlderSmallerFromBack(arr, arr[i], maxOfInterval);
        // It is guaranteed that arr[i] < arr[maxOfInterval.front()] cause you would have pop_back() it if it wasn't
        maxOfInterval.push_back(i);
    }
    // Loop through each window
    for (; i < arr.size(); i++)
    {
        // Add the solution for last window as it would currently be the front of maxOfInterval
        solution.push_back(arr[maxOfInterval.front()]);
        // Get rid of outdated maximum from the front
        getRidOfOutdatedFromFront(i - numContiguousElement, maxOfInterval);
        getRidOfOlderSmallerFromBack(arr, arr[i], maxOfInterval);
        // It is guaranteed that arr[i] < arr[maxOfInterval.front()] cause you would have pop_back() it if it wasn't
        maxOfInterval.push_back(i);
    }
    // Add the solution for the last window 
    solution.push_back(arr[maxOfInterval.front()]);
    return solution;
}

void printSolution(vector<int>& arr, int numContiguousElements) 
{
    cout << "Input: [ ";
    for (auto val : arr) cout << val << " ";
    cout << "], numContigous = " << numContiguousElements << " => ";
    vector<int> solution = MaxContiguousSubarrayElements(arr, numContiguousElements);
    for(auto val : solution) cout << val << " ";
    cout << endl;
}

int main(void) 
{
    vector<int> empty;
    vector<int> single = {1};
    vector<int> normal = {1, 3, 2, 4};
    vector<int> nextLargestInMiddle = {8, 2, 5, 4, 3};
    printSolution(empty, 100);
    printSolution(single, 100); // [1]
    printSolution(normal, 2); // [3, 3, 4]
    printSolution(normal, 3); // [3, 4]
    printSolution(normal, 10); // [4]
    printSolution(nextLargestInMiddle, 4); // [8, 5]
    return 0;
}
// */
//----------------------------------------------------------------------------------------
