//----------------------------------------------------------------------------------------------------------------------------------
/* //
Table of Contents
1. Preorder traversal binary tree recursively. T(n) = O(n), S(n) = O(logn)
2. Preorder traversal binary tree iteratively. T(n) = O(n), S(n) = O(n)
3. Inorder traversal binary tree recursively. T(n) = O(n), S(n) = O(logn)
4. Inorder traversal binary tree iteratively. T(n) = O(n), S(n) = O(n)
5. Levelorder traversal binary tree iteratively. T(n) = O(n), S(n) = O(n)
6. ZigZag Traversal binary tree iteratively, T(n) = O(n), S(n) = O(n)
7. Output number of configurations of binary search tree given n distinct integers. T(n) = O(n), S(n) = O(n) (Dynamic Programming)
8. Find kth smallest element in BST, assuming k's value is valid (1->N), T(n) = O(n), S(n) = O(n)
9. Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
   Find total sum of all root-to-leaf numbers. T(n) = O(n), S(n) = O(n)
10. Flatten binary tree into linkedlist using preorder
11. Print binary tree as seen from right side of tree, T(n) = O(n), S(n) = O(n)
12. Populate next(sibling) pointers binary tree. T(n) = O(n), S(n) = O(n)
13. Balanced Binary Tree: Return true if difference in child's height is <= 1, false otherwise, T(n) = O(n), S(n) = O(n) 
14. Lowest Common Ancestor of Binary Tree, T(n) = O(n), S(n) = O(n)
15. Invert a binary tree side ways, T(n) = O(n), S(n) = O(n)
16. Serializing & De-Serializing a Binary Tree, T(n) = O(n), S(n) = O(n) (Facebook 2nd Phone Interview 2015)
17. Return random node in binary tree (Microsoft: girl, on-site Round 2b), T(n) = O(n), S(n) = O(n)
18. Sum level k nodes in binary tree (Bloomberg First Round), T(n) = O(n), S(n) = O(n)
//----------------------------------------------------------------------------------------------------------------------------------
TODO:
25. Determine if 2 binary trees are equal
    Question: 
        1. Are 2 trees which have totally equal structure and data equal? Or only if both trees point to exact same tree in memory?  
22. Invert binary tree up to down 
23. Given an array where elements are sorted in ascending order, convert it to a height balanced BST. (ECE345 Assignment)  
24. Validate if a binary tree is a Binary Search Tree. T(n) = O(n), S(n) = O(n) (Easy, just inorder traversal making sure more than previous
27. Given a sorted array in increasing order, write algorithm to create balanced binary search tree with minimal height 
    T(n) = O(n), S(n) = O(logn)
28. Given a sorted linkedlist in increasing order, write algorithm to create balanced binary search tree with minimal height
    T(n) = O(n), S(n) = O(logn)
29. Binary Tree Maximum Path Sum, all nodes contains integer values that may be (-) (HARD!)
    Find maximum sum between a path. 
    e.g. 
            1
           / \
          2   4 => Max is 4 + 1 + 2  + 3 = 10 
         / \
        2   3
    if all are(-), max path => Minimum (-) value => biggest value and NOT 0
30. Implement a Binary Tree
    Note: Making recursive inserts (if no need balancing and transfer by values to delete instead of actual node makes implementation a lot easier) 
32. Given a binary tree, create linked list of all nodes at each depth
(if have a tree with depth D, will have D linked list!)
33. Write algorithm to find the next node of a given node in a BST where each node has a link to the parent
36. Given 2 binary tree, where  BT1 > BT2 , decide if BT2 is a subtree of BT1.
37. Given a binary tree where each node contains a value. Design an algorithm to print all paths which sum up
to that value. Note: It can be any path in the tree and does not have to start at root (refer to coding interview)
38. Given the root of a binary tree and a node, return array of path from root to that node or NULL if that node is not in the tree
    Hint: Use stack, go down till find it, then push to stack once found and just keep pushing to stack if one of child found it
22. Serialize & De-Serialize a N-ary Tree
KD Tree
Cover Tree
//----------------------------------------------------------------------------------------------------------------------------------
// Notes:
//----------------------------------------------------------------------------------------------------------------------------------
#include <set> is a balanced binary search tree with single unique value elements, where value itself is used for indexing. 
multiset is similar to set but can contain duplicates.
e.g.
        2           2
       / \         / \
      1   3       2   3 
       set       multiset

#include <map> is a balanced binary search tree with a key,value pair, where the unique keys is used for indexing
multimap is similar to map but can contain duplicates
e.g. 
      (2,1)                    (2,1)
       / \                      / \
    (1,2) (3,4)              (2,3) (3,4)
       map                      multimap

Also, all set, multiset, map, multimap are binary search trees, which means they are sorted. 
Also, it is an augmented version, in the sense that it provides a way to iterate through it in linear time. 
This means every node points to its parent and there are 2 extra pointers, one pointer to the beginning and one pointing to the end
of the balanced binary search tree. 
This also means you can get the min() and max() in constant time. 
map.begin(); // returns iterator to first element which is the minimum in constant time
map.rbegin(); // reverse begin, returns iterator to last element which is maximum in constant time
So now, if you can get minimum and maximum in constant time, what are the benefits of using a heap over these anymore?
This is because if you are given an unsorted array of elements, building a heap is linear whereas building a BST is O(nlogn).
So if the questions ask you to get min() or max() of real-time incoming data, this augmented BST is better over heap.

For hashtables, used #include <unordered_set> and #include <unordered_map> instead for (unordered_set, unordered_multiset, unordered_map, unordered_multimap)
//----------------------------------------------------------------------------------------------------------------------------------
Binary Tree != Binary Search Tree
note: You can store any k-ary tree in an array. (e.g. binary heaps are a type of binary tree) 
Just that you can't efficiently perform rotation on a B.S.T. using array as you have the move entire array around. 

Tree is not necessarily Balanced
Balanced Tree => Red Black Tree & AVL Tree & Splay Tree 
Complete Tree => All leaves are filled => 2^h - 1 nodes, h = height of tree starting from 1
Traversal: PreOrder, InOrder, PostOrder
    PreOrder => Curr, Left, Right (DFS without checking for loops)
    InOrder => Left, Curr, Right
    PostOrder => Left, Right, Curr
void TreeNode::inorder() {
    if (this->left != NULL) left->inorder();
    cout << this->value << endl;
    if (this->right != NULL) right->inorder();
}`
//----------------------------------------------------------------------------------------------------------------------------------
Red Black Tree => For gaming purposes
//----------------------------------------------------------------------------------------------------------------------------------
k-ary tree = k-way tree = n-ary tree = m-way tree
k-ary tree != m-way search tree (In search tree, you must have m-1 values for data) 
note: k-ary tree != general tree 
general tree => Any node can have any number of children (growing infinitely)
k-ary tree => Each node can only have at most k children  => (Easier to implement as can allocate enough space for all k children)
i) Full k-ary tree => Every node has either 0 or k children 
ii) Perfect k-ary tree => Leaf nodes are same depth 
iii) Complete k-ary tree => You insert elements from left to right at each depth (example, a heap is always complete) 

Array Representation
    A node at index: i 
    It's cth child, c < k is at index: k*i + 1 + c (c goes from 0 to k-1)
    Parent is at index, floor((i-1)/k)

Pointer Representation
    Basically a pointer that points to every child

//----------------------------------------------------------------------------------------------------------------------------------
// m-way search tree = multi-way search tree  (m = multi)
e.g. 3-way search tree 
                10,44
                / | \
               /  |  \
            3,7  22,  55,70
                      /  |
                    50,  66,68
thus, the values in between any of the 2 values are in the pointer in between them
//----------------------------------------------------------------------------------------------------------------------------------
B-Trees => Perfectly Height-Balanced M-way search trees 
Applications: For operating on disk = Each node is the size of a disk page
//----------------------------------------------------------------------------------------------------------------------------------
// Common Questions:
//----------------------------------------------------------------------------------------------------------------------------------
    Is binary tree balanced? O(logn) worst case for space
    Is binary tree a BST? 
    Is it a complete binary tree, all leaves are same level, and all leaves exist
    Are there parent pointers? (Doubly linked or singly linked)
    Are all values unique? (useful for BST)
    What value type does it store? 
    How to return values? In vector or print them out or? 
    What happens if root is NULL? 
    What happens if node being searched for doesn't exist? 
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Preorder traversal binary tree recursively. T(n) = O(n), S(n) = O(logn)
// Time Complexity, T(n) = O(n), 
// Space Complexity, S(n) = O(logn) // assuming no need space for pushing back order of roots and tree is balanced
//---------------------------------
/* 
Questions: 
How to return nodes€™ values? In array? vector? 

Function Prototype: 
	vector<int> preorderTraversal(struct node * root); 

Test_cases: 
    1
    \
     2
    /
   3
	=> [1, 2, 3]

Algorithm: 
	Recursively print myself, then print left, then print right. 

Implementation: 
*/
//---------------------------------
/* // 
#include <vector> 
#include <iostream> 
using namespace std; 

struct node {
	int value; 
	node * left; 
	node * right; 
    node(int value_, node* left_, node* right_) : value(value_), left(left_), right(right_) {}
}; 

// [1, 2, 3] 
void preorderHelper(struct node * root, vector<int> & order)
{
	order.push_back(root->value); 
	if(root->left) preorderHelper(root->left, order); 
	if(root->right) preorderHelper(root->right, order); 
	return; 
}

vector<int> preorderTraversal(struct node * root) 
{
	vector<int> preorder; 
	preorderHelper(root, preorder); 
    return preorder;  
}

// TEST! 
int main(void)
{
	struct node C(3, nullptr, nullptr); 
	struct node B(2, &C, nullptr); 
	struct node A(1, nullptr, &B);
	vector<int> ans = preorderTraversal(&A); 
	for(int i = 0 ; i < ans.size(); i++)
	{
		cout << ans[i] << " " ; 
	}
	cout << endl; 
    return 0; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 2 Preorder traversal binary tree iteratively. T(n) = O(n), S(n) = O(n)
// T(n) = O(n), S(n) = O(n)
//---------------------------------
/*
Given a binary tree, return the preorder traversal of its nodes' values.
Iterative! 
Questions: 
    1. How to return nodes€ Print values? In array? vector? 

Function Prototype: 
	vector<int> preorderTraversal(struct node * root); 

Test_cases: 
	1
	  \
	  2
	 /
            3
	=> [1, 2,3 ]

Algorithm: 9
print myself, then print left, then print right. 
      2. Iteratively Print 
push myself into stack 
	while stack not empty 
	Output next node
	Push right into stack 
	Push left into stack 
Implementation: 
*/
//---------------------------------
/*
#include <cstdlib> // for NULL 
#include <vector> 
#include <stack> 
#include <iostream> 
using namespace std; 

struct node {
	int value; 
	struct node * left; 
	struct node * right; 
}; 

vector<int> preorderTraversal(struct node * root) 
{
	vector<int> preorder; 
	stack<struct node*> s; 
	s.push(root); 
	while(!s.empty())
	{
        struct node * curr = s.top(); 
        s.pop(); 
        preorder.push_back(curr->value); 
        if(curr->right) s.push(curr->right);
        if(curr->left) s.push(curr->left);
	}
	return preorder;  
}

// TEST! 
int main(void)
{
	struct node A; 
	struct node B; 
	struct node C; 
	A.value = 1; 
	B.value = 2;
	C.value = 3; 
	A.left = NULL;
	B.right = NULL; 
	C.left = NULL; 
	C.right = NULL; 
	B.left = &C; 
	A.right = &B; 
	vector<int> ans = preorderTraversal(&A); 
	for(int i = 0 ; i < ans.size(); i++)
	{
		cout << ans[i] << " " ; 
	}
	cout << endl; 
    return 0; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 3 Inorder traversal binary tree recursively. T(n) = O(n), S(n) = O(logn)
// Time Complexity, T(n) = O(n),
// Space Complexity, S(n) = O(logn) // assuming no space needed to store final output and tree is balanced
//---------------------------------
/*
Iterative! 
Questions: 
    How to return nodes€™ values? In array? vector? 
    What happen if root is NULL? 

Function Prototype: 
	vector<int> inorderTraversal(struct node * root); 

Test_cases: 
	1
	  \
	  2
	 /
            3
	=> [1, 2,3 ]

Algorithm: 

Implementation: 
*/
//---------------------------------
/* //
#include <cstdlib> // for NULL 
#include <vector> 
#include <stack> 
#include <iostream> 
using namespace std; 

struct node {
	int value; 
	struct node * left; 
	struct node * right; 
}; 

void inorderHelper(struct node* root, vector<int>& inorder)
{
	if(root->left) inorderHelper(root->left, inorder); 
	inorder.push_back(root->value); 
	if(root->right) inorderHelper(root->right, inorder); 
	return; 
}

vector<int> inorderTraversal(struct node * root) 
{
    vector<int> inorder; 
	if(root) 
	{
        inorderHelper(root, inorder); 	
    }
    return inorder;  
}

// TEST!  >> [1,3,2]
int main(void)
{
	struct node A; 
	struct node B; 
	struct node C; 
	A.value = 1; 
	B.value = 2;
	C.value = 3; 
	A.left = NULL;
	B.right = NULL; 
	C.left = NULL; 
	C.right = NULL; 
	B.left = &C; 
	A.right = &B; 
	vector<int> ans = inorderTraversal(&A); 
	for(int i = 0 ; i < ans.size(); i++)
	{
		cout << ans[i] << " " ; 
	}
	cout << endl; 
    return 0; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 4 Inorder traversal binary tree iteratively. T(n) = O(n), S(n) = O(n)
// Time Complexity, T(n) = O(n), S(n) = O(n)
//---------------------------------
/*
Questions: 
    How to return nodes€™ values? In array? vector? 
    What happen if root is NULL? 

Function Prototype: 
	vector<int> inorderTraversal(struct node * root); 

Test_cases: 
	1
	  \
	  2
	 /
    3
	=> [1, 2,3 ]

Algorithm: 
    Go most left, push to stack. 
    Then once null, pop from stack and assign to right. Repeat. (if null, pop from stack) 

Implementation: 
*/
//---------------------------------
/*
#include <cstdlib> // for NULL 
#include <vector> 
#include <stack> 
#include <iostream> 
using namespace std; 

struct node {
	int value; 
	struct node * left; 
	struct node * right; 
}; 

// This is what you came up with after hints on pseudocode
vector<int> inorderTraversalOriginal(struct node * root) 
{
    vector<int> inorder; 
	if(!root) return inorder; 
	stack <struct node *> s; 
	struct node * curr = root; 
	while(curr) 
	{
		// Keep going to left most child, pushing middle to stack 
        while(curr->left)
        {
            s.push(curr); 
            curr = curr->left; 
        }
        // push left most child of current branch 
        inorder.push_back(curr->value); 
        // move to right of left most child 
        curr = curr->right; 
        // if no right most child, 
        while(!curr) 
        {
            if(!s.empty()) 
            {
                curr = s.top(); 
                s.pop();  
                inorder.push_back(curr->value); 
                curr = curr->right; 
            }
            else
            {
                break; 
            }
        }
	}
    return inorder;  
}

// This is actual elegant code you looked up
vector<int> inorderTraversal(struct node * root) 
{
    vector<int> inorder; 
    if(!root) return inorder; 
    stack <struct node *> s; 
    struct node * curr = root; 
    while(curr || !s.empty())
    {
        if(curr)
        {
            s.push(curr); 
            curr = curr->left; 
        } 
        else
        {
            curr = s.top(); 
            s.pop();
            inorder.push_back(curr->value);
            curr = curr->right; 
        }
    }
    return inorder;
}

// TEST!  >> [1,3,2]
int main(void)
{
	struct node A; 
	struct node B; 
	struct node C; 
	A.value = 1; 
	B.value = 2;
	C.value = 3; 
	A.left = NULL;
	B.right = NULL; 
	C.left = NULL; 
	C.right = NULL; 
	B.left = &C; 
	A.right = &B; 
	vector<int> ans = inorderTraversal(&A); 
	for(int i = 0 ; i < ans.size(); i++)
	{
		cout << ans[i] << " " ; 
	}
	cout << endl; 
    return 0; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 5 Levelorder traversal binary tree iteratively.
// Time Complexity, T(n) = O(n), Space Complexity, S(n) = O(n)
//---------------------------------
/*
Questions: 
    1. Do you mean Breadth First Search on Binary Tree ? 
    2. Values binary tree hold? 
    3. Just output values to stdout or return in an array or 2-dimensional array with levels? 
Function Prototype: 
	vector<int> LevelOrderTraversal(struct node* root); 
Test Case: 
	    1
 	2      3
  4   5     7
     8
    Output: 1, 2,3,4,5,7,8
Algorithm: 
    1. 
	Think similarly to BFS of graph. put into queue and pop first in first out 
	O(n) time and space 
    2. 
    Find max depth O(n) , then for height from 0 to maxdepth, traverse tree and print all nodes at that level. 
    O(n^2) time and space since maxDepth = n in worst case (linkedlist) and need traverse O(n^2) time 
Implement: 
Test!
// */
//---------------------------------
/* //
#include <queue> 
#include <vector> 
#include <iostream> 
using namespace std; 

struct node {
    int val; 
    struct node * left; 
    struct node * right; 
    node(int _val, struct node* _left, struct node* _right) : val(_val), left(_left), right(_right) {} 
};

vector<int> LevelOrderTraversal(struct node* root)
{
    vector<int> orders; 
    queue<struct node *> q;  // MISTAKE: queue<int> instead of queue<struct node *>`
    q.push(root); // base case 
    while(!q.empty())
    {
        struct node * curr = q.front(); q.pop();
        orders.push_back(curr->val); // MISTAKE: orders.push() instead of orders.push_back()
        if(curr->left) q.push(curr->left); 
        if(curr->right) q.push(curr->right);  
    }
    return orders; 
} 

int main(void)
{
    struct node a8(8, NULL, NULL); 
    struct node a7(7, NULL, NULL); 
    struct node a5(5, &a8, NULL); 
    struct node a4(4, NULL, NULL); 
    struct node a3(3, NULL, &a7); 
    struct node a2(2, &a4, &a5); 
    struct node a1(1, &a2, &a3);
    vector<int> arr = LevelOrderTraversal(&a1); 
    for(int i = 0; i < arr.size() ; i++) cout << arr[i] << " "; 
    cout << endl;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 6 ZigZag Traversal binary tree iteratively.
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(n)
//---------------------------------
/*
Questions: 
Function Prototype: 
	vector<int> ZigZagTraversal(struct node* root); 
Test_Cases: 
        1
      2   3
    4  5   6 => outputs 1, 3, 2, 4, 5, 6, 8, 7 
      7   8 
Algorithm: 
    Use 2 stacks, push into 1st, and keep popping from 1st and push into 2nd 
    One push left,then right, the other push right then left
Implement!
Test!
// */
//---------------------------------
/* //
#include <vector> 
#include <stack> 
#include <iostream> 
using namespace std; 

struct node {
    int val; 
    struct node * left; 
    struct node * right; 
    node(int _val, struct node* _left, struct node* _right) : val(_val), left(_left), right(_right) {} 
};

vector<int> ZigZagTraversal(struct node* root)
{
    vector<int> orders; 
    stack<struct node *> first; 
    stack<struct node *> second; 
    // Base Case
    if(root) first.push(root); 
    while(!first.empty() || !second.empty())
    {
        if(!first.empty())
        {
            while(!first.empty())
            {
                struct node * curr = first.top(); first.pop();
                orders.push_back(curr->val);
                if(curr->left) second.push(curr->left);
                if(curr->right) second.push(curr->right);
            }
        }
        // second is not empty
        else
        {
            while(!second.empty())
            {
                struct node * curr = second.top(); second.pop();
                orders.push_back(curr->val);
                if(curr->right) first.push(curr->right);
                if(curr->left) first.push(curr->left);
            }
        }
    }
    return orders; 
}

int main(void)
{
    struct node a8(8, NULL, NULL); 
    struct node a7(7, NULL, NULL); 
    struct node a6(6, NULL, &a8); 
    struct node a5(5, &a7, NULL); 
    struct node a4(4, NULL, NULL); 
    struct node a3(3, NULL, &a6); 
    struct node a2(2, &a4, &a5); 
    struct node a1(1, &a2, &a3);
    vector<int> arr = ZigZagTraversal(&a1); 
    // Output: 1, 3, 2, 4, 5, 6, 8, 7 
    for(int i = 0; i < arr.size() ; i++) cout << arr[i] << " "; 
    cout << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 7 Output number of configurations of binary search tree given n distinct integers. T(n) = O(n), S(n) = O(n)
// T(n) = O(n), S(n) = O(n)
//---------------------------------
/*
    e.g n=0 => 1, n=1 => 1, n=2 => 2, n=3 => 5
    hint: Use dynamic programming as overlapping subproblems
	Note: This problem is equivalent to how many ways you can form a well formed parenthesis. 
	e.g. n=1 => 1 ()
    n = 2 => 2 (()), ()()
     n = 3 => 5 ((())), ()()(), (()()), ()(()), (())()
     You can count number of ways by drawing the branch tree, push, (push/pop), ... 
*/
//---------------------------------
/* 
int numTreesHelper(int n, vector<unsigned long long> & compute) 
{
    if (compute[n] != -1) return compute[n]; 
    unsigned long long sum = 0; 
    for(int i = 0; i <= (n-1)/2; i++)
    {
        sum += (2 * numTreesHelper(i, compute) * numTreesHelper(n-1-i, compute)); 
    }
    //  if odd number 
    if (n & 1)
    {
        int i = (n-1)/2; 
        sum -= numTreesHelper(i, compute) * numTreesHelper(n-1-i, compute); 
    }
    compute[n] = sum; 
    return sum; 
}

int numTrees(int n) 
{
    vector<unsigned long long> compute(n+1,-1);  
    // Handle base case
    compute[0] = 1; 
    compute[1] = 1; 
    return numTreesHelper(n,compute); 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 8 Find kth smallest element in BST, assuming k's value is valid (1->N)
// Time Complexity, T(n) = O(n), Space Complexity, S(n) = O(n) 
//---------------------------------
/* 
int kthSmallest(TreeNode* root, int k) 
{
	int count = 0; 
	int value = inorderTraverse(root, k, count); 
	return value; 
}

int inorderTraverse(TreeNode* root, int k, int& count) 
{
	int value; 
	if(root->left)
	{
		value = inorderTraverse(root->left, k, count); 
		if (count == k) return value; 
	}
	count++; 
	value = root->val; 
	if (count == k) return value; 
	if(root->right)
	{
		value = inorderTraverse(root->right, k, count); 
		if (count == k) return value; 
	}
	return value; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 9 Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
// An example is the root-to-leaf path 1->2->3 which represents the number 123.
// Find the total sum of all root-to-leaf numbers.
// Time Complexity, T(n) = O(n), Space Complexity, S(n) = O(n)
//---------------------------------
/* // 
int sumNumbers(TreeNode* root) 
{
	if(!root) return 0; 
	int totalSum = 0; 
	int accumulated = 0; 
	sumNumberHelper(root, totalSum, accumulated); 
	return totalSum; 
}
// note: Pass accumulated by value. 
// Post-order traversal. 
void sumNumberHelper(TreeNode* root, int & totalSum, int accumulated)
{
	if(!root) return; 
	accumulated += root->val; 
	if(!root->left && !root->right)
	{
		// This is a leaf node, add up its value
		totalSum += accumulated; 
		return; 
	}
	// This is not a leaf node 
	accumulated *= 10; // multiply it by 10 to shift the position before passing to next nodes.  
	if(root->left) sumNumberHelper(root->left, totalSum, accumulated); 
	if(root->right) sumNumberHelper(root->right, totalSum, accumulated); 
	return; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 10 Flatten binary tree into linkedlist using preorder
//----------------------------------------------------------------------------------------------------------------------------------
/* //
void flatten(TreeNode* root) {
    TreeNode* lastVisitedNode = NULL; 
    return flattenHelper(root,lastVisitedNode); 
}
void flattenHelper(TreeNode* root, TreeNode* lastVisitedNode)
{
    // Pre-order traversal. 
    if(!root) return; 
    TreeNode* oriRight = root->right; // Save original right as might be changed later by lastVisitedNode. 
    if(lastVisitedNode) 
    {
        lastVisitedNode->right = root; 
    }
    lastVisitedNode = root; 
    flattenHelper(root->left, lastVisitedNode);
    flattenHelper(oriRight, lastVisitedNode);
    root->left = NULL; 
    return; 
 
}
/*
COMPLICATED ATTEMPT from before WHICH IS TOO SLOW & MIGHT BE WRONG.
getMostRight(root)
{
    while(root->right)
    {
        root = root->right;
    }
    return root; 
}
    if(root->left)
    {
        TreeNode* mostRight = getMostRight(root->left); 
        mostRight->right = root->right; 
        // Only change root->right if there is a left. 
        root->right = root->left; 
        //NO! ITS PREORDER, 
        DONT HAVE TO UPDATE ACTUAL ROOT POINER
        // WRONG THINKING BEFORE. need to pass in actual root pointer to keep restoring original root to point to smallest element. 
        // WRONG: root = root->left; // restore original root to point to most left element. 
        flatten(root); 
        // Need to pass in oriRight so don't change actual mostRight's right pointer. 
        flatten(oriRight); 
    }
    flatten(oriRight); 
    root->left = NULL; 
    */
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 11 Print binary tree as seen from right side of tree. 
// Time Complexity, T(n) = O(n), Space Complexity, S(n) = O(n)
//----------------------------------------------------------------------------------------------------------------------------------
/*
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.
  1            <---
 /   \
2     3         <---
 \
  4            <---
Returns [1,3,4]
Questions: 
    Doubly linked or singly linked? 
    Need pointer to parents? 
Function Prototype:
	vector<int> rightSideView(struct TreeNode* root); 
TEST: 
	refer above
Algorithm: 
	passByReference, height seen so far 
	passByValue, currHeight 
	if(currHeight > heightSeen)
	{
		update heightSeen. Add current value to vector. 
	}
	if(root->right) recursively call right 
	if(root->left) recursively call left. 
Implementation:
*/
//---------------------------------
/* // 
#include <cstdlib>
#include <vector>
#include <iostream> 
using namespace std;  

struct TreeNode {
	int val; 
	struct TreeNode* left; 
	struct TreeNode* right; 
	// constructor
	TreeNode(int x) : val(x), left(NULL), right(NULL) {} 
};

void rightSideHelper(struct TreeNode* root, int& maxHeight, int currHeight, vector<int>& answer)
{
	if(!root) return; 
	currHeight++; 
	if (currHeight > maxHeight)
	{
		maxHeight = currHeight; 
		answer.push_back(root->val); 
	}
	if(root->right)
	{
        rightSideHelper(root->right, maxHeight, currHeight, answer); 
	}
	if(root->left)
	{
        rightSideHelper(root->left, maxHeight, currHeight, answer); 
	}
	return;
}

vector<int> rightSideView(struct TreeNode* root)
{
	vector<int> answer; 
	int maxHeight = 0; 
	int currHeight = 0;
    rightSideHelper(root, maxHeight, currHeight, answer); 
    return answer; 
}

int main(void)
{
	struct TreeNode* a1 = new TreeNode(1); 
	struct TreeNode* a2 = new TreeNode(2); 
	struct TreeNode* a3 = new TreeNode(3); 
    struct TreeNode* a4 = new TreeNode(4); 
	a1->left = a2; 
	a1->right = a3; 
	a2->right = a4; 
	vector<int> result = rightSideView(a1); 
	for(int i = 0 ; i < result.size(); i++)
	{	
		cout << result[i] << " ";
	}
	cout << endl; 
	return 0; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 12 Populate next(sibling) pointers binary tree. T(n) = O(n), S(n) = O(n)
// T(n) = O(n), S(n) = O(n)
//---------------------------------
/*
e.g. 
Convert from all next pointing at NULL 
            1     
          /   \
         2     3
        / \   / \
       4  5   6  7
TO: 
            1     
          /   \
         2  -  3
        / \   / \
       4- 5- 6- 7
// */
//---------------------------------
/*
struct node {
    int value;
    struct node* left; 
    struct node* right; 
    struct node* next;
};

void connect(struct node * root) 
{
    if(!root) return; 
    if(root->left) helper(root->left, root, false); 
    if(root->right) helper(root->right, root, true);         
}
void helper(struct node * root, struct node * parent, bool right)
{
    if(!right) root->next = parent->right; 
    else 
    {
        if(parent->next)
        {
            root->next = parent->next->left; 
        }
    }
    if(root->left) helper(root->left, root, false); 
    if(root->right) helper(root->right, root, true); 
    return; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 13 Balanced Binary Tree: Return true if difference in child's height is <= 1, false otherwise
// Time Complexity, T(n) = O(n), Space Complexity, S(n) = O(n)
//---------------------------------
/* //
#include <cmath> // abs()
#include <iostream> 
using namespace std; 

struct node {
    int val; 
    struct node * left; 
    struct node * right; 
    node(int _val, struct node* _left, struct node* _right) : val(_val), left(_left), right(_right) {} 
};

int balancedHelper(struct node * root, int height)
{
    if(!root) return height - 1; // return original root's height
    int leftHeight = balancedHelper(root->left, height + 1);
    if (leftHeight == -1) return -1; // if left tree is unbalanced, return right away before recursing to right for better complexity  
    int rightHeight = balancedHelper(root->right, height + 1); // MISTAKE: called on root->left instead of root->right
    if (rightHeight== -1) return -1; // if right tree is unbalanced, return right away 
    // Here, none of the child nodes are unbalanced, check if this node is balanced
    int diff = abs(rightHeight - leftHeight);
    if(diff > 1) return -1; 
    return max(rightHeight, leftHeight); // return the maxHeight of this node since it is balanced
}

bool isBalanced(struct node * root)
{
    int totalHeight = balancedHelper(root, 1);  // initialize to height of 1 for root, since if root is null, tree is still balanced and returns 0 
    if(totalHeight == -1) return false;
    return true;
}

int main(void)
{
    // Only 1 node
    struct node a4(4, NULL, NULL);
    bool balanced = isBalanced(&a4);
    if(balanced) cout << "Balanced" << endl;
    else cout << "Not Balanced" << endl; 
    // Balanced 
    struct node a3(3, NULL, NULL); 
    struct node a2(2, &a4, NULL); 
    struct node a1(1, &a2, &a3);
    balanced = isBalanced(&a1);
    if(balanced) cout << "Balanced" << endl;
    else cout << "Not Balanced" << endl; 
    // Unbalanced
    struct node a5(5, NULL, NULL); 
    a4.left = &a5; 
    balanced = isBalanced(&a1); 
    if(balanced) cout << "Balanced" << endl;
    else cout << "Not Balanced" << endl; 
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 14 Lowest Common Ancestor of Binary Tree
// Time Complexity, T(n) = O(n), Space Complexity, S(n) = O(n)
//---------------------------------
/* 
Questions: 
    1. Is it a BST? If it is, are all the values unique? 
    2. What happens if both nodes doesn't exist in tree?  Or if 1 node doesnt exist? 
Function Prototype: 
    struct node * LowestCommanAncestor(struct node * root, struct node * left, struct node * right);
Test Cases: 
    For Binary Tree Case
            1
        2       3
      4   5   6   7
    (2,7) => 1
    (6,7) => 3
    (4,2) => 2
    For Binary Search Tree Case
            4 
        1       6a 
      2   3   5   6b 
    (2,6b) => 4 
    (5, 6b) => 6a
    (1,3) => 1
Algorithm: 
    Method 1: Assume BST  T(n) = O(n), S(n) = O(n)
        Return first node that is within the values of left and right, if within values, return current node
        At each recursion, if its not within values, recurse left if lower than both, recurse right if bigger than both
    Method 2: Not BST, compare paths T(n) = O(3n), S(n) = O(3n)
        Find path to first node and store into array, find path to 2nd node and store into array
        Then, loop through both paths till values are not equal anymore (or end of one array), then the last equal value is the lowest common ancestor
        T(n) = O(3n) 2n for finding paths, n for comparing paths , S(n) = O(3n) n for recursion, 2n for keeping both arays
    Method 3: Not BST, T(n) = O(n) , S(n) = O(n)
        Pre-order traversal
            If currNode contains either node, return it
            else if both left and right node contains 1 node each, return curr node
            else if left node or right node contains either node, return that node 
            pass in 2 booleans by reference to check if both nodes are present or only 1 node is present
Implement
Test!
// */ 
//---------------------------------
/* //
#include <iostream> 
using namespace std; 

struct node {
    int val; 
    struct node * left; 
    struct node * right; 
    node(int _val, struct node * _left, struct node * _right) : val(_val), left(_left), right(_right) {}
};

struct node * LowestCommonAncestorBST(struct node * root, struct node * first, struct node * second)
{
    if(!root || !first || !second) return NULL;
    struct node * big = first->val >= second->val ? first: second; 
    struct node * small = first->val >= second->val ? second: first;  
    if((root->val >= small->val) && (root->val <= big->val)) return root; 
    // Check if recurse left or right in BST
    if (root->val <= small ->val) return LowestCommonAncestorBST(root->right, first, second);  // MISTAKE: Recursed root->left instead of root->right
    else return LowestCommonAncestorBST(root->left, first, second); 
}

struct node * LowestCommonAncestor(struct node * root, struct node * first, struct node * second, bool& firstFound, bool& secondFound)
{
    if(!root || !first || !second) return NULL;
    if(root == first || root == second)  // Mistake: Used | instead of || 
    {
        if (root == first) firstFound = true;
        else secondFound = true;
        // note: Can't return here as need to check of the other found node as found if it exist in the tree
    }
    struct node * leftNode = LowestCommonAncestor(root->left, first, second, firstFound, secondFound);
    struct node * rightNode = LowestCommonAncestor(root->right, first, second, firstFound, secondFound);
    // This root is the first time to have both nodes
    if(leftNode && rightNode || (root==first  || root == second))
    {
        return root;
    }
    // Here, one of them must be the found node, otherwise, the booleans will let us know none was found when return to main function below
    // Return this root as the node found
    if(leftNode) 
    {
        return leftNode;
    }
    else
    {
        return rightNode;
    }
}

int main(void)
{
    // BST Lowest Common Ancestor
    struct node a6b(6, NULL, NULL); 
    struct node a5(5, NULL, NULL); 
    struct node a3(3, NULL, NULL); 
    struct node a2(2, NULL, NULL); 
    struct node a6a(6, &a5, &a6b); 
    struct node a1(1, &a2, &a3);
    struct node a4(4, &a1, &a6a); 
    struct node * result = LowestCommonAncestorBST(&a4, &a2, &a6b); // 4
    cout << result->val << endl;
    result = LowestCommonAncestorBST(&a4, &a1, &a3);  // 1 
    cout << result->val << endl;
    result = LowestCommonAncestorBST(&a4, &a5, &a6b);  // 6
    cout << result->val << endl;

    // BT Lowest Common Ancestor
    struct node b7(7, NULL, NULL); 
    struct node b6(6, NULL, NULL); 
    struct node b5(5, NULL, NULL); 
    struct node b4(4, NULL, NULL); 
    struct node b3(3, &b6, &b7); 
    struct node b2(2, &b4, &b5); 
    struct node b1(1, &b2, &b3);
    bool leftFound = false; bool rightFound = false; // to check to make sure both nodes exist
    result = LowestCommonAncestor(&b1, &b2, &b7, leftFound, rightFound);  // 1 
    if(leftFound && rightFound) cout << result->val << endl;
    leftFound = false; rightFound = false;
    result = LowestCommonAncestor(&b1, &b2, &b4, leftFound, rightFound);  // 2 
    if(leftFound && rightFound) cout << result->val << endl;
    leftFound = false; rightFound = false;
    result = LowestCommonAncestor(&b1, &b6, &b7, leftFound, rightFound);  // 3
    if(leftFound && rightFound) cout << result->val << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 15 Invert a binary tree side ways
// T(n) = O(n), S(n) = O(n) 
//---------------------------------
/* // 
struct node {
    int value; 
    struct node * left;
    struct node * right;
};

struct node * invertTree(struct node * root) 
{
    if(root)
    {
        TreeNode* curr = root->right; 
        if(root->left) 
        {
            root->right = invertTree(root->left); 
        }
        if(curr) 
        {
            
            root->left = invertTree(curr);  
        }
    }
    return root; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 16 Serializing & De-Serializing a Binary Tree (Facebook 2nd Phone Interview 2015)
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(n) 
//---------------------------------
/*
Questions:
    1. Is it a Binary Search Tree? 
Function Prototype:
    vector<string> serialize(struct node * root);
    struct node * deSerialize(vector<string> serialTree);
TestCase:
    i) Empty Tree <=> ["#"]
    ii) one Node, 1 <=> ["1", "#", "#"]
    iii) 
        1
     2     4
      3   25
       <=> 
    ["1","2","#","3","#", "#", "4", "25", "#","#", "#"]
    Can't store as string since value can be > 9! Means may have more than 1 character for each value Means may have more than 1 character for each value
Algorithm:
    1. O(2n + 1) space, O(2n + 1) time since need to go through all space to de-serialize, and make all space to serialize`
        Store all NULL nodes with a special marker '#' => All node values need to be stored as char type as well and re-convert back to original type
*/
//---------------------------------
/* //
#include <cstdlib> // for malloc(), itoa(), atoi() Note: itoa() and atoi() only works for char * and NOT string
#include <vector>
#include <string> // To store serialize tree into a string before outputting to a file
#include <iostream> 
using namespace std; 

struct node {
    int value; 
    struct node * left; 
    struct node * right;
    node(int _value, struct node * _left, struct node * _right) : value(_value), left(_left), right(_right) {};
};

void serializeHelper(struct node * root, vector<string>& result)
{
    if(!root) 
    {
        result.push_back("#");
        return;
    }
    char buffer[33]; 
    itoa(root->value, buffer, 10); // base 10
    string newValue = buffer;
    result.push_back(newValue);
    serializeHelper(root->left, result);
    serializeHelper(root->right, result);
    return;
}
vector<string> serialize(struct node * root)
{
    vector<string> result;
    serializeHelper(root, result);
    return result;
}

struct node * deSerialize(vector<string>& serialTree)
{
    if(serialTree.size() <= 0) return NULL;
    if(serialTree[0].compare("#") == 0)
    {
        serialTree.erase(serialTree.begin(),serialTree.begin() + 1); // remove first string
        return NULL;
    }
    struct node * newNode = (struct node *) malloc(sizeof(struct node));
    newNode->value = atoi(serialTree[0].c_str()); 
    serialTree.erase(serialTree.begin(),serialTree.begin() + 1); // remove first string
    newNode->left = deSerialize(serialTree);
    newNode->right = deSerialize(serialTree);
    return newNode;
}

int main(void)
{
    struct node a5(25, NULL, NULL);
    struct node a3(3, NULL, NULL);
    struct node a4(4, &a5, NULL);
    struct node a2(2, NULL, &a3);
    struct node a1(1, &a2, &a4);
    vector<string> serialForm = serialize(&a1);
    string outputSerialForm = "";
    for(int i = 0; i < serialForm.size(); i++)
    {
        outputSerialForm.append(serialForm[i]);
        outputSerialForm.append(" ");
    }
    cout << outputSerialForm << endl; // ["1","2","#","3","#", "#", "4", "25", "#","#", "#"]
    struct node * newRoot = deSerialize(serialForm);
    // try to serialize whatever that was deserialize to see if it is still equal
    serialForm = serialize(newRoot);
    outputSerialForm.assign("");
    for(int i = 0; i < serialForm.size(); i++)
    {
        outputSerialForm.append(serialForm[i]);
        outputSerialForm.append(" ");
    }
    cout << outputSerialForm << endl; // ["1","2","#","3","#", "#", "4", "25", "#","#", "#"]
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 17 Return random node in binary tree (Microsoft: girl, on-site Round 2b)
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(n) // recursion
//---------------------------------
/*
Question
Function Prototype
    struct node * randomNode(struct node * root);
TestCases
    1
   2 3 
Algorithm
    i) original problem
    T(n) = O(n), S(n) = O(n) , takes O(n) space due to recursion 
        Calculate number of nodes in tree with in-order traversal
        calculate probability first out of all number of nodes in equal probability 
        do a in-order traversal and output that number. 
    ii) If each node has number of nodes on left and right, 
        Then, can know number of nodes in tree from root node and skip and traverse right and will be faster, 
        but worst case is still O(n) time if you have a linked list configuration of binary tre
Implement
Test
*/
//---------------------------------
/* //
#include <ctime> // for time()
#include <cstdlib> // for rand()
#include <iostream> 
using namespace std; 

struct node
{
    int value;
    struct node * left;
    struct node * right;
    node(int _val, struct node * _left, struct node * _right) : value(_val), left(_left), right(_right) {}
};

int getSize(struct node* root)
{
    if(!root)
        return 0;
    int size = 1;
    size += getSize(root->left);
    size += getSize(root->right);
    return size;
}

struct node * getNode(struct node* root, int number, int& depth)
{
    if (depth == number)
        return root;
    struct node * curr; 
    if(root->left)
    {
        depth += 1;
        curr = getNode(root->left, number, depth);
        if(curr) return curr; // if found it, return the node
    }
    // here, means node is not yet found
    if(root->right) 
    {
        depth += 1;
        curr = getNode(root->right, number, depth);
        if(curr) return curr; // if found it, return the node
    }
    return NULL; // not found since number is more than size of root
}

struct node * randomNode(struct node * root)
{
    int size = getSize(root); // get size of tree
    srand(time(NULL));
    int number = rand() % size; // get probability of one of the nodes
    // Iterate and return that node
    int depth = 0;
    struct node * randNode = getNode(root, number, depth);
    return randNode;
}
int main(void)
{
    struct node node3(3, NULL, NULL);
    struct node node2(2, NULL, NULL);
    struct node root(1, &node2, &node3);
    struct node * randNode = randomNode(&root);
    cout << randNode->value << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 18 Sum level k nodes in binary tree (Bloomberg First Round)
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(n)
//---------------------------------
/*
Question: 
    1. What if N < 0 || N > maxHeight(tree) 
        N < 0 => Return 0
        N > maxHeight(tree) return 0  // assume no difference with actual 0 answer
    2. Each tree has a value, integers? doubles? int, (-) , (0)
    3. Is tree balanced? Not necessary => S(n) = O(n) != O(logn)
Function Prototype: 
    int sumNodeHeightK(struct node* root, int level);
TestCase:
    0 -       6
    1 -     2    3
    2 -  4    5    7 
    Remember to check level = 0 case 
    0 => 6
    1 => 5
    2 => 16
Algorithm: 
    recursive: preorder:
    return sum of the recursive itself. 
    base case: only return own value to sum if currheight is the right height; need helper function to pass in height 
Implement
Test!
*/
//---------------------------------
/* //
#include <iostream> 
using namespace std; 

struct node {
    int val; 
    struct node* left; 
    struct node* right;
    node(int _val, struct node* _left, struct node* _right) : val(_val), left(_left), right(_right) {}
}; 

int sumNodeHelper(struct node* root, int level, int currLevel)
{
    if(!root) return 0; // base case
    // know this node exist 
    if (currLevel == level) return root->val;  // 2 | 3
    int LeftSum =  sumNodeHelper(root->left, level, currLevel+1); 
    int RightSum =  sumNodeHelper(root->right, level, currLevel+1);  
    return LeftSum + RightSum;  
}

int sumNodeHeightK(struct node* root, int level)
{
    if (level < 0 || !root) return 0; 
    int currLevel = 0; 
    return sumNodeHelper(root, level, currLevel); 
}


int main(void)
{
    node t7(7, NULL, NULL);
    node t5(5, NULL, NULL);
    node t4(4, NULL, NULL);
    node t3(3, NULL, &t7);
    node t2(2, &t4, &t5); 
    node root(6, &t2, &t3);
    cout << sumNodeHeightK(&root, 0) << endl; // 6
    cout << sumNodeHeightK(&root, 1) << endl; // 5
    cout << sumNodeHeightK(&root, 2) << endl; // 16
    cout << sumNodeHeightK(&root, -1) << endl; // 0 
    cout << sumNodeHeightK(&root, 3) << endl; // 0
    return 0; 
}
// */ 
//----------------------------------------------------------------------------------------------------------------------------------
