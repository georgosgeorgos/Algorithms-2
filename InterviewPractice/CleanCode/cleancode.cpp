/* //
Table Of Contents
    Goals
    Names
    Functions
    Comments
    Formatting
    Data Abstraction
    Exception Handling
    Streams
    Constructors
    Logging
    Configuration
    Performance
    Boundaries: Third Party Library
// */

//-------------------------------------------------------------------------------------------
// Goals
//-------------------------------------------------------------------------------------------
Be able to understand your code by just reading your code without comments
Be able to easily understand the entire project of what you large code base covers 
Be able to easily make changes to existing code
Reduce number of WTF's per minute when others read your code = Reduce number of surprise factors in code
//-------------------------------------------------------------------------------------------
// Names
//-------------------------------------------------------------------------------------------
- Descriptive
    Anywhere you see the variable, it comes with it's description 
- Pronounciable
    When you discuss with teammates, you can all pronounce it
- Searchable
    Don't use short words like 'k' cause can't search for an alphabet easily in file. 
    Easy to search
 - Never use l or O (cause L can be l or 1, O can be O or 0)
 - Replace constants (e.g. 200, 300) with what they represent using MACROS! 
    Easy to change in Macro as it is all in one location
    Easy to understand what these constants mean
//-------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------
- Small 
    Readable
    Easy to debug
    Unique
    Break it up
    Does one thing only
- Decrease number of arguments
    Easier to test
        Don't have to create so many mock objects. 
    Reduce flag arguments 
        Arguments that causes function to behave differently according to flag to different functions 
        If similar code exist, just put similar code into functions
    Hard to understand what each parameter does when there's too many arguments
    Group arguments into one List of arguments if treated similarly.
        That way, you know that the arguments are going to be iteratively treated similarly
    Group arguments into an object's properties
        That way, you know that all the arguments belong to an object. 
- Input or Output?
    Hard to tell if the parameter is an input to a function, or if a function is returning by reference to it. 
    Try to keep the convention, where argument is passed as input to the object calling the method. 
        e.g. report.addTitle(titleName); // Input to report
        However, can't alter returning more than 1 value by reference, so meaningful variable names. 
- Separate Command From Query
    if(set(user,attribute))
        Problem:
            Is it return true if successfully set? 
                if
            Is it return true if user was set to attribute previously? 
                Solution:
                if(!attributeExist(user))
                {
                    setAttribute(user,attribute);
                }
- Exceptions > error codes
    Error codes results in many different if and else statement when using the function.
    Exception results in only a try and catch block when using the function. 
    Easier to add new exceptions to a class since it derives from parent Exception class, but need recompile every class if using a set of error codes. 
    Each time you throw a new exception from catching an old one, always append the old method's message so that you don't lose the root of the cause of exception
        catch (Exception e) {
            throw new whateverException("whateverNewMessage\n" + e.getMessage(), e);
        }
- Separate error handling from functionality of code. 
    Try and catch block    
- Write, then refactor. 
    You can't write clean function on the first try, first try is for getting it to work. Then, clean it up before you push it for review. 
//-------------------------------------------------------------------------------------------
// Comments
//-------------------------------------------------------------------------------------------
Code changes, comments may not follow. 
    Understand the code when you see it, and not have to search through the comment that explains that code 
        e.g. methods and variables that gets used everywhere but explained once in comments
Don't: 
    comment bad code, rewrite it.
    repeat what code is saying using comments.
        Explaining constructor/getters/setters 
    journal of changes (version control does that for you now!) 
    Mark closing braces, make function shorter instead, editors does that for you as well.
    e.g. 
            } // if
        } // try
    Comment out old code (version control saves it for you now!) 
Replace comments that describe what a function does by describing it in the function name. 
When to comment: 
    Can't figure out how to explain it clearly using code. 
        Prevent using comment to cover up what your bad code is trying to do, clean up your bad code so it is easy to understand.  
    What to explain a design decision on why your code implements it this way. 
    Warning of consequence
        e.g. This function is NOT thread safe
    TODO: comments that tells programmer feature that aren't implemented yet
    FIXME: comments that tells programmer there is a bug in a certain function
    Amplification
        e.g. You must trim white space to make sure the objects are comparable. 
   Documentation Generator 
        e.g. JavaDocs, DOxygen
//-------------------------------------------------------------------------------------------
// Formatting
//-------------------------------------------------------------------------------------------
In a team, stick to team's style conventions. 
Each file should be as simple as possible at the top of file. 
The user can then dive to bottom of the file for details. 
Vertical distance between related code should be close
    e.g. 
       Removing the comments on top of member variables, you can easily see how many member variables a file has, and number of methods
       BAD: 
            // The age
            int age; 

            // The height
            int height; 
       GOOD: 
            int age; 
            int height; 
Prevent reader from hoping around too much between related code. 
//-------------------------------------------------------------------------------------------
// Data Abstraction
//-------------------------------------------------------------------------------------------
You want to hide implementation.
    Don't always put getters and setters for every single member variable you have
        class sillyClassExposingEverything {
            private int a; 
            private int b;
            void setA(int _a);
            void setB(int _b);
            int getA();
            int getB();
        }
    Getters()
        // Doesn't hide implementation: you know it's stored in gasoline with unit gallons
            getGallonsInGasoline();
        // Hides implementation
            getPercentageOfFuelRemaining();
    Setters()
        // Doesn't hide implementation: you know there is an X point and a Y point
            setX()
            setY() 
        // Hides implementation: you don't know how it stores its values, can set via radius or points, also, must set both values together.
            setPolarCoordinates(double r, double theta);
            setCartesianCoordinates(int x, int y);
//-------------------------------------------------------------------------------------------
// Exception Handling
//-------------------------------------------------------------------------------------------
Separate actual program logic with exception logic. 
    Wrap the actual program logic in a class that handles exceptions. Call that wrappers method instead. 
Never use return codes to indicate error, always use exceptions. 
    For example, if error occurs, instead of returning -1 to indicate error, or even constructing special Integer wrappers so you can return null to handle errors,
    you simply throw an exception! 
Stack Trace from exception are the basic requirements, however do add informational messages at each level of the stack trace to know why it failed at each level. 
Never return NULL 
    Then, won't have own logic code filled with if(variable != null) 
    If 3rd party API returns NULL, create a wrapper and return a special exception instead! 
Never pass NULL
    Try not to design function that accepts null as an argument, so you will never pass the NULL values to them! 
Always throw only 1 class of Checked Exception finally in your interface. Catch all other runtimeexception. This way
    users to your interface won't be shocked by all the other exceptions. However, throw unchecked exceptions within the classes themselves. 
    This way, your own classes won't need so many try and catch blocks to catch checked exceptions, and instead can check all other exceptions under the Exception parent class. 
    e.g. 
        interfaceMethod() throws customException {
            try {
            } catch (Exception e) { // catches all exceptions
                throw new customException(e.getMessage, e);
            }
        }
        ownMethodThatDontNeedThrowStatement() {
            ...
            throw new RuntimeException(...);
        }
        ownMethodUsingownMethodThatDontNeedThrowStatementWillNotNeedTryCatchBlocks {
            ...
            // don't need try block for below
            ownMethodThatDontNeedThrowStatement();
            // don't need catch block for above
            ...
        }
//-------------------------------------------------------------------------------------------
// Streams 
//-------------------------------------------------------------------------------------------
Always close all streams properly using try with resources block 
    boolean exceptionOccurred = false; // only needed if have finally block to close streams that do not implement AutoCloseable
    try ( 
        ... // open few streams
    ) {
        ... // actual code
        try (
            ... // open more streams
        ) {
            ... // actual code
        }
    } catch(Exception e) {
        // handle exceptions 
        exceptionOccurred = true;
    } finally {
        // close streams that do not override Autocloseable
        // Ensure this code is run and isn't prevent from exception
    }
    Assert.assertFalse(exceptionOccurred, "Reason why it failed");
For languages like C++ without any finally block or tryWithResources block, ensure stream are closed properly by using
    objects to manage resources. It closes it automatically using it's destructor.
//-------------------------------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------------------------------
Should always be declared public.
    public className(...) {}

Unless you don't want users to use it
    private className(...) {}

If you don't users to use it, but you want it to be testable, make it package private
    className(...) {}

//-------------------------------------------------------------------------------------------
// Logging
//-------------------------------------------------------------------------------------------
Try to use a facade like SLF4J so that the implementation can differ and can be injected but same API 
Format logging to be more readable. 
    Not very readable
        logger.info("This is " + var1 + " not very " + var2 + " okay!");
    Readabale
        logger.info("This is {} not very {} okay!", var1, var2);
Debugging logs should be informative enough to re-construct failure scenarios
//-------------------------------------------------------------------------------------------
// Configuration
//-------------------------------------------------------------------------------------------
Dependency Management: 
    Never depend on SNAPSHOT for production company services, always depend on a stable release version.  
//-------------------------------------------------------------------------------------------
// Performance
//-------------------------------------------------------------------------------------------
80-20 rule: A program normally spends 80% of time executing 20% of code. Figure out which 20% needs to be highest performance.
Bottlenecks: There is no point making a section of code faster if it isn't the bottleneck region.
Move running time to compilation time: Reduce program run time by moving it to compilation time. 
        e.g. Making sure everything is defined via interfaces during compilation time
             instead of using polymorphism to infer object type during runtime
//-------------------------------------------------------------------------------------------
// Boundaries: Third Party Library
//-------------------------------------------------------------------------------------------
Use Libraries that are well known and robust, instead of re-writing your own code from scratch. 
Create wrappers for third party library
    Advantages: 
        Own code logic can be independent on 3rd party API as well as their updates. 
        Can mock so that only test own code.
        Can handle exception code in the wrappers
        Can find out if new version of Third Party Library deprecated automatically
Write learning test:
    Unit test that test Third Party Library code behaves like what we expect. 
    This way, when Third Party Library updates to not be backward compatible, we will find out. 
    Learning test cost nothing, cause you had to learn the API anyway, might as well learn while writing them. 
Disadvantage: 
    Increasing unit test time taken due to extra test
//-------------------------------------------------------------------------------------------
