//
//----------------------------------------------------------------------------------------
/* //
Table of Contents
1. Introduction to Stacks with C++ Standard Template Library, T(n) = O(1), S(n) = O(1)
2. Stack that can return mininum value element efficiently, T(n) = O(1), S(n) = O(n). (Bloomberg 2nd round)

TODO:
0. Implement a class for Stacks using (Array, LinkedList) and comparisons
3. Implement to add more stacks when 1 stack is filled as well as add rollover
    // rollover => If delete from lower stacks, need shift all elements from upper stacks down
4. Code Tower of Hanoi solution using stacks
note: Your solution was not the best, the best it to have a 2nd array for mins
and whenever you pop a value that is the same as the current min, you pop the min as well
or when you add a value lower than current min, you push to the 2nd array's min.
6. Implement a queue using 2 stacks
7. Find out if the braces, brackets open and close properly (Cast Software Interview)
2. Implement 3 stacks in one array, T(n) = O(...), S(n) = O(n)
    // Note: basically every stack function has an additional stackNumber parameter. 
// */
//----------------------------------------------------------------------------------------
/* //
// 1 Introduction to Stacks with C++ Standard Template Library
#include <iostream>
#include <stack>
    // s.push(value)
    // s.top()
    // s.pop()
    // s.size()
    // s.empty()
    // s1.swap(s2)
        // swap 2 stacks with each other

using namespace std;

int main(void)
{
    // values of the stack
    stack<int> s;
    s.push(3);
    if (!s.empty())
    {
        // is peeking the top element
        cout << s.top()  << endl;
    }
    s.pop(); // no return values
    if(s.empty())
    {
        cout << "Stack is empty" << endl;
    }
    s.push(4);
    s.push(5);
    cout << "Number of elements in stack is " << s.size() << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------
/* //
// 2  Stack that can return the minimum value element efficiently.  
// Time Complexity, T(n) = O(1)
// Space Complexity, S(n) = O(n)
#include <cstdio> 
#include <cstdlib> 
#include <iostream> 
#include <stack>
using namespace std; 

class minStack {
private:
    stack<int> s; 
    stack<int> sMin; 
public:
    minStack();
    void push(int value);
    void pop();
    int top();
    int min();
    bool empty();
};

minStack::minStack() 
{
    cout << "Contructor created" << endl;
}

void minStack::push(int value) 
{
    // If first minimum value or the latest value is a new minimum
    if(sMin.empty() || value <= sMin.top())
    {
        sMin.push(value);
    }
    // push the value to actual stack regardless
    s.push(value);
}

void minStack::pop()
{
    // If stack is empty, don't do anything
    if (s.empty()) return;
    // If popping a minimum value
    if (s.top() == sMin.top())
    {
        // Pop the latest minimum value
        sMin.pop();
    }
    s.pop();
}

int minStack::top()
{
    return s.top();
}

int minStack::min()
{
    return sMin.top();
}

bool minStack::empty()
{
    return s.empty();
}


int main(void)
{
    minStack m; 
    // Set stack to be 2,5,3,3,4
    // which means minStack is: 2,3,3,4
    m.push(4);
    m.push(3);
    m.push(3);
    m.push(5);
    m.push(2);
    while(!m.empty())
    {
        cout << m.top() << " : " << m.min()  << endl;
        m.pop();
    }
    return 0;
}
// */
//----------------------------------------------------------------------------------------
