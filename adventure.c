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
};

typedef struct user user;


 user* initialize(struct Item*bag, chamber* begin){ //creates the player character
	struct user* mario = (struct user*)malloc(sizeof(struct user)); //allocates memory for the user
	mario->bag = bag; //sets the bag
	mario->stage = begin; //sets the room the user starts at
	mario->task=0;
	return mario;
}


void look(chamber*ptr){ //prints out the description of the room
	display_room(ptr);
}


bool can_access(char*direction, user*ptr){ //checks if the direction is blocked or not
	
	if(strncmp("NORTH", direction, 5)==0 && ptr->stage->north !=NULL && ptr->stage->north->isBlocked == false){
  		return true; //checks if north room is blocked
   	}
  	else if(strncmp("SOUTH", direction, 5)==0 && ptr->stage->south !=NULL && ptr->stage->south->isBlocked == false){
  		return true; //checks if south room is blocked
  	}
  	else if(strncmp("EAST", direction, 4)==0 && ptr->stage->east !=NULL && ptr->stage->east->isBlocked == false){
  		return true; //checks if east room is blocked
  	}
  	else if(strncmp("WEST", direction, 4)==0 && ptr->stage->west !=NULL && ptr->stage->west->isBlocked == false){
  		return true; //checks if west room is blocked
  	}
  	else if(strncmp("UP", direction, 2)==0 && ptr->stage->up !=NULL && ptr->stage->up->isBlocked == false){
  		return true; //checks if above room is blocked
  	}
 	else if(strncmp("DOWN", direction, 4)==0 && ptr->stage->down !=NULL && ptr->stage->down->isBlocked == false){
  		return true; //checks if lower room is blocked
  	} 

  	return false;
}



void go(user* ptr, char* direction){  //changes the room user is in
	if(strncmp("NORTH", direction, 5)==0){ //goes north
  		ptr->stage = ptr->stage->north; 
  		printf("You moved NORTH\n\n"); 
  		
   	}
  	else if(strncmp("SOUTH", direction, 5)==0){ //goes south
  		ptr->stage = ptr->stage->south;
  		printf("You moved SOUTH\n\n");
  		
  	}
  	else if(strncmp("EAST", direction, 4)==0){ //goes east
  		ptr->stage = ptr->stage->east;
  		printf("You moved EAST\n\n");
  		
  	}
  	else if(strncmp("WEST", direction, 4)==0){ //go west
  		ptr->stage = ptr->stage->west;
  		printf("You moved WEST\n\n");
  		
  	}
  	else if(strncmp("UP", direction, 2)==0){ //go uo
  		ptr->stage = ptr->stage->up;
  		printf("You moved UP\n\n");
  		
  	}
 	else if(strncmp("DOWN", direction, 4)==0){ //go down
  		ptr->stage = ptr->stage->down;
  		printf("You moved DOWN\n\n");
  		
  	}
	
}


void play_game(user* ptr){ //USER API

		bool end = false; //keeps the game going until player wins or quits

	while(!end){ // not quit or not complete game
		printf("What do you do? Type \"help\" for a list of commands\n");
		char* input1 = (char*)malloc(sizeof(char*));        //initialize strings for input
		scanf(" %s", input1); //stores input in input1
		
		if( strcmp ("look", input1) == 0){ //look at room
			look(ptr->stage);
		}

		else if(   strcmp("go", input1) == 0){ //go to another room
		char* input2 = (char*)malloc(sizeof(char*));        //initialize strings for input


			scanf("%s", input2); //stores input in input2
			if(can_access(input2, ptr)){ //if room is not blocked
				go(ptr, input2); //go to the room
				continue;
			}
			else{
				system("setterm -bold on");
				printf("You can't go that way.\n");
				system("setterm -bold off");
			}
		}

		else if( strcmp("take", input1) == 0){ //take an item


			char* input2 = (char*)malloc(sizeof(char*));
			fgets(input2, 20, stdin);
			

				if( ptr->stage->item == NULL || strcmp(input2, ptr->stage->item->next->name) != 0){
					printf("I don't understand what you want to take!\n");
				}
				else{
					add_item(ptr->bag, item_take(input2, ptr->stage->item)); //takes item and adds it to the player's bag
				}

		
		}

		else if(strcmp("use", input1) == 0){ //use an item from your bag
			
			char* input2 = (char*)malloc(sizeof(char*));
			fgets(input2, 20, stdin);





			if(    strcmp(ptr->stage->reqItem, input2) == 0 ){ //take item from bag
				item_take(input2,ptr->bag);
				if(toggleBlocked(ptr->stage)){ //unblock next room
				ptr->task=+1;
				printFlavor(input2, ptr->stage);
				}
			}
			else{
				printf("You can't use that item here.\n");
			}
			
		}

		else if(strcmp("drop", input1) == 0){ //drop an item
			/*
			print_list(ptr->bag); //prints out bag list
			printf("what do you want to drop: ");
			fgets(input2, 20, stdin); //stores input in input2
			Item*drop_ptr = item_take(input2, ptr->bag); //take item out of bag
			printf("You dropped the %s\n", drop_ptr->name);
			add_item(ptr->stage->item, drop_ptr); //adds item to the room's item list
			
			printf("\nYOUR INVENTORY:\n");
			print_list(ptr->bag); 
			continue;
			*/
		}

		else if(strcmp("help", input1) == 0){
			printf("Type \"go\" to go to another room.\nType \"look\" to look at your surroundings.\nType \"inventory\" to look inside your inventory.\nType \"take\" to take an item in a room.\nType \"drop\" to drop something from your inventory.\nType \"use\" to use something in your inventory.\nType \"quit\" to quit the game. Your progress won't be saved.\n");
		}
		else if(strcmp("inventory", input1) == 0){
			print_list(ptr->bag); 
		}
		else if(strcmp("quit", input1) == 0){
			end = true;
		}
		else{
			printf("I don't know what you mean.\n\n");
		}
	}
	
}


int main(){
	//prototypes
	chamber* load_rooms(); 
	Item*bag=item("","", item("test","testing",NULL)); //testing items
	//initializes user with a NULL inventory and load_rooms() returning the starting room
	chamber* start = load_rooms(); //creates the rooms
	user* mario = initialize(bag, start); //creates the player character

	printf("\nAnother perfect day at the Mushroom Kingdom has been ruined yet again. Princess Toadstool has been kidnapped and taken away to a far off castle.\nNow it's your job to get her back. Your story starts as you travel to the looming castle and opening its metal doors. They shut loudly behind you.\n\n");

	play_game(mario);
	
	return 0;
}
