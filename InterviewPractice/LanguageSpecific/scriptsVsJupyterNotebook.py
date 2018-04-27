Below are the arguments for advantages and disadvantages of Pythons vs Jupyter Notebook

#-----------------------------------------------------------------------------------------
# Jupyter Notebook: (Behaves like Matlab)
#-----------------------------------------------------------------------------------------
Advantages
- Easy to explain
- Easy to store global variables and work on small interactive code.
- Easy to debug (can split into small sections)
- Can change hyperparameter values while code is training.
- Can pause execution of code, change variable (e.g. hyperparam) values, and resume training.
- Good for explanation on scientific work.
- Good for easily duplicating notebook to test out other ideas.

Disadvantages:
- Difficult to share or re-use code
- Not robust as you keep copying code.
- Difficult to search for code as latex search only works within current small window
- Not versio control friendly as you cannot know what change
#-----------------------------------------------------------------------------------------
# Python Scripts
#-----------------------------------------------------------------------------------------
Advantages
- Easy to share code
- Easy to re-use code
- Robust (production code)
- Version control friendly to keep track of updates.

Disadvantages:
- Difficult to debug as hard to run small snippets without running from scratch.
- Need to run from scratch or load from saved values everytime.
- Difficult to test out ideas as need code to work with existing interface.

#-----------------------------------------------------------------------------------------
# Conclusion
#-----------------------------------------------------------------------------------------
Code on jupyter notebook for experimentation. 
Once everything works and you have enough knowledge.
e.g. need scalable matrix, need work with bandits, one class, rating matrix
e.g. need prediction over observes only, or prediction over everything.
e.g. need add 1 for bias to rating matrix.
Then you spend a few days coding it into a nicely tested library.
