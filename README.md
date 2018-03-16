# CS100 rshell Assignment 4
==========================

Authors
-------------
Thomas Lee
tlee066@ucr.edu

Kimberly Wu
kwu017@ucr.edu 

Repository
--------------
https://github.com/tlee066/CS100-Assignment-4-Kim-Thomas

Task Distribution
--------------
Thomas Lee complete:

Task 1: Github Setup (10%)

Task 2: Input redirection (For commands contain "<", 20%);

Task 3: output redirection (For commands contain ">" and ">>", 5%);

Task 5: construct test scripts (enough test cases, 15%);

Total: 50%


Kimberly Wu complete:

Task 3: "Test" command 2 (for the case "[ -e test/file/path ]", 15%);

Task 4: Piping (25%)

Task 6: construct json and README files, and git commit (that means, all the works meaned from the part "Submission" to "Coding Conventions" in assignment 4 description)(10%) 

Total: 50%


Summary
--------------
***rshell*** is a command shell program, created to have the ability to implement BASH commands. rshell
prints a command prompt (ex. $) then reads user input on one line. 

Commands syntax:
```
executable [ argumentList ] [ connector cmd ]
```
Available Connectors:
```
&&, ||, ;
```
Comments are supported in ***rshell***.
Anything after the # symbol will be considered a comment.

Connector Descriptions
---------
; (semicolon) - if a command is followed by ;, the next command is always executed.

&& (and) - if a command is followed by &&, the next command is executed only if the first succeeds.

|| (or) - if a command is followed by ||, the next command is executed only if the first fails.

Test Scripts
----------
Our version of ***rshell*** comes with multiple testing scripts designed to display proper functionality
of our program. To run any of the scrips, navigate to the tests directory and enter:
```
./<scriptname>
```
Scripts include:
```
append_redirect_test.sh		#tests appending redirection
input_redirect_test.sh		#tests input redirection
output_redirect_test.sh		#tests output redirection
pipe_test.sh				#tests piping

```
To run rshell
---------
Open the terminal and run these commands:
```
1. git clone https://github.com/tlee066/CS100-Assignment-4-Kim-Thomas.git
2. cd CS100-Assignment-4-Kim-Thomas
3. git checkout assn4
4. make
5. ./bin/rshell
```
Known Bugs
--------
1. Does not handle quotations. (ex. echo "Hello world" should print hello world, but instead rshell prints the entire string including quotations "hello world".)
2. As of now multiple precedence operators (parentheses) work, when they shouldn't. (ex. ((ls)) should not work, but our program treats them as balanced operators and executes normally.)
3. Piping test script has a few errors when run, but running the exact same test cases with normal program execution does not yield any errors.

