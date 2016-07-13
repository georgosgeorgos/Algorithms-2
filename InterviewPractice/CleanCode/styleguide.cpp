//----------------------------
// Soon Chee Loong's personal style guide for C++
//----------------------------
from:
    // Saves more lines, Java style
    if (...) {
    } else {
    }
to:
    // Clearer to distinguish, especially for long programs in C++
    if (...)
    {
    }
    else
    {
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
    // Will always prefer re-using existing methods than accessing variables directly
    class A {
        public:
            void funcA();
            int memberVariableA;
        private:
            void funcB();
            int memberVariableB;
    };
//----------------------------
