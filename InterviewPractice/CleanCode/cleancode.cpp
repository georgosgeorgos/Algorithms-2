/* //
Table Of Contents
    Goals
    Names
    Functions
    Comments
    Formatting
// */

//-------------------------------------------------------------------------------------------
// Goals
//-------------------------------------------------------------------------------------------
Be able to understand your code by just reading your code without comments
Be able to easily understand the entire project of what you large code base covers 
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
