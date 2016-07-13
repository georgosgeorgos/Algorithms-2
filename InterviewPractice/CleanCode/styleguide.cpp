//----------------------------
// Soon Chee Loong's personal style guide for C++
//----------------------------
from:
    // Saves more lines, Java style
    if (...) {
        ...
    } else {
        ...
    }
    for (...) {
        ...
    }
    while (...) {
        ...
    }
to:
    // Clearer to distinguish, especially for long programs in C++
    if (...)
    {
        ...
    }
    else
    {
        ...
    }
    for (...)
    {
        ...
    }
    while (...)
    {
        ...
    }
//----------------------------
from:
    if(expression)
    while(expression)
    for(expression)
    else if(expression)
to:
    // Clearer with just an extra space
    if (expression)
    while (expression)
    for (expression)
    else if (expression)
//----------------------------
from:
    // As maintainer, easier to see what is used by public before looking at public
    class A {
        private:
        public:
    };
to:
    // As user, easier to just look at API provided from public and ignore details from private.
    class A {
        public:
        private:
    };
//----------------------------
from:
    // Variables before methods.
    class A {
        public:
            int memberVariableA;
            void funcA();
        private:
            int memberVariableB;
            void funcB();
    };
to: 
    // Will always prefer re-using existing methods than accessing variables directly, so list method definitions first
    class A {
        public:
            void funcA();
            int memberVariableA;
        private:
            void funcB();
            int memberVariableB;
    };
//----------------------------
from:
   // Appending '_' for member variable is only a style guide and is not enforced by compilers to actually represent a member variable.
   doSomething(memberVariable_);
to:
   // Keyword 'this' specifies it is actually a member variable in code
   doSomething(this->memberVariable);
//----------------------------
from:
    // Problem: Need to make changes to functionA() in both places each time make a change
    void functionA();
    void functionB
    {
        ...
        functionA();
        ...
    }
    void functionA()
    {
        ...
    }
to:
    // Define before needed, so don't have to change twice anything make a change to functionA()
    void functionA()
    {
        ...
    }
    void functionB()
    {
        ...
        functionA();
        ...
    }
from:
    Problem: If circular dependencies, need a .h file
    void functionB1() 
    {
        functionB2();
    }
    void functionB2() 
    {
        functionB1();
    }
to:
    // .h file
    void functionB1();
    void functionB2();
    // .cpp file
    void functionB1() 
    {
        functionB2();
    }
    void functionB2() 
    {
        functionB1();
    }
//----------------------------
Save header files with .h extension
Save C++ files with .cpp extension
//----------------------------
