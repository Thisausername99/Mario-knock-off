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


 user* initialize(struct Item*bag, chamber* begin){ //creates the player character
	struct user* mario = (struct user*)malloc(sizeof(struct user)); //allocates memory for the user
	mario->bag = bag; //sets the bag
	mario->stage = begin; //sets the room the user starts at
	mario->task=0;
	mario->bag_size=1;
	return mario;
}


void look(chamber*ptr){ //prints out the description of the room
	display_room(ptr);
}




bool can_access(char*direction, user*ptr){ //checks if the direction is blocked or not
	
	if(strncmp("NORTH", direction, 5)==0 && ptr->stage->north !=NULL && ptr->stage->north->isBlocked == false){
  		ptr->stage = ptr->stage->north; 
  		printf("You moved NORTH\n\n"); 
  		return true; //checks if north room is blocked
   	}
  	else if(strncmp("SOUTH", direction, 5)==0 && ptr->stage->south !=NULL && ptr->stage->south->isBlocked == false){
  		ptr->stage = ptr->stage->south;
  		printf("You moved SOUTH\n\n");
  		return true; //checks if south room is blocked
  	}
  	else if(strncmp("EAST", direction, 4)==0 && ptr->stage->east !=NULL && ptr->stage->east->isBlocked == false){
  		ptr->stage = ptr->stage->east;
  		printf("You moved EAST\n\n");
  		return true; //checks if east room is blocked
  	}
  	else if(strncmp("WEST", direction, 4)==0 && ptr->stage->west !=NULL && ptr->stage->west->isBlocked == false){
  		ptr->stage = ptr->stage->west;
  		printf("You moved WEST\n\n");
  		return true; //checks if west room is blocked
  	}
  	else if(strncmp("UP", direction, 2)==0 && ptr->stage->up !=NULL && ptr->stage->up->isBlocked == false){
  		ptr->stage = ptr->stage->up;
  		printf("You moved UP\n\n");
  		return true; //checks if above room is blocked
  	}
 	else if(strncmp("DOWN", direction, 4)==0 && ptr->stage->down !=NULL && ptr->stage->down->isBlocked == false){
  		ptr->stage = ptr->stage->down;
  		printf("You moved DOWN\n\n");
  		return true; //checks if lower room is blocked
  	} 
  	printf("YOU CAN'T GO THAT WEI\n");
  	return false;
}



void alter_state(char* item){
	if(strcmp(item,"Fire Flower")){
		printf("THE FIERY FIRE BALLS SCATTERED AROUND THE ROOM WITH BLAMING TOUCH DECIMATED EVERY KOOPA NEAR BY. THEY ARE SCREAMING IN AGONIZE WHILE BEING ROASTED ALIVE\n");
	}
}



void play_game(user* ptr){ //USER API
	char input1[20]; //initialize strings for input
	char input2[20]; //initialize strings for input

	bool end = false; //keeps the game going until player wins or quits

	while(!end && ptr->task!=4){ // not quit or not complete game
		printf("What do you do? Type \"help\" for a list of commands\n");
		fgets(input1,10,stdin);
		//fgets(input1, 20, stdin); //stores input in input1
		
		if(strncmp("look", input1, 4) == 0){ //look at room
			look(ptr->stage);
		}

		else if(strncmp("go", input1, 2) == 0){ //go to another room
			fgets(input2,10,stdin);//stores input in input2
			can_access(input2, ptr); //if room is not blocked		
		}
			

		else if(strncmp("take", input1, 4) == 0){ //take an item
			printf("THE ITEMS AVAILABLE IN THIS ROOM\n");

			if(ptr->stage->item->next != NULL){ //item list not empty
				print_list(ptr->stage->item); //prints list of items
				printf("What you want to take: "); 
				fgets(input2, 20, stdin); //stores input in input2

				while(!contain(input2, ptr->stage->item) && !strncmp("x", input2, 1) == 0){ //rechoose if incorrect input given
					printf("ITEM IS NOT EXIST!!!!\n"); 
					print_list(ptr->stage->item); //prints list again
					printf("Choose again or x to stop: ");
					fgets(input2, 20, stdin); //stores input in input2
				}

				add_item(ptr->bag, item_take(input2, ptr->stage->item)); //takes item and adds it to the player's bag
				printf("\nYOUR NEW INVENTORY\n");
				print_list(ptr->bag); //prints out list of bag items
				printf("\n");
				}

			else
				printf("ROOM IS EMPTY\n");
		}


		else if(strncmp("use", input1, 3) == 0){ //use an item from your bag
			print_list(ptr->bag); //prints out bag
			printf("\nWHAT YOU WANT TO USE: ");
			fgets(input2, 20, stdin); //stores input in input2
			if((ptr->stage->reqItem!=NULL) && (strncmp(ptr->stage->reqItem, input2, strlen(ptr->stage->reqItem))==0)){ //check if it the right item
				item_take(input2,ptr->bag);  //take item from bag
				alter_state(input2);
				toggleBlocked(ptr->stage); //unblock next room
				ptr->task=+1;

				printf("The next room has been unblocked.\n");
				
			}
			else{
				printf("YOU CAN'T USE THAT ITEM HERE or ITEM IS NOT EXIST.\n");
				
			}
		}

		else if(strncmp("drop", input1, 4)){ //drop an item
			if(ptr->bag_size>0){
			print_list(ptr->bag); //prints out bag list
			printf("what do you want to drop: ");
			fgets(input2, 20, stdin); //stores input in input2

			if(contain(input2,ptr->bag)){
				//Item*drop_ptr = item_take(input2, ptr->bag); //take item out of bag
				//printf("You dropped the %s\n", drop_ptr->name);
				add_item(ptr->stage->item, item_take(input2, ptr->bag)); //adds item to the room's item list
			
				printf("\nYOUR INVENTORY:\n");
				print_list(ptr->bag); 
			}
			else
				printf("YOU DONT HAVE THAT ITEM\n");
			}
			printf("YOUR BAG IS EMPTY!\n");
		}


		else if(strncmp("help", input1, 4) == 0){
			printf("Type \"go\" to go to another room.\nType \"look\" to look at your surroundings.\nType \"take\" to take an item in a room.\nType \"drop\" to drop something from your inventory.\nType \"use\" to use something in your inventory.\nType \"quit\" to quit the game. Your progress won't be saved.\n");
			
		}

		else if(strncmp("quit", input1, 4) == 0){
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

	printf("WORLD DESCRIPTION:\nAnother perfect day at the Mushroom Kingdom has been ruined yet again. Princess Toadstool has been kidnapped and taken away to a far off castle.\nNow it's your job to get her back. Your story starts as you travel to the looming castle and opening its metal doors. They shut loudly behind you.\n\n");

	play_game(mario);
	
	return 0;
}
