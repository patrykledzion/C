#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BOARD_SIZE 3

#define O_CHAR 'O'
#define X_CHAR 'X'

#define UP_KEY 'w'
#define LEFT_KEY 'a'
#define DOWN_KEY 's'
#define RIGHT_KEY 'd'
#define ENTER_KEY 13
#define ESCAPE_KEY 'e'

#define ENTER_KEY_STR "ENTER"



struct Game {
	int turn;
	char* board;
	int pos;
	int playing;
}; typedef struct Game Game;

void draw(Game *game)
{
	/*
	   Board

	 0 | 1 | 2 
	---+---+---
	 3 | 4 |(5)
	---+---+---
	 6 | 7 | 8

	*/
	if (game == NULL || game->board==NULL)return;

	system("cls");
	printf("KEY BINDS: \n");
	printf(" - UP:	  %c\n", UP_KEY);
	printf(" - DOWN:  %c\n", DOWN_KEY);
	printf(" - LEFT:  %c\n", LEFT_KEY);
	printf(" - RIGHT: %c\n", RIGHT_KEY);
	printf(" - PLACE: %s\n", ENTER_KEY_STR);
	printf(" - ESCAPE:%c\n\n", ESCAPE_KEY);
	char t[2] = { O_CHAR , X_CHAR };
	printf("TURN: %c\n", t[game->turn]);
	//DRAWING
	for (int i = 0; i < BOARD_SIZE;i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			char c = game->board[i* BOARD_SIZE + j];
			if (game->pos == i * BOARD_SIZE + j)
			{
				if (j < BOARD_SIZE - 1)
					printf("(%c)|", c);
				else
					printf("(%c)", c);
			}
			else {
				if (j < BOARD_SIZE - 1)
					printf(" %c |", c);
				else
					printf(" %c ", c);
			}
			
		}
		if (i < BOARD_SIZE -1)
			printf("\n---+---+---\n");
	}

	printf("\n\n");

}

void make_move(Game *game)
{
	if (game == NULL || game->board == NULL)return;

	char key = _getch();
	char c;
	switch (game->turn)
	{
	case 0:
		c = O_CHAR;
		break;
	default:
		c = X_CHAR;
		break;
	}

	switch (key)
	{
	case UP_KEY:
		game->pos -= BOARD_SIZE;
		break;
	case LEFT_KEY:
		game->pos -= 1;
		break;
	case DOWN_KEY:
		game->pos += BOARD_SIZE;
		break;
	case RIGHT_KEY:
		game->pos += 1;
		break;
	case ESCAPE_KEY:
		game->playing = 0;
		break;
	case (int)ENTER_KEY:
		if (game->board[game->pos] != ' ')return;
		game->board[game->pos] = c;
		game->turn++;
		if (game->turn > 1)game->turn = 0;

		break;
	default: return;
	}

	if (game->pos < 0)game->pos = 9 + game->pos;
	if (game->pos > 8)game->pos = game->pos - 9;

	
}

int check_winner(Game* game)	//0 - no winner, 1 - O, 2 - X
{
	if (game == NULL || game->board == NULL)return -1;
	int is_winner = 0;

	int is_full = 3;
	//CHECK IF BOARD IS FULL
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		if (game->board[i] == ' ')is_full = 0;
	}
 
	//HORIZONTALLY WIN
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (game->board[i * BOARD_SIZE + 0] == game->board[i * BOARD_SIZE + 1] &&
			game->board[i * BOARD_SIZE + 1] == game->board[i * BOARD_SIZE + 2] &&
			game->board[i * BOARD_SIZE + 0]!=' ')is_winner = 1;
	}

	//VERTICALLY WIN
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (game->board[i + BOARD_SIZE * 0] == game->board[i + BOARD_SIZE * 1] && 
			game->board[i + BOARD_SIZE * 1] == game->board[i + BOARD_SIZE * 2] && 
			game->board[i + BOARD_SIZE * 0] != ' ')is_winner = 1;
	}

	//CROSS WIN
	if (game->board[0] == game->board[4] && game->board[4] == game->board[8] && game->board[0] != ' ')is_winner = 1;
	if (game->board[2] == game->board[4] && game->board[4] == game->board[6] && game->board[2] != ' ')is_winner = 1;

	//0 - NO ONE, 1 - X, 2 - O, 3 - DRAW
	return is_winner * (game->turn + 1) + is_full * !is_winner;
}

int main()
{

	Game* game = malloc(sizeof(Game));
	if (game == NULL)return -1;

	game->board = malloc(sizeof(char) * BOARD_SIZE * BOARD_SIZE);
	if (game->board == NULL)
	{
		free(game);
		return -1;
	}

	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		game->board[i] = ' ';
	}

	game->turn = 0;
	game->pos = 0;
	game->playing = 1;

	
	while (game->playing)
	{
		draw(game);
		make_move(game);
		int winner = check_winner(game);
		if (winner > 0)
		{
			draw(game);
			char winners[3] = { X_CHAR, O_CHAR};
			if(winner!=3)
				printf("WINNER: %c\n\n", winners[winner-1]);
			else
				printf("IT'S A DRAW\n\n");

			game->playing = 0;
		}
	}

	free(game->board);
	free(game);
	
	return 0;
}