//----------------------------------------------------------------------------------------
/* 
1 Implement BuildHeap, which converts an unsorted array into a Binary Heap, T(N) = O(N), S(N) = O(1)

TODO:
2. Implement a Heap with Arrays 
    // If index starts from 0
    parent  = floor(i/2 - 1/2)
    leftChild = 2i + 1 
    rightChild = 2i + 2
3. Implement HeapSort() 
4. Find kth largest elements from an array , T(n) = O(klogk), S(n) = O(k) 

Implement Heapify() T(n) = O(logN)
5. Heapify
6. HeapSort

Binary Heap
Binomial Heap 
B-Heap 
Fibonacci Heap 
Treap 
etc. (refer to wikipedia)
// */
//----------------------------------------------------------------------------------------
/* 
// 1 Implement BuildHeap, which converts an unsorted array into a Binary Heap 
// Time Complexity, T(N) = O(N)
// Space Complexity, S(N) = O(1)

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


// O(N) 
// Note: The reason that the complexity is O(N) instead of O(NlogN) is because 
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

