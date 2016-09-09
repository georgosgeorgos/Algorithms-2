Programming Paradigm
//-----------------------------------------------------------------------------------------------------------
Table Of Contents
//-----------------------------------------------------------------------------------------------------------
    Imperative Programming = Every command shows how programming takes place, step by step
    Structured = No goto statements, replaced with functions instead
    Procedural = Sequence of instructions
    Object-Oriented = Everything is an object
    Declarative = Program state the result you want, not how to get it.
    Logic = Uses or and and
    Functional = no assignments of variables. 
    Template Metaprogramming = Executes during compilation
    Generic Programming = Programming that works for multiple types.
    Dependency Injection = All dependencies to an object is injected to it automatically.
    Scientific Computing = Solving engineering, mathematical, and scientific problems using code.
//-----------------------------------------------------------------------------------------------------------
Imperative Programming = Every command shows how programming takes place, step by step
    Properties:
        - Uses lots of goto (to move to a subroutine) 
    Advantages:
        - Closer to machine-level programming
            - Variable assignment = store
            - Mutable Variables = memory cells
            - Variable dereferences = load
    Languages:
        - Assembly
//-----------------------------------------------------------------------------------------------------------
Structured = No goto statements, replaced with functions instead
    Languages:
        - C
//-----------------------------------------------------------------------------------------------------------
Procedural = Sequence of instructions
    Advantages:
        - Easy to add new functions
            - Just define a function, and everything can start using it.
    Languages: 
        - C
//-----------------------------------------------------------------------------------------------------------
Object-Oriented = Everything is an object
    Properties:
    Advantages: 
        - Closer to real world objects
        - Is-A, Has-A relationships modelling
        - Supports SOLID
            - Single Responsibility = every class has 1 responsibility
            - Open/Closed = open for extension, closed for modification
            - Liskov Substitution = Can replace all of A to B without breaking code if B is child of A
            - Interface Segregation
            - Dependency Inversion = Changes at bottom level doesn't affect top level
        - Easier to add new objects
            - Adding a new object simply requires just creating a new class
    Disadvantages:
        - Difficult to add new methods
            - Adding a new method requires implementing that method in every single existing class
    Languages:
        - Java
        - C++
//-----------------------------------------------------------------------------------------------------------
Declarative = Program state the result you want, not how to get it.
    Languages: 
        - SQL
//-----------------------------------------------------------------------------------------------------------
Logic =  Uses or and and
    Languages: 
        - Prolog
//-----------------------------------------------------------------------------------------------------------
Functional = no assignments of variables. 
    Properties:
        - no assignment to variables => no variables
    Advantage:
        - Easier to prove mathematically
        - Closer to mathematical world
    Disadvantage:
        - Less efficient as function gets evaluated many times instead of re-using evaluations using variables
//-----------------------------------------------------------------------------------------------------------
Template Metaprogramming = Executes during compilation
    Reduces running time by moving work to compile time
    Runtime errors are shifted to compile time errors, which eases debugging. 
    Smaller executables, lower memory requirements.
//-----------------------------------------------------------------------------------------------------------
Generic Programming = Programming that works for multiple types.
Methods:`
    Implemented as Templates in C++
    Writing code for general class
        Implemented by accepting Object Class as parameters in Java
        Disadvantage:
            Every class has to now extend the Object Class. However, this is automatically done in Java.
    Pre-processor => A compilation before actual compilation that reads the types and outputs actual source code
        Disadvantage:
            Code outputted is not formatted properly
Prevents re-inventing the wheel => Lower errors.
//-----------------------------------------------------------------------------------------------------------
Event-Driven = Control flow is determined by asynchronous actions (from humans or sensors).
Constraint = Programmer specifies a set of constraints, and an engine infers the answers to questions.
Aspect-Oriented = Programs have cross-cutting concerns applied transparently.
Reflective = Programs manipulate their own structures.
Array = Operators are extended to arrays, so loops are normally unnecessary.
//-----------------------------------------------------------------------------------------------------------
Scientific Computing = Solving engineering, mathematical, and scientific problems using code.
Programming is very mathematical in nature and often deals with matrices. 
Examples Programming Languages: Matlab, Numpy, R
//-----------------------------------------------------------------------------------------------------------
