//----------------------------------------------------------------------------------------------------------------------------------
/* //
TODO: 
    Add 'using' as replacement for typedef
    Add nullptr
    add constexpr
    Add checking resource is closed properly in clean code (C++ does not have finally block) 
Table of Contents
C++ is divided into:
  - C
  - Classes
  - STL
  - Templates (Generics)
  Practices depends on which part of C++ you are using.
//-------------------------
// A) Standard Template Library
//-------------------------
1. Implementation of Standard Template Library  internally
2. Benefits of Iterators
//-------------------------
// B) Functions
//-------------------------
1. Pass by Value vs Pass by Reference
2. Pass by Reference Avoids Slicing
3. Return By Value > Return By Reference for Local (stack,heap,static) Variables
//-------------------------
// C) Constructors & Overloading
//-------------------------
1. Default Constructors
2. Copy Constructor vs Assignment Operator vs Move Constructor
3. Flow of Program
4. Operator Overloading
5. Initialization > Default Constructor + Assignment
6. Destructors Throwing Exceptions Must Be Handled
7. Explicit Constructors
8. No Virtual methods in Constructor & Destructor
9. No Copy And Assign
10. Right Associative Assignment Operators
11. Overriding Copy Constructor and Assignment Operator
//-------------------------
// D) Inheritance
//-------------------------
1. Inheritance
2. Virtual
3. Private, Protected, Public
4. this vs *this
5. Never Inherit Non-virtual Destructors
6. override & final
//-------------------------
// E) Plain Old C, C++, C++11, C++14
//-------------------------
1. const
2. (const, enum, inline) > define
3. Order of Initialization
4. auto , auto& , auto*
TODO:
  100. Memory Layout of C Programs
      http://www.geeksforgeeks.org/memory-layout-of-c-program/
//-------------------------
Reference:
Effective C++ Series by Scott Meyers
Exceptional C++ Series by Herb Sutter
//-------------------------
// */
//----------------------------------------------------------------------------------------------------------------------------------
// A) Standard Template Library
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
// 2 Benefits of Iterators
//----------------------------------------------------------------------------------------------------------------------------------
Without Iterators,
    indexing an array can be done using *p to get the value, p++, p+5 etc.
    indexing a linked list has to be done using p = p->next;
With Iterators,
    indexing both a <vector> and <list> can be done using p++; (instead of p = p->next), where p++ is operator overloaded of ++ by doing p = p->next; 
//----------------------------------------------------------------------------------------------------------------------------------
// B) Functions
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Pass by Value vs Pass by Reference
//---------------------------------
Reference
    Can't change a reference or assign a reference to another object
    Can't reference a reference
    Taking address of a reference is just the reference of the object instead of address of the reference itself. 

Pass by:
value                               |           reference
local copy, returns new copy                    changes actual copy, modifies actual data
Can't change actual copy                        Less memory used
can only return 1 value                         Can return multiple values  
less efficient due to copying                   More efficient as no copy constructor called

//----------------------------------------------------------------------------------------------------------------------------------
// 2 Pass by Reference Avoids Slicing
//---------------------------------
If you pass by value, the object gets copied in the function. 
Problem:
    MethodPassByValueWillSliceChildren(ParentClass parent); 
    MethodPassByValueWillSliceChildren(child); // Problem: Only the parent's part are copied, not the children. 
Solution:
    MethodPassByReferenceWillNotSliceChildren(ParentClass& parent);
    MethodPassByReferenceWillNotSliceChildren(child); // success, it gets a reference to child, so no slicing occurs.

//----------------------------------------------------------------------------------------------------------------------------------
// 3 Return By Value > Return By Reference for Local (stack,heap,static) Variables
//---------------------------------
// Problem: Return by reference;
ClassName& functionReturnsByReference() {
    ClassName localStackVariable;
    ClassName localHeapVariable = new ClassName();
    static ClassName localStaticVariable;
    ...
    return localStackVariable; 
        // Problems: 
        //  This local stack will not exist after function goes out of scope, undefined behavior!
    return localHeapVariable;
        // Problems:
            // How does client know it needs to call delete on this? resource leak!
            //  If this function was overloading operators like '*', then this client expression:
            //      ClassName result = a * b * c; will definitely leak resources as no one has access to result of (b*c) in (a*(b*c))

    return localStaticVariable; 
    // If this function was overloading operator '*', then AssertTrue((a*b)==(c*d)) since will always refer to same static result value returned
}
Solution: Return by value for localStackVariable
//----------------------------------------------------------------------------------------------------------------------------------
// C) Constructors
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Default Constructors
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
// 2 Copy Constructor vs Assignment Operator vs Move Constructor
//---------------------------------
// Copy constructor is called when an object is passed by value into a function, or when instantiate using 'new' 
// If no pointers, no need to define destructor as default destructor deletes original object for you
a = b; // invokes Assignment Operator, NOT copy constructor  , when '=' is used for assignment (not constructing a new 'a')
className a = b; // invokes Copy Constructor when '=' is used for initialization (constructing a new 'a')
a = new b; // '=' invokes Assignment Operator, 'new' invokes Copy Constructor
a = std::move(b); // invokes Move Constructor
return b; // invokes Move Constructor
//----------------------------------------------------------------------------------------------------------------------------------
// 3 Flow of Program
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
// 4 Operator Overloading 
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
// 5 Initialization > Default Constructor + Assignment
//---------------------------------
// note: This is only true for classes. There is no difference for primitives like int, double
from:
  // This constructor calls default constructor, then assigns the value, which wastes the effort of default constructor
  ClassName(const std::string& input_name) { this->name = input_name; }
to:
  // This constructor initializes member variable this->name to name, therefore is more efficient
  ClassName(const std::string& input_name) : this->name(input_name) {}
//----------------------------------------------------------------------------------------------------------------------------------
// 6 Destructors Throwing Exceptions Must Be Handled
//---------------------------------
If a class's destructor throws exceptions that isn't handled, undefined behavior can occur. 
If a vector contains multiple instances of this class, destruction of this vector may result in more than 1 exception
being thrown which will result in undefined behavior. 
Therefore, all destructors that contain exceptions must be handled by either:
1. Terminating the program.
2. Swallowing the exception, then logging the error, and maybe notify client via another function. 
e.g. 
public:
  bool errorOccurred;
  ~ClassName() {
    try {
      database.close(); // may throw exception
    } catch (int e) {
      cerr << "Error occurred" << endl;
      errorOccurred = true; // allows clients to detect
    }
  }
//----------------------------------------------------------------------------------------------------------------------------------
// 7 Explicit Constructors
//---------------------------------
// Implicit conversions can happen automatically 
class Foo {
Foo(int integerNeededForFooConstructor);
};

methodThatUsesFoo(Foo aFooObject);

int main() {
    methodThatUsesFoo(42); // legal, implicitly called Foo's constructor, construct Foo's object, thatn uses this method
}
Problems & Solution:
class MyString {
MyString(int sizeOfStringToAllocate);
}
class MyExplicitString {
explicit MyExplicitString(int sizeOfStringToAllocate);
}
printMethodForMyString(MyString stringToPrint);
printMethodForMyExplicitString(MyExplicitString stringToPrint);
int main() {
    // Want to print "50", but printed an empty string with size 50 instead. 
    printMethodForMyString(50); 
    // Want to print "50"
    printMethodForMyExplicitString(50);  // Error!
    printMethodForMyExplicitString(MyExplicitString(50)); // you know exactly what is happening here, it prints en empty string with size 50, so it's clearer. 
    MyExplicitString mES(50);
    mES.setString("50");
    printMethodForMyExplicitString(mES);
}
//----------------------------------------------------------------------------------------------------------------------------------
// 8 No Virtual methods in Constructor & Destructor
//---------------------------------
Problem: Will not call derived class's method during construction and destruction. 
Assume you wanna output logs for each derived class constructored

class BaseClass {
    BaseClass() {
        logOutput(); // output logs each time anything is constructed
        indirectNonVirtualButCallsVirtual();
    }
    virtual void logOutput() = 0; // must be overriden
    void indirectNonVirtualButCallsVirtual() {
        logOutput(); 
    }

};

class Derive1 : public BaseClass {
    virtual void logOutput() override;
};

int main() {
    // Want to log "derive1", but resulted in undefined behavior instead.
    Derive1 derive1; 
}

Problem: 
    When Base class is constructed, derived class isn't constructed yet, therefore, virtual methods such as logOutput() will call the
    Base class's logOutput() instead of derived classes logOutput()
    logOutput() wouldn't compile since BaseClass does not implement it
    indirectNonVirtualButCallsvirtual() will compile since it is non-virtual but will have linking errors during runtime since it calls
        logOutput() which isn't define in base class during construction().
    Destructors have a similar problem since the derived classes are destroyed before the Base classes' destructor are called. 
Solution:
    Pass the info needed by base class during construction and use only non-virtual methods that do not call any virtual methods

class BaseClass { 
    BaseClass(string logOutputString) {
        logOutput(logOutputString);
    }
    void logOutput(string stringToLog);
}
class Derive1 : public BaseClass {
    // Pass log information to base class during construction
    Derive1() : BaseClass("I am derive class 1") {};
}

int main() {
    Derive1 derive1; // does what you want, the base class will constructor will log the correct log information as needed.
}
//----------------------------------------------------------------------------------------------------------------------------------
// 9 No Copy And Assign
//---------------------------------
No copying
    NoCopyingAndAssignClass original;
    NoCopyingAndAssignClass copy(original); // copy constructor
    NoCopyingAndAssignClass reassign = original; // assignment operator

class NoCopyingAndAssignClass{
    // Set both copy constructor and assignment operator to '= delete'
    NoCopyingAndAssignClass(const NoCopyingAndAssignClass&) = delete; 
    NoCopyingAndAssignClass& operator = (const NoCopyingAndAssignClass&) = delete;
}
//----------------------------------------------------------------------------------------------------------------------------------
// 10 Right Associative Assignment Operators
//---------------------------------
// Applies to (= , +=, -=, *=, /=)
// x = y = z = 15 means x = (y = (z = 15 ))
// Convention from C++ is to be right associative assignment. 
// To do so, you return this* in overloading any assignment operators

ClassName& operator = (const ClassName& rhs) {
    ...
    return *this;
}
//----------------------------------------------------------------------------------------------------------------------------------
// 11 Overriding Copy Constructor and Assignment Operator
//---------------------------------
Problems:
    Assume you override copy constructor and Assignment Operator, however, you added a new member variable, now you must remember
    to update both of them to copy that extra member variable.

    Similarly, must always call base's classes copy constructor and assignment operator as there may be member variables
    that are only visible in base class that needs to be copied over. 

    Copy constructor and Assignment operator shares a lot of common code. DON'T call one from the other as neither makes any sense. 
    Put common code in a local function that both calls. In other words, don't call copy constructor from assignment operator and vice versa. 
    Doesn't make sense because:
        call assignment operator from copy constructor => Assigning to existing when not even created yet
        call copy constructor from assignment operator => creating something new when it already exist
Solution:
    Copy everything
        Need to update both of them each time new member comes
        Need to remember to call base's classes copy constructor and assignment operator
    Share common methods in a local private method. 

ChildClass::ChildCass(const ChildClass& rhs)
    : ParentClass(rhs), // invoke parent's copy constructor
      childClassMemberOne(rhs.childClassMemberOne) { 
      init();}
      
ChildClass& ChildClass::operator = (const ChildClass& rhs) {
    ParentClass::operator=(rhs); // assign parent's class member variable
    childClassMemberOne = rhs.childClassMemberOne;
    init(); // call common function
    return *this;
} 
//----------------------------------------------------------------------------------------------------------------------------------
// D) Inheritance
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Inheritance
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
// 2 Virtual
//---------------------------------
// Function
A function declared virtual will call its derived class before itself for a pointer from the base class
Without virtual, the pointer will call the base's class function 
//---------------------------------

//----------------------------------------------------------------------------------------------------------------------------------
// 3 Private, Protected, Public
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
// 4 this vs *this
//---------------------------------
this => A pointer to the object calling the function
*this => A reference to the object calling the function
    e.g.
    className& className::operator = (const className &rhs) {
        this->value = rhs.value;
        return *this;
    }
//----------------------------------------------------------------------------------------------------------------------------------
// 5 Never Inherit Non-virtual Destructors
//---------------------------------
Virtual destructor ensures that it calls the child's destructor before itself.
If you inherit non-virtual destructors, deleting the object using the parent's pointer may only call the parent's destructor,
resulting in memory leak.
  public OwnString :: std::string {
  }
  OwnString* os = new OwnString("lala");
  std::string* s; 
  s = os;
  delete s; // Will only call std::string's destructor without calling own string's destructor
// note: Don't always declare every destructor virtual unless it is needed
// because anything declared virtual will require a virtual table and virtual
// pointers which takes up more memory in C++ (e.g. from 32-bit to 64-bit) 
//----------------------------------------------------------------------------------------------------------------------------------
// 6 override & final
//---------------------------------
// Problem: Think you override a base class's method but you didn't due to typo. 
    // Imagine base class's method is 
    const void methodName(); 
    // But child class wanted to override was
    void methodName(); 
    // Then in code, think you are calling child class method but actually calling base class method cause didn't override
// Solution: 
    //In child class, type
    void methodName() override; // will generate compile time error as you are not overriding anything. 
    const void methodName() override; // no compile time error as did override
 
// If don't want a method to be overriden, declare it final
    // In base class, 
   final void methodName();
   // In derived class,
   void methodName() override; // compile time error! Can't override final methods
//----------------------------------------------------------------------------------------------------------------------------------
// E) Plain Old C, C++, C++11, C++14
//----------------------------------------------------------------------------------------------------------------------------------
// 1 const
//---------------------------------
// value is constant (const before '*')
const char * aa = "lala"; 
char const * aa = "lala"; 
// pointer is const (const after '*')
char * const aa = "lala";
// both value and pointer are const
const char * const aa = "lala";
char const * const aa = "lala";
// Make all results of user-defined operator (+,-,*,/) constants
const className operator*(const className& lhs, const className& rhs);
  // This avoid typos of using '=' instead of '=='
    if((a*b) = c) // this will be true if c != 0 since it is an assignment!
    // However, defining results of operator to be constant makes this a compilation error.

//----------------------------------------------------------------------------------------------------------------------------------
// 2 (const, enum, inline) > #define
//---------------------------------
// Simple Constants
#define LALA 1.653
Problems:
  When error occurs, compiler will say error with 1.653, it doesn't actually save the word 'LALA' into symbol table, this makes it harder to debug. 
  There is no scoping for #define
  Can't take address to #define & enum, but can take address of const

Solution: // const
  const double Lala = 1.653;

// Imagine you want the constant to be within the scope of class only that is
// used directly in an array
class someClass {
private:
  const double Lele = 3;
  int scores[Lele]
}
Problems:
  Some compilers don't let you define the values during compilation time
Solution: // enum
  class someClass {
  private:
    enum { Lele = 3 };
    int scores[Lele]
  }
//---------------------------------
// Function macros
#define CALL_MAX(a,b) f((a) > (b) ? (a) : (b))
Problems:
  Hard to write, need '()' for every argument
  Different behavior depending on argument
    int a = 5, b = 0;
    CALL_MAX(++a, b); // a is incremented twice
    CALL_MAX(++a, b+10); // a is  incremented once
Solution: inline
  template<typename T>
  inline void callMax(const T& a, const T& b) {
    f(a > b ? a : b);
  }
//----------------------------------------------------------------------------------------------------------------------------------
// 3 Order of Initialization
//---------------------------------
Unitialize objects that are accidentally used are  very common and yields undefined behavior.
  from:
    int x;
    doSomething(x); // may cause error since x has random values
  to:
    int x = 0;
    doSomething(x); // easier to debug if errors
If order of initialization matters, using another object may result in that object not being initialized yet.
Therefore, define static objects in functions as they are guaranteed to be initialized if local static to a function (Singleton Pattern)
  from:
    static int aStaticThatDependsOnStatic = bStaticThatMayNotYetBeInitialized + 3;
    static int bStatic = 0;
  to:
    int aStaticThatDependsOnStatic() {
      static int aStaticThatDependsOnStatic = bStaticThatWillBeInitialized() + 3;
      return aStaticThatDependsOnStatic;
    }
    int bStaticThatWillBeInitialized() {
      static int bStaticThatWillBeInitialized = 0;
      return bStaticThatWillBeInitialized;
    }
//----------------------------------------------------------------------------------------------------------------------------------
// 4 auto , auto& , auto*
//---------------------------------
// auto will copy by value for references, however, if you want to copy by reference, use auto&, 
// auto* is useless as it behaves the same as auto when copying pointers. 
int a = 2; 
int& b = a;
auto c = b; // note: c is an 'int', NOT 'int&' like b
int* p1 = &a;
auto d = p1 // d is 'int*', auto does correct behavior
auto* e = p1; // e is also 'int*', so auto* is useless as it does the same thing as 'auto' on pointers
//----------------------------------------------------------------------------------------------------------------------------------
