#include <stdio.h>
#include <stdlib.h>
#include "items.h"
#include "rooms.h"
#include <string.h>
#include <stdbool.h>


struct user{
 struct Item* bag;
 chamber* stage;
 int task;
 int bag_size; 
};
typedef struct user user;



/**
  * @desc initialize the avatar and its component
  * @param Item*bag - pointer to avatar inventory
  * @param chamber*begin - starting room
  * @return avatar pointer
*/
user* initialize(Item*bag, chamber* begin){ //creates the player character
	struct user* mario = (struct user*)malloc(sizeof(struct user)); //allocates memory for the user
	mario->bag = bag; //sets the bag
	mario->stage = begin; //sets the room the user starts at
	mario->task = 0; //sets amount of tasks complete
	mario->bag_size = 1; //sets the bag size
	return mario;
}


/**
  * @desc print out room description for user observation
  * @param chamber*ptr - choosen room
*/
void look(chamber*ptr){ //prints out the description of the room
	display_room(ptr); //prints description
}



/**
  * @desc free the pointer to a room and its components
  * @param chamber*room - choosen room
*/
void free_room(chamber* room){ //frees the room and any items in it
	struct Item* bag = room->item; //player's bag
	struct Item* temp = bag; //temp used for freeing
	while(bag != NULL){ //while bag is not empty
		temp = bag; //temp holds baggie
		bag = bag->next; //baggie is now the next item in list
		free(temp); //frees the temp
	}
	free(room);
}



/**
  * @desc free all the pointer to room and user inventory
  * @param user*ptr - pointer to avatar
  * @param chamber*start - starting room
*/
void freedom(user* ptr, chamber* start){ //frees the space after the game is over
	Item* baggie = ptr->bag; //player's bag
	Item* temp = baggie; //temp used for freeing
	while(baggie != NULL){ //while bag is not empty
		temp = baggie; //temp holds baggie
		baggie = baggie->next; //baggie is now the next item in list
		free(temp); //frees the temp
	}
	free_room(start->east->north->up); //free room 2-4
	free_room(start->east->north->west->up->south->east); //free room 2-3
	free_room(start->east->north->west->up->south); //free room 2-2
	free_room(start->east->north->west->up); //free room 2-1
	free_room(start->east->north->west); //free room 1-4
	free_room(start->east->north); //free room 1-3
	free_room(start->east); //free room 1-2
	free_room(start);//free room 1-1
}



/**
  * @desc determine if a direction is valid and the room is accessible
  * @param char* direction- the direction user input
  * @param user*ptr - the avatar of the game
  * @return accessible and move the avatar or unaccessible
*/
bool can_access(char*direction, user*ptr){ //checks if the direction is blocked or not and moves to that room
	if(strcmp("NORTH", direction)==0 && ptr->stage->north !=NULL && ptr->stage->north->isBlocked == false){//checks if north room is blocked
  		ptr->stage = ptr->stage->north; //moves north
  		printf("You moved NORTH\n\n"); 
  		return true; 
   	}
  	else if(strcmp("SOUTH", direction)==0 && ptr->stage->south !=NULL && ptr->stage->south->isBlocked == false){//checks if south room is blocked
  		ptr->stage = ptr->stage->south; //moves south
  		printf("You moved SOUTH\n\n");
  		return true; 
  	}
  	else if(strcmp("EAST", direction)==0 && ptr->stage->east !=NULL && ptr->stage->east->isBlocked == false){//checks if east room is blocked
  		ptr->stage = ptr->stage->east; //moves east
  		printf("You moved EAST\n\n");
  		return true;
  	}
  	else if(strcmp("WEST", direction)==0 && ptr->stage->west !=NULL && ptr->stage->west->isBlocked == false){//checks if west room is blocked
  		ptr->stage = ptr->stage->west;//moves west
  		printf("You moved WEST\n\n");
  		return true;
  	}
  	else if(strcmp("UP", direction)==0 && ptr->stage->up !=NULL && ptr->stage->up->isBlocked == false){//checks if above room is blocked
  		ptr->stage = ptr->stage->up; //moves up
  		printf("You moved UP\n\n");
  		return true; 
  	}
 	else if(strcmp("DOWN", direction)==0 && ptr->stage->down !=NULL && ptr->stage->down->isBlocked == false){//checks if lower room is blocked
  		ptr->stage = ptr->stage->down; //moves down
  		printf("You moved DOWN\n\n");
  		return true; 
  	} 
  	printf("YOU CAN'T GO THAT WAY\n");
  	return false;
}





/**
  * @desc initiate the game and all the command
  * @param user*ptr- struct avatar to interact with the game
*/
void play_game(user* ptr){ //USER API
	char* input1 = (char*)malloc(sizeof(char*)); //initialize strings for input
	char* input2 = (char*)malloc(sizeof(char*)); //initialize string for input
	bool end = false; //keeps the game going until player wins or quits

	while(!end && ptr->task != 4){ // not quit or not complete game
		printf("What do you do? Type \"help\" for a list of commands\n");
		scanf(" %s", input1); //stores input in input1

		if(strcmp("look", input1) == 0){ //look at room
			look(ptr->stage); //prints description of room
		}

		else if(strcmp("go", input1) == 0){ //go to another room
			scanf("%s", input2); //stores input in input2
			can_access(input2, ptr); //if room is not blocked		
		}


		else if(strcmp("take", input1) == 0){ //take an item
			fgets(input2, 20, stdin); //stores input in input2
			if(ptr->stage->item == NULL || !contain(input2, ptr->stage->item)){ //if item is not in the room 
				printf("I don't understand what you want to take!\n");
			}
			else{
				add_item(ptr->bag, item_take(input2, ptr->stage->item)); //takes item and adds it to the player's bag
				print_list(ptr->bag);
			}
		}

		else if(strcmp("use", input1) == 0){ //use an item from your bag
			fgets(input2, 20, stdin); //stores input in input2
			if(strcmp(ptr->stage->reqItem, input2) == 0 && contain(input2, ptr->bag)){ //take item from bag
				free(item_take(input2, ptr->bag)); //takes item out of the bag
				ptr->task += 1; //increases the count for complete tasks
				useItem(input2, ptr->stage); //uses the item 
			}
			else{
				printf("You can't use that item here or it doesn't exist.\n");
				}
		}

		else if(strcmp("drop", input1) == 0){ //drop an item
			fgets(input2, 20, stdin); //stores input in input2
			if(contain(input2, ptr->bag)){ //item is in bag
				add_item(ptr->stage->item, item_take(input2, ptr->bag)); //adds item to the room's item list
			}
			else{
				printf("Item does not exist.\n");
			}
		}

		else if(strcmp("help", input1) == 0){ //help menu
			printf("Type \"go DIRECTION\" to go to another room.\nType \"look\" to look at your surroundings.\nType \"inventory\" to look inside your inventory.\nType \"take ITEM\" to take an item in a room.\nType \"drop ITEM\" to drop something from your inventory.\nType \"use ITEM\" to use something in your inventory.\nType \"quit\" to quit the game. Your progress won't be saved.\n");

		}

		else if(strcmp("inventory", input1) == 0){ //player's bag of item
			print_list(ptr->bag); 
		}

		else if(strcmp("quit", input1) == 0){ //quit out of the game
			end = true;
		}

		else{
			printf("I don't know what you mean.\n\n");
		}
	}
	free(input1); 
	free(input2);
}


int main(){
	//prototypes
	chamber* load_rooms(); 

	Item*bag=item("","", NULL); //initializes user with a NULL inventory 
	chamber* start = load_rooms(); //returns the starting room and creates the map
	user* mario = initialize(bag, start); //creates the player character

	printf("\nAnother perfect day at the Mushroom Kingdom has been ruined yet again. Princess Toadstool has been kidnapped and taken away to a far off castle.\nNow it's your job to get her back. Your story starts as you travel to the looming castle and opening its metal doors. They shut loudly behind you.\n\n");

	play_game(mario); //begins the game

	freedom(mario, start); //frees everything that needs to be freed
	return 0;
}
