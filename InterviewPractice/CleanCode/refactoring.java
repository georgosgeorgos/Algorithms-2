/* //
Table Of Contents
    Goals
    Methods
        Privatize
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
        Unidirectional To Bidirectional
        Bidirectional To Unidirectional
    Member Variables
        Finalized and Remove Setter
        Replace Member Variable with Object
        Replace Member Array with Object
        Replace Magic Number with Symbolic Constant
        Encapsulate Collection
    Programming Paradigms
        Flexible Objects
        Flexible Methods
    Conditionals
        Explaining Method
        Consolidate 2 conditions to initialization
        Or Same Results
        And Nested Ifs
        Bring Out Repeated Statements
        Probability To Complete Condition
    Iterations
        Replace Control Flag With Break
    Nulls
        Null Object
    Parameters
        Encapsulate Side Effects
        Parametrized Method
        Replace Parameter With Explicit Method
        Replace Parameter With Getter
        Encapsulate Downcast
    Exceptions
        Replace Error Code
        Replace Exception With Test
// */

//-------------------------------------------------------------------------------------------
// Goals
//-------------------------------------------------------------------------------------------
Refactoring = A change made to internal structure of software so that it is easier to understand, modify, and debug without changing any observable behavior.
//-------------------------------------------------------------------------------------------
// Methods
//-------------------------------------------------------------------------------------------
//----------------------------
// Privatize
//----------------------------
Make any methods that shouldn't be use outside this class private
    from:
        void method();
    to:
        private void method();
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
        class A {
            method1();
            method2() {
                ...
                method1();
                ...
            }
        }
    to:
        class A {
            B b;
            method2() {
                ...
                b.method1();
                ...
            }
        }
        class B {
            method1();
        }
//----------------------------
// Move Member Variables
//----------------------------
    Move member variable from one class to another, when the other class actually uses it more. 
    from:
        class A {
            int a;
            int lala;
            ...
                
        }
        class B {
            string b;
        }
    to:
        class A {
            int lala;
            ...
        }
        class B {
            int b;  // Rename int a to int b here
            string b;
        }
//----------------------------
// Move Methods
//----------------------------
    Move member methods from one class to another, when the other class actually uses it more
    from:
        class A {
            int lala;
            ...
            method1() {
                method2();
                method3();
            }
            method2(){
                int var = this.lala;
                ...
            }
            method3(){
                int var = this...; // lots of member variables used
            }
        }
        class B{
            ...
        }
    to:
        class A {
            int lala;
            B B; // need to contain a ClassB
            method1() {
                // Update to create delegation to ClassB
                B.method2(this.lala);
                B.method3(this);
            }
        }
        class B {
            method2(int lala); // pass in Class A's member variable as arguments
            method3(A a); // pass in a type of Class A
        }
//----------------------------
// Hide Delegate
//----------------------------
    Want to remove dependency on Class C from Class A. Make all operations of Class C go through Class B for Class A
    Think of Delegate as Backend objects called by FrontEnd objects. 
    from:
        class A {
            B b;
            C c;
        }
        class B {}
        class C {}
   to:
        class A {
            B b;
        }
        class B {
            C c;
        }
        class C {}
    FrontEnd = B
    Delegate = C
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
//----------------------------
// Unidirectional To Bidirectional
//----------------------------
    Want to create a bi-directional relationship between 2 classes. 
        // note: Code below hasn't been tested for correctness
        This is actually an awesome interview coding question that you came up with
        TestCase to check for future (check for both correctness and ensure no infinite loops)
            - setBMultipleTimesInARow();
            - setAMultipleTimesInARow();
            - setAthatHasAlreadyBeenSetToAnotherB();
    Relationships: 
        //------------
        // 1 to 1:
        //------------
            class OneA {
                OneB b; 
                void setB(OneB _b) {
                    if(this.b) this.b.unsetA();
                    this.b = _b;
                    if(this.b.getA() != this)
                        this.b.setA(this);
                }
                OneB getB() {return this.b;}
                void unsetB() {
                    OneB bPlaceHolder = this.b; // get place holder cause going to remove
                    this.b = null; // remove to prevent circular infinite loops in next statement
                    if (bPlaceHolder!= null && bPlaceHolder.getA() == this) {
                        bPlaceHolder.unsetA(); 
                    }
                }
            }
            class OneB {
                OneA a; 
                void setA(OneA _a) {
                    if(this.a) this.a.unsetB();
                    this.a = _a;
                    if(this.a.getB() != this) 
                        this.a.setB(this);
                }
                void unsetA() {
                    OneA aPlaceHolder = this.a; // to prevent circular infinite loops 
                    this.a = null; // remove circular infinite loops 
                    if (aPlaceHolder!= null && aPlaceHolder.getB() == this) {
                        aPlaceHolder.unsetB(); 
                    }
                }
                OneA getA() {return this.a;}
            }
        //------------
        // 1 to Many:
        //------------
            class OneA {
                Set<ManyB> setOfB; 
                void addB(ManyB _b) {
                    this.setOfB.add(_b);
                }
                void removeB(ManyB _b) {
                    this.setOfB.remove(_b);
                } 
            }
            class ManyB {
                OneA a;
                void setA(OneA _a) {
                    if(this.a) {
                        this.a.removeB(this);
                    }
                    this.a = _a;
                    this.a.addB(this);
                }
                OneA getA() {return this.a;}
            }
        //------------
        // Many to Many:
        //------------
            class ManyA {
                Set<ManyB> setOfB; 
                void addB(ManyB _b) {
                    this.setOfB.add(_b);
                    if(!_b.contains(this))
                        _b.addA(this);
                }
                void removeB(ManyB _b) {
                    this.setOfB.remove(_b);
                } 
            }
            class ManyB {
                Set<ManyA> setOfA; 
                void addA(ManyA _a) {
                    this.setOfA.add(_a);
                    if(!_a.contains(this))
                        _a.addA(this);
                }
                void removeA(ManyA _a) {
                    this.setOfA.remove(_a);
                    // note: Didn't implement the place holder logic, etc. for this case
                } 
            }
//----------------------------
// Bidirectional To Unidirectional
//----------------------------
    Opposite of Unidirectional To Bidirectional.
    A drawback is the huge complexity as you can see from the attempted implementation in Unidirectional To Bidirectional.
    Therefore, if there is no need for Bidirectional, refactor it to only become unidirectional. 
//-------------------------------------------------------------------------------------------
// Member Variables
//-------------------------------------------------------------------------------------------
//----------------------------
// Finalized and Remove Setter
//----------------------------
Finalize and remove setter for any member variables that shouldn't change past constructor
    from:
        class A {
            private int memberVariable;
            setMemberVariable(int _memberVariable);
        }
    to:
        class A {
            final private int memberVariable;
        }
//----------------------------
// Replace Member Variable with Object
//----------------------------
    A class does too much work for working with member variable. Replace that member variable with a new class Object 
    with methods that modify that member variable
//----------------------------
// Replace Member Array with Object
//----------------------------
    Replace an array used in a class for conventions to an object itself
    from:
        class ConventionArrayExist {
            Array<String> name; 
            ConventionArrayexist(String lastname, String firstanme) {
                this.name[0] = lastname;
                this.name[1] = firstname;
            }
        }
    to: 
        class NoMoreConventionArray {
            Name name; 
            NoMoreConventionArray(String lastname, String firstname) {
                this.name.setLastName(lastname);
                this.name.setFirstName(firstname);
            }
        }
//----------------------------
// Replace Magic Number with Symbolic Constant
//----------------------------
    Replace a magic number with a symbolic constant
    from:
        class A {
            double potentialForce(double mass) {
                return mass * 9.81;
            }
        }
    to:
        class A {
            static final double GRAVITATIONAL_CONSTANT = 9.81;
            double potentialForce(double mass) {
                return mass * GRAVITATIONAL_CONSTANT;
            }
//----------------------------
// Encapsulate Collection
//----------------------------
    Encapsulate collection that is being worked with 
    from: 
        class hasCollection {
            List<Object> listOfObj;
            List<Object> getList(); 
            void setList(List<Object> listOfObj);
        }
    to:
        class hasCollection {
            List<Object> listOfObject;
            final List<Object> getList(); // unmodifiable list
            void addObj(Object obj);
            void removeObj(Obj obj);
        }
//-------------------------------------------------------------------------------------------
// Programming Paradigms
//-------------------------------------------------------------------------------------------
To satisfy closed for modification, open for extension principle. 
Want to use OOP if often add new objects, want to use procedural if often add new functions
    OOP: 
        Add new objects => Easy
            Doesn't affect existing code. 
            Just need to implement all existing method for the new object, can inherit functionalities
        Add new methods => Hard
            Affects all existing objects.
            All objects  now need to implement the new method
    Procedural: Easy to add new functions, but hard to add new data structures. 
        Add new objects => Hard
            Affects all existing methods.
            All methods need to account for new objects
        Add new methods => Easy
            Doesn't affect existing code. 
            New method just need to account for all existing objects
//----------------------------
// Flexible Objects
//----------------------------
Switch Procedural Code to OOP 
    from:
        class Geometry implements Methods{
            // note: Adding new object here will require modifying both area and perimeter
            double area(Object object) {
                if (Object instanceof Square)
                    return Square.topLeft * Square.btmRight;
                else if (Object instanceof Circle)
                    return Circle.radius*Circle.radius*Math.pi;
                // note: Need modify here if add new object
            }
            double perimeter(Object object) {
                if (Object instanceof Square)
                    return 2 * (Math.abs(Square.topLeft.x - Square.btmRight.x) + Math.abMath.abs(Square.topLeft.y - Square.btmRight.y);
                else if (Object instanceof Circle)
                    return 2*Circle.radius*Math.pi;
                // note: Need modify here if add new object
            }
        }
        class Square extends Object {
            public Point topLeft;
            public Point btmRight;
        }
        class Circle extends Object {
            public Point center; 
            public double radius; 
        }
   to:
        class Square implements Methods {
            double area();
            double perimeter();
            // note: Need modify here if add new function
        }
        class Circle implements Methods {
            double area();
            double perimeter();
            // note: Need modify here if add new function
        }
//----------------------------
// Flexible Methods
//----------------------------
Switch from OOP to Procedural 
    from: 
        Refer to to: of Flexible Objects
    to:
        Refer to from: of Flexible Objects
//-------------------------------------------------------------------------------------------
// Conditionals
//-------------------------------------------------------------------------------------------
//----------------------------
// Explaining Method
//----------------------------
    Introduce a new method to explain a complicated expression.
    from:   
        if( age >= 21 && age <= 55) 
    to:
        if(isAdult())
//----------------------------
// Consolidate 2 conditions to initialization
//----------------------------
    Remove the else statement by making it the initialization
    from:
        if(...)
            charge = 1;
        else
            charge = 0;
    to:
        charge = 0;
        if(...)
        charge = 1;
//----------------------------
// Or Same Results
//----------------------------
    from:
        if(A()) return 0;
        else if(B()) return 1;
        else if(C()) return 1;
        else if(D()) return 0;
    to:
        if(A() || D()) return 0;
        return 1;
//----------------------------
// And Nested Ifs
//----------------------------
    from:
       if(A())
           if(B())
               ...
    to:
        if(A() && B())
            ...
//----------------------------
// Bring Out Repeated Statements
//----------------------------
    from:
        if(A())
            kara = 0;
            ...
            result += 1;
        else
            kara = 0;
            ...
            result += 1;
    to:
        kara = 0;
        if(A())
            ...
        else
            ...
        result += 1;
//----------------------------
// Probability To Complete Condition
//----------------------------
    Swap between  && and || so that the probability of complete condition is faster
        if(a && b && c && d && e) 
            need to pass all 5 to be complete condition
            can fail any 1 to complete condition
        if(a || b || c || d || e)
            need to fail all 5 to complete condition
            can pass any 1 to complete condition
    note: Can only swap if 2nd condition doesnt depend of first. e.g. ( if (a && a.getItem) (need check null before getItem)
    from:
        if(probability90Percent && probability10Percent) {...}
        else if(probability10Percent || probability90Percent) {...}
    to: 
        if(probability10Percent && probability90Percent) {...}
        else if(probability90Percent || probability10Percent) {...}
//-------------------------------------------------------------------------------------------
// Iterations
//-------------------------------------------------------------------------------------------
//----------------------------
// Replace Control Flag With Break
//----------------------------
Control flag is only used as a control flag.
    from:
        boolean gameOver = false;
        while(!gameOver) {
            preProcessing();
            if(playerLoses) gameOver = true;
            ...
            if(computerWins) gameOver = true;
            postProcessing();
        }
    to:
        while(true) {
            preProcessing();
            if(playerLoses)  break;
            ...
            if(computerWins) break;
            postProcessing();
        }
        postProcessing(); // don't need this line if no post processing code
//-------------------------------------------------------------------------------------------
// Nulls
//-------------------------------------------------------------------------------------------
//----------------------------
// Null Object
//----------------------------
To replace default handles for nulls to normal method call. 
Makes code a lot cleaner from null checks.
    from:
        Customer customer = site.getCustomer();
        if(customer == null) // imagine a lot more of this kind of code everywhere. 
            logger.info("No customer");
        else 
            customer.print();

        class Site {
            Customer getCustomer() {
                return this.stack.pop();
            }
        }
    to:
        Customer customer = site.getCustomer(); 
        customer.print(); // now code is a lot cleaner everywhere by just writing one extra method below

        class Site {
            getCustomer() {
                if(this.stack.top() == null) return NullCustomer();
                return this.stack.pop();
            }
        }
        class NullCustomer extends Customer {
            @Override
            void print() {
                logger.info("No customer");
            }
        }
//-------------------------------------------------------------------------------------------
// Parameters
//-------------------------------------------------------------------------------------------
//----------------------------
// Encapsulate Side Effects
//----------------------------
Split a method that has side effect and non-side effect components to be able to re-use non-side effect components using functional programming paradigm.
    from:
        HasSideEffects() {
            ...
            sideEffectCodeStarts();
            sideEffectCodeEnds();
            ...
        }
    to:
        HasSideEffects() {
            noSideEffect1();
            sideEffectCode();
            noSideEffect2();
        }
        sideEffectCode() {
            sideEffectCodeStarts();
            sideEffectCodeEnds();
        }
//----------------------------
// Parametrized Method
//----------------------------
For multiple methods that performs similar calculations that can be grouped up. Parametrize them. 
    from:
        printUSD() {
            logger.info("USD");
        }
        printCAD() {
            logger.info("CAD");
        }
    to:
        print(String value) {
            logger.info(value);
        }
//----------------------------
// Replace Parameter With Explicit Method
//----------------------------
Replace parameter when it causes the method to do 2 totally different things. 
    from:
        doDifferent("Engineer");
        void doDifferent(String type) {
            if(type.equals("Engineer")
                ...
            else if(type.equals("Doctor")
                ...
        }
    to:
        doEngineer();
        void doEngineer();
        void doDoctor(); 
//----------------------------
// Replace Parameter With Getter
//----------------------------
    from:
        workWithThis(int height) {
            int tall = height * 3;  
            ...
        }
    to:
        workWithThis() {
            ...
            int tall = this.compositionObject.getHeight();
        }
        int getHeight() {
            return this.height;
        }
//----------------------------
// Encapsulate Downcast
//----------------------------
Don't let client code do any casting
    from:
        Object lastReading() {
            return reading.lastElement();
        }
        Reading read = (Reading) lastReading();
    to:
        Object lastReading() {
            return (Reading) reading.lastElement();
        }
        Reading read = lastReading();
//-------------------------------------------------------------------------------------------
// Exceptions
//-------------------------------------------------------------------------------------------
//----------------------------
// Replace Error Code
//----------------------------
    from:
        method() {
            if (errorOccurs()) return -1;
        }
    to:
        method() throws ErrorOccursException {
            if (errorOccurs()) throw new ErrorOccursException("error occured");
        }
//----------------------------
// Replace Exception With Test
//----------------------------
Some Exceptions are really basic requirements to the program that the client should check. 
Allow the check by creating a test method for client to call before calling actual method.
    from:
        actualMethod() throws CheckedException {...}
    to:
        boolean testIfSafeToCallActualMethodFirst();
        actualMethod() { 
            throws UnCheckedException();
        }
//-------------------------------------------------------------------------------------------
