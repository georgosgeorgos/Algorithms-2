//
//----------------------------------------------------------------------------------------------------------------------------------
/* //
Table of Contents
1. Implementation of Standard Template Library  internally
2. Pass by Value vs Pass by Reference
3. Default Constructors
4. Copy Constructor vs Assignment Operator
5. Virtual
6. Benefits of Iterators
7. Flow of Program
8. Operator Overloading 
9. Inheritance
10. Private, Protected, Public
11. this vs *this
//-------------------------
TODO:
21. Memory Layout of C Programs
    http://www.geeksforgeeks.org/memory-layout-of-c-program/

//----------------------------------------------------------------------------------------------------------------------------------
// notes
//-------------------------
- Nothing is this file is actually compilable so no point commenting out everything. It is more of answering by proof of concept style questions
//----------------------------------------------------------------------------------------------------------------------------------
// Common Hints
//-------------------------
- 
//-------------------------
// Common Questions
//-------------------------
- 
// */
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Implementation of Standard Template Library  internally
//---------------------------------
<array> => One dimensional Fixed Sized array
<vector> => Dynamically resizable One Dimensional array
    note: Can use vector<vector<int>> to make a 2D container
<deque> => Double Ended Queue
<queue> => Queue, Priority Queue
<stack> => Stack
<list> => Doubly Linked List
<forward_list> => Singly Linked List
<bitset> => array of bools
<set> => Set, Multiset (multi => Duplicated keys allowed)
<map> => Associative Array (Balanced Binary Tree), Multimap (multi => Duplicated keys allowed)
    Keys in map are automatically sorted
<unordered_map> => Hashed Associative Array (Hash Table)
    unordered => Don't have any > or <  relation
<unordered_set> => Hashed Set
//----------------------------------------------------------------------------------------------------------------------------------
// 2 Pass by Value vs Pass by Reference
//---------------------------------
Reference
    Can't change a reference or assign a reference toa nother object
    Can't reference a reference
    Taking address of a reference is just the reference of the object instead of address of the reference itself. 

Pass by: 
value                               |           reference
local copy, returns new copy                    changes actual copy 
Can't change actual copy                        Less memory used
can only return 1 value                         Can return multiple values  
//----------------------------------------------------------------------------------------------------------------------------------
// 3 Default Constructors
//---------------------------------
// Default Constructor
classname::classname(); // Does a shallow copy of everything (pointers point to exact same object that exists before) 
// Copy Constructor
classname::classname(const classname &a); // Pass by reference, if pass by value, the copy constructor will call itself infinitely. 
// Default Destructor
classname::~classname(); // A shallow destroy 
// Note: Once you declare any constructor, the default constructors won't be defined anymore! Trying to use them without defining them will cause compile error.
Constructors and Destructors are called in a Stack approach. 
The first constructor that is called is called last from destructor at end of program 
//----------------------------------------------------------------------------------------------------------------------------------
// 4 Copy Constructor vs Assignment Operator
//---------------------------------
// Copy constructor is called when an object is passed by value into a function, or when instantiate using 'new' 
// If no pointers, no need to define destructor as default destructor deletes original object for you
a = b; // invokes Assignment Operator, NOT copy constructor  , when '=' is used for assignment
className a = b; // invokes Copy Constructor when '=' is used for initialization
a = new b; // '=' invokes Assignment Operator, 'new' invokes Copy Constructor
//----------------------------------------------------------------------------------------------------------------------------------
// 5 Virtual
//---------------------------------
A function declared virtual will call its derived class before itself for a pointer from the base class
Without virtual, the pointer will call the base's class function 
//----------------------------------------------------------------------------------------------------------------------------------
// 6 Benefits of Iterators
//---------------------------------
Without Iterators,
    indexing an array can be done using *p to get the value, p++, p+5 etc.
    indexing a linked list has to be done using p = p->next;
With Iterators,
    indexing both a <vector> and <list> can be done using p++; (instead of p = p->next), where p++ is operator overloaded of ++ by doing p = p->next; 
//----------------------------------------------------------------------------------------------------------------------------------
// 7 Flow of Program
//---------------------------------
#include <cstdlib>
#include <iostream>
using namespace std;

class A {
public:
    A() { cout << "A instantiated" << endl; }
    ~A() { cout << "A deleted" << endl; }
};

A * foo()
{
    A b; // 4
    A * p = NULL;
    cout << "baba" << endl; // 5
    p = new A[2]; // 6 , Note: Does not get deleted
    return p;
    // 7 (4 gets deleted)
}

A a; // 1 Global Variable called before program

int main(void)
{
    A c[3]; // 2
    A * q = NULL; // does not call any constructor since pointer
    cout << "haha" << endl; // 3
    q = foo();
    delete [] q; // 8

    cout << "done" << endl; // 9
    return 0;
    // 10 (2 gets deleted)
}
// 11 (1 gets deleted)
//----------------------------------------------------------------------------------------------------------------------------------
// 8 Operator Overloading 
//---------------------------------
className:: operator * (const className &rhs) const 
// 1st const is to make rhs const
// 2nd const is to make lhs const (lhs is the object calling this operator function) 
c = lhs * rhs; // In this case, lhs is not modified by copy constructor

className::operator - () {
// This is used for the the unary case where:
// a = -b;
}
//----------------------------------------------------------------------------------------------------------------------------------
// 9 Inheritance
//---------------------------------
Derived class inherits:
    i) Member data 
    ii) Member function

Derived class does not inherit: 
    i) Copy constructor 
    ii) Destructor 
    iii) Assignment operator

Derived class can only overload existing member variable or function but can't remove them

Base Class b; 
DerivedClass d; 
DerivedClass * d1 = &b; // this is okay 
BaseClass * b1 = &d; // Compile time error 

// To include BaseClass default constructor in DerivedClass default constructor
DerivedClass::DerivedClass () : BaseClass() {
    // ...
}

// To automatically assign values to members in constructor
BaseClass::BaseClass(int a1, int b1) : a(a1), b(b1) {} 
//----------------------------------------------------------------------------------------------------------------------------------
// 10 Private, Protected, Public
//---------------------------------
#include <iostream>
#include "Class2a.cpp"
using namespace std;
int main()
{
    Class1a OneA;
    OneA.print("1a");
// Error!: cause you are trying to access protected functions in a main's scope
            //    OneA.prosetpriX(4);
            //    OneA.prosetproX(5);
            //    OneA.prosetpubX(6);
// Error!: cause you cant access private and protected members of a class directly in this main scope
            //    OneA.prix = 13;
            //    OneA.prox = 14;
    OneA.pubx = 15; // you can access directly public data from anywhere including in main
    OneA.print("1b");
    Class1a OneA2 = OneA; // copy constructor called, if not defined, a default one that does shallow copy is given!
    OneA2.print("1a2");

    Class1b OneB; // calls constructor from A
    OneB.print("2a");
    OneB.pubsetpriX(1); // main() can make changes from private member data from A
                    // by calling public methods defined
    OneB.pubsetproX(2);
    OneB.pubsetpubX(3);
    OneB.print("2b");
// Error!: cause you are trying to access protected functions in a main's scope
            //    OneB.prosetpriX(4);
            //    OneB.prosetproX(5);
            //    OneB.prosetpubX(6);
// Error!: cause you cant access private and protected members of a class directly in this main scope
            //    OneB.prix = 13;
            //    OneB.prox = 14; // You use this inside classB directly itself, refer to printDerived3
    OneB.pubx = 15;
    OneB.print("2c");
    OneB.printDerived(); // works cause you only access protected methods of A in class B
    OneB.printDerived3();
    Class1b OneB2 = OneB; // calls copy constructor of class B, note: it does not inherit,
                          // copy constructor of class A, so it has its default copy constructr defined
    OneB2.print("2a2");

    Class1a *OneApointer;
    OneApointer = new Class1a; // calls default constructor for Class1a
    OneApointer->print("1Apointer");
    // Note: if you do not delete OneApointer, program will never call the destructor for it!!
    // it only destroys the pointer, not the object OneApointer points to.
    delete OneApointer;
    OneApointer = new Class1b;
// Note: it does not call destructor for Class1b if destructor is not virtual!
    delete OneApointer;
    cout <<" Next Chapter" <<endl;
    Class1b *OneBpointer;
    OneBpointer = new Class1c;
    OneBpointer->print("1Bpointer");

// NOTE: BEFORE TESTING BELOW, OPEN CLASS1A.CPP AND UNCOMMENT LINE
// virtual ~Class1a() and comment out ~Class1a()
// FROM ABOUT LINE 92 of Class1a.cpp
//    ~Class1a()
//   //virtual ~Class1a()

// Note: as long as destructor for class1a is virtual,
// Destructor class1b need not be virtual, and B's pointer destroying class1c
// will still call class1c's destructor first
    delete OneBpointer;
// Similarly for pointerA whose destructor is virtual.
    OneApointer = new Class1c;
    OneApointer->print("1ApointerOnClassC");
    delete OneApointer;

    Class1b hahad;
    hahad.haha(); // you can invoke static functions with an object
    Class1b::haha(); // or without an object, but must declare the class that the static function is in
    // haha(); // ERROR! haha() not declared in this scope cause it doesnt know where to get it from
    return 0;
}
//----------------------------------------------------------------------------------------------------------------------------------
// 11 this vs *this
//---------------------------------
this => A pointer to the object calling the function
*this => A reference to the object calling the function
    e.g. 
    className& className::operator = (const className &rhs) {
        this->value = rhs.value; 
        return *this;
    }
//----------------------------------------------------------------------------------------------------------------------------------
