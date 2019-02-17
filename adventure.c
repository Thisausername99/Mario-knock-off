#include<stdio.h>
#include<stdlib.h>
#include "items.h"
#include "rooms.h"
#include <string.h>
#include<stdbool.h>


//#define 

struct avatar{
 char*name;
 struct Item*bag;
 int score;
 chamber*stage;
};
typedef struct avatar user;

struct avatar* initialize(char*name,struct Item*bag, chamber* begin){
	struct avatar*user=(struct avatar*)malloc(sizeof(struct avatar));
	user->name=name;
	user->bag=bag;
	user->stage=begin;
	user->score=0;
	return user;
}

void add_item(struct Item*bag, struct Item*new){ //pass a pointer to add the item
	if(bag->next==NULL){
		bag->next=new;
	}	
	while(bag->next!=NULL){
		bag=bag->next;
	}
	bag->next=new;
	
}


void LOOK_cmd(chamber*ptr){
	display_room(ptr);
}


void interact_room(){

	
}




bool room_exit(user*ptr , char* direction){ 
	chamber*temp=ptr->stage;

	if(strcmp("north",direction)==0 && (ptr->north->challenge)){
  	ptr->stage=temp->north;
  	return true;
   	}
  	if(strcmp("south",direction)==0 && (ptr->south->challenge)){
  	ptr->stage=temp->south;
  	return true;
  	}
  	else if(strcmp("east",direction)==0 && (ptr->east->challenge)){
  	ptr->stage=temp->east;
  	return true;
  	}
  	else if(strcmp("west",direction)==0 && (ptr->west->challenge)){
  	ptr->stage=temp->west;
  	return true;
  	}
  	else if(strcmp("up",direction)==0 && (ptr->up->challenge)){
  	ptr->stage=temp->up;
  	return true;
  	}
 	else if(strcmp("down",direction)==0 && (ptr->down->challenge)){
  	ptr->stage=temp->down;
  	return true;
  	}
  	else
  	printf("The wey is blocked");
	free(temp);
	return true;
}


void play_game(user*ptr){ //USER API
	char decision;
	char direction;
	bool stop=false;
	while(!stop){
		printf("CHOOSE AN ACTION: L For LOOK  T to TAKE , G to go or Q to quit or I for INVENTORY:");
		scanf(" %c",&decision);
		if(decision=='L'){
			LOOK_cmd(ptr->stage);
			continue;
		}
		else if(decision='I'){
			print_list(ptr->bag);
			continue;
		}
		else if(decision=='Q'){
			break;
	}

printf("Thank for playing");
}


typedef struct avatar user;

int main(void){
char*name;
struct Item *bag=item("","",item("ID","To enter club",NULL));
chamber*first_stage=initiate_room();
printf("Welcome to Text Adventure\nPlease choose a name for you avatar:");
scanf("%s",name);
struct avatar*user=initialize(name,bag,first_stage);
printf("%s\n",user->name);
play_game(user);

/*room_item(first_stage);
print_list(bag);
printf("*PLAYER INVENTORY*\n");
add_item(bag,item_take("key",first_stage->item));
//printf("%s",(item_take("key",first_stage->item))->description);
print_list(bag);

printf("first stage after remove\n");

display_room(first_stage);*/
return 0;
}