/**********************
PLAY A TIC-TAC-TOE GAME
***********************/
//Version 1
//Author: Omkar Oak

/*
THE PROGRAM HAS FOUR PARTS:-
1.) The main function containing the game controls
2.) The 'check for win' function contains all the possibilities of winning,game in progress and draw
3.) The 'display board' function prints all the output on the screen like lines numbers etc
4.) The 'mark board' function marks 'X' or 'O' in the right place
*/

#include <stdio.h>
#include <stdlib.h>

//declaring global variables

char square[10] = {'0','1','2','3','4','5','6','7','8','9'};
int choice,player;

//declaring functions

int check_for_win();
void display_board();
void mark_board(char mark);

/****************
THE MAIN FUNCTION
****************/

int main()
{
    int game_status;
    char mark;
    player = 1;

    do
    {
        display_board();

        player = (player % 2) ? 1 : 2;

        printf("Player %d, enter a number:",player);
        scanf("%d",&choice);

        if (player == 1)
        {
            mark = 'X';
        }
        else
        {
            mark = 'O';
        }

        mark_board(mark);

        game_status = check_for_win();

        player ++;

    }
    while (game_status==-1);

    if (game_status == 1)
    {
        printf("\nPLAYER %d WINS!!\n\n",--player);
    }
    else
    {
        printf("THE GAME IS DRAW");
    }

    return 0;
}

/*********************
CHECK FOR WIN FUNCTION
**********************/

/**
FUNCTION TO RETURN GAME STATUS:-

1 FOR GAME IS OVER WITH RESULT
-1 FOR GAME IS IN PROGRESS
0 FOR GAME IS OVER AND NO RESULT
**/

int check_for_win()
{
    int return_value=0;

    /*The following if statement contains all possibilities of winning
     They are:-
     1-2-3
     4-5-6
     7-8-9
     1-4-7
     2-5-8
     3-6-9
     1-5-9
     7-5-3
     */

 if (square[1] == square[2] && square[2] == square[3])
 {
     return_value = 1;
 }
 else if (square[4] == square[5] && square[5] == square[6])
 {
     return_value = 1;
 }
 else if (square[7] == square[8] && square[8] == square[9])
 {
     return_value = 1;
 }
 else if (square[1] == square[4] && square[4] == square[7])
 {
     return_value = 1;
 }
 else if (square[2] == square[5] && square[5] == square[8])
 {
     return_value = 1;
 }
 else if (square[3] == square[6] && square[6] == square[9])
 {
     return_value = 1;
 }
 else if (square[1] == square[5] && square[5] == square[9])
 {
     return_value = 1;
 }
 else if (square[7] == square[5] && square[5] == square[3])
 {
     return_value = 1;
 }

 //The folllowing else if checks for a draw

 else if (square[1] != '1' && square[2] != '2'
          && square[3] != '3' && square[4] != '4'
          && square[5] != '5' && square[6] != '6'
          && square[7] != '7' && square[8] != '8'
          && square[9] != '9')
 {
     return_value = 0;
 }

 //The following else is for game in progress

 else
 {
     return_value = -1;
 }

 return return_value;
}

/****************************************
FUNCTION TO DRAW THE BOARD OF TIC TAC TOE
*****************************************/
//This function return no value,it is just displaying the layout of the game

void display_board()
{
    //the following command clears the screen

    system("clear");

    //This is the layout of the game

    printf("TIC TAC TOE GAME\n\n");
    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");

    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n",square[1],square[2],square[3]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c  \n",square[4],square[5],square[6]);

    printf("_____|_____|_____\n");
    printf("     |     |     \n");

    printf("  %c  |  %c  |  %c  \n",square[7],square[8],square[9]);
    printf("     |     |     \n\n");
}

/*************************
FUNCTION TO SET THE BOARD
WITH THE CORRECT CHARACTER,
X OR O IN THE CORRECT SPOT
**************************/

void mark_board(char mark)
{
    /*This if else statement is assigning 'X' or 'O'
    only if it is not occupied before hand*/

    if (choice == 1 && square[1] == '1')
    {
        square[1] = mark;
    }
    else if (choice == 2 && square[2] == '2')
    {
        square[2] = mark;
    }
    else if (choice == 3 && square[3] == '3')
    {
        square[3] = mark;
    }
    else if (choice == 4 && square[4] == '4')
    {
        square[4] = mark;
    }
    else if (choice == 5 && square[5] == '5')
    {
        square[5] = mark;
    }
    else if (choice == 6 && square[6] == '6')
    {
        square[6] = mark;
    }
    else if (choice == 7 && square[7] == '7')
    {
        square[7] = mark;
    }
    else if (choice == 8 && square[8] == '8')
    {
        square[8] = mark;
    }
    else if (choice == 9 && square[9] == '9')
    {
        square[9] = mark;
    }
    else
    {
        printf("Invalid move");
        player --;
        void getch();
    }
}
//program ends
