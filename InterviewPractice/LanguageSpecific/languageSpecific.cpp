//----------------------------------------------------------------------------------------------------------------------------------
/* //
TODO: 
    Add 'using' as replacement for typedef
    Add nullptr
    add constexpr
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
4. Non Member Function to Allow Commutative Operations
5. Postpone Variable Definitions As Long As Possible but Outside Loops
6. Lambdas & Functors && std::function
//-------------------------
// C) Constructors & Overloading
//-------------------------
1. Constructors Given For A Class With No Constructor Implementation
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
12. Handle Assignment To Self
13. No Default Constructor TradeOffs
14. Private Member Method to Function If No Member Variable
15. Multiple Dispatch
//-------------------------
// D) Inheritance
//-------------------------
1. Inheritance
2. Virtual
3. Private, Protected, Public
4. this vs *this
5. Never Inherit Non-virtual Destructors
6. override & final
7. Reduce Compilation Dependencies
8. Overriding Base Method Hides All Overloaded Base Method
9. Private Inheritance for Sharing Code Without Relationships
10. Virtual Public Inheritance for Multiple Paths To Base
11. Array/Pointer Arithmetics and Polymophism Doesn't Work
//-------------------------
// E) Exceptions
//-------------------------
1. Exception Safety
2. No Exceptions in Destructor
3. Exception vs Method
4. throw vs throw e
//-------------------------
// F) Plain Old C, C++, C++11, C++14
//-------------------------
1. const
2. (const, enum, inline) > define
3. Order of Initialization
4. auto , auto& , auto*
5. inline
6. Pointer vs Reference
7. (new, operator new, delete, operator delete, new [], delete [], operator new [], operator delete [])
8. Include Only Files Needed By Client
9. Switch vs Else If 
10. Using
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
// 4 Non Member Function to Allow Commutative Operations
//---------------------------------
You can overload operator '*' for a RationalNumber class.
const Rational operator * (const Rational& rhs) const; 
Problem:
    // In client code
    Rational oneHalf(1,2);
    Rational result = oneHalf * 2; // fine, because it implicitly converts 2 to a Rational assuming constructor Rational(int) exist
    Rational result2 = 2 * oneHalf; // error, because the type 'int' doesn't take in Rational as its constructor
Solution:
    Declare a non-member function that takes 2 class objects instead. 
const Rational operator * (const Rational& lhs, const Rational& rhs);
    // In client code
    Rational result = oneHalf * 2; // Works
    Rational result2 = 2 * oneHalf; // Works as well
//----------------------------------------------------------------------------------------------------------------------------------
// 5 Postpone Variable Definitions As Long As Possible but Outside Loops
//---------------------------------
Always postpone variable definition until you need them
from:
    string encrypted;
    thisFuncMayThrowError(); // Problem: If this throws error, then you are creating and destructing encrypted for no reason
    functionUsingEncrypted(encrypted);
to:
    thisFuncMayThrowError();
    string encrypted;
    functionUsingEncrypted(encrypted);

from:
    // Problem: n constructor + n destructor
    for(int i = 0; i < n; i++) {
        string encrypted(assignValueDependentOn(i);
        functionUsingEncrypted(encrypted);
    }
to:
    // Solution: 1 constructor + 1 desctructor + n assignments
    string encrypted
    for(int i = 0; i < n; i++) {
        encrypted = assignValueDependentOn(i)
        functionUsingEncrypted(encrypted);
    }
    // note: Use the one inside loop if (cost(assignment) > (cost(constructor) + cost(destructor)))
//----------------------------------------------------------------------------------------------------------------------------------
// 6 Lambdas & Functors && std::function
//---------------------------------
Functors = Function Objects = Objects that can be treated like functions & function pointers.
    Overload operator() to indicate a class is a Functor
Functors allow easier to  with STL or third party code (note: Functors were made for cases like this
// e.g. To work with STL's sort, it must take in a comparison function that only accepts (lhs,rhs) and returns bool
//      But if your own comparison function needs extra parameters, you can encapsulate it inside a Functor object
//      Otherwise, would have to write own sort() function that is aware of the extra parameters
from: Writing own sort() function
    bool SuperLongOwnSortFunctionToWorkWithExtraVariableCalledPercentageComparison(vector<objectToCompare>& objects, int percentageComparison){
        .... // code to sort the objects
    }
to: Using existing std::sort()
    class aFunctorClass {
     public:
     // Overriding operator() makes this class a Functor object
     aFunctorClass(int percentageComparison_) : this->percentageComparison(percentageComparison_) {}
     bool operator() (const objectToCompare& lhs, const objectToCompare& rhs) {
        return lhs.calculateFinalWeightBasedOnPercentage(this->percentageComparison) < rhs.calculateFinalWeightBasedOnPercentage(this->percentageComparison);
     }
     private:
     // Extra parameters needed
     int percentageComparison; // e.g. of an extra parameter to comparison function
    };
    // Now, you can use existing STL's sort function
    std::vector<objectToCompare> objects;
    aFunctorClass comparator(30);
    std::sort(objects.begin(), objects.end(), comparator);
// Now, for Lambda
Lambda => Replaces Functors. Similar to Callbacks & Closures in the sense that you can embed variables in it, and use it as a function with lesser or no variables
std::function => Used to declare a Lambda as a variable
    std::function<void(int)> aLambdaThatTakesInIntAndReturnsVoid = [/* Does not use any variables in current scope */] (int x) -> void { return x+2; };
    // Syntax: A function parameter without the function name
        std::function<void(int)>
        // means
        void funcName(int x)
// Benefits of Lambda
// Benefit 1: A shorter code replacement for Functor
The above example of uses of Functor can be replaced with a much shorter code below.
to:
    int percentageComparison = 30;
    std::vector<objectToCompare> objects;
    // Feed in the Functor as lambda into std::sort
    std::sort(objects.begin(), objects.end(), [&percentageComparison] (const objectToCompare& lhs, const objectToCompare& rhs) {
        return lhs.calculateFinalWeightBasedOnPercentage(percentageComparison) < rhs.calculateFinalWeightBasedOnPercentage(percentageComparison);
    });
// Benefit 2: Eliminate the need to write separate function for each purpose.
// e.g. Want to filter a string exist in name field or date field
from:
    class someClass {
     public:
        // First need to define comparison functions 
        bool matchesNameFilter(std::string data, std::string val) {
            // Assume strip() and contains() implemented
            if(stripName(data).contains(val)) return true;
            return false;
        }
        bool matchesDateFilter(std::string data, std::string val) {
            // Assume strip() and contains() implemented
            if(stripDate(data).contains(val)) return true;
            return false;
        }
        // Now, need to define functions that uses these comparison functions but are very similar
        std::vector<std::string> addToFilterByName(std::string val) {
            std::vector<std::string> results;
            for (auto i = this->datas.begin(); itr != this->datas.end(); ++i) {
                if(matchesNameFilter(*i,val)) {
                    results.push_back(*i);
                }
            }
            return results;
        }
        std::vector<std::string> addToFilterByDate(std::string val) {
            std::vector<std::string> results;
            for (auto i = this->datas.begin(); itr != this->datas.end(); ++i) {
                if(matchesDateFilter(*i,val)) {
                    results.push_back(*i);
                }
            }
            return results;
        }
     private:
       std::vector<std::string> datas; // datas containing name and date, name:date
    };
to:
    // Basically, now both functions can re-use similar code in the function called addToFilter
    // and pass in the comparison function as a lambda instead of declaring them by their own functions matchesNameFilter & matchesDateFilter
    template<typename aFunctor>
    addToFilter(string val, aFunctor func) {
        std::vector<std::string> results;
        for (auto i = this->datas.begin(); itr != this->datas.end(); ++i) {
            if(func(*i, val)) {
                results.push_back(*i);
            }
        }
    } 
    std::vector<std::string> datas;
    addToFilterByName(val) {
        addFilter(val, [](&data, &val) -> bool {
            if(stripName(data).contains(val)) return true;
            return false;
        }
    }
    addToFilterByDate(val) {
        addFilter(val, [] (&data, &val) -> bool {
            if(stripDate(data).contains(val)) return true;
            return false;
        }
    }
//----------------------------------------------------------------------------------------------------------------------------------
// C) Constructors
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Constructors Given For A Class With No Constructor Implementation
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
notes: None of these constructors will be implemented as soon as you implement any of your own constructor
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
    virtual void logOutput() = 0; // must be overriden as indicated by '= 0'
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
// 12 Handle Assignment To Self
//---------------------------------
When overloading operator = , always remember to handle assignment to self. 
Assignment to self may not always be obvious to a method. 
Method(BaseClass b, DerivedClass d); // note: d and b may refer to the same object, due to multiple pointers/references to same object

from:
    // Problem: rhs may refer to the current object itself. 
    ClassName& ClassName::operator = (const ClassName& rhs) {
        delete this->memberVariable;
        this->memberVariable = new ClassForMemberVariable(*rhs.memberVariable); // ERROR! *rhs.memberVariable was already deleted in previous line
        return *this;
    }
to: // Solution: Check for self-identities
    ClassName& ClassName::operator = (const ClassName& rhs) {
        // Problem: How often does assignment to self actually occur? This code executes everytime. Inefficient!
        if(this == &rhs) return *this; // checking for self identities here
        delete this->memberVariable;
        this->memberVariable = new ClassForMemberVariable(*rhs.memberVariable); // no errors here as rhs definitely not referring to itself
        return *this;
    }
to: // Solution: Delete only after copying
    ClassName& ClassName::operator = (const ClassName& rhs) {
        ClassForMemberVariable *pointerToOriginal = this->memberVariable; // delete only after assign to new one
        // Problem: Not exception safe, as creating a new memberVariable may throw exceptions
        // Create a new memberVariable
        this->memberVariable = new ClassForMemberVariable(*rhs.memberVariable); // no errors, as won't be deleted yet
        delete pointerToOriginal; // can delete the old one even if (&rhs == this) since nothing refers to it anymore
        return *this;
    }
to: // Solution: Copy & Swap (non throwing) (also makes it exception safe)
    ClassName& ClassName::operator = (const ClassName& rhs) {
        ClassName aNewCopy(rhs);
        this->swap(aNewCopy); // non-throwing swap
        return *this;
        // note: Automatic destruction by garbage collection
    }
//----------------------------------------------------------------------------------------------------------------------------------
// 13 No Default Constructor TradeOffs
//---------------------------------
Some classes doesn't make sense to provide a default constructor (constructor with no arguments), as some classes
must be initialize with a uniqueID in order to work properly. 

Class with no default constructor
// Problem:
    // Unable to work with template design or classes that assume default constructor exists.
// Solution:
    // Have to re-write the template design or those classes to assume no default constructor exist

// Problem:
    // Unable to define arrays easily
    ClassWithNoDefaultConstructor arr[10]; // Error! No way to call default constructor of ClassWithNoDefaultConstructor
    ClassWithNoDefaultConstructor *arr = new ClassWithNoDefaultConstructor[10]; // Error! Similarly, no default constructor
// Solution1: Initialize array of pointers instead
    ClassWithNoDefaultConstructor* arrOfPointersToClassWithNoDefaultConstructor[10]; // no error
    // Now you can initialize them whenever you have the constructor arguments
    for(int i = 0; i < 10; i++) 
    { 
        arrOfPointersToClassWithNoDefaultConstructor[i] = new ClassWithNoDefaultConstructor(constructorArguments);
    }
// Costs:
    // More space required as need to store both objects and pointers to them instead of just objects.

// Solution2: Allocate raw memory first, therefore only need space for objects and extra space for pointers needed
    void* rawMemory = operator new[] (10 * sizeof(ClassWithNoDefaultConstructor));
    // Now make the array point to it, casting the raw memory to the appropriate type (pointer to the class type)
    ClassWithNoDefaultConstructor* arrOfPointersToClassWithNoDefaultConstructor = static_cast<ClassWithNoDefaultConstructor*> (rawMemory)
    // Now, can make space using reference
    for(int i = 0; i < 10; i++) 
    { 
        new &arrOfPointersToClassWithNoDefaultConstructor[i] ClassWithNoDefaultConstructor(constructorArguments);
    }
// Cost:
    // Can't delete the easy way as didn't use the easy way of new[] to initialize it
        delete [] arrOfPointersToClassWithNoDefaultConstructor; // Error! didn't initialize using new [] operator
    // Therefore Need to manually call destructor
        for(int i = 9; i >= 0; --i) {
           // Destroy each object individually by calling its destructor
           arrOfPointersToClassWithNoDefaultConstructor[i].~ClassWithNoDefaultConstructor();
        } 
        // Deallocate raw memory
        operator delete[] (rawMemory);

// Solution3: Can also avoid all problems above by defining a dummy default constructor 
// Classes with dummy default constructor 
ClassNameDefaultConstructor() {
    this->idValue = UNDEFINED; // defined to be some out of valid logical application-dependent range number
}
// Cost:
    All code must now check if the (this->idValue != UNDEFINED), which is a little ugly code
//----------------------------------------------------------------------------------------------------------------------------------
// 14 Private Member Method to Function If No Member Variable
//---------------------------------
If a private member method does not use any of it's member variables inside it, 
then it should not be a member method but should just be a function inside the .cpp as an unnamed namespace,
this why, people using the .h file won't have to see it as private.
//----------------------------------------------------------------------------------------------------------------------------------
// 15 Multiple Dispatch
//---------------------------------
Single Dispatch => Only one object is dynamic in a function
class Dynamic Object {
    virtual void print() = 0;
}
// Each object overrides their own print function
class ObjectK : public Dynamic Object {...}
DynamicObject* dym = ObjectK();
dym->print();

Problem:
    Whenever more than 1 object can be dynamic in a function => Multiple Dispatch
    e.g. DoubleDispatch => 2 objects can be dynamic

void Collision(GameObject obj1, GameObject obj2);

from: 1 object is virtual, the other is RunTimeTypeInformation

    class GameObjectOne : public GameObject {
        Collision(GameObject otherObject) {
            if (IsGameObjectTwo(otherObject))
                ...
            } else if (IsGameObjectThree(otherObject)) {
                ...
            } ...
            else {
                throw CollisionWithUnknownObject(otherObject);
            }
        }
    }
    Problems:
        Clients may not be able to handle the exception that is thrown
to: Both are virtual, therefore, no longer throw exception, simply doesns't compile if compilation can't figure out it's type.
    class GameObject {
        void Collision(GameObject obj) {
            // Here, since obj will never be instantiate as a GameObject, we immediately know what its type is
            // It will be a concrete type with a method call Collision()
            obj.Collision(*this);
        }
    }
    class GameObjectOne : public GameObject {
        void Collision(GameObjectTwo obj2) {...}
        void Collision(GameObjectThree obj3) {...}
    }
    class GameObjectTwo : public GameObject { 
        void Collision(GameObjectOne obj1) {...}
        void Collision(GameObjectThree obj3) {...}
    }
    class GameObjectThree : public GameObject { 
        void Collision(GameObjectOne obj1) {...}
        void Collision(GameObjectTwo obj2) {...}
    }
    // note: The only problem with this approach is that every new object, will need to re-define
    //       how to handle that object in each class, requiring each class to compile
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
class Base {
    virtual void methodWithBaseImplementation();
    virtual void methodThatMustBeImplementedByDerived() = 0;
};
virtual void Base::methodWithBaseImplementation() { ... }

note: Never redefine a default parameter value for a function
// Problem:
class Base {
    virtual void printNumber(int num = 1) const = 0;
}

class Derive : public Base {
    virtual void printNumber(int num = 2) const = 0;
}
int main(void) {
    Base* basePointToDerive;
    Derive * dPointer = new Derive();
    basePointToDerive = dPointer;
    basePointToDerive->printNumber(3); // calls Derive::printNumber(3);
    // note: Default arguments are linked during creation time. Thus, it will print the number 1 instead of 2!
    basePointToDerive->printNumber(); // WARNING! calls Derive::printNumber(1) instead of Derive::printNumber(2)!
}
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
// 7 Reduce Compilation Dependencies
//---------------------------------
// Reducing compilation depencencies reduces compile time.
// Problem:
class ASemiInterfaceCLass {
 public:
    virtual std::string method1() const = 0;
    virtual std::string method2() const = 0;
 private:
    AnotherClass className; // this will cause you to compile entire AnotherClass.h for any file that #include ASemiInterfaceClass.h
};

// Solution
class AnInterfaceClass {
 public:
    virtual std::string method1() const = 0;
    virtual std::string method2() const = 0;
 private:
   AnotherClass* className; // this is fine, pointers won't cause re-compile
 // Perfect, client's only need to compile AnIntefaceClass.h instead of compiling ItsImplementation.h file as well
};
// Therefore, to reduce compilation dependencies, use Interfaces.
// If Interfaces needs private members, try to use pointers and references instead of actual objects.

// An alternative to the Interface is the Handle class
// It achieves the same no-compilation dependency by implementing all it's methods using a pointer to the implementation object
// It makes each of it's own method a 1-liner, which makes compilation equally quick.
class HandlerClass {
 public:
   void aMethod() {
       this->handlerClassImplementation->aMethod(); // only 1 line for each method, not much compilation needed.
       // Drawback: Adds a layer of indirection to code, violating OOP principles
   }
 private:
   HandlerClassImplementation* handlerCLassImplementation; // a pointer, won't need to include this file
}

Small Disadvantage:
    Interfaces and Handlers increase object code size and require slightly more time to run the code as it adds a layer of indirection.
//----------------------------------------------------------------------------------------------------------------------------------
// 8 Overriding Base Method Hides All Overloaded Base Method
//---------------------------------
// Problem:
class Base {
 public:
    void overloadedMethod();
    void overloadedMethod(int a);
};
class Derive : public Base {
 public:
     void overloadedMethod();
};

int main(void) {
    Base b; 
    b.overloadedMethod();
    b.overloadedMethod(1);
    Derived d; 
    d.overloadedMethod();
    d.overloadedMethod(1); // Error! Derive class which overrides overloadedMethod() from Base now hides all overloaded methods of overloadedMethod()
    return 0;
}
// Solution:
class Derive : public Base {
public:
    using Base::overloadedMethod; // make both overloadedMethod() and overloadedMethod(int a) from Base class visible
    void overloadedMethod(); // only override the overloadedMethod()
};
int main(void) {
    Derived d;
    d.overloadedMethod(1); // fine, class Base::overloadedMethod(int a)
}
//----------------------------------------------------------------------------------------------------------------------------------
// 9 Private Inheritance for Sharing Code Without Relationships
//---------------------------------
class PublicDeriveIsAOrImplements : public Base {}; // inherits all public and protected from base class  as public and protected
class PrivateDerive : private Base {}; // inherits all public and protected from base class  as private
private inheritance is used when you want to re-use code from Base but PrivateDerive is not a Base. 
This means that there is no relationship at all between PrivateDerive and Base, just re-using code from Base.
However, you can almost always turn private inheritance into composition which is better for testing.
The only time when you can't do that is if you want to inherit protected members from Base class, that you wouldn't have available via Composition.
from:
    class PrivateDerive : private Base {};
to:
    class StandAlone {
    private:
        Base baseObject;
    };
//----------------------------------------------------------------------------------------------------------------------------------
// 10 Virtual Public Inheritance for Multiple Paths To Base
//---------------------------------
// Problems: Data duplication when have multiple paths to base

class GrandPa{
 public:
    int dataMemberThatCanBeDuplicatedByGrandChild;
}

class Mama : public GrandPa {};
class Papa : public GrandPa {};

class ChildA : public Mama, public Papa {};
// In this case ChildA->Mama->GrandPa and ChildA->Papa->GrandPa. 
// C++ compiler will replicate the members of GrandPa in ChildA, which is redundant and wastes space. 

// Solution: To prevent this, inherit with virtual.
class MamaVirtual : virtual public GrandPa {};
class PapaVirtual : virtual public GrandPa {};
// No longer duplicates dataMemberThatCanBeDuplicatedByGrandChild
class ChildB : public MamaVirtual, public PapaVirtual {};
// note: Can't just blindly inherit by virtual all the time. 
// Virtual Inheritance costs: (when used blindly without any actual need as no GrandChild via > 1 path)
    // Larger Object Code compiled.
    // Slower code 
//----------------------------------------------------------------------------------------------------------------------------------
// 11 Array/Pointer Arithmetics and Polymophism Doesn't Work
//---------------------------------
class Child : public Base {...};
void methodThatTakesBase(const Base[] arrOfBase, int numElements) {
    for(int i = 0; i < numElements; i ++) {
        // note: Pointer arithmetic is perform here
        //       It skips every interval of memory containing Base
        //       However, a child class objects will be larger than Base class objects
        //       So the interval it skips for child class objects would be incorrect
        cout << arrOfBase[i]; // assume operator '<<' is defined for Base objects
    }
}
int main(void) {
    Base arrOfBase[10]; 
    methodThatTakesBase(arrOfBase); // this is fine
    Child arrOfChild[10];
    // The below causes an error as the array skips the child class objects wrongly
    methodThatTakesBase(arrOfChild); // runtime error! 
}

// Thus, pointer arithmetics (array) and polymorphism never works in C++ 
//----------------------------------------------------------------------------------------------------------------------------------
// E) Exceptions
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------
// 1 Exception Safety
//---------------------------------
Goals:
    - No memory leaks
    - No corrupted state
Guarantees:
    - No throw
        The code will never throw exceptions. Therefore, they don't need to be exception safe. Used by Google due to legacy reasons
        Disadvantages:
            Will rely on error codes, which is bad coding style.
            Unable to work with code that throws exceptions
    - Basic Guarantee
        Multiple states, whatever exceptions are thrown, the code will be in 1 of the stable states, client code needs to 
        call a getCurrentState() function to find out which state the code is in.
    - Strong Guarantee
        2 states, either the code executed, and the code is in the new state,
        or the code fails, and the code remains in the previous state as if it wasn't executed.
Methods:
    Strong Guarantee
        Copy & Swap. 
        Basically copy the current object entirely, so and work on modifying the copied object. If anything fails,
        just return the original unmodified object. If everything passes, then the copied object is now in the new state. 
        Just swap to the copied object and return it. Assuming swap operation doesn't throw exceptions.
note:
      A method containing Basic Guarantee can never be Strong Guarantee. 
      A method containing > 1 Strong Guarantee can never be Strong Guarantee.
      e.g. 
        void methodWithMoreThan1StrongGuaranteeIsntStrongGuarantee() {
            StrongGuaranteeMethod1(); // Fail here, is fine, we return at original state
            // Pass Method1();
            StrongGuaranteeMethod2(); // ERROR! Fail method2 but pass method1, no longer at original state nor final state. 
            // Pass both methods, we are at final state
        }
//----------------------------------------------------------------------------------------------------------------------------------
// 2 No Exceptions in Destructor
//---------------------------------
Destructors can be called normally (out of scope, explicitly called using delete) or via exceptions
If destructor is called via exception, and an exception is thrown in destructor, C++ automatically terminates entire program.
//----------------------------------------------------------------------------------------------------------------------------------
// 3 Exception vs Method
//---------------------------------
Differences between exception and method calls. 
Difference1: Method returns to original place method was called, exception gets out and never returns to original place
    ...
    callMethod();
    // will be here after callMethod
    throw anException;
    // will never come here
Difference2: Due to Difference1 above, exceptions creates a temporary copy for both 
             throw by value and throw by reference as original object will go out of scope and be destroyed.
    method(className aCopyOfClass);
    method(className& aReferenceToAnExistingClassObjectPassedIn);
    method(className* aPointerToAnExistingClassObjectOrNull);

    // note: the first copy made, it will copy for the exact same type, 
    // for the 2nd co
    catch(className aCopyOfTheTemporaryCopyMade); // note: 2 copies are made, 1 for temporary, and 1 from temporary to inside catch
                                                  //       for the 2nd copy made, if it's made for the base class from a derived class object,
                                                  //       it will lost the derived class properties which is bad. This is known as slicing problem.
    catch(className& aReferenceToTheTemporaryCopy); // 1 copy made, it will copy for exact same type, no slicing problem, no cleaning memory problem
                                                    // A tradeoff between catch by value and catch by pointer
    catch(className* aPointerToToExistingObject); // no copies made, expects throw clause to throw only exceptions in which will still exist (e.g. global, static)
                                               // However, hard for client code to know if they are supposed to call delete on the pointer exception or not
                                               // If don't delete when need to, may end up with memory leak
                                               // If delete when don't need to, will end up with segmentation fault

Difference3: No implicit conversions in exception
    int x;
    funcThatTakesInDouble(x); // this is fine
    catch(double a); // this will never catch 'x' as 'x' is type int

Difference4: A higher exception will always catch anything below it;
    class Base {...};
    class Derive : public Base {...};
    try {
        Derive d;
        throw d;
    }
    // catches all class of type 'Base' and anything under the inheritance hierarchy of class 'Base'
    // note: As this is catch by value, it will slice off any derive components when making copies
    catch(Base b) {
        ...
    }
    // Note: Below will never be executed as above catches everything 
    catch(Derive d) {
        ...
    }
    try {
        Derive d;
        throw &d; // throw a pointer
    }
    // This catches all types of pointers
    catch(const void*) {
        ...
    }
    // note: below will never be executed as above catches all types of pointers
    catch(const Base*) {
    }
//----------------------------------------------------------------------------------------------------------------------------------
// 4 throw vs throw e
//---------------------------------
DeriveClass derived;
BaseClass& base = derived; // base refers to a derived class
throw base; // this will throw a class of type Base NOT derived 
            // Remember that throwing will always invoke a copy constructor to make a temporary object.
            // The copy constructor will invoke whatever the variable's static type is NOT what it points to.

catch(Base b) {
    // Let's just say the above catch clause catches a Derived type
    
    // this rethrows current Exception
    throw; // this will throw the same class, Derived

    // this rethrows a copy of the caught exception
    throw b; // this will throw the static type, Base
}
//----------------------------------------------------------------------------------------------------------------------------------
// F) Plain Old C, C++, C++11, C++14
//----------------------------------------------------------------------------------------------------------------------------------
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
// 5 inline
//---------------------------------
inline is a suggestive instruction to the compiler, not the code. 
inline => Suggests compiler to replace each call to a function with actual function body's code.
Usage:
    Implicit:
        Defining it inside the .h file
        class className {
         public:
            // This is same as: inline int className::getAge() { return this->age; } defined in .cpp file
            int getAge() { return this->age; }
        }
    Explicit: Using the keyword 'inline'
        inline const funcName();
Advantages:
    Avoid costs of function call in code => Higher performance
Disadvantages:
    Increased size in object code.
        Results in additional paging => Lower performance
    Reduced instruction cache hit rate => Lower performance
    Requires recompilation for any change in the function by entire client code.
        If the function wasn't inline, client's code would just have to re-link that single function you have already compiled for them.
        This is because inline means that the function is copied pasted inside client's code themselves, requiring client to re-compile their entire code.
note: Compiler can ignore suggestion made by inlining (it simply treats is as a normal function with function calls)
    - Ignores when it needs a function pointer to a function defined inline, because you need an actual function to be able to point to it
    inline void f() {...}
    void (*pointerToF)() = f;
    f(); // this may be an inline call
    pf(); // this won't be an inline call
Solution:
    Use it only when function body is very small, smaller that the amount of overhead code used to store the function. 
    e.g.
        inline int age() const { return age; }
    Never inline constructors and destructor. 
        Compilers for C++ must ensure constructor and destructor things are automatically destroyed.
        Thus, there will be a lot of extra code in constructor and destructor auto-generated by compilers. 
        Inlining would end up being a disadvantage as you would be inlining a big function.
//----------------------------------------------------------------------------------------------------------------------------------
// 6 Pointer vs Reference
//---------------------------------
// Pointers can refer to NULL, References must always refer to an object
// Pointers can switch objects it refers to, References always refer to the same object

// References must be initialized to an object
    int& referenceCantBeInitializeWithoutObjects; // Error! References must be initialized

    int anObject = 2;
    int& referenceInitializeToObjectsAreLegal = anObject; // no error
    
    // note: The special case where reference can refer to null is when you do this.
        // This is very BAD CODE and must never be written
        int *pointerToNull = 0;
        int& referenceToNull = *pointerToNull; // reference refers to a dereferenced null pointer

// Pointers can refer to NULL
int * pointerCanBeInitializedToNothing; // no error

// Pointer changes object it points to, references changes the value of its object

int one = 1;
int two = 2;
int& referenceOfOne = one;
int* pointerToOne = &one; 
pointerToOne = &two; // pointerToOne now points to 'two', 'one' is unchanged
referenceToOne = two; // referenceToOne still refers to 'one', however, now ( one = 2 ), value of 'one' is now 2

// Use references when overloading '[]' operator
//----------------------------------------------------------------------------------------------------------------------------------
// 7 (new, operator new, delete, operator delete, new [], delete [], operator new [], operator delete [])
//---------------------------------
new
    1. Calls operator new
    2. Calls constructor
operator new 
    Similar to malloc() from C, only allocates memory
new []
    1. Calls operator new []
    2. Calls constructor
operator new []
    malloc for entire array
operator delete
    Similar to free() from C, only deallocates memory
// note: new and operator new can always throw the an exception indicating not enough memory (bad_alloc), therefore, must be prepared to handle them
//----------------------------------------------------------------------------------------------------------------------------------
// 8 Include Only Files Needed By Client
//---------------------------------
// .h files should include files that are needed by clients importing that file
// .cpp files should include files that are needed for implementation only, that were not used in the .h files.
// This way, clients don't have to include files it may not need
//----------------------------------------------------------------------------------------------------------------------------------
// 9 Switch vs Else If 
//---------------------------------
Problem: Will need compulsory default value if using else if
    if(caseOne) {
        return 1;
    } else if (caseTwo) {
        return 2;
    }
    return 3; // Needs a compulsory default

Solution:
    switch(value) {
        case caseOne:
            return 1;
        case caseTwo:
            return 2;
        // optional default, don't need it if not needed, compiler will check and make sure you covered all cases
    }
//----------------------------------------------------------------------------------------------------------------------------------
// 10 Using
//---------------------------------
Replacement for typedef
    using aShorterName = const vector<int>* existingLongClassName;
Forward Declaraction
    using packageName::subPackageName::TheSingleMethodOrClassNameYouNeedToAvoidIncludingEntireFile;
Resolving an entire namespace 
    using namespace namespaceName;
    vector<int> a; // same as namespaceName::vector<int> a
Resolving Conflicts (lets just say className is ambigious cause it can be packageA::className or packageB::clasName
    using packageA::className;
    className a; // same as packageA::className a
//----------------------------------------------------------------------------------------------------------------------------------
