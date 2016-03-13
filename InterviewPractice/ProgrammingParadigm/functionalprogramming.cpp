Functional Programming
    - Imposes restrictions on how to write program, while maintaining what programs we can write
    - Maintains Referencial Integrity

Higher-Order Functions
    - Functions that take in other functions as parameters and output functions 

Pure Functions
    - no hidden inputs and hidden outputs

Writing code that doesn't change state
    - Can call same function multiple times
        - Easier to parallelize
    - Same input => Same output 
        - Reusable code
        - Order of execution doesn't matter
            - Easier to parallelize
    - Easier to test
    - Less prone to bugs
    - Easier to prove for correctness

- Reduce hidden inputs and hidden outputs to conform with some of functional programming's specialties
    Hidden inputs => Inputs that function depends on, but isn't pass in as parameter
        - state of global/static variable
        - Current time
        - Reading user input
        - Reading from file
    Hidden outputs => Outputs that function changes but isn't in the return by reference/value.
        - changing state of global/static variable
        - changing state of input variable in-place
        - sending output to ethernet, audio, file, screen
        - Throwing exception
        - Halting with errors

