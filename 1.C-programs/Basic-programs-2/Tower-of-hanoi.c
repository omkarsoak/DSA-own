/*******
RULES OF TOWER OF HANOI :
*Only one disk may be moved at a time.
*Each move consists of taking the upper disk from one of the 
    stacks and placing it on top of another stack or on an empty rod.
*No disk may be placed on top of a disk that is smaller than it.
*******/
#include <stdio.h>
#include <stdlib.h>

void towers(int num, char src, char dest, char aux)
{
    // Base Condition (exit for recursive call)
    if (num == 1)
    {
        printf("\n Move disk 1 from peg %c to peg %c", src, dest);
        return;
    }
    // Recursively calling function twice
    towers(num - 1, src, aux, dest);
    printf("\n Move disk %d from peg %c to peg %c", num, src, dest);
    towers(num - 1, aux, dest, src);
}

int main()
{
    int num;
    printf("Enter the number of disks : ");
    scanf("%d", &num);
    printf("The sequence of moves involved in the Tower of Hanoi are :\n");
    towers(num, 'A', 'C', 'B');   //A - source, B - destination, C - auxillary
    return 0;
}
//Time complexity - O(2^n)