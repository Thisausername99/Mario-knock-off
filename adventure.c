#include <stdio.h>
#include <stdlib.h>
#include "items.h"
#include "rooms.h"
#include <string.h>
#include <stdbool.h>


struct user{
 struct Item* bag;
 chamber* stage;
};

typedef struct user user;



 user* initialize(struct Item*bag, chamber* begin){
	struct user* mario=(struct user*)malloc(sizeof(struct user));
	mario->bag=bag;
	mario->stage=begin;
	return mario;
}

void add_item(struct Item*bag, struct Item*new){ //pass a pointer to add the item

	if(bag == NULL){
		bag = new;
	}
	else if(bag->next==NULL){
		bag->next=new;
	}	
	while(bag->next!=NULL){
		bag=bag->next;
	}
	bag->next=new;
	
}


void look(chamber*ptr){
	display_room(ptr);
}




bool go(user* ptr, char* direction){ 
	chamber*temp=ptr->stage;

	if(strcmp("NORTH",direction)==0 && (temp->north->challenge)){
  	ptr->stage=temp->north;
  	return true;
   	}
  	if(strcmp("SOUTH",direction)==0 && (temp->south->challenge)){
  	ptr->stage=temp->south;
  	return true;
  	}
  	else if(strcmp("EAST",direction)==0 && (temp->east->challenge)){
  	ptr->stage=temp->east;
  	return true;
  	}
  	else if(strcmp("WEST",direction)==0 && (temp->west->challenge)){
  	ptr->stage=temp->west;
  	return true;
  	}
  	else if(strcmp("UP",direction)==0 && (temp->up->challenge)){
  	ptr->stage=temp->up;
  	return true;
  	}
 	else if(strcmp("DOWN",direction)==0 && (temp->down->challenge)){
  	ptr->stage=temp->down;
  	return true;
  	}
  	else
  	printf("You can't go that way.");
	free(temp);
	return true;
}


void play_game(user* ptr){ //USER API
	char* input1 = (char*)malloc(sizeof(char*));
	char* input2 = (char*)malloc(sizeof(char*));

	char direction;
	bool end=false;

	while(!end){

		printf("What do you do? Type \"help\" for a list of commands\n");

		scanf("%s",input1);


		if(strcmp("look", input1) == 0){
			look(ptr->stage);
		}
		else if(strcmp("go", input1) == 0){
					scanf("%s",input2);
			go(ptr,input2);
		}
		else if(strcmp("take", input1) == 0){
					scanf("%s",input2);

		}
		else if(strcmp("use", input1) == 0){
					scanf("%s",input2);

		}
		else if(strcmp("drop", input1) == 0){
					scanf("%s",input2);

		}
		else if(strcmp("help", input1) == 0){
			printf("Type \"go\" to go to another room. Type \"look\" to look at your surroundings.\nType \"take\" to take an item in a room. Type \"drop\" to drop something from your inventory.\nType \"use\" to use something in your inventory. Type \"quit\" to quit the gane. Your progress won't be saved.");
		}
		else if(strcmp("quit", input1) == 0){
			end = true;
		}
		else{
			printf("I don't know what you mean.\n");
		}
	}
	
}


int main(){
	//prototypes
	chamber* load_rooms();


	//initializes user with a NULL inventory and load_rooms() returning the starting room
	chamber* start = load_rooms();
	user* mario = initialize(NULL, start);


	printf("\n\nAnother perfect day at the Mushroom Kingdom has been ruined yet again. Princess Toadstool has been kidnapped and taken away to a far off castle.\nNow it's your job to get her back. Your story starts as you travel to the looming castle and opening its metal doors. They shut loudly behind you.\n\n");
	

	play_game(mario);

	return 0;
}