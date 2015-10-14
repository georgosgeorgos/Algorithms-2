//----------------------------------------------------------------------------------------------------------------------------------
/* //
Table of Contents
1. Preorder traversal binary tree recursively. T(n) = O(n), S(n) = O(n)
2. Preorder traversal binary tree iteratively. T(n) = O(n), S(n) = O(n)
3. Inorder traversal binary tree recursively. T(n) = O(n), S(n) = O(n)
4. Inorder traversal binary tree iteratively. T(n) = O(n), S(n) = O(n)
5. Populate next pointers binary tree. T(n) = O(n), S(n) = O(n)
6. Invert a binary tree side ways, T(n) = O(n), S(n) = O(n)
7. Output number of configurations of binary search tree given n distinct integers. T(n) = O(n), S(n) = O(n)
8. Find kth smallest element in BST, assuming k's value is valid (1->N), T(n) = O(n), S(n) = O(n)
9. Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
   Find total sum of all root-to-leaf numbers. T(n) = O(n), S(n) = O(n)
10. Flatten binary tree into linkedlist using preorder
11. Print binary tree as seen from right side of tree, T(n) = O(n), S(n) = O(n)
12. Levelorder traversal binary tree iteratively. T(n) = O(n), S(n) = O(n)
//----------------------------------------------------------------------------------------------------------------------------------
TODO:
21. Print all nodes in a binary tree at level k
22. Invert binary tree up to down 
23. Given an array where elements are sorted in ascending order, convert it to a height balanced BST. (ECE345 Assignment)  
24. Validate if a binary tree is a Binary Search Tree. T(n) = O(n), S(n) = O(n)
25. Calculate Maximum Depth of a Binary Tree, T(n) = O(n), S(n) = O(logn)
26. Check if a binary tree is balanced T(n) = O(n), S(n) = O(n)
        // 1 Check if a binary tree is balanced
print(tree root , int level)
Method1: BFS.
Method2:
    We can also do a simple post-order traversal.
    void printNodesAtGivenLevel(Node node, final int requiredLevel, int currLevel){
        if(node != null){
            if(currLevel < requiredLevel){
                printNodesAtGivenLevel(node.left, requiredLevel, currLevel + 1);
                printNodesAtGivenLevel(node.right, requiredLevel, currLevel + 1);
            }
            else if(currLevel == requiredLevel){
                System.out.println(node.data);
            }
        }
    }
//call the function as printNodesAtGivenLevel(root, n, 1);
27. Given a sorted array in increasing order, write algorithm to create balanced binary search tree with minimal height 
    T(n) = O(n), S(n) = O(logn)
28. Given a sorted linkedlist in increasing order, write algorithm to create balanced binary search tree with minimal height
    T(n) = O(n), S(n) = O(logn)
29. Binary Tree Maximum Path Sum, all nodes contains integer values that may be (-)
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
31. Serializing a Tree
32. Given a binary tree, create linked list of all nodes at each depth
(if have a tree with depth D, will have D linked list!)
33. Write algorithm to find the next node of a given node in a BST where each node has a link to the parent
35. Design algorithm to find first common ancestor in a binary tree (not necessarily BST!)
Avoid storing additional nodes in data structure.
36. Given 2 binary tree, where  BT1 > BT2 , decide if BT2 is a subtree of BT1.
37. Given a binary tree where each node contains a value. Design an algorithm to print all paths which sum up
to that value. Note: It can be any path in the tree and does not have to start at root (refer to coding interview)
//----------------------------------------------------------------------------------------------------------------------------------
Notes:
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
Questions:
//----------------------------------------------------------------------------------------------------------------------------------
// Is binary tree balanced? O(logn) worst case
// Is binary tree a BST? 
// Is it a complete binary tree, all leaves are same level, and all leaves exist
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Preorder traversal binary tree recursively. T(n) = O(n), S(n) = O(n)
// T(n) = O(n), S(n) = O(n)
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
	=> [1, 2,3 ]

Algorithm: 
	Recursively print myself, then print left, then print right. 

Implementation: 
*/
//---------------------------------
/* // 
#include <cstdlib> // for NULL 
#include <vector> 
#include <iostream> 
using namespace std; 

struct node {
	int value; 
	struct node * left; 
	struct node * right; 
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
// 2 Preorder traversal binary tree iteratively. T(n) = O(n), S(n) = O(n)
// T(n) = O(n), S(n) = O(n)
//---------------------------------
/*
Given a binary tree, return the preorder traversal of its nodes' values.
Iterative! 
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
	=> [1, 2,3 ]

Algorithm: 9
Recursively print myself, then print left, then print right. 

	
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
// 3 Inorder traversal binary tree recursively. T(n) = O(n), S(n) = O(n)
// Time Complexity, T(n) = O(n), S(n) = O(n)
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
// 5 Populate next pointers binary tree. T(n) = O(n), S(n) = O(n)
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
//----------------------------------------------------------------------------------------------------------------------------------
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
// 6 Invert a binary tree side ways
// T(n) = O(n), S(n) = O(n) 
//---------------------------------
/*
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
// 12 Levelorder traversal binary tree iteratively.
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
	Think similarly to BFS of graph. put into queue and pop first in first out 
	O(n) time and space 
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
