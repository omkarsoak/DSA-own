# BC Binary calculator - (A Linux Utility)
- Arbitrary precision calculator that can add, subtract, multiply and divide arbitrary length numbers
- Can compute arbitrary length expressions
- numbers are stored in the form of linked list, with each digit forming a node
- Example of calculation is $12038138198*120398019281-1232198319283+834729387242/32242$

------------
## WORKING
Input: On the command line
INPUT: STRING OF NUMBERS AND '+ - * /' IN BETWEEN 
OUPUT: ANSWER 
EXAMPLE:
198237918479+83634875862-123312*242
Answer: 281842952837

## DATA STRUCTURES USED:
- LINKED LIST (to store each number with each digit as a node in the LL)
- NODE STACK (stores the numbers as pointer to head node of LL during infix evaluation)
- char STACK (stores operators during infix evaluation)


-------------
### Author
Omkar Oak - 112103099

