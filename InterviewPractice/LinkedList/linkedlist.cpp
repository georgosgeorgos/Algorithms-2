//----------------------------------------------------------------------------------------
/* //
Table of Contents
1. Reverse a Linked list, T(n) = O(n),  S(n) = O(1)
2. Adding two numbers that are represented by linked lists, T(n) = O(n), S(n) = O(n)
3. Remove Duplicates From Linked List, T(n) = O(n^2), S(n) = O(1), (if don't need maintain order), T(n) = O(nlogn), S(n) = O(n)
4. Return Last K Elements of a Linked List, T(n) = O(n), S(n) = O(1)
5. Delete Node From Middle Of Linked List, Given Access to That Node, T(n) = O(n), S(n) = O(1)
6. Detect if a Linked List is circular, T(n) = O(n), S(n) = O(1)
7. Given Circular Linked List, return node at beginning of circular list, T(n) = O(n), S(n) = O(1) TODO: INT
8. Detect if a Linked List is a palindrome T(n) = O(n) , S(n) = O(n)
9. Pairwise Swap: Swap every two adjacent nodes and return its head.
   If odd number of elements, ignore the last element. Time Complexity, T(n) = O(n), S(n) = O(1) 
10. Given a linked list and a value x, partition it such that all nodes less than x come 
    before nodes greater than or equal to x, T(n) = O(n), S(n) = O(1)
11. Insert an element into a sorted circular linked list (Microsoft Round 1), T(n) = O(n) (single pass), S(n) = O(1) TODO: INT
12. Find intersection point of 2 singly linked list, T(n,m) = O(n + m + max(n,m)), S(n,m) = O(1)
13. Reverse linked list in groups of given size, T(n) = O(n), S(n) = O(1)
//----------------------------------------------------------------------------------------
TODO: 
21. Partition List: 
    (done in leetCode)
21. Merge K sorted linked list into 1 sorted linked list
    T(n) = O(nklogk), S(n) = O(1) 
    Hint: MergeSort
22. Copy List with Random Pointer (Bloomberg Interview) 
    A linked list has next pointer and random pointers to either NULL or random nodes on this linked list. 
    Clone this linked list. 
    Your solution during interview, T(n) = O(n), S(n) = O(n) (hash table)
    Optimal Solution to figure out, T(n) = O(n), S(n) = O(1) (if allowed to modify original linked list)
//----------------------------------------------------------------------------------------
#include <forward_list> 
//----------------------------------------------------------------------------------------
forward_list<int> listA;
e.g.: int curr = listA.front(); 
    push_front() // insert element to beginning
    pop_front() // removes first element
    front() // get first element
    unique() // remove duplicates (only works if list is sorted)
    sort()
    clear()
    insert_after()
    emplace_after()
    emplace_front()
    erase_after()
    resize()
    swap()
//----------------------------------------------------------------------------------------
Notes: 
    If you ever need to re-point head to something else in list, (e.g. Sorting), you MUST work with double pointers
    When you work with double pointers, make sure you keep track on where the current double pointer is pointing at 
    as the pointing it is pointing at may be re-assigned from NULL to something else which may result in infinite loop

    Or a better approach is to always return the pointer that the new head should point to as a return value. 
    That way, you won't have weird problems

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
// Common Hints
//----------------------------------------------------------------------------------------
- Memory address of linkedlist is unique (pointed to by pointers)
- Can always break circular linked list, solve the problem, then link it back to become circular again
- Use while(curr->next) instead of while(curr) to be able to use less pointers and reduce logic complexity
- If a second pointer is running twice as fast, the middle pointer will reach the middle when 2nd pointer reaches the end
- Can always transfer values of linkedlist instead of the nodes themselves
- Always initialize all created linkedlist to NULL! If not may have weird errors
- REMEMBER TO SET HEAD TO LATEST ACTUAL HEAD and ANY OTHER RELEVANT NODES TO POINT TO NULL
- Consider these cases into logic: 
    > curr, > next
    < curr, < next
    == curr, == next
    next > curr? next < curr ? next == curr
 if circularLinkedList, next == head? 
//----------------------------------------------------------------------------------------
// Common Questions
//----------------------------------------------------------------------------------------
Is it a singly linked is or doubly linked list?
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Reverse a Linked list
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
//---------------------------------
/* //
#include <stdlib.h>
#include <iostream>
using namespace std;

struct node
{
    int value;
    struct node* next;
};

struct node* reverseLinkedList(struct node* head);

int main(void)
{
    struct node* head;
    struct node* a = (struct node*)malloc(sizeof(struct node));
    struct node* b = (struct node*)malloc(sizeof(struct node));
    struct node* c = (struct node*)malloc(sizeof(struct node));
    struct node* d = (struct node*)malloc(sizeof(struct node));
    a->value = 1;
    a->next = b;
    b->value = 2;
    b->next = c;
    c->value = 3;
    c->next = d;
    d->value = 4;
    d->next = NULL;
    head = a;
    struct node* curr = head;
    cout <<"Before Reversing" << endl;
    // while (curr)
    while(curr != NULL)
    {
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl;
    // MISTAKE: Must always return pointer to head using return value.
    // You cannot return pointer to head using parameters
    // Maybe it works with double pointers??
    curr = reverseLinkedList(head);
    cout << "After Reversing" << endl;
    while(curr != NULL)
    {
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl;
}

struct node* reverseLinkedList(struct node* head)
{
    struct node* prev;
    struct node* curr;
    struct node* next;
    // if (!head)
    if(!head || !head->next)
        return head;
    prev = head;
    curr = head->next;
    // NOTE: MISTAKE HERE!! Forgot to point first element to NULL
    prev->next = NULL; // point first element to NULL
    //while(curr) // NOTE: MISTAKE HERE! DID while(!curr) instead of while(curr) 
    while(curr != NULL)
    {
        next= curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev; // set head to previous
    // Note: Mistake!! You can never return pointer by reference, return pointer using return value instead!!
    return head;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 2 Adding two numbers that are represented by linked lists
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(n)
//---------------------------------
/*
Algorithm:
    5->4 + 8->7  = 1->4->1
    Simply perform reverse  linked list algorithm on both lists first, then you can add from the back 
*/
//---------------------------------
/* //
#include <forward_list> // singly linked list
#include <iostream>
using namespace std;

int main(void)
{
    forward_list<int> list1;
    forward_list<int> list2;
    // 54, 4->5
    list1.push_front(5);
    list1.push_front(4);
    // 87 , 7->8
    list2.push_front(8);
    list2.push_front(7);
    // note: will traverse from 6->3
    // => will print 6 3

    // Note: the result list will be in proper order
    // 36 + 55 = 91 => 9->1

    // Note: If above is not in right order, simply do reverseLinkedList algorithm first. T(n) = O(n) 

    for ( int& node: list1 )
    {
        cout << ' ' << node;
    }
    cout << endl;
    for ( int& node: list2 )
    {
        cout << ' ' << node;
    }
    cout << endl;
    // 55+36 = 91, 1->9
    forward_list<int> result;
    int carry = 0; // note: Carry will never be > 1, since 9+9 = 18 => 1
    while(1)
    {
        int value1 = list1.front();
        list1.pop_front();
        int value2 = list2.front();
        list2.pop_front();
//cout << "val1: " << value1 << " val2: " << value2 << " carry: " << carry << endl;
        int sum = carry + value1 + value2;
        carry = 0;
        result.push_front((sum)%10);
        if(sum >= 10)
        {
            //carry = (carry + value1 + value2)/10; //
            carry++;
        }
        if (list1.empty() || list2.empty()) break;

    }
    if(!list1.empty())
    {
        while(1)
        {
            int value1 = list1.front();
            list1.pop_front();
            int sum = carry + value1;
            carry = 0;
            result.push_front((sum)%10);

            if(sum >= 10)
            {
                carry++;
            }
            if (list1.empty()) break;
        }
    }
    else if (!list2.empty())
    {
        while(1)
        {
            int value2 = list2.front();
            list2.pop_front();
            int sum = carry + value2;
            carry = 0;
            result.push_front((sum)/10);

            if(sum >= 10)
            {
                carry++;
            }
            if (list2.empty()) break;
        }
    }
    if(carry > 0)
    {
        result.push_front(carry);
    }
    for ( int& node: result )
    {
        cout << ' ' << node;
    }
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 3 Remove Duplicates From Linked List
// Time Complexity, T(n) = O(nlogn) 
// Space Complexity, S(n) = O(1) 
//---------------------------------
/* 
Algoritm:
    Method 1: Sort, Then Remove Duplicates 
    Time Complexity, T(n) = O(nlogn) 
    Space Complexity, S(n) = O(1) 
    Method 2: Remove Duplicates Directly
    Time Complexity, T(n) = O(n^2) 
    Space Complexity, S(n) = O(1) 
    note: Can reduce T(n) to O(1) by sacrificing space using hash table
    Method 3: Hashing
    Time Complexity, T(n) = O(n)
    Space Complexity, S(n) = O(n)
*/
//---------------------------------
/* //
#include <cstdio>
#include <cstdlib> 
#include <iostream> 
#include <forward_list> // singly linked list
using namespace std; 

struct node {
    int value; 
    struct node* next; 
};

struct node* removeDuplicate(struct node* head)
{
    struct node * curr; 
    struct node * check; 
    if(!head) return head; 
    curr = head; 
    check = curr; 
    while(curr)
    {
        while(check->next)
        {
            if (check->next->value == curr->value)
            {
                check->next = check->next->next;
            }
            else 
            {
                check = check->next; 
            }
        }
        curr = curr->next; 
        check = curr; 
    }

    return head;
}

forward_list<int> removeDuplicateWithSort(forward_list<int> dup)
{
    dup.sort(); // sort using mergesort(), T(n) = O(nlgn)
    dup.unique(); // remove duplicate elements in 1 run across linkedlist, T(n) = O(n)
    return dup;
}

int main(void)
{
    forward_list<int> list1 = {2,3,8,1,5,2,3,5,8}; 
    // input: 2->3->8->1->5->2->3->5->8
    // output: 2->3->8->1->5
    for(int& node: list1)
    {
        cout << node << ' '; 
    }
    cout << endl << "Method1: Sort Then Remove" << endl; 
    list1 = removeDuplicateWithSort(list1);
    for(int& node: list1)
    {
        cout << node << ' '; 
    }
    cout << endl; 
    struct node* list2;
    struct node* a1 = (struct node*) malloc(sizeof(struct node));
    struct node* a2 = (struct node*) malloc(sizeof(struct node));
    struct node* a3 = (struct node*) malloc(sizeof(struct node));
    struct node* a4 = (struct node*) malloc(sizeof(struct node));
    struct node* a5 = (struct node*) malloc(sizeof(struct node));
    struct node* a6 = (struct node*) malloc(sizeof(struct node));
    struct node* a7 = (struct node*) malloc(sizeof(struct node));
    struct node* a8 = (struct node*) malloc(sizeof(struct node));
    struct node* a9 = (struct node*) malloc(sizeof(struct node));
    a1->value = 2;
    a1->next = a2;
    a2->value = 3;
    a2->next = a3;
    a3->value = 8;
    a3->next = a4;
    a4->value = 1;
    a4->next = a5;
    a5->value = 5;
    a5->next = a6;
    a6->value = 2;
    a6->next = a7;
    a7->value = 3;
    a7->next = a8;
    a8->value = 5;
    a8->next = a9;
    a9->value = 8;
    a9->next = NULL;
    list2 = a1;
    cout << endl; 
    struct node* head = list2;
    while(head)
    {
        cout << head->value << " "; 
        head = head->next; 
    }
    cout << endl << "Method2: Remove Directly" << endl; 
    list2 = removeDuplicate(list2);
    head = list2;
    while(head)
    {
        cout << head->value << " "; 
        head = head->next; 
    }
    return 0; 
}

// */
//----------------------------------------------------------------------------------------------------------------------------------
// 4 Return Last K Elements of a Linked List 
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
//---------------------------------
/* //
#include <cstdio> 
#include <cstdlib> 
#include <iostream> 
using namespace std; 
struct node {
    int value;
    struct node* next; 
};

struct node * getLaskK(struct node * head, int k);

int main(void)
{
    struct node * head; 
    struct node* first = (struct node *) malloc(sizeof(struct node));
    head = first;
    struct node* prev = first; 
    prev->value = 8;
    for (int i = 0; i < 10; i++)
    {
        struct node* temp = (struct node *) malloc(sizeof(struct node));
        prev->next = temp; 
        prev = temp; 
        prev->value = i; 
        prev->next = NULL;
    }
    prev = head; 
    while(prev)
    {
        cout << prev->value << " ";
        prev = prev->next;
    }
    cout << endl;
    int k = 5; 
    head = getLaskK(head, k);
    prev = head; 
    while(prev)
    {
        cout << prev->value << " ";
        prev = prev->next;
    }
    return 0;
}

// if k = 0 => Return NULL
struct node * getLaskK(struct node * head, int k)
{
    if (k <= 0) return NULL;
    struct node * last = head; 
    for (int i = 1; i < k; i++)
    {
        // If less than k elements, return all the elements
        if(!last) return head; 
        last = last->next; 
    }
    while(last->next)
    {
        last = last->next; 
        head = head->next; 
    }
    return head;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 5 Delete Node From Middle Of Linked List, Given Access to That Node
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
//---------------------------------
/*
Question:  
    1. What happens if last node given? Ignore
        Algorithm doesn't work if last node given
*/
//---------------------------------
/* //
#include <cstdio> 
#include <cstdlib> 
#include <iostream> 
using namespace std; 

struct node {
    int value;
    struct node * next; 
};
void deleteThis(struct node * curr);

int main(void)
{
    int i = 0; 
    struct node* head = (struct node *) malloc(sizeof(struct node)); 
    struct node* curr; 
    head->value = 3;
    head->next = NULL;
    for(int i = 0; i < 10; i++)
    {
        struct node* temp = (struct node *) malloc(sizeof(struct node)); 
        temp->value = i; 
        temp->next = head;
        head = temp;
        if(i == 5)
        {
            curr = temp;
        }
    }
    struct node* loop = head; 
    while(loop)
    {
        cout << loop->value << " "; 
        loop = loop->next;
    }
    cout << endl;
    deleteThis(curr);
    loop = head;
    while(loop)
    {
        cout << loop->value << " "; 
        loop = loop->next;
    }
    cout << endl;
    return 0;
}

void deleteThis(struct node * curr)
{
    while(curr->next)
    {
        curr->value = curr->next->value;
        // Note: Mistake here! Forgot to release last node 
        if(!curr->next->next)
        {
            curr->next = NULL;
            break;
        }
        curr = curr->next;
    }
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 6 Detect if a Linked List is circular, T(n) = O(n), S(n) = O(1)
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
//---------------------------------
/* // 
#include <cstdio> 
#include <cstdlib> 
#include <iostream> 
using namespace std; 

struct node {
    int value; 
    struct node * next;
};

bool checkCircular(struct node * head)
{
    if (!head) return false;
    struct node * slow = head; 
    struct node * fast = head->next; 
    while (fast)
    {
        fast = fast->next;
        if (fast == slow) return true;
        slow = slow->next; 
        // MISTAKE: Forgot to check fast has a next value here! If fast has no next, will result in segmentation fault
        if(fast)
        {
            fast = fast->next;
            if (fast == slow) return true;
        }
        else 
        {
            return false;
        }
    }
    return false;
}

int main(void)
{
    struct node * head = (struct node *) malloc(sizeof(struct node));
    head->value = 15;
    head->next = NULL;
    struct node * last = head;
    for (int i = 0; i < 5; i++)
    {
        struct node * temp = (struct node *) malloc(sizeof(struct node));
        temp->value = i;
        temp->next = head;
        head = temp;
    }
    last->next = head;
    struct node * curr = head;
    for(int i = 0; i < 12; i++)
    {
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl; 
    bool circle = checkCircular(head);
    if (circle) cout << "Circular Linked List Detected" << endl;
    else cout << "No Circular Linked List Detected" << endl;
    head = (struct node *) malloc(sizeof(struct node));
    head->value = 15;
    head->next = NULL;
    for (int i = 0; i < 5; i++)
    {
        struct node * temp = (struct node *) malloc(sizeof(struct node));
        temp->value = i;
        temp->next = head;
        head = temp;
    }
    curr = head;
    while (curr)
    {
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl;
    curr = head;
    circle = checkCircular(curr);
    if (circle) cout << "Circular Linked List Detected" << endl;
    else cout << "No Circular Linked List Detected" << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------
// 7 Given Circular Linked List, return node at beginning of circular list
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
//---------------------------------
/*
Questions:
    1. What happens if there is no cycle? return NULL
    2. What happens if node is empty? return NULL
*/
//---------------------------------
/* //
#include <cstdio> 
#include <cstdlib> 
#include <iostream> 
using namespace std; 

struct node {
    int value; 
    struct node * next;
};

struct node * getStartNode(struct node * head)
{
    if(!head) return NULL; 
    struct node * curr = head; 
    struct node * fast = head->next; 
    while(curr != fast)
    {
        curr = curr->next; 
        if(fast)
            fast = fast->next; 
        else
            return NULL;
        if(fast)
            fast = fast->next; 
        else
            return NULL;
    }
    curr = head; 
    fast = fast->next;
    while(curr != fast) // here, it is confirmed there is a cycle, so no null checking needed
    {
        curr = curr->next;
        fast = fast->next;
    }
    return curr;
}

int main(void)
{
    struct node * head = (struct node *) malloc(sizeof(struct node));
    head->value = 15;
    head->next = NULL;
    struct node * last = head;
    struct node * curr;
    for (int i = 0; i < 8; i++)
    {
        struct node * temp = (struct node *) malloc(sizeof(struct node));
        temp->value = i;
        temp->next = head;
        head = temp;
        if (i == 5) curr = head;
    }
    last->next = curr;
    curr = head;
    for(int i = 0; i < 20; i++)
    {
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl; 
    curr = getStartNode(head);
    for(int i = 0; i < 20; i++)
    {
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl; 
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 8 Detect if a Linked List is a palindrome 
// Time Complexity, T(n) = O(n) 
// Space Complexity, S(n) = O(n) 
//---------------------------------
/* // 
#include <cstdio> 
#include <cstdlib> 
#include <iostream> 
#include <stack> 
using namespace std; 

struct node {
    int value;
    struct node * next;
};

bool isPalindrome(struct node * head);
int main(void)
{
    struct node * head = (struct node *) malloc(sizeof(struct node));
    head->value = 0;
    head->next = NULL;
    for(int i = 1; i < 4; i++)
    {
        struct node * temp = (struct node *) malloc(sizeof(struct node));
        temp->value = i;
        temp->next = head;
        head = temp;
    }
    for(int i = 4; i >= 0; i--)
    {
        struct node * temp = (struct node *) malloc(sizeof(struct node));
        temp->value = i;
        temp->next = head;
        head = temp;
    }
    struct node * curr = head;
    while(curr)
    {
        cout << curr->value << " ";
        curr = curr->next; 
    }
    cout << endl;
    bool palindrome = isPalindrome(head);
    if(palindrome) cout << "Linked list is a palindrome" << endl;
    else cout << "Linked list is NOT a palindrome" << endl;
    head = (struct node *) malloc(sizeof(struct node));
    head->value = 0;
    head->next = NULL;
    for(int i = 1; i < 4; i++)
    {
        struct node * temp = (struct node *) malloc(sizeof(struct node));
        temp->value = i;
        temp->next = head;
        head = temp;
    }
    curr = head;
    while(curr)
    {
        cout << curr->value << " ";
        curr = curr->next; 
    }
    cout << endl;
    palindrome = isPalindrome(head);
    if(palindrome) cout << "Linked list is a palindrome" << endl;
    else cout << "Linked list is NOT a palindrome" << endl;
    return 0;
}

bool isPalindrome(struct node * head)
{
    stack<int> s; 
    struct node * curr = head; 
    struct node * fast = head; 
    while(curr)
    {
        if(fast)
        {
            s.push(curr->value);
            fast = fast->next;
            if(fast) fast = fast->next;
            // Pop the middle element
            else s.pop();
        }
        else 
        {
            int val = s.top();
            s.pop();
            if (val != curr->value) return false;
        }
        curr = curr->next;

    }
    // Iterated through entire linked list and no problems, it is a palindrome
    return true;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 9 Pairwise Swap: Swap every two adjacent nodes and return its head. If odd number of elements, ignore the last element.
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1) 
//---------------------------------
/*
    1->2->3->4->5 => 2->1->4->3->5
    1->2->3 => 2->1->3
    1->2 => 2->1
    1 => 1
Questions: 
Is it a singly linked list or doubly linked list? 
Am i allowed to swap values or I must swap the nodes? 
FunctionPrototype: 
	struct node * swapAdjacent(struct node * root); 
Test Case 
	1
	1->2
	1->2->3 
	1->2->3->4->5
Algorithm: 
	if(!root || !root->next) return root; 
	recurseRoot= root->next->next; 
	replaceRoot = root->next; 
	root->next->next = root; 
	root->next = recurseRoot; 
	root = replaceRoot; 
	swapAdajacent(recurseRoot);
	return root; 
Implementation: 
*/
//---------------------------------
/* //
#include <cstdlib> 
#include <iostream> 
using namespace std; 

struct node {
	int value; 
	struct node * next; 
};

struct node * swapAdjacent(struct node * root)
{
	// Base case 
	if(!root || !root->next) return root; 
	struct node* recurseRoot = root->next->next; 
	struct node* replaceRoot = root->next; 
	root->next->next = root; 
	root->next = recurseRoot; 
	root = replaceRoot; 
	swapAdjacent(recurseRoot); 
	return root; 
}

int main(void)
{
	struct node * a = (struct node*) malloc(sizeof(struct node)); 
	struct node * b = (struct node*) malloc(sizeof(struct node)); 
	struct node * c = (struct node*) malloc(sizeof(struct node)); 
	a->value = 1; 
	b->value = 2; 
	c->value = 3; 
	a->next = b; 
	b->next = c; 
	c->next = NULL; 
    struct node * newRoot = swapAdjacent(a); 
    struct node* curr = newRoot; 
	while (curr)
	{
		cout  <<  curr->value << " "; 
		curr = curr->next; 
	}
	cout << endl; 
return 0; 
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 10 Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
// Time Complexity, T(n) = O(n) single pass
// Space Complexity, S(n) = O(1)
//---------------------------------
/* 
You should preserve the original relative order of the nodes in each of the two partitions.
For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
*/
//---------------------------------
/* //
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
ListNode* partition(ListNode* head, int x) 
{
    if(!head) return head; 
    ListNode* lastLess = NULL; 
    ListNode* lastMore = NULL; 
    ListNode* curr = NULL;
    if(head->val < x) lastLess = head; 
    else lastMore = head; 
    curr = head->next; 
    while(curr)
    {
        if(curr->val < x)
        {
            if(!lastLess) //the first element from head is a More swap with that instead
            {
                // This can only happen once or none. 
                lastMore->next  = curr->next; 
                curr->next = head; 
                lastLess = curr; 
                head = curr; 
                curr = lastMore->next; 
            }
            else
            {
                if(!lastMore)
                {
                    lastLess = curr; // MISTAKE: FORGOT TO REASSIGN LASTLESS HERE
                    curr = curr->next; // haven't seen a more. started from less, no swaps needed. 
                }
                else
                {
                    lastMore->next = curr->next; 
                    curr->next = lastLess->next; 
                    lastLess->next = curr; 
                    lastLess = curr; 
                    curr = lastMore->next; 
                }
            }
        }
        else
        {
            // this is the latest maximum, update it 
            lastMore = curr; 
            curr = curr->next; 
        }
    }
    return head; 
}
// */
//----------------------------------------------------------------------------------------
// 11 Insert an element into a sorted circular linked list (Microsoft Round 1)
// Time Complexity, T(n) = O(n) (single pass)
// Space Complexity, S(n) = O(1)
//---------------------------------
/*
Questions: 
    1. Sorted increasing order or decreasing order? 
    2. Can the linked list contain duplicates? 
    3. If contain duplicates, and get duplicate, does it matter where in duplicate i append it? or must it be before the duplicate, after or doesn't matter? 
    4. Does the head always point to smallest/largest element? 
    5. After I insert, does the head maintain where it was or point to new element? 
Function Prototype: 
TestCases: 
    1 => A node by itself
    NULL => No nodes
    1 1 1 2 2 3 -4 -4 -3 -2 => Loop back with duplicates (add biggest of all)
    -4 -3 0 1 1 2 => start from smallest (add smaller than all, add bigger than all, add equal to duplicates)
Algorithm:
    Break into 3 cases: (refer to code for exact implementation, was basically accounting for all corner cases)
        < head
        > head 
        == head 
            whenever == curr => just append there  (newnode->next= curr->next; curr->next = newNode);
        account for reaching back into head after a loop
        next is >, < , == current? 
*/
//---------------------------------
/* //
#include <cstdlib>
#include <vector>
#include <iostream> 
using namespace std; 

struct node {
    int value; 
    struct node * next; 
};

void insertHere(struct node * here, struct node * newNode)
{
    newNode->next = here->next; 
    here->next = newNode; 
    return;
}

void insertCircularLinkedList(struct node * head, int value)
{
    // Handle base case
    struct node * newNode = (struct node *) malloc(sizeof(struct node));
    newNode->value = value; 
    newNode->next = newNode; // point to itself originally
    if(!head) head = newNode; 
    bool more = false; // initialize to value is < current value
    // Check if less than or more than
    struct node * curr = head; 
    if(value > head->value)
    {
        more = true;
    }
    while(curr->next != head)
    {
        // If ever equal, just append it right away
        if(value == curr->value) 
        {
            return insertHere(curr, newNode); // MISTAKE: Forgot to return after inserting
        }
        // Handle the < case
        else if(!more)
        {
            // If pass maximum and still less than 
            if(curr->next->value < curr->value && value < curr->next->value)
            {
                return insertHere(curr, newNode); 
            }
            // else if starts to get bigger, treat as bigger case
            else if( value > curr->next->value)
            {
                more = true; 
            }
        }
        else
        {
            // If it has been more than curr node, insert if it is now less than next node or next node is the crossing of the loop, which means this element is biggest than all
            if(value < curr->next->value || curr->next->value < curr->value)
            {
                return insertHere(curr, newNode);
            }
        }
        curr = curr->next;
    }
    // here, curr->next is equal to head
    // If it was smaller all along, appending to 
    return insertHere(curr, newNode);
}

void printCircularLinkedList(struct node * head)
{
    if(!head) return;
    struct node * curr = head;
    cout << curr->value << " ";
    curr = curr->next;
    if(head->next == head) return;
    cout << curr->value << " ";
    curr = curr->next;
    while(curr != head->next)
    {
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl;
    return;
}

int main(void)
{
    int N = 20; 
    struct node * head = NULL;
    struct node * last = NULL;
    for(int i = N-1; i >= 0; i--)
    {
        struct node * newNode = (struct node*) malloc(sizeof(struct node));
        newNode->value = i & 0x1 ? i*2 - 2 - N/2 : i*2 - N/2;
        newNode->next = head; 
        head = newNode;
        if(!last) last = newNode;
    }
    last->next = head;
    printCircularLinkedList(head);
    for (int i = 0; i < 2; i++)
    {
        // Start inserting
        int val = -30 + 2*i;
        // Head points to smallest at first, but will no longer point to smallest once inserting starts
        // i) Insert smaller than head
        insertCircularLinkedList(head , val);
        cout << "Inserting value: " << val << endl;
        printCircularLinkedList(head);
        val = 30 + 2*i;
        // ii) Insert biggest
        insertCircularLinkedList(head , val);
        cout << "Inserting value: " << val << endl;
        printCircularLinkedList(head);
        // iii) Insert middle
        val = 5 + 2*i;
        insertCircularLinkedList(head , val);
        cout << "Inserting value: " << val << endl;
        printCircularLinkedList(head);
        // iii) Insert duplicate
        val = 6 + 2*i;
        insertCircularLinkedList(head , val);
        cout << "Inserting value: " << val << endl;
        printCircularLinkedList(head);
        // move the head and insert again
        head  = head->next->next->next; 
    }
    // Head points to middle 
    return 0;
}
// */
//----------------------------------------------------------------------------------------
// 12 Find intersection point of 2 singly linked list
// Time Complexity, T(n,m) = O(n + m + max(n,m))
// Space Complexity, S(n,m) = O(1)
//---------------------------------
/*
Questions:
    1. What if no intersection? return NULL
*/
//---------------------------------
/* //
#include <cstdlib> // malloc()
#include <iostream> 
using namespace std; 

struct node {
    int value; 
    struct node* next; 
};

struct node * findIntersectionPointLinkedList(struct node * head1, struct node * head2)
{
    if(!head1 || !head2) return NULL; // no intersection if any list is NULL
    int lengthOne = 0, lengthTwo = 0;
    struct node * curr = head1;
    while(curr)
    {
        lengthOne++;
        curr = curr->next;
    }
    curr = head2;
    while(curr)
    {
        lengthTwo++;
        curr = curr->next;
    }
    struct node * bigHead = lengthOne >= lengthTwo ? head1 : head2;
    struct node * smallHead = lengthOne >= lengthTwo ? head2 : head1;
    int bigLength = lengthOne >= lengthTwo ? lengthOne : lengthTwo;
    int smallLength = lengthOne >= lengthTwo ? lengthTwo : lengthOne;
    curr = bigHead;
    while(bigLength > smallLength)
    {
        bigHead = bigHead->next;
        bigLength--;
    }
    while(bigHead)
    {
        if(bigHead == smallHead) return bigHead;
        bigHead = bigHead->next;
        smallHead = smallHead->next;
    }
    // here means no intersection
    return NULL; 
}

void printLinkedList(struct node* head)
{
    struct node* curr = head; 
    while(curr)
    {
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl;
}

int main(void)
{
    int N = 8;
    int M = 5; 
    struct node * head2 = NULL;
    struct node * last2 = NULL;
    for(int i = 1; i < 3; i++)
    {
        struct node* newNode = (struct node *) malloc(sizeof(struct node));
        newNode->value = -i; // doesn't matter here
        newNode->next = head2; 
        head2 = newNode;
        if(!last2) last2 = newNode;
    }
    struct node * head1 = NULL;
    for(int i = 0; i < N; i++)
    {
        struct node* newNode = (struct node *) malloc(sizeof(struct node));
        newNode->value = i; // doesn't matter here
        newNode->next = head1; 
        head1 = newNode;
        if(N-M-1 == i) last2->next = newNode;
    }
    printLinkedList(head1);
    printLinkedList(head2);
    struct node * newHead = findIntersectionPointLinkedList(head1, head2);
    printLinkedList(newHead);
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 13 Reverse linked list in groups of given size
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
//---------------------------------
/*
Questions:
    1. What if size is more that the size of linked list? Reverse entire linked list
    2. What if size of linked list is not exactly divisble by size? Then reverse the initial groups and reverse the final smaller size group by itself
Function Prototype:
    struct node * reverseLinkedListGroup(struct node * head, int size);
TestCases: 
    1 -> 2 -> 3 -> 4 -> 5, 2 => 2 -> 1 -> 4 -> 3 -> 5
    1 -> 2 -> 3 -> 4 -> 5, 3 => 3 -> 2 -> 1 -> 5 -> 4
    1 -> 2, 2 => 2 -> 1
Algorithm: 
    T(n) = O(n), S(n) = O(1)
    Just iterate until reach size and reverse it in place
    Base case: size == 1, or 1 node or no node, return head
    While(!curr)
        If size > linked list's current group
            Then just reverse entire remaining linked list
            Point last group's lastNode to latest first node. 
        else
            switch the entire current group first. 
            Point last element of last group to current group new first element
    Corner case: Assign ret node to the first group's first element and return that for function
Implement
Test!
*/
//---------------------------------
/* //
#include <iostream> 
using namespace std; 

struct node {
    int val; 
    struct node * next; 
    node(int _val, struct node * _next) : val(_val), next(_next) {}
};

struct node * reverseLinkedListGroup(struct node * head, int size)
{
    if((size <= 1) || (!head) || (!head->next)) return head;  // Base case
    struct node * prev, * curr, * next, * groupTail, * lastGroupTail, * ret; // Mistake: Did not include '*' before each other variable declaration
    ret = NULL;
    lastGroupTail = NULL;
    groupTail = head;
    prev = head; 
    curr = prev->next;
    while(curr)
    {
        for(int i = 1; i < size; i++) // TODO: Account for size larger than initial and size smaller than initial
        {
            if(!curr) break;
            next = curr->next;
            curr->next = prev; 
            prev = curr; 
            curr = next; 
        }
        if(curr)
        {
            // Here, means current group is done
            if(!ret) ret = prev; // assign first node if not yet assigned
            else lastGroupTail->next = prev; // Mistake: Did not handle lastGroupTail to point to current group's new head
            prev = curr;
            curr = curr->next; 
            lastGroupTail = groupTail;
            groupTail = prev; // point to new groupTail
        }
        // If already last group
        if(!curr) // note: Needs to be if instead of else to handle conditions after the if(curr) above
        {
            groupTail->next = NULL;
            if(lastGroupTail) lastGroupTail->next = prev;  // assign last group's tail to current group's head
            if(ret) return ret; 
            return prev; // If size is larger than entire linked list
        }
    }
    // Will never be here
}

void printLinkedList(struct node * head)
{
    struct node * curr = head;
    while(curr)
    {
        cout << curr->val << " ";
        curr = curr->next; 
    }
    cout << endl;
    return;
}

int main(void)
{
    struct node a5(5, NULL);
    struct node a4(4, &a5);
    struct node a3(3, &a4);
    struct node a2(2, &a3);
    struct node a1(1, &a2);
    struct node * a1a = reverseLinkedListGroup(&a1, 2);
    printLinkedList(a1a);
    a1a = reverseLinkedListGroup(a1a, 2); // fix original
    a1a = reverseLinkedListGroup(&a1, 3);
    printLinkedList(a1a);
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------
