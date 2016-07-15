//----------------------------
// Soon Chee Loong's personal style guide for C++
// Save header files with .h extension
// Save C++ files with .cpp extension
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
    // Able to look the same across different computers as long as same size monitors
    indentUsingSpaces;
to:
    // Less to type since it's one keystroke versus many space strokes.
    // Similarly, less keystrokes when hitting backspace
    indentUsingTabs
//----------------------------
from:
    if( expression )
    while( expression )
    for( expression )
    else if( expression )
to:
    // Clearer with just an extra space
    if ( expression )
    while ( expression )
    for ( expression )
    else if ( expression )
to:
    // Don't need extra space within '()' as it is clearer without
    if (expression)
    while (expression)
    for (expression)
    else if (expression)
//----------------------------
from:
    arr[i,j,k]
    function(int a,int b)
    vector<int> a = {1,2,3};
to:
    // Space after each ',' to be clearer
    arr[i, j, k]
    function(int a, int b)
    vector<int> a = {1, 2, 3};
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
note: The only time you cannot use 'this' is for constructor initialization list
    ClassConstructor(int val) : this->val(val) {} // Compile error!
    ClassConstructor(int val) : val(val) {}
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
from:
    int var_name;
    using type_name = int;
    int member_variables_;
    void FunctionNames();
    namespace parent_a
    {
        namespace child_a
        {
            codeIndentedFromNamespace;
        }
    }
to:
    // Shorter to type
    int varName;
    using typeName = int;
    int memberVariables; // access using this->memberVariables
    void functionNames();
    namespace parentA
    {
    namespace childA // access using parentA::childA::whateverItHas;
    {
    codeSameLineAsNamespace; // may have a lot of nested namespaces, no point indenting code from namespace
    // Always have the closing comment for namespace so it's clear as may have lots of nested namespaces
    } // namespace childA
    } // namespace parentA
//----------------------------
from:
    // Problem: using 'k' is a Google Style Guide convention, people outside Google wouldn't know.
    static const int kConstantNames;
to:
    // easy to know it's a constant and doesn't change since it's all capitals
    // Also, need to use '_' to read since all capitals.
    static const int CONSTANTS_NAMES
//----------------------------
from:
    // Problem: Hard to comment sections of files without using an IDE to do it for you
    /* */
    /**
     * 
     */
    //
    code();    // too many spaces after code
to:
    // Able to easily comment entire section during testing using /* */
    //
    // 
    //
    //
    code(); // one space is more than enough to be clear
//----------------------------
from: 
    // todo this
    // fix this
to:
    // Adopted from Java which is pretty universal
    // TODO:
    // FIXME:
//----------------------------
from:
    class A {
        public:
            int publicA;
        private:
            int privateA;
    };
to:
    // Only 1 space needed for 'private' & 'public' so don't have to indent twice for members
    class A {
     public:
        int publicA;
     private:
        int privateA;
    };
//----------------------------
from:
    fileName.h
    fileName.cpp
    fileNameTest.cpp
to:
    // No capital alphabets, and add '_' for test
    filename.h
    filename.cpp
    filename_test.cpp
//----------------------------
