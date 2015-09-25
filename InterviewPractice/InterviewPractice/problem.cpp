// This file generates a random question to solve
// No databases needed
#include <ctime> 
#include <cstdlib>
#include <vector> 
#include <iostream> 
using namespace std; 

int main(void)
{
    vector<string> p;
    p.push_back("Search: Binary Search (personal and bsearch())");
    p.push_back("Sort: Randomized QuickSort Array (personal and qsort())");
    p.push_back("Sort: MergeSort Array");
    p.push_back("Heap: HeapSort");
    p.push_back("Heap: A* Search");
    p.push_back("Heap: Get Top K heap elements");
    p.push_back("Graphs: Finding Connected components using BFS & DFS");
    p.push_back("Graphs: Topological Sort using DFS with timestamp");
    p.push_back("Disjoint Set: Kruskal Algorithm");
    p.push_back("Linked List: Reverse a Linked List");
    p.push_back("Linked List: Insert a node to a circular sorted linked list");
    p.push_back("Array: Kadane's Algorithm for Maximum Subarray Problem");
    p.push_back("MultidimensionalArray: Traverse an array spirally");
    p.push_back("MultidimensionalArray: Rotate an image 90 degrees in place");
    p.push_back("DynamicProgramming: Calculate Nth Fibonacci Number");
    p.push_back("Strings: Remove duplicated character from string in place, e.g. abaaaacccead => abced");
    p.push_back("Sort: Radix Sort");
    p.push_back("Mathematics: Implement Pow() function");
    p.push_back("DynamicProgramming: Longest Common Subsequence between 2 strings");
    p.push_back("BitManipulation: Count first occurence of leading 1 in a variable");
    p.push_back("Prims Algorithm");
    p.push_back("Djikstra Algo.");
    p.push_back("Bellman Ford algorithm");
    p.push_back("Floyd Warshall Algo.");
    p.push_back("String:Knuth Morris Pratt");
    p.push_back("String:Rabin Karp");
    p.push_back("N-ary Tree:");
    p.push_back("Trie Tree:");
    p.push_back("Avl Tree Double Traversal for balancing");
    p.push_back("BinaryIndexedTree/FenwickTree: Count consecutive sums efficiently");
    cout << p.size() << endl;
    srand(time(NULL));
    int random = rand() % p.size();
    cout << p[random] << endl;
    return 0;
}
