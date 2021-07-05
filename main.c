/***********************************************************
* Author: Austin Friedrich, Benjamin Cha, Jawad Alamgir , Tae, Soo KiM
* Email: alamgirj@oregonstate.edu, jalamgir.62@gmail.com
* Date Created:8/5/2020
* Filename: main.c
*
* Overview:
*	driver page for out text adventure game
*	game will take in 2 parameters a size and a debug status
*	The game will use a dynamic array for movement and a linked list
*	for each new encounter
************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include<time.h>
#include "functions.h"


/*********************************************************************
** Function:main
** Description:main
** Parameters: none
** Pre-Conditions:
** Post-Conditions:game done
*********************************************************************/


int main() {
	// Allows for restart of game and choice of mapsize
	srand(time(0));
	display_title();
	int gameloop = 1;

	while (gameloop == 1) {
		//game_loop
		int play_again = 1;
		//debugmode
		int debug_mode = 2;
		//size of map
		int game_size;
		//player lifes
		int player_life = 5;
		//Number of encounters
		int number_of_encounters = 10;

		//COMMENT ME OUT FOR FINAL GAME*********
		printf("debug mode (1) on (2) off?\n");
		debug_mode = player_choice(1,2);
		printf("Debug mode status %d \n", debug_mode);
		//COMMENT ME OUT FOR FINAL GAME*********

		//get size of array
		printf("Enter Size of dungeon 4-30\n");
		game_size = player_choice(4,30); // allows choice 1-40
		printf("Size of dungeon %d \n", game_size);

		//generate randome starting postion in dungeon (range between 0 and gamesize)
		int x_cord = rand() % game_size;
		int	y_cord = rand() % game_size;


		printf("Enter number of lives (5 is default 99 max)\n");
		player_life = player_choice(5,99); // allows for choice 1-100
		printf("Number of lives %d \n", player_life);

		// Create game board
		encounter** game = create_dungeon(game_size, number_of_encounters);
		Node* head = create_events();


		//set starting postion, declare starting position safe.
		set_player_position(game, x_cord, y_cord, game_size);
		game[x_cord][y_cord].hasVisted = 1;
		clear_screen();


		int temp_damage;

		int x_win = 0;
		int y_win = 0;

		do {
			x_win = rand() % game_size;
			y_win = rand() % game_size;

		} while ((x_win == x_cord) && (y_win == y_cord));

		while (play_again == 1) {

			display_title();
			printf("Number of lives %d \n", player_life);

			print_game(game, game_size, debug_mode);
			printf("%d, %d \n", x_win, y_win);
			player_move(game, game_size, &x_cord, &y_cord);

			//IF player has not visted current location then play event.
			if (chk_has_visited(game, x_cord, y_cord) != 1) {
				temp_damage = player_event(game, game_size, *head);
				player_life = update_life(player_life, temp_damage);
			}

			if (player_life <= 0) {
				printf("Not enough lives. Player died...");
				break;
			}

			if (game[x_win][y_win].playerHere == 1) {
				printf("Reached the room. Won the game!\n");
				break;
			}

			sleep(3);
			clear_screen();


		}

		int restart = 0;
		free_game(game, game_size,head);
		printf("restart? (1) yes (2) no\n");
		scanf("%d", &restart);
		if (restart == 1)
			continue;
		else
			return 0;

		//add function to make restart possible

	}
}
