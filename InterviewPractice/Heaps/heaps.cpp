//----------------------------------------------------------------------------------------
// 4 Prim's Algorithm
// TODO: THIS IS TOO MUCH IMPLEMENTATION, DON'T THINK CAN FIT IN 1 INTERVIEW SLOT, YES YOU CAN! JUST PRACTICE IMPLEMENTING 10 TIMES
//       CAN IF YOU USE STL's PRIORITY_QUEUE 
//----------------------------------------------------------------------------------------
/* 
1. BuildHeap, converts an unsorted array into a Binary Heap, T(n) = O(n), S() = O(1)
2. HeapSort, T(n) = O(nlogn), S(n) = O(1)
//-------------------------
TODO:
4. Prims Algorithm
3. Find the kth largest elements from a heap, T(n) = O(klogk), S(n) = O(k) 
Binary Heap
Binomial Heap 
B-Heap 
Fibonacci Heap 
Treap 
5. A* search (you maintain the next best node in the queue using a heap)
etc. (refer to wikipedia)

//-------------------------
// priority_queue
//-------------------------
#include <iostream> // cout
#include <vector> // for vector<int>
#include <functional> // for greater<int>
#include <queue> // for priority_queue<int>
using namespace std; 
int main(void)
{
    priority_queue<int> maxHeap; 
    maxHeap.push(20);
    maxHeap.push(10);
    maxHeap.push(40);
    while(!maxHeap.empty()) // outputs 40,20,10 since it's maxHeap
    {
        cout << maxHeap.top() << endl;
        maxHeap.pop();
    }

    priority_queue<int, vector<int>, greater<int> > minHeap;
    minHeap.push(20);
    minHeap.push(10);
    minHeap.push(40);
    while(!minHeap.empty()) // outputs 10,20,40 since it's maxHeap
    {
        cout << minHeap.top() << endl;
        minHeap.pop();
    }
    return 0;
}
// */
//----------------------------------------------------------------------------------------
// 1 BuildHeap, converts an unsorted array into a Binary Heap 
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
//-------------------------
/* //
#include <cmath> // for log2()
#include <iostream> 
using namespace std; 

// true => Build a max heap, false => Build a min heap
int * buildHeap(int * a, int size, bool maxOrMin); 
int * heapify (int * a, int index, int size, bool maxOrMin);
void swap(int* a, int* b);

int main(void)
{
    int n = 10;
    int * a = new int[n];
    for (int i = 0; i < n; i++)
    {
        if (i%2)
            a[i] = i * 3; 
        else 
            a[i] = i * 2; 
                
    }
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    cout << "Building Max Heap" << endl;
    buildHeap(a, n, true); 
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    cout << "Building Min Heap" << endl;
    buildHeap(a, n, false); 
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0; 
}
// O(n) 
// Note: The reason that the complexity is O(n) instead of O(NlogN) is because 
// only at the node that you traverse O(logN) nodes in the worst case whereas the finalIndex you will traverse only 1 node
// Therefore, you traverse:  logN + (logN - 1) + (logN - 2) + ... + 1 in the worst case. 
// This sums up to N(logN) - ( 1 + 2 + ... + (logN-1)) 
// At each level, i (root node is level = 1), the maximum number of nodes at that level is  (N+1)/((2^i) + 1)
// Cost of heapify  at height, i is at most i 
// Doing the calculations, you will find that the worst case complexity is O(N) instead.  
// Refer to this for more information: http://www.dgp.toronto.edu/people/JamesStewart/378notes/08buildheap/ 

int * buildHeap(int * a, int size, bool maxOrMin)
{
    // calculate finalIndex that you need to begin with since there is no point starting from the leaves
    int finalIndex = floor(log2(size));  
    finalIndex = pow(2,finalIndex) - 2;
    for (int i = finalIndex; i >= 0; i--)
    {
        // heapify from that index onwards
        a = heapify(a, i, size, maxOrMin);
    }
    return a; 
}

// Assumes the binary heap below this node is indeed a binary heap 
// T(n) = O(logn)
int * heapify (int * a, int index, int size, bool maxOrMin)
{
    // Get index of left and right child
    int left = 2*index + 1; 
    int right = 2*index + 2; 
    // Mistake: Declared smallest and largest within if statement instead of here so that below can access
    int smallest = -1;
    int largest =  -1;
    if(left < size && right < size) 
    {
        // if want largest to be on top 
        if (maxOrMin)
        {
            int larger = a[left] >= a[right] ? left : right;
            largest = a[index] >= a[larger] ? index : larger;
        }
        else 
        {
            int smaller = a[left] <= a[right] ? left : right;
            smallest = a[index] <= a[smaller] ? index : smaller;
        }
    }
    else if (left < size) 
    {
        if (maxOrMin)
        {
            largest = a[index] >= a[left] ? index : left;
        }
        else 
        {
            smallest = a[index] <= a[left] ? index : left;
        }
    }
    else if (right < size) 
    {
        if (maxOrMin)
        {
            largest = a[index] >= a[right] ? index : right;
        }
        else 
        {
            smallest = a[index] <= a[left] ? index : left;
        }
    }
    // Else, if no child, just return it
    else 
    {
        return a;
    }
    // If has any child
    if (maxOrMin)
    {
        if(largest != index) 
        {
            swap (&a[largest], &a[index]);
            // Recursively heapify 
            heapify(a, largest, size, maxOrMin);
        }
        // Return a at the end
        return a; 
    }
    else
    {
        if(smallest != index) 
        {
            swap (&a[smallest], &a[index]);
            // Recursively heapify 
            heapify(a,smallest, size, maxOrMin);
        }
        return a; 
    }
}

void swap(int* a, int* b)
{
    int temp = *a; 
    *a = *b;
    *b = temp;
    return;
}
// */
//----------------------------------------------------------------------------------------
// 2 HeapSort
// Time Complexity, T(n) = O(nlogn)
// Space Complexity, S(n) = O(1)
//-------------------------
/* //
#include <cmath> // for log2()
#include <iostream> 
using namespace std; 

// true => sort ascending order, false => sort descending order
int * heapSort(int * a, int size, bool ascOrDesc);
// true => Build a max heap, false => Build a min heap
int * buildHeap(int * a, int size, bool maxOrMin); 
int * heapify (int * a, int index, int size, bool maxOrMin);
void swap(int* a, int* b);

int main(void)
{
    int n = 10;
    int * a = new int[n];
    for (int i = 0; i < n; i++)
    {
        if (i%2)
            a[i] = i * 3; 
        else 
            a[i] = i * 2; 
                
    }
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    cout << "Sort ascending" << endl;
    heapSort(a,n,true);
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    cout << "Sort descending" << endl;
    heapSort(a,n,false);
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0; 
}

int * heapSort(int * a, int size, bool ascOrDesc)
{
    // First, build a heap. 
    // If ascending, need to build a maxHeap, if descending, need to build a minHeap
    buildHeap(a, size, ascOrDesc);
    // Now, sort it 
    for(int i = size - 1; i >= 0; i--)
    {
        // first swap the root element (currMax) with the last,
        swap(&a[0], &a[i]);
        // and heapify the root element downwards
        heapify(a, 0, i, ascOrDesc);
    }
    return a;
}

// O(n) 
int * buildHeap(int * a, int size, bool maxOrMin)
{
    // calculate finalIndex that you need to begin with since there is no point starting from the leaves
    int finalIndex = floor(log2(size));  
    finalIndex = pow(2,finalIndex) - 2;
    for (int i = finalIndex; i >= 0; i--)
    {
        // heapify from that index onwards
        a = heapify(a, i, size, maxOrMin);
    }
    return a; 
}

// Assumes the binary heap below this node is indeed a binary heap 
// T(n) = O(logn)
int * heapify (int * a, int index, int size, bool maxOrMin)
{
    // Get index of left and right child
    int left = 2*index + 1; 
    int right = 2*index + 2; 
    // Mistake: Declared smallest and largest within if statement instead of here so that below can access
    int smallest = -1;
    int largest =  -1;
    if(left < size && right < size) 
    {
        // if want largest to be on top 
        if (maxOrMin)
        {
            int larger = a[left] >= a[right] ? left : right;
            largest = a[index] >= a[larger] ? index : larger;
        }
        else 
        {
            int smaller = a[left] <= a[right] ? left : right;
            smallest = a[index] <= a[smaller] ? index : smaller;
        }
    }
    else if (left < size) 
    {
        if (maxOrMin)
        {
            largest = a[index] >= a[left] ? index : left;
        }
        else 
        {
            smallest = a[index] <= a[left] ? index : left;
        }
    }
    else if (right < size) 
    {
        if (maxOrMin)
        {
            largest = a[index] >= a[right] ? index : right;
        }
        else 
        {
            smallest = a[index] <= a[left] ? index : left;
        }
    }
    // Else, if no child, just return it
    else 
    {
        return a;
    }
    // If has any child
    if (maxOrMin)
    {
        if(largest != index) 
        {
            swap (&a[largest], &a[index]);
            // Recursively heapify 
            heapify(a, largest, size, maxOrMin);
        }
        // Return a at the end
        return a; 
    }
    else
    {
        if(smallest != index) 
        {
            swap (&a[smallest], &a[index]);
            // Recursively heapify 
            heapify(a,smallest, size, maxOrMin);
        }
        return a; 
    }
}

void swap(int* a, int* b)
{
    int temp = *a; 
    *a = *b;
    *b = temp;
    return;
}
// */
//----------------------------------------------------------------------------------------
