/* //
Table Of Contents
    Goals
    Methods
        Replace Temp
        Split Variable
        Explaining Variable
        Extract Method
        Method Object   
    Classes
        Extract Class
        Move Member Variables
        Move Methods
        Hide Delegate
        Remove Middle Man
        Local Extension
// */

//-------------------------------------------------------------------------------------------
// Goals
//-------------------------------------------------------------------------------------------
Refactoring = A change made to internal structure of software so that it is easier to understand, modify, and debug without changing any observable behavior.
//-------------------------------------------------------------------------------------------
// Methods
//-------------------------------------------------------------------------------------------
//----------------------------
// Replace Temp
//----------------------------
    Remove any temporary variables with the function calls that gave them directly 
    from: 
        int lala = getLala();
        doBaba(lala);
        doCaca(lala);
    to:
        doBaba(getLala());
        doCaca(getLala());
//----------------------------
// Split Variable
//----------------------------
    Replace a single variable that gets re-assigned many times to what it represents
    from: 
        int a = scoreX + scoreY; 
        ...
        a /= (maxScoreX + maxScoreY); 
    to:
        int sumScore = scoreX + scoreY; 
        ...
        int normalizedSumScore = sumScore/(maxScoreX + maxScoreY);
    to: 
        getSumScore();
        ...
        getNormalizedSumScore(); 
//----------------------------
// Explaining Variable
//----------------------------
    Introduce a new variable to explain a complicated expression.
    from:   
        doPhysics(mass * acceleration);
    to:
        int force = mass * acceleration;
        doPhysics(force);
//----------------------------
// Extract Method
//----------------------------
    Copy paste a block of code from a method into a new method so that the old method becomes clearer. 
    Note: Can only do this if method doesn't refer to 
    from:
        int kara = getKara();
        int usefulVariable = 0; 
        ...
        return usefulVariable;
    to:
        int getUsefulVariable() { 
            int result = 0
            ...
            return result;
        }
        int kara = getKara();
        return getUsefulVariable();
//----------------------------
// Method Object   
//----------------------------
    Replace an entire method with a new class defined just for that method
    from:
        int method1() {
            int firstVariable = 0;
            ...
            return lastVariable;
        }
    to:
        Method1 method1 = new Method1(firstVariable, ..., lastVariable);
        int result = method1.execute();
//-------------------------------------------------------------------------------------------
// Classes
//-------------------------------------------------------------------------------------------
//----------------------------
// Extract Class
//----------------------------
    Move responsibilities from a class to a new class, and make the original class contain that new class as a member variable. 
    from:
        classA {
            method1();
            method2() {
                ...
                method1();
                ...
            }
        }
    to:
        classA {
            classB b;
            method2() {
                ...
                b.method1();
                ...
            }
        }
        classB{
            method1();
        }
//----------------------------
// Move Member Variables
//----------------------------
    Move member variable from one class to another, when the other class actually uses it more. 
    from:
        ClassA {
            int a;
            int lala;
            ...
                
        }
        ClassB {
            string b;
        }
    to:
        ClassA {
            int lala;
            ...
        }
        ClassB {
            int b;  // Rename int a to int b here
            string b;
        }
//----------------------------
// Move Methods
//----------------------------
    Move member methods from one class to another, when the other class actually uses it more
    from:
        ClassA {
            int a;
            ...
            method1() {
                method2();
                method3();
            }
            method2(){
                int var = this.a;
                ...
            }
            method3(){
                int var = this...; // lots of member variables used
            }
        }
        ClassB{
            ...
        }
    to:
        ClassA {
            ClassB B; // need to contain a ClassB
            method1() {
                // Update to create delegation to ClassB
                B.method2(this.a);
                B.method3(this);
            }
        }
        classB {
            method2(int a); // pass in ClassA's member variable as arguments
            method3(classA A); // pass in a type of Class A
        }
//----------------------------
// Hide Delegate
//----------------------------
    Want to remove dependency on Class C from Class A. Make all operations of Class C go through Class B for Class A
    Think of Delegate as Backend objects called by FrontEnd objects. 
    from:
        ClassA {
            ClassB b;
            ClassC c;
        }
        ClassB {}
        ClassC {}
   to:
        ClassA {
            ClassB b;
        }
        ClassB {
            ClassC c;
        }
        ClassC {}
    FrontEnd = Class B
    Delegate = Class C
//----------------------------
// Remove Middle Man
//----------------------------
    Opposite of Hide Delegate. The problem with Hide Delegate is that sometimes, it ends up making Class B become too much of a Middle Man. 
    Therefore, extract a lot of it from Class B to Class C so that Class C can become in independent class by itself.
//----------------------------
// Local Extension
//----------------------------
    A Third Party API class doesn't have the features you need. 
    Therefore, create a local extension for the 3rd Party API:
       Method1-SubClass: Extending what it has, but adding more features into this new class. Become a child of the Third Party API
            - Automatically extends all behavior of original class
       Method2-Composition: Wrapper to the class, redefine methods and call the 3rd party methods. 
            - Change Interface (e.g. change method signature of previous class)
            - Delay creation of delegates. 
//-------------------------------------------------------------------------------------------
