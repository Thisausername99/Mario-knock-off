#include<stdio.h>
#include<stdlib.h>
#include "items.h"
#include "rooms.h"
#include <string.h>


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

	//Item*slot=bag->next;	
	while(bag->next!=NULL){
		bag=bag->next;
	}
	bag->next=new;
	
}


void room_exit(struct avatar*ptr , char* direction){ 
	chamber*temp=ptr->stage;

	if(strcmp("north",direction)==0){
  	ptr->stage=temp->north;
   	}
  	if(strcmp("south",direction)==0){
  	ptr->stage=temp->south;
  	}
  	else if(strcmp("east",direction)==0){
  	ptr->stage=temp->east;
  	}
  	else if(strcmp("west",direction)==0){
  	ptr->stage=temp->west;
  	}
  	else if(strcmp("up",direction)==0){
  	ptr->stage=temp->up;
  	}
 	else if(strcmp("down",direction)==0){
  	ptr->stage=temp->down;
  	}

  	free(temp);
}


/*void play_game(user*ptr){
	while(ptr->score<8){


	}


}*/


typedef struct avatar user;

int main(void){
char*name;
struct Item *bag=item("","",item("ID","To enter club",NULL));
chamber*first_stage=initiate_room();
printf("Welcome to Text Adventure\nPlease choose a name for you avatar:");
scanf("%s",name);
struct avatar*user=initialize(name,bag,first_stage);
printf("%s\n",user->name);
room_item(first_stage);
print_list(bag);
printf("*PLAYER INVENTORY*\n");
add_item(bag,item_take("key",first_stage->item));
//printf("%s",(item_take("key",first_stage->item))->description);
print_list(bag);

printf("first stage after remove\n");

display_room(first_stage);
return 0;
}