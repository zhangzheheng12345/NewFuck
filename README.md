# NewFuck  
Call it NF in the following statements.  

## NF Language  

This language is quite similar to the language of BrainF*ck (which is called BF in the following statements).But some more new grammar is added to NF so that NF is more easy to use and powerful.  
Though BF is more likely to be a special toy for programmers,its son NF is more meaningful(probably more interesting as well).  

## Grammar
### Data and Their Types

+---+---+---+----+  
|    |    |    |...,|  
+---+---+---+----+  
Values are put in continuous boxes like BF,but they can have different types. In BF there is only one type,and now we got integers,characters and strings.  
### Operators
'+': Plus 1.  
'-': Minus 1.  
'>': Move to the next box.  
'<': Move to the last box.  
'.': Print the value in the present box.  
',': Get user's input and put it in the present box.  
';': Get user's input (the whole line) and put it in the present box.(Different from BF)  
'[': If the value in the present box isn't 0,enter the loop.  
']': End loop.  
'(': If the value in the present box isn't 0,enter the block(run once).(Different from BF)  
')': End block.(Different from BF)  
'i': Set the present box int.(Default, and different from BF)  
'c': Set the present box char.(Not default, and different from BF)  
's': Set the present box string.(Max 1025 size, not default and different from BF)  
'=': Fill the present box with the following constant value.(Different from BF)   

* (Example:"=10" set the present box 10)   

12345: Constant int value.(Different from BF)  
'a': Constant char value.(Different from BF)  
"hello": Constant string value.(Different from BF)
'r': Run NF script.(Path should be put in the present box before, different from BF)    

## Interpreter
It's written by C++ in the directory of "NewFuck".(NewFuck.cpp).  
My platform is Windows 10 & Visual Studio 2019 Community and you can open the NewFuck.sln to open the project or just use g++ to compile it(might work).  