#include <stdio.h>
#include <string.h>
#include "items.h"
#include "rooms.h"


chamber * new_room(char* description, Item* item_list,struct Room *north, struct Room *south,
	struct Room *east, struct Room *west,struct Room *up, struct Room *down){
	chamber*new_room=(chamber*)malloc(sizeof(chamber));
	new_room->score=0;
	new_room->challenge=false;
	new_room->description=description;
	new_room->item=item_list;
	
	new_room->south=south;
	new_room->north=north;
	new_room->east=east;
	new_room->west=west;
	new_room->up=up;
	new_room->down=down;

	return new_room;
}


/*void room_exit(chamber* current, chamber* other,char* direction){ 
	if(strcmp("north",direction)==0){
  	current->north=other;
   	}
  	else if(strcmp("south",direction)==0){
  	current->south=other;
  	}
  	else if(strcmp("east",direction)==0){
  	current->east=other;
  	}
  	else if(strcmp("west",direction)==0){
  	current->west=other;
  	}
  	else if(strcmp("up",direction)==0){
  	current->up=other;
  	}
 	else if(strcmp("down",direction)==0){
  	current->down=other;
  	}
}*/

void room_item(chamber*room){
 	print_list(room->item);
}



bool state_conquered(chamber* current){
	if(current->score==3){
		current->challenge=true;
		current->description="Room mission has been completed";
		return true;
	}
	return false;
}


chamber* initiate_room(){
	Item* room_one=item(" "," ",item("sword of ALL Sword","to slay a beast",item("fire","to melt the ice",NULL)));
	Item* room_two=item(" "," ",item("key","to unlock a chest",NULL));
	chamber * level_one=new_room("A room that hibernate by a giant serpent that can only be killed with the sword of ALL Sword",
	room_two,NULL,NULL,NULL,NULL,NULL,NULL);
	return level_one;
}






