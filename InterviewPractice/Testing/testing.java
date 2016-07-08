// Mockito, Junit
/*
Goals
Code Guidelines
    Testing
    Unit-Test

Categorizing Tests

Types of Test:
    Unit Test
      - State Test
      - Interaction Test
      - Behavior-Driven Testing
    Integration Test
    System Test == Functional Test
    User Interaction Test (Web Driver, e.g. Selenium simulates browser interactions)

    A/B Testing => e.g. Change color and measure impact to amount of user interaction.
    Accessibility Testing => Ensure people with disability can use it
    Internalization Testing => Ensure it works for both boy, girls

Mocking:
    Benefits
    Types of Test Doubles

What to Test:
    State Test
        Test that function returns right results based on tested input 
        Basically, if it returns the right tested input, that means the state of the objects changed correctly. 
    Interaction Test
        Test that function calls the right method properly (e.g. a Sort master class calls the quicksort method instead of bubblesort method)
        Test code's response to certain result (if dependent object returns this, independent object will response a certain way)
    Behavior Test
        Test methodNames should be sentences describing behavior of test. 
Writing Testable Code:
    Single Thread Test
    Multi Thread Test
*/
//---------------------------------------------------------------------------------------------------------------------------------
// Goals
//---------------------------------------------------------------------------------------------------------------------------------
Ensure code works as expected.
  - Ensures you fix the right thing. Worst problem: Having the same bug appear twice.
Allows developer to modify code without breaking existing functionality as long as they pass the unit test. => Encourages more flexible code
A form of documentation for large code bases, and how the code is supposed to run, that doesn't become obsolete.
  - Test is the first user.
Minimize use of debugger when code breaks.
Predicts failure
//---------------------------------------------------------------------------------------------------------------------------------
// Test Driven Development
//---------------------------------------------------------------------------------------------------------------------------------
Goal:
    Writing easy to test code 
    Focusing on ease of use rather than ease of implementation. (test code = usage code)
    Think about corner cases (similar to thinking about test cases first before designing the algorithms in interviews)
Methods:
    Write test before writing code.
    Write a failing test, then write enough code to pass the test. 
    Then, refactor the code, making sure it still passes the test. 
//---------------------------------------------------------------------------------------------------------------------------------
// Code Guidelines
//---------------------------------------------------------------------------------------------------------------------------------
Testing
    testClassName shoulld be the word Test right after word class, so in testing ClassName, the test's class's name should be ClassNameTest
    testMethodNames should be sentences describing behavior of test, what exactly is being tested, what are the inputs and what are the expected outputs. 
    testMethodNames should have the word 'should'
    testMethodNames should begin with what the inputs are
    e.g. 
        onePartitionAndOneNegativeReplicationShouldThrowIllegalArgumentException
        onePartitionAndOneReplicationShouldReturnAListOfValidKafkaTopics
    This is because during testing, some test frameworks like JUnit will only show you the test method name and line number. Therefore, naming the test method name is very important.
    Don't bother catching exceptions in test, just define test to throws Exception 
    e.g.    
        @Test
        public void inputShouldDoThis() throws Exception {
            try (openingResources();) {
                ...
            } // no need catch block as throws Exception
        }
    Complexity of calculations should be in code! NOT in test!
      This way, if a test fails, you know something is wrong with the code, NOT the test. 
    e.g.
      testDoesComplicatedChecks() {
        // Test failing, not sure if test written wrongly or code is wrong
        assertEquals(this.getExpected, kaka.a() + kaka.b() * kaka.c() + kaka.d());
      }
      testIsSimple() {
        // Test failing, something is wrong with  kaka.getResult()
        assertEquals(this.getExpected, kaka.getResult());
      }
    A little deviation from actual Code's Clean Code:
      Conciseness: Less distractions from what the test code does
      Completeness: Readers should be able to understand what the test is testing (input to test, behavior, expected output) without diving out into any methods called by the test.
      Balance between conciseness and completeness.
Unit Test
    Don't use functions inside Unit Test cause you don't want to be testing, debugging your unit test. Instead, re-write every code. 
    setup() and cleanup() only works if ALL your unit test uses them. 
    Each test should only setup things that it needs in order for the test to pass. Not the generic setup for everything! 
    Front Door First: Don't write test for a class in a way that users won't be able to
      Test only the public API available for people using your class, NOT the internal private methods. 
      This allows test to be used as a form of documentation.
      This makes the test resilient to internal implementation changes. (test code doesn't have to change) 
//---------------------------------------------------------------------------------------------------------------------------------
// Categorizing Test
//---------------------------------------------------------------------------------------------------------------------------------
Metrics:
  Speed
  Isolation
  Confidence In Parts
  Confidence In Systems
  Fragility = How much test code needs to change if code changes. 
Unit Test => High (speed, isolation, confidence in parts, fragility), Low(others)
Integration Test => Medium (all)
System Test => High (confidence in systems), Low(others)
//---------------------------------------------------------------------------------------------------------------------------------
// Unit Test
//---------------------------------------------------------------------------------------------------------------------------------
Readable
    Unit test should clearly tell the behavior of application and which scenario is being tested.
Fast
    Unit test needs to execute fast so that developers can run them often
    No calls to database, filesystem. 
Reliable/Deterministic
    Passing unit test in development must pass in production
    Failing unit test in production should be reproducible in development
Unit Not Integration
    Independent of external environments
    No dependency
Resilient
  Test code shouldn't change as much if actual code changes.
Clean
    Test code is production code
//---------------------------------------------------------------------------------------------------------------------------------
// Mocking
//---------------------------------------------------------------------------------------------------------------------------------
Benefits
    Test each unit in isolation
        Get to really test that one class you are testing instead of also testing the objects that are composed by it. 
    Don't actually call the methods that are being mocked
        e.g. Don't want to actually send an email for exception each time test runs
        e.g. Faster test run-time as don't need to run mocked objects
    Allow to test how component would react in low probability of occurence cases by hardcoding those cases in.

Types of Test Doubles: Similar to acting, where a Double does crazy stunts, Mockito mocks out doubles for you
    Dummy
        Doesn't actually get used anywhere. 
        Only use to satisfy parameter lists for a method
    Fake
        Has actual working implementation
        However, the implementation will be different from production. (e.g. method that stores into in-memory database instead of actual production database) 
    Stub
        Record information about calls made to it
        Provide hard-coded return values when it's methods are called
    Mocks
        Objects with expectations about calls that are expected to receive. 
//---------------------------------------------------------------------------------------------------------------------------------
// Interaction Test
//---------------------------------------------------------------------------------------------------------------------------------
Want to check that certain interactions:
        - Occur
        - Occur with the correct inputs
        - Occur in the correct order
        - Occur the correct number of time
    when the conditions are met.

Algorithm:
    WantToTest ClassToTest's MethodToTest's with hardCodedInputs both state and interaction
    // Step1: Define mock objects that are composed by the class you want to test, setup. 
        @Mock classToMock
    // Step2: Define what the mock objects should return when their methods are called.
        when(classToMock.methodNameWith(methodParametersA,methodParametersB)).thenReturn(hardCodedReturnValue); 
    // Step3: Create your class along with the mock objects (composition instead of inheritance, easier to test composition objects than inheritance as it is decoupled)
        new ClassToTest classToTest = ClassToTest(classToMock);
    // Step4: Run the method   
       boolean returnValue = classToTest.runMethodToTest(hardCodedInputs));
    // Step5: State Verification: The actual class we are testing for the hardCodedInputs should return True or now have a member variable equal true
        AssertTrue(returnValue); 
        AssertNull(classToTest.getSomething());
    // Step6: Interaction Verification: Verfiy that the classToMock's method was indeed called, with correct input parameters, the right number of times, with right order. 
        verify(classToMock.methodNameWith(methodParametersA, methodParametersB)); 
        // verify second method gets run once only and was only run after the first method is called.
        verify(once(classToMock.anotherMethodName.).after(classToMock.methodNameWith());
    // Step7: Tear down
        classToTest.methodToResetOrCleanup();
//-------------------------------------
e.g. 
public void testSortNumbers_quicksortIsUsed() {
    // Step1
    Mock classToMock = new Mock(ClassToMock.class); 
    // Step3
    NumberSorter numberSorter = new NumberSorter(mockQuicksort, mockBubbleSort);
    // Step4
    numberSorter.sortNumbers(new ArrayList(3, 1, 2)); // Call the numberSorted method
    // Step5
    AssertTrue(numberSorters.getNumbers().compareTo([3,1,2]))
    // Step6: Verify numberSorted used quicksort's sort() method. The line below fails if the function below wasn't executed
    verify(mockQuicksort).sort(new ArrayList(3, 1, 2));
}
//---------------------------------------------------------------------------------------------------------------------------------
// Behavior Driven Testing
//---------------------------------------------------------------------------------------------------------------------------------
A method can contain multiple behaviors (does different things)
Multiple methods can be used for a single behavior. 
Test each possible behavior (path) in separate test. 
  Each test should test only 1 behavior, not all the behaviors for 1 method.
Code Coverage == Line Coverage, Code Coverage != Path Coverage
  Make sure your tests cover every important path in the code.
  Test from user's API perspective.
//---------------------------------------------------------------------------------------------------------------------------------
// Integration Test
//---------------------------------------------------------------------------------------------------------------------------------
Pairwise components interact correctly
  - Test 2 components at a time.
//---------------------------------------------------------------------------------------------------------------------------------
// System Test == Functional Test
//---------------------------------------------------------------------------------------------------------------------------------
End to End testing
Involves everything
//---------------------------------------------------------------------------------------------------------------------------------
// Accessibility Testing
//---------------------------------------------------------------------------------------------------------------------------------
There's no replacement for staring at the target user use your product in person at their location. 
Accessibility Design:
  Focus on the user
  Design the IDEAL Wallet
    Some cool watch that pays by scanning automatically.
  Design the IDEAL Wallter for blind people in Asian countries
    User:
        Poor
        Uses cash instead of cards
        Can't identify how much money being held/received
    Mechanical wallet that sorts money your drop into it based on weight.
  Notice how the goal is still the same (storing money), but the design changes completely
//---------------------------------------------------------------------------------------------------------------------------------
// Internalization Testing
//---------------------------------------------------------------------------------------------------------------------------------
Test your app on slow wifi, if it doesn't work, billions of people can't use it.
Red colored $$$ in US is bad, but in China is good
Ensure message is translatable using Google Translate, and is still culturally acceptable
Same words in some languages may vary from less characters to more characters
    Super long words in other languages may not fit screen.
Muslims do not like default picture to be substituted to a puppy.
Some cultures prefer more privacy, some prefers less.
  e.g.
    System.out.println(name + " added " + number + " person to his circles");
      Problems:
          Number > 1 ? => "persons"
          gender(name).equals("girl") ? => "her"
Top 10 apps at every country is different => Some apps are more targetted in some countries.
//---------------------------------------------------------------------------------------------------------------------------------
// Writing Testable Code
//---------------------------------------------------------------------------------------------------------------------------------
// Single Thread Test
//---------------------------------------------------------------------------------------------------------------------------------
Move to input method parameters
    Problem: Method depends on the changing input (e.g. current time, which changes depending on when test is run)
    Code: Should accept the environment (e.g. currTime) as input parameter
    Test Code: can pass in a hardcoded currTime as input during testing
Move to class member variables, passed as dependency injection
    Problem: Highest level client code will have to rely changing input, and can't just pass it as input parameter
    Code: Should get the dependency changing input as a member variable, initialized as a dependency injection 
    TestCode: Can now pass the dependency to the constructor, as a mocked object. 
Reduce dependencies
    Problem: Too many dependencies, that are moved to member variables, that needs to be mocked. 
    Code: Reduce dependencies by depending only on a few classes. Basically, turn the sparse dependency graph into a deep one.
    TestCode: Each class only needs to create a few mock objects, instead of one class creating too many mock objects and needs to be initialize with too many dependencies. 
Separate Construction from Logic
    Problem: Class method itself uses new operators to construct dependencies
    Code: Delegate all the construction logic (logic with all the 'new' operators) to another Factory Class
    TestCode:  Only need to mock next node in the graph (the Factory class) instead of too many, test code looks cleaner and not as cluttered with construction logic
Prevent automatic creation in Constructor
    Problem: Constructor has uses the keyword 'new', can't be mocked
    Code: Replace 'new' objects via parameters in the constructor, this way, the created objects
    TestCode: Able to mock the dependencies into the constructor
Constructor doing too much work
    Problem: Constructor needs to read from file (super slow), refer to a globally flag value to create objects, test code forced to go through slow process of creating objects
    Code: Replace with parameters in constructor
    TestCode: Is not forced to read from file to create object which is slow, can now mock stuff which is fast as doesn't require reading from file
Reduce static (procedural) code
    Problem: Static methods and classes cannot be injected and cannot be mocked, a code base with all static methods is basically a procedural code and not Object Oriented
    Code: Replace static methods called by receiving those classes as dependencies and calling the classes method
    TestCode: Now, those static methods can be mocked by creating those classes
Wrapper around other people's static code
    Problem: Cannot replace static methods in code that belongs to other libraries
    Code: Create a wrapper class that wraps around those static methods
    TestCode: Can now mock those wrapper classes.
//---------------------------------------------------------------------------------------------------------------------------------
// Multi Thread Test
//---------------------------------------------------------------------------------------------------------------------------------
// Main thread => Thread running the test code and set up logic
// Callback thread => Anything that is not the main thread that was spawn in code
Use Only 1 Callback Thread
    Problem: Too many threads, difficult to debug what is going on.
    Code: Allow variable number of threads for threadpool.
    TestCode:
        Set up test to set only a single callback thread for threadpool so it's easier to debug what is happening as there are only 2 threads:
            - Main Test Thread
            - Callback Thread that runs in actual code. 
Call Mockable Methods
    Problem: Code runs in multiple threads. 
    Code: Ensure callback threads calls mockable methods to allow test code to synchronize threads.
    TestCode: 
        Can now determine where callback thread runs from main thread. 
Perform Copy By Object
    Problem: Callback thread relies on main thread test method objects.
    Code: Copy objects given by test method to Callback thread.
    TestCode:
        Can now be sure that callback thread does not depend on main thread's object after a certain point as everything has been copied.
