#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* program will generate a random number from 0 to 20
user will be able to enter a number from 0 to 20
the program will indicate if each guess is high or low than original number
the player wins the game if they can guess the number within 5 tries
*/

int main()
{
 //generating random number
 time_t t;
 srand((unsigned)time(&t));
 int random_num = rand() % 21;

 // display instructions
 printf("This is a guessing game\n");
 printf("I have choosen a number between 0 to 20 which you must guess\n\n");

 //calculations
 int tries,guess_num;

 for(tries=5;tries>=1;tries--)
 {
   printf("\nYou have %d tr%s left",tries,tries == 1 ? "y" : "ies");
   printf("\nEnter a guess:");
   scanf("%d",&guess_num);
   printf("\n");
   if (guess_num == random_num)
   {
       printf("Congratulations you have won the game!\n");
       return 0;
   }
   else if (guess_num > random_num && guess_num <= 20)
   {
       printf("Sorry. %d is wrong. My number is less than that.\n",guess_num);
   }
   else if (guess_num < random_num)
   {
       printf("Sorry. %d is wrong. My number is more than that.\n",guess_num);
   }
   else if (guess_num > 20)
   {
       printf("Read instructions carefully\nEnter a number less than 20\n");
   }
 }
 printf("\nYou lost the game.The number was %d\n",random_num);

 return 0;
}
