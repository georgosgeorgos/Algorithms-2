/* //
Table Of Contents
    Goals
    Names
    Functions
    Comments
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




