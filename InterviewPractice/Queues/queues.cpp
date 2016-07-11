//
//----------------------------------------------------------------------------------------
/* //
Table of Contents
1. Find Maximum of Every Contiguous k Subarray Elements in An Array, T(n,k) = O(n), S(n,k) = O(k)

TODO: Implement LRU Cache
// */
//----------------------------------------------------------------------------------------
/* //
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
//-------------------------------------------
// Common Questions
//-------------------------------------------
    Is it a double ended queue or single ended queue? 
// */
//----------------------------------------------------------------------------------------
// 1 Find Maximum of Every Contiguous k Subarray Elements in An Array
// Time Complexity, T(n,k) = O(n)
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
Algorithm:
    Solution 1: Push and pop from queue, checking queue each iteration, T(n,k) = O(nk), S(n,k) = O(k)
        (n iteration), each iteration need O(k) to check max)
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
Implement!
Test!
*/
//-------------------------------------------
/* //
#include <deque>
#include <algorithm> // std::min()
#include <vector>
#include <iostream>
using namespace std;

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

vector<int> MaxContiguousSubarrayElements(const vector<int>& arr, int numContiguousElement)
{
    vector<int> solution;
    if(arr.empty() || numContiguousElement <= 0) return solution;
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
    vector<int> solution = MaxContiguousSubarrayElements(arr, numContiguousElements);
    for(int val : solution) cout << val << " ";
    cout << endl;
}

int main(void) 
{
    vector<int> empty;
    vector<int> single = {1};
    vector<int> normal = {1, 3, 2, 4};
    printSolution(empty, 100);
    printSolution(single, 100); // [1]
    printSolution(normal, 2); // [3, 3, 4]
    printSolution(normal, 3); // [3, 4]
    printSolution(normal, 10); // [4]
    return 0;
}
// */
//----------------------------------------------------------------------------------------
