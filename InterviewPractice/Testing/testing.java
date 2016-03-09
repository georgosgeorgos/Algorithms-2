// Mockito
/*
Types of Test:
    Unit Test
    Integration Test

What to Test:
    State Test
        Test that function returns right results based on tested input 
         Basically, if it returns the right tested input, that means the state of the objects changed correctly. 
    Interaction Test
        Test that function calls the right method properly (e.g. a Sort master class calls the quicksort method instead of bubblesort method
        
    Behavior Test
        Test methodNames should be sentences describing behavior of test. Ignore clean code practices for unit testing. It's different!
*/

Testing Guidelines:
    testMethodNames should be sentences describing behavior of test, what exactly is being tested, what are the inputs and what are the expected outputs. 
    testMethodNames should begin with word 'should'
Unit Test Guidelines:
    Don't use functions inside Unit Test cause you don't want to be testing, debugging your unit test. Instead, re-write every code. 
    setup() and cleanup() only works if ALL your unit test uses them. 

Mocking Benefits: 
    Test each unit in isolation
        Get to really test that one class you are testing instead of also testing the objects that are composed by it. 
    Don't actually call the methods that are being mocked
        e.g. Don't want to actually send an email for exception each time test runs
        e.g. Faster test run-time as don't need to run mocked objects

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
