/***********************************************************
* Author: Austin Friedrich, Benjamin Cha, Jawad Alamgir , Tae Soo KiM
* Email: alamgirj@oregonstate.edu, jalamgir.62@gmail.com
* Date Created:8/5/2020
* Filename: maze.c
*
* Overview:
*   function library for game
*   function name and discription will be posted below
************************************************************/
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>/* time() */
#include "functions.h"

#define MAX_CHAR 500

// Struct refrence
//struct encounter
//{
//    int enc;
//    int hasVisted;
//    int playerHere;
//};
//
//struct Node
//{
//    // Any data type can be stored in this node
//    char encounter_text;
//    char keywords;
//    int encounter_num;
//    struct Node* next;
//};


/******************************************************
** ClearScreen
** clears screen
******************************************************/
void clear_screen() {
    int n;
    for (n = 0; n < 10; n++)
        printf("\n\n\n\n\n\n\n\n");
}


//The function needs to change once the linked list is created
// we need to assign the "enc" a random number from our linked list events table
// from there each room will have a number associated with a event in a linked list tree
// then we can run each event as we get to it.
/*********************************************************************
 ** Function:         create_dungeon
 ** Description:      Created dungeon and sets the events of each tile
 ** Parameters:       takes in an int and creates dungeon of X size, then then number of encounters
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/


encounter** create_dungeon(int x, int number_of_encounters) {
    srand(time(0));

    encounter** arr = (encounter**)malloc(sizeof(encounter*) * x);
    for (int i = 0; i < x; i++)
    {
        arr[i] = (encounter*)malloc(sizeof(encounter) * x);
    }


    int i, j, count = 0;
    for (i = 0; i < x; i++) {

        for (j = 0; j < x; j++) {
            count = count + 1;

            // printf("%d \n ", count);

            arr[i][j].enc = rand() % number_of_encounters + 1;
            arr[i][j].hasVisted = 0;
            arr[i][j].playerHere = 0;
        }
    }
    return arr;
}

/*********************************************************************
 ** Function:         player_choice
 ** Description:      takes an int and makes any input between 1 and X valid, and all other inputs invalid
 ** Parameters:       takes in an int of X size
 ** Pre-Con:          NONE
 ** Post-Con:         returns the number used by user that is valid
 *********************************************************************/

int player_choice(int z, int x) {

    char userInput[64];
    int num = 0;
    char temp;
    size_t length = 0;
    int index = 0;
    int flag = 0;
    while (num == 0) {

        length = 0;
        flag = 0;
        num = 0;

        printf("\n\nPlease enter a number %d to %d\n\n", z , x);
        fgets(userInput, 63, stdin);
        length = strlen(userInput);

        if (length < 2 || length > 3) {
            printf("\nInvalid strlen()\n");
            continue;
        }

        length--;

        for (index = 0; index < length; ++index) {
            if (userInput[index] < '0' || userInput[index] > '9')
            {
                flag = 1;
                break;
            }
        }

        if (flag) {
            printf("\nInvalid character\n");
            continue;
        }

        if (sscanf(userInput, "%d", &num) != 1) {
            printf("\nInvalid sscanf()\n");
            continue;
        }

        if (num < z || num > x) {
            printf("\nInvalid range\n");
            num = 0;
            continue;
        }

        //printf("\nNumber OK:%d\n", num);
    }
    return num;
}
/*********************************************************************
 ** Function:         chk_has_visited
 ** Description:      returns 1 if visited
 ** Parameters:       takes dungeon 2d array, x and y
 ** Pre-Con:          NONE
 ** Post-Con:         returns 1 if player has visited this location before.
 *********************************************************************/
int chk_has_visited(encounter** arr, int x, int y) {
    if (arr[x][y].hasVisted == 1) {
        return 1;
    }
}
/*********************************************************************
 ** Function:         chk_enc_number
 ** Description:      Returns encounter number
 ** Parameters:       takes dungeon 2d array, x and y
 ** Pre-Con:          NONE
 ** Post-Con:         returns encounter number of grid location
 *********************************************************************/
int chk_enc_number(encounter** arr, int x, int y) {
    return arr[x][y].enc;
}

/*********************************************************************
 ** Function:         print_game
 ** Description:      prints the dungeon, if debug mode is on then it also shows all events by number
 **                   and if that player has been there before
 ** Parameters:       takes dungeon 2d array, size of dungeon, and debug_mode
 ** Pre-Con:          NONE
 ** Post-Con:         returns the number used by user that is valid
 *********************************************************************/

 // takes game board, size and debug mode and diplays the dungeon accordingly
void print_game(encounter** arr, int size, int debug_mode) {
    int i, j, count = 0;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            count = count + 1;
            if (debug_mode == 1) {
                if (arr[i][j].playerHere == 1) {
                    printf("| *--%d |", arr[i][j].hasVisted);
                }
                else {
                    printf("| %d--%d |", arr[i][j].enc, arr[i][j].hasVisted);
                }
            }
            else if (debug_mode == 2) {
                if (arr[i][j].playerHere == 1) {
                    printf("| * |");
                }
                else {
                    printf("|   |");
                }
            }

            if (count == size) {
                printf("\n");
                count = 0;
            }


        }
    }
}

//displayes title.
/*********************************************************************
 ** Function:         display_title
 ** Description:      display_title
 ** Parameters:       NONE
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/

void display_title() {
    printf("----------------------------------------------------------------\n");
    printf("\n");
    printf("d8888b. db    db d8b   db  d888b  d88888b  .d88b.  d8b   db \n");
    printf("88  `8D 88    88 888o  88 88' Y8b 88'     .8P  Y8. 888o  88 \n");
    printf("88   88 88    88 88V8o 88 88      88ooooo 88    88 88V8o 88 \n");
    printf("88   88 88    88 88 V8o88 88  ooo 88~~~~~ 88    88 88 V8o88\n");
    printf("88  .8D 88b  d88 88  V888 88. ~8~ 88.     `8b  d8' 88  V888 \n");
    printf("Y8888D' ~Y8888P' VP   V8P  Y888P  Y88888P  `Y88P'  VP   V8P \n");
    printf("\n");
    printf("\n");
    printf("db   d8b   db  .d8b.  .88b  d88. d8888b. db    db .d8888. \n");
    printf("88   I8I   88 d8' `8b 88'YbdP`88 88  `8D 88    88 88'  YP \n");
    printf("88   I8I   88 88ooo88 88  88  88 88oodD' 88    88 `8bo.   \n");
    printf("Y8   I8I   88 88~~~88 88  88  88 88~~~   88    88   `Y8b. \n");
    printf("`8b d8'8b d8' 88   88 88  88  88 88      88b  d88 db   8D \n");
    printf(" `8b8' `8d8'  YP   YP YP  YP  YP 88      ~Y8888P' `8888Y'\n");
    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("Created by: Austin Friedrich, Benjamin Cha, Jawad Alamgir , Tae Soo Kim\n");
    printf("----------------------------------------------------------------\n");
    printf("\n");
}


//frees array
/*********************************************************************
 ** Function:         free_game
 ** Description:      frees game
 ** Parameters:       NONE
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/

void free_game(encounter** arr, int size, Node* head) {
    for (int i = 0; i < size; i++)
    {
        free(arr[i]);
    }
    free(arr);

    Node* temp = (struct Node*)malloc(sizeof(struct Node));
    Node* next = (struct Node*)malloc(sizeof(struct Node));
    temp = head;
    next = temp->next;
    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }

}


/*********************************************************************
 ** Function:         set_player_position
 ** Description:      Scans map for players last position and updates that with a have visited node
 **                   then updates player location
 ** Parameters:       game arr, x and y cord, and size of arr
 ** Pre-Con:          player at old location
 ** Post-Con:         player at new location with updated node
 *********************************************************************/

void set_player_position(encounter** arr, int x_cord, int y_cord, int size) {

    int i, j = 0;

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (arr[i][j].playerHere == 1) {
                arr[i][j].hasVisted = 1;
            }

        }
    }
    arr[x_cord][y_cord].playerHere = 1;
}

//scans dungeon gets current location and determines in what directions the player can move.

/*********************************************************************
 ** Function:         player_move
 ** Description:      Scans map for players last position and saves it so that we can check if new movement is within
 **                   the bounds of the array, then checks players input and updates location finaly the old location is removed
 ** Parameters:       game arr, size of arr
 ** Pre-Con:          player at old location
 ** Post-Con:         player at new location with updated node
 *********************************************************************/
void player_move(encounter** arr, int size, int* x_pointer, int* y_pointer) {
    int player_x;
    int player_y;
    int i, j = 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (arr[i][j].playerHere == 1) {
                player_x = i;
                player_y = j;
            }

        }
    }
    int choice_loop = 0;
    while (choice_loop == 0) {
        printf("\n(1 -- Up) (2 -- Down) (3 -- Left) (4 -- Right)\n");
        int choice = player_choice(1,4);

        // UP
        if (choice == 1) {
            if (player_x == 0) {
                printf("A gritty wall blocks my path");
            }
            else if (player_x != 0) {
                set_player_position(arr, player_x - 1, player_y, size);
                choice_loop = 1;
                *x_pointer = player_x - 1;
                *y_pointer = player_y;
            }
        }
        // down
        else if (choice == 2) {
            if (player_x == size - 1) {
                printf("A slimy wall blocks my path");
            }
            else if (player_x != size - 1) {
                set_player_position(arr, player_x + 1, player_y, size);
                choice_loop = 1;
                *x_pointer = player_x + 1;
                *y_pointer = player_y;
            }
        }
        // left
        else if (choice == 3) {
            if (player_y == 0) {
                printf("A crumbling wall blocks my path");
            }
            else if (player_y != 0) {
                set_player_position(arr, player_x, player_y - 1, size);
                choice_loop = 1;
                *x_pointer = player_x;
                *y_pointer = player_y - 1;
            }
        }
        // right
        else if (choice == 4) {
            if (player_y == size - 1) {
                printf("A moss covered wall blocks my path");
            }
            else if (player_y != size - 1) {
                set_player_position(arr, player_x, player_y + 1, size);
                choice_loop = 1;
                *x_pointer = player_x;
                *y_pointer = player_y + 1;
            }
        }
        arr[player_x][player_y].playerHere = 0;

    }




}

// EVENTS TREEES
// MAKE TREES HERE!

/*********************************************************************
 ** Function:         event_1
 ** Description:      Has all the data for the first encounter
 ** Parameters:       NONE
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/

// Even 1 example event
Node* event_1() {
    //temp node to be passed
    Node* temp = (struct Node*)malloc(sizeof(struct Node));

    //this is event 1 change this number when you create your own events ( so event 2 would have 2 as encounter num)
    temp->encounter_num = 1;

    //Encounter splash text
    temp->encounter_text = "You enter a dark damp room, in the corner you notice a goblin";

    // Words you can choose from

    temp->next = NULL;

    char* keword_temp[10] = { "Fight","Sneak" };

    for (int i = 0; i < 10; i++) {
        temp->keywords[i] = keword_temp[i];
    }

    //words that complete even
    char* correct_keword_temp[10] = { "Fight", "Sneak" };

    for (int i = 0; i < 10; i++) {
        temp->correct_keywords[i] = correct_keword_temp[i];
    }

    return temp;
}

/*********************************************************************
 ** Function:         event_2
 ** Description:      Has all the data for the second encounter
 ** Parameters:       NONE
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/
Node* event_2() {
    //temp node to be passed
    Node* temp = (struct Node*)malloc(sizeof(struct Node));

    //this is event 1 change this number when you create your own events ( so event 2 would have 2 as encounter num)
    temp->encounter_num = 2;

    //Encounter splash text
    temp->encounter_text = "You enter a well lit room with a table and chair at the centre. The table has a bottle on it";

    // Words you can choose from
    char* keword_temp[10] = { "Drink","Move on" };

    for (int i = 0; i < 10; i++) {
        temp->keywords[i] = keword_temp[i];
    }

    //words that complete even
    char* correct_keword_temp[10] = { "Drink","Move on" };

    for (int i = 0; i < 10; i++) {
        temp->correct_keywords[i] = correct_keword_temp[i];
    }

    temp->next = NULL;

    return temp;
}

/*********************************************************************
 ** Function:         event_3
 ** Description:      Has all the data for the third encounter
 ** Parameters:       NONE
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/
Node* event_3() {
    //temp node to be passed
    Node* temp = (struct Node*)malloc(sizeof(struct Node));

    //this is event 1 change this number when you create your own events ( so event 2 would have 2 as encounter num)
    temp->encounter_num = 3;

    //Encounter splash text
    temp->encounter_text = "You enter a cemented room scattered with slimy patterns and notice three slimes next to a corpse";

    // Words you can choose from
    char* keword_temp[10] = { "Fight", "Sneak" };

    for (int i = 0; i < 10; i++) {
        temp->keywords[i] = keword_temp[i];
    }
    //words that complete even
    char* correct_keword_temp[10] = { "Fight","Sneak" };

    for (int i = 0; i < 10; i++) {
        temp->correct_keywords[i] = correct_keword_temp[i];
    }
    temp->next = NULL;
    return temp;
}

/*********************************************************************
 ** Function:         event_4
 ** Description:      Has all the data for the fourth encounter
 ** Parameters:       NONE
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/
Node* event_4() {
    //temp node to be passed
    Node* temp = (struct Node*)malloc(sizeof(struct Node));

    //this is event 1 change this number when you create your own events ( so event 2 would have 2 as encounter num)
    temp->encounter_num = 4;

    //Encounter splash text
    temp->encounter_text = "As you get closer to the room your hear the sound of running water and soon spot an enormous fountain with water falling from a statue that is half gargoyle and half angel. A sign engraved on the side says 'lady luck is fickle'";

    // Words you can choose from
    char* keword_temp[10] = { "Drink", "Ignore", };
    for (int i = 0; i < 10; i++) {
        temp->keywords[i] = keword_temp[i];
    }

    //words that complete even
    char* correct_keword_temp[10] = { "Drink", "Ignore" };
    for (int i = 0; i < 10; i++) {
        temp->correct_keywords[i] = correct_keword_temp[i];
    }
    temp->next = NULL;
    return temp;
}

/*********************************************************************
 ** Function:         event_5
 ** Description:      Has all the data for the fifth encounter
 ** Parameters:       NONE
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/
Node* event_5() {
    //temp node to be passed
    Node* temp = (struct Node*)malloc(sizeof(struct Node));

    //this is event 1 change this number when you create your own events ( so event 2 would have 2 as encounter num)
    temp->encounter_num = 5;

    //Encounter splash text
    temp->encounter_text = "You encounter a well dressed goblin standing next to a wheel with different symbols on it. As you approach he smiles at you saying 'Let's spin the wheel' as he pushes it down with his full force";

    // Words you can choose from
    char* keword_temp[10] = { "Wait", "Run", "Fight" };
    for (int i = 0; i < 10; i++) {
        temp->keywords[i] = keword_temp[i];
    }

    //words that complete even
    char* correct_keword_temp[10] = { "Wait", "Run", "Fight" };
    for (int i = 0; i < 10; i++) {
        temp->correct_keywords[i] = correct_keword_temp[i];
    }
    temp->next = NULL;
    return temp;
}

/*********************************************************************
 ** Function:         event_6
 ** Description:      Has all the data for the sixth encounter
 ** Parameters:       NONE
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/
Node* event_6() {
    //temp node to be passed
    Node* temp = (struct Node*)malloc(sizeof(struct Node));

    //this is event 1 change this number when you create your own events ( so event 2 would have 2 as encounter num)
    temp->encounter_num = 6;

    //Encounter splash text
    temp->encounter_text = "You encounter a group of what seem to be adventurers sitting around a fire drinking and eating as they have a jolly time. One of them notices you waving to you. As you approach closer he smiles at you asking if you would like to join them";

    // Words you can choose from
    char* keword_temp[10] = { "Accept", "Refuse" };
    for (int i = 0; i < 10; i++) {
        temp->keywords[i] = keword_temp[i];
    }

    //words that complete even
    char* correct_keword_temp[10] = { "Accept", "Refuse" };
    for (int i = 0; i < 10; i++) {
        temp->correct_keywords[i] = correct_keword_temp[i];
    }
    temp->next = NULL;
    return temp;
}

/*********************************************************************
 ** Function:         event_7
 ** Description:      Has all the data for the seventh encounter
 ** Parameters:       NONE
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/
Node* event_7() {
    //temp node to be passed
    Node* temp = (struct Node*)malloc(sizeof(struct Node));

    //this is event 1 change this number when you create your own events ( so event 2 would have 2 as encounter num)
    temp->encounter_num = 7;

    //Encounter splash text
    temp->encounter_text = "You enter a small room and notice two figures standing across from each other as one of them shouts to you 'witness our duel stranger' as they both start striking at each other exchanging blows";

    // Words you can choose from
    char* keword_temp[10] = { "Watch","Ignore" };
    for (int i = 0; i < 10; i++) {
        temp->keywords[i] = keword_temp[i];
    }

    //words that complete even
    char* correct_keword_temp[10] = { "Watch", "Ignore" };
    for (int i = 0; i < 10; i++) {
        temp->correct_keywords[i] = correct_keword_temp[i];
    }
    temp->next = NULL;
    return temp;
}

/*********************************************************************
 ** Function:         event_8
 ** Description:      Has all the data for the eighth encounter
 ** Parameters:       NONE
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/
Node* event_8() {
    //temp node to be passed
    Node* temp = (struct Node*)malloc(sizeof(struct Node));

    //this is event 1 change this number when you create your own events ( so event 2 would have 2 as encounter num)
    temp->encounter_num = 8;

    //Encounter splash text
    temp->encounter_text = "You enter a barren room the only defining feature a split in the ground that seems too deep to see the bottom of. What will you do?";

    // Words you can choose from
    char* keword_temp[10] = { "Jump Over" };
    for (int i = 0; i < 10; i++) {
        temp->keywords[i] = keword_temp[i];
    }

    //words that complete even
    char* correct_keword_temp[10] = { "Jump Over" };
    for (int i = 0; i < 10; i++) {
        temp->correct_keywords[i] = correct_keword_temp[i];
    }
    temp->next = NULL;
    return temp;
}

/*********************************************************************
 ** Function:         event_9
 ** Description:      Has all the data for the ninth encounter
 ** Parameters:       NONE
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/
Node* event_9() {
    //temp node to be passed
    Node* temp = (struct Node*)malloc(sizeof(struct Node));

    //this is event 1 change this number when you create your own events ( so event 2 would have 2 as encounter num)
    temp->encounter_num = 9;

    //Encounter splash text
    temp->encounter_text = "As you enter the room you notice it being quite steep and as soon as you notice a large boulder drops down rolling towards you";

    // Words you can choose from
    char* keword_temp[10] = { "Strike","Run","Dodge" };
    for (int i = 0; i < 10; i++) {
        temp->keywords[i] = keword_temp[i];
    }

    //words that complete even
    char* correct_keword_temp[10] = { "Strike","Run","Dodge" };
    for (int i = 0; i < 10; i++) {
        temp->correct_keywords[i] = correct_keword_temp[i];
    }
    temp->next = NULL;
    return temp;
}

/*********************************************************************
 ** Function:         event_10
 ** Description:      Has all the data for the tenth encounter
 ** Parameters:       NONE
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/
Node* event_10() {
    //temp node to be passed
    Node* temp = (struct Node*)malloc(sizeof(struct Node));

    //this is event 1 change this number when you create your own events ( so event 2 would have 2 as encounter num)
    temp->encounter_num = 10;

    //Encounter splash text
    temp->encounter_text = "As you enter the room you notice the floor looks odd. As you walk further inside suddenly the floor gives way into a humoungous room with a minoutar, a troll and a cyclops blocking the paths ahead. The only way forward is to fight";

    // Words you can choose from
    char* keword_temp[10] = { "Minoutar","Troll","Cyclops" };
    for (int i = 0; i < 10; i++) {
        temp->keywords[i] = keword_temp[i];
    }

    //words that complete even
    char* correct_keword_temp[10] = { "Minoutar","Troll","Cyclops" };
    for (int i = 0; i < 10; i++) {
        temp->correct_keywords[i] = correct_keword_temp[i];
    }
    temp->next = NULL;
    return temp;
}

int return_int(int num) {
    return num;
}


/*********************************************************************
 ** Function:         display_choice
 ** Description:      Displays the valid options for the player for each
                      encounter and takes input.
 ** Parameters:       Node*
 ** Pre-Con:          called by call_event
 ** Post-Con:         returns the number of the option chosen by the player
 *********************************************************************/
int display_choices(Node* temp_node) {
    // char* user_choice[20];

    printf("%s\n", temp_node->encounter_text);
    printf("What will you do? \n");
    int i = 0;

    //gives seg fault
    // printf("%s\n", temp_node->keywords[1]);
    if (temp_node->encounter_num == 5 || temp_node->encounter_num == 9 || temp_node->encounter_num == 10) {
        for (int i = 0; i < 3; i++) {
            printf("%s\n", temp_node->keywords[i]);
        }
    }
    else if (temp_node->encounter_num == 8) {
        printf("%s\n", temp_node->keywords[0]);
    }
    else {
        for (int i = 0; i < 2; i++) {
            printf("%s\n", temp_node->keywords[i]);
        }
    }

    int flag;
    do {
        printf("your choice: ");
        char buff[256];
        fgets(buff, 255, stdin);

        char* usertemp;
        usertemp = strtok(buff, "\n");

        if (temp_node->encounter_num == 5 || temp_node->encounter_num == 9 || temp_node->encounter_num == 10) {
            for (int i = 0; i < 3; i++) {
                char* tempbuff2 = temp_node->keywords[i];
                if (strcmp(strtok(buff, "\n"), temp_node->keywords[i]) != 0) {
                    printf("Please choose one of the specified options.\n");
                    flag = 1;
                }
                else {
                    return i;
                    break;
                }
            }
        }
        else if (temp_node->encounter_num == 8) {
            char* tempbuff2 = temp_node->keywords[i];
            if (strcmp(strtok(buff, "\n"), temp_node->keywords[0]) != 0) {
                printf("Please choose one of the specified options.\n");
                flag = 1;
            }
            else {
                return i;
                break;
            }
        }
        else {
            for (int i = 0; i < 2; i++) {

                if (strcmp(strtok(buff, "\n"), temp_node->keywords[i]) != 0) {
                    printf("Please choose one of the specified options.\n");
                    flag = 1;
                }
                else {
                    printf("\n");
                    return i;

                }
            }
        }
    } while (flag == 1);

}

/*********************************************************************
 ** Function:         update_life
 ** Description:      Updates player health according to encounter
 ** Parameters:       int player_life, int amount
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/
int update_life(int player_life, int amount) {
    return player_life + amount;
}

int player_event(encounter** arr, int size, Node head) {
    int player_x = 0;
    int player_y = 0;
    int i, j = 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (arr[i][j].playerHere == 1) {
                player_x = i;
                player_y = j;
            }

        }
    }

    int hasVisted = arr[player_x][player_y].hasVisted;
    int event_num = arr[player_x][player_y].enc;

    Node* event = (struct Node*)malloc(sizeof(struct Node));

    event = &head;

    for (int i = 1; i < event_num; i++) {
        event = event->next;
    }//searches the event through the list

    call_event(event);



}

/*********************************************************************
 ** Function:         call_event
 ** Description:      Calls the encounters stored in event functions
 ** Parameters:       Node* event
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/
int call_event(Node* event) {
    int tempint = 0;
    int temp = event->encounter_num;


    srand(time(NULL));
    switch (temp) {
    case 1:


        tempint = display_choices(event);

        if (strcmp(event->keywords[0], event->keywords[tempint]) == 0) {
            printf("You begin fighting the goblin striking him with your fists as you start getting complacent against the weaker goblin he manages to land a hit on you. You angrily kick the goblin knocking him out. (1 damage)\n");
            return -1;
        }
        else {
            int x = rand() % 2;
            if (x == 0) {
                printf("as you attempt to sneak past the goblin he notices you going past and manages to land a surprise attack on you. You flinch and kick the goblin away getting ready to fight(2 damage)\n");
                printf("You begin fighting the goblin striking him with your fists as you start getting complacent against the weaker goblin he manages to land a hit on you. You angrily kick the goblin knocking him out. (1 damage)\n");
                return -3;
            }
            else {
                printf("You crouch low moving from one shadow of the room to another while keeping an eye on the goblin. Soon you slip past the goblin heading to the next room the goblin none the wiser\n");
                return 0;
            }
        }
    case 2:

        tempint = display_choices(event);
        if (strcmp(event->keywords[0], event->keywords[tempint]) == 0) {
            printf("You walk up to the table looking closely at the large vial on it. You hear it bubling as you notice it fizz adn change color, your curiosity gets the better of you as you grab the vial tkaing off it's cap and down it in one go \n");
            int x = rand() % 2;
            if (x == 0) {
                printf("As the liquid fills your stomach you are surprised by how great it tastes and moments later feel yourself brimming with energy. Feeling invigorated you continue onwards. (6 healing)\n");
                return 6;
            }
            else {
                printf("As the liquid passes through your mouth you taste nothing. You cautiously drink all of it feeling no change. You decide to leave the room but as soon as you take a step you fall to your knees retching and puking violently your head starting to throb and hurt as you satrt feeling dizzy. (6 damage)\n");
                return -6;
            }
        }
        else {
            printf("OPTION 2 for case 2\n");
        }
    case 3:

        tempint = display_choices(event);
        if (strcmp(event->keywords[0], event->keywords[tempint]) == 0) {
            printf("You pull out the small dagger you keep in your back pocket and cautiously approach the slimes. As you get closer the slimes don't react, taking advantage of the situation you plunge your dagger into the slime causing it to splatter everywhere. The slime burns your skin searing your skin as your realize the slime is just some toxic substance. Not everything is a monster. (2 damage)\n");
            return -2;
        }
        else {
            printf("You carefully walk across the room making no noise as your eyes are focused on the slimes in the corner. Your caution pays off and you get through the room uneventfully\n");
            return 0;
        }

    case 4:

        tempint = display_choices(event);
        if (strcmp(event->keywords[0], event->keywords[tempint]) == 0) {
            int x = rand() % 2;
            if (x == 0) {
                printf("You lean down collecting water from the fountain in your hand and slowly bring your hands to your mouth drinking unsure to what it will lead to. Despite your fears you suddenly start feeling rejuvinated and fresh, so energized you could take on an army. (100 healing)\n");
                return 100;
            }
            else {
                printf("You lean down collecting water from the fountain in your hand and slowly bring your hands to your mouth drinking unsure to what it will lead to. Moments after the water trickles down your throat you begin finding it hard to breathe as your throat restricts and you fall to your side. As you lay there suffocating you notice the gargoyle statu looking down at you confident the grin on it wasn't there before. (100 damage)\n");
                return -100;
            }

        }
        else {
            printf("You look at the fountain and laugh to yourself thinking it would take a realy idiot to attempt drinking from a fountain which definetely looked like it was hiding something sinister. Not wanting to wait and find out what that something was you press on\n");
            return 0;
        }
    case 5:

        tempint = display_choices(event);
        int y = rand() % 2;
        if (strcmp(event->keywords[0], event->keywords[tempint]) == 0) {
            printf("You look at the goblin for a few moments impressed by his sense of fashion before you realize the clear possibilty of danger from him and decide to lunge at him before he can do anything. He simply steps to the side and you feel a sharp pain on your back. You turn to look at him but the goblin as well as the wheel are nowhere to be seen\n");
        }
        else if (strcmp(event->keywords[1], event->keywords[tempint]) == 0) {
            printf("Not wanting to wait and see what the wheel or that goblin have in store for you you run towards the exit of the room. Running you can hear the sound of the whell spinning behind you, almost at the exit of the room you turn to look back but end up tripping. when you look at where you came from neither the goblin or his wheel are anywhere to be found\n. (2 damage)");
            return -2;
        }
        else {
            printf("You decide to humor the goblin and wait for the wheel to stop the goblin smiling at you 'Thank you for the wait' he says in sync with the wheel stopping");
            if (y == 0) {
                printf("You notice the wheel has stopped at what looks to be a heart. The goblin conragulates you on your victory as smoke envelops you making you feel rejuvinated. By the time the smoke is gone so is the goblin the wheel there assuring you that you aren't going insane.(15 healing)\n");
                return 15;
            }
            else if (y == 1) {
                printf("You notice the wheel has stopped at what looks to be a knife. The goblin takes off his hat bowing to you 'so sorry for your loss' he says as you suddenly fall to your knees feeling a stabbing pain in your chest. By the time the pain subsides and you can look up the goblin is gone only the remaining giving you soome assurance that you aren't going insane.(15 damage)\n");
                return -15;
            }
        }
    case 6:

        tempint = display_choices(event);
        if (strcmp(event->keywords[0], event->keywords[tempint]) == 0) {
            printf("You take a seat beside him as he offers you a mug filled with beer and gestures to the pot offering you food. You thank him enjoying the beer and food soon you find yourself getting tired and pass out. You wake up slightly hungover but in a better. (10 healing)\n");
            return 10;
        }
        else {
            printf("That's a shame he says as another person shouts at you 'you too good to be drinking with us' clearly not sober. You try to move on before the situtaion escalates and he blocks your path landing a sucker punch on you knocking you to the ground. The last thing you remeber before passing out is his kick coming towards your face. You wake up your face bruised and your body sore. (10 damage)\n");
            return -10;
        }
    case 7:

        tempint = display_choices(event);
        if (strcmp(event->keywords[0], event->keywords[tempint]) == 0) {
            printf("you think about it and then decide to watch their duel. Their swords clash violently the sound of metal hitting metal filling the room soon one of them makes a mistake only to find themselves impaled on the others blade. The victor first gives a bow to his fallen opponet before tossig you a potion saying 'for your trouble' and continuing on his way. (6 healing)\n");
            return 6;
        }
        else {
            printf(" you almost burst out laughing hearing hs request but manage to compose yourself. You consider his request for a moment before decidng you don'tt have the time to bother with this. you start heading for the next room and suddenly teh sound of blades clashing finishes. You look behind to see an empty room the sight sends chills done your spine as you hurry on ahead.\n");
            return 0;
        }
    case 8:

        tempint = display_choices(event);
        if (strcmp(event->keywords[0], event->keywords[tempint]) == 0) {
            printf("seeing no way ahead without crossing the gap you stand on the edge building up the courage to jump across what looks like a bottomless pit. You step back running towards the split jumping at the last moment. You manage to jump the gap easily landing clean on the other side.");
            return 0;
        }
    case 9:

        tempint = display_choices(event);
        if (strcmp(event->keywords[0], event->keywords[tempint]) == 0) {
            printf("without much time to think you decide to strike the boulder with all your might. The boulder breaks as you strike it but leaves your arm feeling number and sore while your hand bleeds (16 damage)");
            return -16;
        }
        else if (strcmp(event->keywords[1], event->keywords[tempint]) == 0) {
            int o = rand() % 2;
            printf("Without thinking you start running away from the boulder. ");
            if (o == 0) {
                printf("The boulder right behind you, you sprint as fast as you can and just barely make it past the opening too small for the boulder to roll through\n");
                return 0;
            }
            else {
                printf("The boulder right behind you, you sprint as fast as you can the end of the corridor only a few meters from you as the boulder hits your back launching you through the opening. You land on the floor your body hurting from the shock. (13 damage)\n");
                return -13;
            }
        }
        else {
            int h = rand() % 2;
            if (h == 0) {
                printf("You instinctively jump to the side the boulder rolling by you barely missing you asit hits the opening at the end of the corridor breaking. You breather a sigh of relief\n");
            }
            else {
                printf("You instinctively jump to the side the boulder but you're too slow. The boulder hits your legs knocking you to the side as it rolls past you crashing against the opening int the wall and breaking. You get up, your legs wobbly from the shock (6 damage)\n");
                return -6;
            }
        }
    case 10:

        tempint = display_choices(event);
        if (strcmp(event->keywords[0], event->keywords[tempint]) == 0) {
            printf("Scenario for minotaur fight (18 damage)");
            return -18;
        }
        else if (strcmp(event->keywords[1], event->keywords[tempint]) == 0) {
            printf("Scenario for troll fight (18 damage)");
            return -18;
        }
        else {
            printf("Scenario for Wendigo fight (18 damage)");
            return -18;
        }
    }
    return 0;
}


/*********************************************************************
 ** Function:         create_events
 ** Description:      loads the events into a linked list
 ** Parameters:       NONE
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/
Node* create_events() { //stores all the nodes in a form of linked list
    Node* head = (struct Node*)malloc(sizeof(struct Node));
    Node* temp = (struct Node*)malloc(sizeof(struct Node));
    head = event_1();

    push_event(head, event_2());
    push_event(head, event_3());
    push_event(head, event_4());
    push_event(head, event_5());
    push_event(head, event_6());
    push_event(head, event_7());
    push_event(head, event_8());
    push_event(head, event_9());
    push_event(head, event_10());


    return head;

}

/*********************************************************************
 ** Function:         push_event
 ** Description:      Used by create_events to store nodes
 ** Parameters:       Node* prev, Node* new_node
 ** Pre-Con:          NONE
 ** Post-Con:         NONE
 *********************************************************************/
void push_event(Node* prev, Node* new_node) {


    while (prev->next != NULL) {
        prev = prev->next;
    }

    prev->next = new_node;

}
