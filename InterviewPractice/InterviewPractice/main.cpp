//-----------------------------------------------------------------------------------------------
// Interview Practice
// This file used to be for rough paper:
    // 1. To practce previous programming questions
    // 2. To practice new programming questions before documenting into other files
// However, you should just practice on CoderPad and paste to the correct files if your implementation improves
// Coderpad also works with Vim, Syntax highlighting, and google hangout, which is nice.
https://coderpad.io
// It also contains notes for you to read to practice programming challenges
// Before interviewing, go through each problem again was you would not be as good as you were in interviews.
// To make this more enjoyable, jump through each question, so like do 1 Array, then 1 String, then ... then 1 Graph, then 1 Array again
// Also, document any new refactoring skills you found out if your new solutions are in any way better than existing ones.
//-----------------------------------------------------------------------------------------------
/*
Testing your code after implementing it
Don't compile it until you check it! Then add to here when errors are made.
With practice comes confidence. Account for errors as you code to try to write perfect code the first time without checking. 
Check that:
    - What you pass into each variables is actually type (don't pass in int to double)
    - Classes are terminated with ; 
    - Static instances are initialize outside a class, defining an init() private function if necessary for STL 
    - Constructors are defined in child classes as they are not inherited
    - Any parent function used in child class must be either public or protected, if used by child class inside main(), it must be public!
*/
//-----------------------------------------------------------------------------------------------
/*
// Temporary Practice:
*/
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
// For Interviews online, you need to be able to code it.
// Thus, you need to use Standard Template Library as copying pasting your own previous code is not acceptable
// Therefore, need to use C++'s STL

//-----------------------------------------------------------------------------------------------
// Need to know how to:
// stable_sort()
// reverse() // to sort in reverse order
// binary search()
// TODO: qsort() with any arbitrary class
// work with hash tables, stack, queue, linked list, binary tree, heap
// lower_bound(), upper_bound(), bsearch(), find()
// i) Insert
// ii) Delete
// iii) Traverse
// iv) Search
// v) Max? Min?
//-----------------------------------------------------------------------------------------------
/* //
template <class X>
int binarySearch(X a[], X element, int n);

// returns index of found element or -1 if not found
// a[] contains sorted array to be search
// element is the element being looked for
// n is the total number of elements in sorted array
template <class X>
int binarySearch(X a[], X element, int n)
{
    int first = 0;
    int last = n - 1;
    int mid = (first + last)/2
    while (first <= last)
    {
        if (element == a[mid])
        {
            return mid;
        }
        else if (element < a[mid])
        {
            last = mid-1;
        }
        else // element >= a[(first+last)/2]
        {
            first = mid +  1;
        }
    }
    return -1;
}
// */

// use bsearch () from C or lower_bound() from C++ 
// use qsort() from C or sort() from C++ 

/*
2.Find average of an array after removing min and max
    -Loop and add and keep track of min and max
    -deduct both and divide by n-2
3. Find number of zeroes in a number factorial
4. add last n elements for new fibonacci instead of 2
7. Find all anagrams of a given word
Constructor, Destructor, Multithreading
C++ questions!

Given 2 large numbers
that cannot be stored in 64 bit,
how to calculate final product?
*/

// Let N = range of values given
// N = R-L+1
// then, total possible combinations is N choose 2 + N
// Example, N = 6 => N choose 2 + N = 15 + 6 = 21
// + N cause every value can be with itself

// Note: Can eliminate the N since a number XOR itself is always 0
// thus, initialize max to 0 and if a value is same with itself, don't bother comparing
 // */
//----------------------------------------------------------------------------------------

/*
// Low Level Programming
int main(void)
{
    unsigned short i, j;  // short makes it 16 bits
    i = 13;
    j = i << 2; // shift bits of i to left by 2 appending 0
    j = i >> 2; // shift bits of i to right by 2

    // If only manipulate 1 variable
    i <<= 2; // shift bits of i to left by 2
    i >>= 2; // shift bits of i to right by 2
    j = ~i; // bitwise NOT
    j = i ^ i; // xor
    j = i | i; // or
    j = i & i; // bitwise and
    struct file
    {
        unsigned int day: 5;            // 5 bits for day
        unsigned int month: 4;          // 4 bits for month
        unsigned int year: 7;           // 7 bits for year e
    };
    // Note: i << 2 + 1 means i << (2+1)
}
*/

//----------------------------------------------------------------------------------------
void swap(int ab[], int a, int b)
{
    int temp = ab[a];
    ab[a] = ab[b];
    ab[b] = temp;
}
void swap(int*a, int*b)
{
    int temp = *a; 
    *a = *b; 
    *b = temp;
}
// */
//----------------------------------------------------------------------
 //
/*
// Type of Interview Questions
// 1. OOP Design Principles (Amazon, Bloomberg, WorkDay)
    // - need know how to implement OOP!!!!!
    // e.g. Garbage Collection Analysis!!
        // Just define a baseclass that keeps track of number of objects created (it has to be static)
        // Then, each time create or destroy, we incremement and decrement the reference counter!
        // Note: All the childs' constructor and destructor must call this super class to do reference counting.
        // Then, can easily keep track of which objects are not freed from memory.

// 2. Algorithms (All Companies)
    // - all the usual algorithms questions
    // Note: It's not similar to programming challenges as it won't ask you to program Prim's algorithm or implement a Red Black Tree in 30 minutes. 
    // However, it's more of understanding the tricks to a problem (IQ based) and solving it. 

// 3. C++ Language Specific (Bloomberg)
    // - what does static, const, volatile, virtual, mutable, explicit, friend keywords do?
    // - Perform multiple inheritance, its problems, and when it is used?
    // - Perform operator overloading
    // - Implement copy constructor
    // - What are the constructors initialize if none is defined by user?
    // - Reference vs Pointers

// 4. Product Design (Microsoft, PM Roles) 
    // - Who are the users? What are their needs? 
    // - What conditions & Scenarios is it used? 
    // - What is the goal? 
    // - What is the problem with existing solutions? 
    // - Run through scenarios
    // - Get user requirements
    // - State user design 
    // - Design specification to solve problem 
    // - Evaluate whether design fulfills requirements to enable scenarios to meet goals to solve problem

// 5. Testing (Microsoft) 
    // e.g. Test Soda Machine
    // Questions - Where is the soda can? Who is it being used by? 
    // Stress testing - Keep using it 1000 times to see if it breaks. put many coins at once 
    // Performane - how long does it take to dispense a can? 
    // Security - 
    // Global - 
    // Accessibility - 
    // Usability - 

1) Object Oriented Design Principles
//----------------------------------------------------------------------
DESIGN PROCESS
//----------------------------------------------------------------------
QUESTIONS, TEST CASES, THINK, DO, TEST
//----------------------------------------------------------------------
A) QUESTIONS
//----------------------------------------------------------------------
Ask a lot of smart questions! It's a (+) for your work.
Do NOT rub away the test cases as they serve as a reminder for you to TEST.
//----------------------------------------------------------------------
B) THINK
//----------------------------------------------------------------------
// What is general? What is specific?  (general=> base class, specific => child class
// Is A? Has A?
// Design Top-Down approach!
// Run through list of design principles to see which fit:
// note: List is at GitHub
// Careful of time! It is important to show your code.
// Implement brute force approach as may have 2nd part, optimize after interviewer asks.
// If running out of time, just implement the brute force approach.
//----------------------------------------------------------------------
C) DO
//----------------------------------------------------------------------
// Just write out method prototypes and class prototypes first before implementing anything!
//      It is impossible to implementing everything in that 45 minutes of interview

2) Algorithms & Data Structures
//----------------------------------------------------------------------
DESIGN PROCESS
//----------------------------------------------------------------------
QUESTIONS, FUNCTION PROTOTYPE, TEST_CASES, ALGORITHM, IMPLEMENT, TEST
Listen to clues in question: 
    e.g. Build a binary search tree from scratch, and later return a random node in tree in uniform distribution. (each node is 1/n chance)
    clue1: Binary Search Tree
    clue2: Building from scratch => you can store an index for each node and have internals to tree to optimize random access tree
            - store number of nodes i nleft subtree and right subtree, then 1/(numLeft+numRight) to pick current, numLeft/numL+numR to go left and 
                remaining chances to go right
QUESTIONS
- Clarify with example problem and the final solution
- Clarify with function prototype, Clarify Return Value!! (IBM Round 1 compress string)
- Clarify what it is used for.
- For programming competitions: Read the question properly!
- EVEN IF IT'S NOT INTERVIEWS, YOU NEED TO ASK QUESTIONS TO: BETTER UNDERSTAND PROBLEM AND IDENTIFY CORNER CASES
    JUST ASK QUESTIONS AND ASSUME ALL ANSWERS ARE WHAT LEAD TO A MORE GENERAL SOLUTION
FUNCTION PROTOYTPE 
- Clarify return value 
- Clarity type of return value put into it
- Make sure have meaningful names 
TEST_CASES
- Come up with test cases, does it work for +, -, 0? (VERY IMPORTANT STEP), and their expected output
- Come up with simple enough test case that covers the corner cases (simple enough -> Quick to test using head), 
ALGORITHM 
- When saying complexity, make sure to define variables, O(logn), where n = number of nodes in tree or O(n) where n = height of tree
- Come up with a solution, test for complexity. 
- Come up with a better solution, test for complexity and compare
- Share both good and bad solution and why. 
- Can you do this recursively? Can you do this iteratively?
- Check solution with all the test cases
- Methods to come up with algorithm:
	i) Specific example solution -> General Rule solution
	ii) Find similar problems and match 
	iii) Simplify problem and solve. Then Generalize
	iv) Start with base case then build 
	v) Brainstorm data structures (some questions require tradeoff between data structures)
        HashTables
                O(1) Insertion, access, delete
                BUT O(capacity) iteration across all elements
            unordered_map => Hash table with key,value pairs where keys are unique
            unordered_multimap => Hash table with  key,value pairs where keys can be repeated
            unordered_set => Hash table with values as keys themselves and are unique.
            unordered_multiset => Hash table with values as keys themselves and are not unique. Each value has a 'count'
        Balanced Binary Search Tree with pointers to min(), max() and each node has pointer to parent to iterate in sorted order in linear time.
                O(logN) insertion, access, delete
                O(1) min, max
                O(n) iteration
                Sorted
            map => BST with key, value pairs, with sorted unique keys
            multimap => BST with key, value pairs, with sorted keys that can be repeated
            set => BST with values, sorted by values which are unique.
            multiset => BST with values, sorted by values that can be repeated.
        Linked List
                Can easily insert in the middle of the list.
                Can easily merge parts of 2 lists together using splice() in constant time
                BUT takes O(n) to calculate size of linked list.
            list => Doubly linked list (forward and back)
            forward_list => Singly linked list
        Queue
                Easy to push into the back of queue and pop from front of queue.
            queue => FIFO
        Stack
                Easy to push into the top of stack and pop from top of stack.
            stack => LIFO
        Double Ended Queue
            deque => Can push and pop from both sides.
        Heap
                Min() and Max() in linear time
                BuildHeap() from array takes only O(n) time.
            priority_queue
        Resizable Array
                Random access at any position
                Can be sorted and searched in logN time using binary search.
            vector
        BitSet
                Saves space if all you need is storing true/false
            bitset => Contains N number of bits that can either be true or false. Use this instead of vector<bool>
        Graphs (build yourself)
            Adjacency Matrix
            Adjacency List
- DON'T INTERRUPT INTERVIEWER WHEN HE/SHE SPEAKS!
IMPLEMENT
- Implement brute force if you can't come up with better one quickly as there may be 2nd part to a question.
- Implement solution
- Write code in detail 
- Write neatly & organize space 
- Write excellent code! 
    - Clean Code (variable name meanings), Refactoring, Testable
        - Don't use i & j because you may end up confusing yourself. Give them useful names.
    - Google's coding style
    - TODO: 
    - FIXME: 
TEST
- Check solution again
- Run example on code
- Check all lines to make sure ends with ';' 
- Check to make sure functions used in function is defined above it and not below it (forward declarations)
- Check to make sure variable parameters are actually used, and all variables used are defined? Also, are the scoping of variables correct? 
- Ensure type passed into function is actual type defined, ensure type returned from function is same as actual type collecting
- Ensure vector is push_back() NOT push(), ensure stack is push() and top() with pop() NOT JUST pop() 
- Fix any possible bugs 
- Check that in Binary Tree traversals, you pass in root->left into function instead of root->left! 
- Always use pointers for structs to prevent mistakes! Do constructor in structs to initialization in main is simpler! 
//----------------------------------------------------------------------
A) QUESTIONS & Function Prototype
//----------------------------------------------------------------------
// Common Questions
//----------------------------------------------------------------------
Function Prototype:
    What are the parameters? 
    What are the return values? Are you returning anything be reference?
    Can the input be modified?
        If not, input has to be const, and can pass in by const reference
        If yes, you can return the result by modifying the input and save space as you don't create any extra
    What if input is empty (has no elements) or NULL?
What extra/specific functionalities?
What is the problem I am trying to solve?
What does the sentence '...' mean exactly? 
Are the inputs sorted? 
    If it is not, sort them at cost of O(nlgn), if it is, then you just reduced your complexity by a lot
Are the values unique or can they be repeated? 
Use bit representation if it helps using #include <bitset> as not limited to 64 bits. 
Integers: Can there be (-) values?
    If doesn't, then use unsigned int 
    If (-) => Can only use 32 bit for bit manipulation, otherwise 64 bits (but can just use bitset)
Integers: Is there a limit to the values the numbers can have? 
    If small then counting sort is better
Is there a limit to the number of values? (If small then bubble sort is better) 
    If the number is too large but less than 2^64, use unsigned long long int instead of just int
    Refer to below for exact value ranges
    http://www.cplusplus.com/reference/climits/
//----------------------------------------------------------------------
B) FUNCTION PROTOTYPE 
//----------------------------------------------------------------------
Clarify function prototype is correct. Create multiple if flexible. 
Make sure check function prototype has return value, for C's array, make sure pass in length of array as well. 
//----------------------------------------------------------------------
C) TEST_CASES
//----------------------------------------------------------------------
Come up with a short enough test case that covers all the required corner cases 
Came up with more than 1 test case, maybe 2 or 3. Each testing specifics like what if n = 1, n = even, n = odd
From test case, you may notice pattern in data. 
FOr each test case, come up with expected output 
//----------------------------------------------------------------------
D) ALGORITHM 
//----------------------------------------------------------------------
Come up with the design for the algorithm. Must come up with multiple solutions and not just one. 
Improve time complexity? Improve space complexity? Tradeoff one for the other? 
Compare solutions and make sure they work with your 2-3 test cases
//----------------------------------------------------------------------
E) IMPLEMENT 
//----------------------------------------------------------------------
Implement your algorithms!
- Don't assume your variables / arrays are initialize to 0 , initialize them yourself!
- For loop iterator, (i or j etc.) must be same type as condition being compared to (N)
    // if N is unsigned int, for loop i has to be unsigned int as well
- If adding contiguously,
    // e.g. 1 2 3 4 5 => 1 3 6 10 15
    // instead of for looping and adding, just add each next one with the new value read with previous
    // for loop => O(n^2), add previous => O(n)
- When working with unsigned, the value can never be < 0!! So cannot terminate when j < 0 cause j will never be < 0!!
    // also careful with starting loops with N-2, cause if N is 1 then value will be 1-2 = very large (+) number!
//----------------------------------------------------------------------
F) TEST
//----------------------------------------------------------------------
Run through test cases with the algorithm. 
Make sure to actually run step by step with the conditions and code! Assume you are the compiler. 
// */
//----------------------------------------------------------------------
/* //
//----------------------------------------------------------------------
// Ways to Become the Best Programmer
// Technical Skills, Usefulness to society, Produces income, Brings Fame
//----------------------------------------------------------------------
// note: Refer to below for more details on each of them
// Understand a basic course of all the technologies you could have picked at Google which are:

TODO (1 course each! => 3 to 4 assignments to upload to Github)
    Machine Learning
    Natural Language Processing 
    Distributed Systems & Parallel Computing
    Distributed Algorithms
    Concurrency & Multithreading
    Information Retrieval 
    Computer Networks
    Compilers
    Security 
    Economics & Electronic Commerce
    Data Mining
    Speech Processing 
    Statistics 
    UX & UI 
DONE
    Computer Vision
    Computer Graphics 
    Algorithms
    Operating Systems 
    Web Front End
    Web Back End 
    Databases

You need to prove to yourself and the world that you are the best by winning competitions. 
1. Compete in hackathons (Build a prototype from a great idea quickly) 
	- Goal:
		- Difficulty => Was what you built difficult to implement, is it just nice graphics on some API? 
		- Usefulness => Will people use your hack, does it solve a real problem 
		- Originality => Were you the first person to come up with this solution
		- Design => How is the user experience and user interface in using your product? How complete does it look?  
	- Preparation: 
		- Did you practice working with the technologies you need before the hackathon? 
			(e.g. Google Maps, Android Sound, NodeJS/Javascript/AngularJS)
		- Are you able to team up with a strong team? 
	- Ability to learn something new and use it very quickly
	_ Ability to implement things quickly 
	- Ability to motivate, stay productive, sleep less. 
	- Ability to pitch your idea to everyone during presentation and team gathering. 
	- Ability to divide work and integrate between teams
2. Compete in programming challenges (Algorithms, Problem Solving, Efficient Coding) 
	- Based on: 
		- Algorithms => Knowledge on time space complexity 
        - Data Structures => How well do you know all existing data structures and their implementation and their details in implementation differences. 
        - Math => How well can you solve a math problem
        - IQ => How well do you detect special cases for this problem
3. Kaggle Competitions (Machine Learning, Statistic, Data Mining)
	- Based on: 
		- Proficiency in Analyzing Existing Data
		- Proficiency in Data Mining 
		- Proficiency in using the right ML models and libraries 
4. Open Source (Working Efficiently with Legacy Code, Code Complete, Testing, Working with large code bases, Understand cutting edge technologies) 
	- Based on: 
		- How often do other programmers use your work? 
		- How easy are you able to understand large amount of code and improve it
        - Can you parallelize code and build robust, scalable, efficient systems.
        - Do you understand the architecture of a new technology, how it works and why it beats older technologies? 
    - Need to know: 
        - Competent in both using these new technologies as well as understand how they work and why. 
        - Technologies: 
            Apache Kafka => Message Queues
            Apache Zookeeper => An abstraction for concurrency problems
5. Start Ups (Compete in Life) 
	- Based on: 
		- Creating a solution that is: 
			- Large User Base  or Difficult to re-invent by competitors
			- Has a large market (people will use it) 
			- Has a business model (how does your product produce revenue) 
		- Ability to pitch to investors 
			- What the problem is? 
			- What your solution is? 
				- Why is it unique? 
			- What the business model is? 
				- How will you earn money
		- Ability to use open source code to achieve what you ned
		- Ability to gather a strong team 
6. Research Papers (Mathematics) 
    - Based on:
        - Ability to understand difficult math. 
        - Ability to solve difficult problems using math
        - Ability to write well (Excellent Technical Writing) 
Technical Skills Steps: (How to acquire the technical skills you need)
1. Solve programming challenges quickly
	- (Understand, Augment, Create) algorithms & data structures
	- Code on paper (from memory => Memorize syntax)
	- Solve problems flexible (time & space tradeoffs)
	- Handle corner cases efficiently
	- Ability to reduce problems to existing ones ( Max consecutive words -> Max substring , Reverse Words -> Reverse strings)
	- Write test cases for own code (C: Check, Java: Junit)
	- Use debugger (C: GDB, C: Valgrind) (e.g. Prof. Ashvin found out your problem quickly)
	- Profile code for speed & space optimality
	- Analyze how many time you would hit a function and reconsider if need to put inside while loop (Bloomberg Interview)
	- Ace Programming Interviews (speak out loudly)

2. Complete Hackathon Projects quickly
	- Integrate API's together (REST API)	
	- Integrate Internet of Things 
		- How to connect Leap Motion with Air Drone 2.0 with Node Server 
	- Fix other people's bugs (Stack Overflow -> Use it like piazza)
	- Create new algorithms to solve problems.

3. Understand large amount of code and use it
	- Contribute to open source (code daily), able to understand open source code quickly from documentation
	- Write test cases within development code using compiler primitives (e.g. #ifdef DEBUG assert(i == 1); #endif)
	- Code for fun! (code sudoku game, payment at restaurants, playstation randomizer)
	- Use Software Tools (Compilation, Documentation, Source Control) (C: Makefile, C: Doxygen, GIT, Subversion)
	- Combine multiple languages together (Matlab, C++, JAVA, C, Android) (Don't be a language person, use what works best for a specific tool)
	- Code modularity & portability (Classes, Helpfer Functions, Templates, Function pointers, Variable argument)
	- Find out things about system (ECE344 Bonus Assignment), how the open source code is implemented (Piazza Hack)
	- Read and perform code reviews on stack exchange.
		http://codereview.stackexchange.com/
	-  Code using Vim and do everything on commandPrompt/Terminal (Add environment variables!)
		(e.g.: Cygwin, gdb, makefile, git status)
		Basically, stop using every IDE and just use VIM! and make use of the features of VIM!
	- Follow GitHub Users with lots of followers for a specific technology/language.
	- Contribute to opensource on GitHub
	- Code up softwares that people use on GitHub. That's much more impressive than winning coding competitions. 
	- Hack into programs (e.g. Try to hack into Diablo)

4. Kaggle competitions (Big Data)
	- Parallelize code (Threads, Processes, Scheduling, Event based, Map & Reduce, Using GPUs)
	- Work with Cloud Computing technologies

5. Start Ups 
	- Throw and Exception Handling
	- Perform garbage collection analysis the right way.
	- Master OOP Design patterns
	- Focus on graphical user interface designs to make work a marketable product.
	- User experience and user interface
	- Code has to be designed such that it is (testable, maintainable, extensible) 
	- Learn to package your code into an installer and executable. So non-programmers can just download it, install it, and run the .exe file! 

6. Research Papers

//----------------------------------------------------------------------
// Track Your Progress
//----------------------------------------------------------------------
- Able to know if your current approaches are working and change if it doesn't
- TODO:  More on this later
// */
//----------------------------------------------------------------------
//
/*
// Using GDB on terminal
Commands
print j  // print variable j
watch z // break when variable z changes value
watch (z > 28) // break when variable z is more than 28
                // note: Watching local variable is canceled as soon as variable goes out of scope
                // Thus, will normally only watch global variables or local variables in main()
up // brings you to function that called this function
down // brings you to function that is called
     // Changing stack frames will change the value of the local variable at that frame
backtrace // shows entire collection of stack currently in existence
help breakpoints // access documentation of gdb's commands such as breakpoints

// Using compilation on terminal
gcc -g -Wall -o programName main.c // Note: -g command is needed to store symbol table used during gdb sessions
// */
//----------------------------------------------------------------------

/*
//----------------------------------------------------------------------
// If super lost for any combination, math type question, try everything
//----------------------------------------------------------------------
1. Code brute force solution (BFS,DFS), use A* search if needed. Basically A.I. is all about trying everything
2. Code dynamic programming solution, come up with 1. 
3. Code greedy solution. 
4. Find out optimal solution with math if needed
5. Assume that you have some function available that already works, how can you use that to solve current problem
    (Google Interview: where you assume you have function to find a range of a duplicated number in sorted array and solved the bigger problem)
Just trial and error and see which works
//----------------------------------------------------------------------
// When do you look at solution  
//----------------------------------------------------------------------
1. After you are making no progress even after coming back to problem later. 
2. After you have tried every single approach (dynamic, greedy, bit manipulation, every single data structure (graph, heap, trie, disjointset), sort, search algo you know) 
3. After you have accounted for all assumptions and every possible corner cases. 
4. After you try dynamic programming on every single dimension and variable combination.
5. However, if you feel you are learning more about problem even if it fails, you can't look at solution. 
6. Only after you have tried everything, and you are sure you made no progress at all. Then you look at solution a little and work from the hints. 
Then finally, when you solved it with helps from hint or copying solution, you add to your notes. What approach did you not account for
that did not get you to that solution. 
//----------------------------------------------------------------------
// Lessons Learnt
//----------------------------------------------------------------------
//----------------------------------------------------------------------
1. Can only use sizeof(ab)/sizeof(ab[0]) when ab is a variable, NOT a parameter (must pass in value of n to a function for arrays)
int main(void)
{
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    int n = sizeof(a)/ sizeof(a[0]) ; // correct this gives you 10,
    someFunction(a);
}
// inside someFunction();
someFunction(int a[])
{
    //WRONG!!!!!!!!! CAN'T USE SIZEOF from AN ARRAY PARAMETER
    int n = sizeof(a)/ sizeof(a[0]) ;
}
Solution:
// inside main
someFunction(a, sizeof(a)/sizeof(a[0]));
someFunction(int a[], int n) { }
//----------------------------------------------------------------------
Notes:
1. Remember to write: using namespace std; // with #include <iostream>
2. Remember to check for correct output in main() after calling the function!
3. It's swap(arrayVar, j, j+1) NOT swap(arrayVar, arrayVar[j], arrayVar[j+1]) OR just (arrayVar[j], arrayVar[j+1]) if passing by pointer for integers
4. if define, int main(void), always remember to return 0!! or any integer
5. In forloop, it's (int j = 0; j< something; j++) NOT (int j = 0; something; j++)!!!
6. When have nested for loops and while loops, make sure remember to close and open curly braces properly!
7. set an entire array to 0 using  memset(arrayName,0,sizeof(arrayName)); // to set an array to 0
    // memset() is defined in <string.h>
*/
// */
