// Ignore this, it's useless to do this once you have full-time offer at a company and not planning to move to a new company. 
// This file generates a random question to solve
#include <ctime> 
#include <cstdlib>
#include <vector> 
#include <iostream> 
using namespace std; 

int main(void)
{
    // TODO: Add design pattern challenges as designing each class with an example, also other challenges like designing URL shortener etc. 
        // Anything that seems reasonable to design in an interview of 45 minutes
    vector<string> p;
    p.push_back("Search: Binary Search (personal and bsearch())");
    p.push_back("Sort: Randomized QuickSort Array (personal and qsort())");
    p.push_back("Sort: MergeSort Array");
    p.push_back("Search: Search for element in rotated sorted array with distinct elements"); // need rotated problem
            // Hint: Find index of rotation first, k. Then search for element knowing index of rotation.  
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
    p.push_back("BitManipulation: Given an array of 2n + 2 integers where n of them are repeated twice and 2 of them are unique, output the 2 unique integers");
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
