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



 user* initialize(struct Item*bag, chamber* begin){
	struct user* mario=(struct user*)malloc(sizeof(struct user));
	mario->bag=bag;
	mario->stage=begin;
	//mario->current_stage=current_stage;
	return mario;
}



void look(chamber*ptr){
	display_room(ptr);
}



bool can_access(char*direction, user*ptr){
	
	if(strcmp("NORTH",direction)==0 && ptr->stage->north !=NULL && ptr->stage->north->isBlocked == false){
  		return true;
   	}
  	else if(strcmp("SOUTH",direction)==0 && ptr->stage->south !=NULL && ptr->stage->south->isBlocked == false){
  		return true;
  	}
  	else if(strcmp("EAST",direction)==0 && ptr->stage->east !=NULL && ptr->stage->east->isBlocked == false){
  		return true;
  	}
  	else if(strcmp("WEST",direction)==0 && ptr->stage->west !=NULL && ptr->stage->west->isBlocked == false){
  		return true;
  	}
  	else if(strcmp("UP",direction)==0 && ptr->stage->up !=NULL && ptr->stage->up->isBlocked == false){
  		return true;
  	}
 	else if(strcmp("DOWN",direction)==0 && ptr->stage->down !=NULL && ptr->stage->down->isBlocked == false){
  		return true;
  	}
  	return false;
}



void go(user* ptr, char* direction){ 
	if(strcasecmp("NORTH",direction)==0){
  		ptr->stage=ptr->stage->north;
  		printf("You moved NORTH\n\n");
  		
   	}
  	else if(strcasecmp("SOUTH",direction)==0){
  		ptr->stage=ptr->stage->south;
  		printf("You moved SOUTH\n\n");
  		
  	}
  	else if(strcasecmp("EAST",direction)==0){
  		ptr->stage=ptr->stage->east;
  		printf("You moved EAST\n\n");
  		
  	}
  	else if(strcasecmp("WEST",direction)==0){
  		ptr->stage=ptr->stage->west;
  		printf("You moved WEST\n\n");
  		
  	}
  	else if(strcasecmp("UP",direction)==0){
  		ptr->stage=ptr->stage->up;
  		printf("You moved UP\n\n");
  		
  	}
 	else if(strcasecmp("DOWN",direction)==0){
  		ptr->stage=ptr->stage->down;
  		printf("You moved DOWN\n\n");
  		
  	}
	
}


void play_game(user* ptr){ //USER API
	char* input1 = (char*)malloc(sizeof(char*));
	char* input2 = (char*)malloc(sizeof(char*));

	char direction;
	bool end=false;

	while(!end){
		printf("What do you do? Type \"help\" for a list of commands\n");
		fgets(input1,100,stdin);
		
		if(strcasecmp("look", input1) == 0){
			look(ptr->stage);
		}
		else if(strcmp("go", input1) == 0){
			scanf("%s",input2);
			if(can_access(input2,ptr)){
				go(ptr,input2);
			}
			else
			system("setterm -bold on");
			printf("You can't go that way.\n");
		}

		else if(strcmp("take", input1) == 0){
			printf("THE ITEMS AVAILABLE IN THIS ROOM\n");

			if(ptr->stage->item->next!=NULL){ // check if room has item
				print_list(ptr->stage->item);
				printf("what you want to take:");
				fgets(input2,100,stdin);

				while(!contain(input2,ptr->stage->item) && !strcasecmp(input2,"x")==0){
					printf("ITEM IS NOT EXIST!!!!\n");

					print_list(ptr->stage->item);
					printf("Choose again or x to stop:");
					fgets(input2,100,stdin);
				}
				add_item(ptr->bag,item_take(input2,ptr->stage->item)); //add item into bag
				printf("YOUR NEW INVENTORY\n");
				print_list(ptr->bag);
				continue;
				}
			else
				printf("ROOM IS EMPTY\n");
				continue;
		}

		else if(strcmp("use", input1) == 0){
			print_list(ptr->bag);
			printf("WHAT YOU WANT TO USE:\n");
			scanf("%s",input2);
			if(strcmp(item_take(input2,ptr->bag)->name,ptr->stage->reqItem)==0){
				toggleBlocked(ptr->stage);
			}
			else
				printf("You can't use that item here.\n");
				continue;
		}

		else if(strcmp("drop", input1) == 0){		

			print_list(ptr->bag);
			printf("what do you want to drop:"); 
			scanf("%s",input2);
			Item*drop_ptr=item_take(input2,ptr->bag);
			printf("You dropped the %s\n",drop_ptr->name);
			add_item(ptr->stage->item,drop_ptr); // add item to room item ==drop in room

			printf("what do you want to drop:");
			print_list(ptr->bag);
			scanf("%s",input2);
			Item*drop_ptr=item_take(input2,ptr->bag);
			printf("You dropped the %s\n",drop_ptr->name);
			add_item(ptr->stage->item,drop_ptr);

			printf("YOUR INVENTORY:\n");
			print_list(ptr->bag);
			continue;
		}

		else if(strcasecmp("help", input1) == 0){
			printf("Type \"go\" to go to another room\nType \"look\" to look at your surroundings.\nType \"take\" to take an item in a room\nType \"drop\" to drop something from your inventory.\nType \"use\" to use something in your inventory\nType \"quit\" to quit the gane. Your progress won't be saved.\n");
			continue;
		}
		else if(strcasecmp("quit", input1) == 0){
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
	Item*bag=item("","", item("test","testing",NULL));
	//initializes user with a NULL inventory and load_rooms() returning the starting room
	chamber* start = load_rooms();
	user* mario = initialize(bag, start);

	printf("WORLD DESCRIPTION:\nAnother perfect day at the Mushroom Kingdom has been ruined yet again. Princess Toadstool has been kidnapped and taken away to a far off castle.\nNow it's your job to get her back. Your story starts as you travel to the looming castle and opening its metal doors. They shut loudly behind you.\n\n");
	

	play_game(mario);
	
	return 0;
}