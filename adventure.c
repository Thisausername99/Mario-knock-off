#include <stdio.h>
#include <stdlib.h>
#include "items.h"
#include "rooms.h"
#include <string.h>
#include <stdbool.h>


struct user{
 struct Item* bag;
 chamber* stage;
 //char*current_stage;
};

typedef struct user user;


 user* initialize(struct Item*bag, chamber* begin){ //creates the player character
	struct user* mario = (struct user*)malloc(sizeof(struct user)); //allocates memory for the user
	mario->bag = bag; //sets the bag
	mario->stage = begin; //sets the room the user starts at
	//mario->current_stage = current_stage;
	return mario;
}


void look(chamber*ptr){ //prints out the description of the room
	display_room(ptr);
}


bool can_access(char*direction, user*ptr){ //checks if the direction is blocked or not
	
	if(strcmp("NORTH",direction)==0 && ptr->stage->north !=NULL && ptr->stage->north->isBlocked == false){
  		return true; //checks if north room is blocked
   	}
  	else if(strcmp("SOUTH",direction)==0 && ptr->stage->south !=NULL && ptr->stage->south->isBlocked == false){
  		return true; //checks if south room is blocked
  	}
  	else if(strcmp("EAST",direction)==0 && ptr->stage->east !=NULL && ptr->stage->east->isBlocked == false){
  		return true; //checks if east room is blocked
  	}
  	else if(strcmp("WEST",direction)==0 && ptr->stage->west !=NULL && ptr->stage->west->isBlocked == false){
  		return true; //checks if west room is blocked
  	}
  	else if(strcmp("UP",direction)==0 && ptr->stage->up !=NULL && ptr->stage->up->isBlocked == false){
  		return true; //checks if above room is blocked
  	}
 	else if(strcmp("DOWN",direction)==0 && ptr->stage->down !=NULL && ptr->stage->down->isBlocked == false){
  		return true; //checks if lower room is blocked
  	} 

  	return false;
}



void go(user* ptr, char* direction){  //changes the room user is in
	if(strcmp("NORTH", direction)==0){ //goes north
  		ptr->stage = ptr->stage->north; 
  		printf("You moved NORTH\n\n"); 
  		
   	}
  	else if(strcmp("SOUTH", direction)==0){ //goes south
  		ptr->stage = ptr->stage->south;
  		printf("You moved SOUTH\n\n");
  		
  	}
  	else if(strcmp("EAST", direction)==0){ //goes east
  		ptr->stage = ptr->stage->east;
  		printf("You moved EAST\n\n");
  		
  	}
  	else if(strcmp("WEST", direction)==0){ //go west
  		ptr->stage = ptr->stage->west;
  		printf("You moved WEST\n\n");
  		
  	}
  	else if(strcmp("UP", direction)==0){ //go uo
  		ptr->stage = ptr->stage->up;
  		printf("You moved UP\n\n");
  		
  	}
 	else if(strcmp("DOWN", direction)==0){ //go down
  		ptr->stage = ptr->stage->down;
  		printf("You moved DOWN\n\n");
  		
  	}
	
}


void play_game(user* ptr){ //USER API
	char* input1 = (char*)malloc(sizeof(char*)); //allocate memory to store first input string
	char* input2 = (char*)malloc(sizeof(char*)); //allocate memory to store second input string

	//char direction; //direction player chooses to go
	bool end = false; //keeps the game going until player wins or quits

	while(!end){
		printf("What do you do? Type \"help\" for a list of commands\n");
		scanf("%s", input1); //gets player's input
		
		if(strcmp("look", input1) == 0){ //look at room
			look(ptr->stage);
		}

		else if(strcmp("go", input1) == 0){ //go to another room
			scanf("%s", input2);
			if(can_access(input2, ptr)){ //if room is not blocked
				go(ptr, input2); //go to the room
			}
			else{
				system("setterm -bold on");
				printf("You can't go that way.\n");
				system("setterm -bold off");
			}
		}

		else if(strcmp("take", input1) == 0){ //take an item
			printf("THE ITEMS AVAILABLE IN THIS ROOM\n");

			if(ptr->stage->item->next != NULL){ //item list not empty
				print_list(ptr->stage->item); //prints list of items
				printf("what you want to take: "); 
				scanf("%s", input2);

				while(!contain(input2, ptr->stage->item) && !strcmp(input2,"x")==0){ //rechoose if incorrect input given
					printf("ITEM IS NOT EXIST!!!!\n"); 
					print_list(ptr->stage->item); //prints list again
					printf("Choose again or x to stop: ");
					scanf("%s", input2);
				}
				add_item(ptr->bag, item_take(input2, ptr->stage->item)); //takes item and adds it to the player's bag
				printf("YOUR NEW INVENTORY");
				print_list(ptr->bag); //prints out list of bag items
				continue;
				}
			else{
				printf("ROOM IS EMPTY\n");
				continue;
			}
		}

		else if(strcmp("use", input1) == 0){ //use an item from your bag
			print_list(ptr->bag); //prints out bag
			printf("WHAT YOU WANT TO USE:\n");
			scanf("%s", input2);
			if(strcmp(item_take(input2,ptr->bag)->name, ptr->stage->reqItem)==0){ //take item from bag
				toggleBlocked(ptr->stage); //unblock next room
			}
			else{
				printf("You can't use that item here.\n");
				continue;
			}
		}

		else if(strcmp("drop", input1) == 0){ //drop an item
			print_list(ptr->bag); //prints out bag list
			printf("what do you want to drop: ");
			scanf("%s", input2);
			Item*drop_ptr = item_take(input2, ptr->bag); //take item out of bag
			printf("You dropped the %s\n", drop_ptr->name);
			add_item(ptr->stage->item, drop_ptr); //adds item to the room's item list
			
			printf("YOUR INVENTORY:\n");
			print_list(ptr->bag); 
			continue;
		}

		else if(strcmp("help", input1) == 0){
			printf("Type \"go\" to go to another room.\nType \"look\" to look at your surroundings.\nType \"take\" to take an item in a room.\nType \"drop\" to drop something from your inventory.\nType \"use\" to use something in your inventory.\nType \"quit\" to quit the game. Your progress won't be saved.\n");
			continue;
		}
		else if(strcmp("quit", input1) == 0){
			end = true;
		}
		else{
			printf("I don't know what you mean.\n\n");
			continue;
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

	printf("WORLD DESCRIPTION:\nAnother perfect day at the Mushroom Kingdom has been ruined yet again. Princess Toadstool has been kidnapped and taken away to a far off castle.\nNow it's your job to get her back. Your story starts as you travel to the looming castle and opening its metal doors. They shut loudly behind you.\n\n");

	play_game(mario);
	
	return 0;
}
