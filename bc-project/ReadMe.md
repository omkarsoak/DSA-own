# Arbitrary length binary calculator (bc) - Linux Utility
- Arbitrary precision calculator that can add, subtract, multiply and divide arbitrary length numbers
- Can compute arbitrary length expressions
- numbers are stored in the form of linked list, with each digit forming a node
- Direct infix evaluation (using stack) without converting to postfix
- Example of calculation is $12038138198*120398019281-1232198319283+834729387242/32242$

------------
## Run Locally

```bash
gcc -Wall main.c linked_list.c stack.c operations.c -o main
```
INPUT: STRING OF NUMBERS AND '+ - * /' IN BETWEEN  <br>
OUPUT: ANSWER <br>
EXAMPLE: <br>
198237918479+83634875862-123312*242  <br>

```bash
./main 198237918479+83634875862-123312*242
```

## OUTPUT
```bash
281842952837
```


## DATA STRUCTURES USED:
- LINKED LIST (to store each number with each digit as a node in the LL)
- NODE STACK (stores the numbers as pointer to head node of LL during infix evaluation)
- char STACK (stores operators during infix evaluation)


-------------
### Author
[Omkar Oak - 112103099](https://github.com/omkaroak26)

