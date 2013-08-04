WIC Interpreter
    by Jacob Seibel
    for Dr. Jay Fenwick's Programming Languages Course
========================================================

I.   How To Use
II.  What Works
III. What Doesn't Work
IV.  What I'm Proud Of


I.   How To Use
--------------------------

The proper use of the WIC Interpreter is to run it like so:

> wi <filename.wic>

If there is an error in entry, such as the file not existing or
leaving off the filename, you will receive an appropriate message.

The testX.wic files included test the following:
test1.wic - Tests push, pop, get, put, and halt
test2.wic - Tests the arithmetic ops
test3.wic - Tests the boolean ops
test4.wic - Tests the test ops
test5.wic - Tests the jump and jump-false
test6.wic - Tests how the program holds up in a while loop

Each of the testX.wic files works perfectly.

To test the stack, symbol table, and instruction table, use these commands:
wi -s
wi -t
wi -i

These commands run a series of tests on the stack, symbol table, and
instruction table respectively.

II.  What Works
--------------------------

All the opcodes, the symbol table, the instruction table, the stack, the
loader.  Essentially, everything.

III. What Doesn't Work
--------------------------

The only thing that doesn't work is the gcd.wic program that was provided.
When I attempt to run this program it overfills my symbol table.  I was
unable to discover the source of this problem.

IV.  What I'm Proud Of
--------------------------

I'm proud of the suffixes used to test the tables and stack, the extensive
syntax checks I added, and some of my error messages.


That's that, then.

Have a nice day!  :)
