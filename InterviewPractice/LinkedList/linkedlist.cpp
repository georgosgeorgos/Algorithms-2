//
//----------------------------------------------------------------------------------------
/* //
>> g++ -std=c++11 linkedlist.cpp
>> a.exe
Table of Contents
1. Reverse a Linked list, T(n) = O(n),  S(n) = O(1)
2. Adding two numbers that are represented by linked lists, T(n) = O(n), S(n) = O(n)
3. Remove Duplicates From Linked List, T(n) = O(n^2), S(n) = O(1), (if don't need maintain order), T(n) = O(nlogn), S(n) = O(n)

Hints: 
- Memory address of linkedlist is unique (pointed to by pointers)
- Can always break circular linked list, solve the problem, then link it back to become circular again

#include <forward_list> 
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

// TODO: Detect if a Linked List is circular
// TODO: Insert an element into a sorted circular linked list (Microsoft Round 1)
// */

//----------------------------------------------------------------------------------------
/*
// 1 Reverse a Linked list
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
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
    if(head == NULL)
        return head;
    prev = head;
    curr = head->next;
    if(curr == NULL)
        return head;

    // NOTE: MISTAKE HERE!! Forgot to point first element to NULL
    prev->next = NULL; // point first element to NULL
    //while(curr) // NOTE: MISTAKE HERE! DID while(!curr) instead of while(curr) 
    while(curr!= NULL)
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
//----------------------------------------------------------------------------------------
/* //
// 2 Adding two numbers that are represented by linked lists
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(n)
// 5->4 + 8->7  = 1->4->1
// Simply perform reverse  linked list algorithm on both lists first, then you can add from the back 
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
//----------------------------------------------------------------------------------------
/* //
// 3 Remove Duplicates From Linked List

// Method 1: Sort, Then Remove Duplicates 
// Time Complexity, T(n) = O(nlogn) 
// Space Complexity, S(n) = O(1) 
// Method 2: Remove Duplicates Directly
// Time Complexity, T(n) = O(n^2) 
// Space Complexity, S(n) = O(1) 
// note: Can reduce T(n) to O(1) by sacrificing space using hash table

#include <cstdio>
#include <cstdlib> 
#include <iostream> 
#include <forward_list> // singly linked list
using namespace std; 

forward_list<int> removeDuplicateWithSort(forward_list<int> dup);
struct node* removeDuplicate(struct node* head);
struct node {
    int value; 
    struct node* next; 
};

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
// */
//----------------------------------------------------------------------------------------
