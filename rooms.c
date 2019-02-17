#include <stdio.h>
#include <string.h>
#include "items.h"
#include "rooms.h"




chamber * new_room(char* desc,char*tool, Item* item_list,chamber *north, chamber *south,
	chamber *east, chamber *west,chamber *up, chamber *down){
	chamber*new_room=(chamber*)malloc(sizeof(chamber));
	
	new_room->challenge=false;
	
	new_room->desc=desc;
	new_room->item=item_list;
	new_room->tool=tool;

	new_room->south=south;
	new_room->north=north;
	new_room->east=east;
	new_room->west=west;
	new_room->up=up;
	new_room->down=down;

	return new_room;
}

void set_north(chamber*current,chamber*other){
	current->north=other;
}

void set_south(chamber*current,chamber*other){
	current->south=other;
}

void set_east(chamber*current,chamber*other){
	current->east=other;
}

void set_west(chamber*current,chamber*other){
	current->west=other;
}

void set_up(chamber*current,chamber*other){
	current->up=other;
}

void set_down(chamber*current,chamber*other){
	current->down=other;
}


void display_room(chamber*ptr){
	printf("%s",ptr->desc);
}

void room_item(chamber*room){
 	print_list(room->item);
}


bool state_conquered(char*item,chamber* current){
	if(strcmp(item,current->item_req)==0){
		current->challenge=true;
		current->desc="Room mission has been completed";
		return true;
	}
	return false;
}


chamber* initiate_room(){

	Item* room_one=item(" "," ",item("sword of ALL Sword","to slay a beast",item("fire","to melt the ice",NULL)));
	Item* room_two=item(" "," ",item("key","to unlock a chest",NULL));
	
	chamber * level_two=new_room("Then exit is blocked by a boulder, need shroom to break","Shroom";
	room_one,NULL,NULL,NULL,NULL,NULL,NULL);

	chamber * level_one=new_room("A room that hibernate by a giant serpent","sword",
	room_two,level_two,NULL,NULL,NULL,NULL,NULL);

	chamber * level_three=new_room("This room guarded by army of Koopa","fire ball",
	room_two,level_two,NULL,NULL,NULL,NULL,NULL);

	chamber * level_four=new_room("This room has a piranhaplant guarding","fire ball",
	room_two,level_two,NULL,NULL,NULL,NULL,NULL);

	chamber * level_five=new_room("This room has no obstacle","free to loot",
	room_two,level_two,NULL,NULL,NULL,NULL,NULL);

	chamber * level_six=new_room("A room that hibernate by a giant serpent that can only be killed with the sword of ALL Sword",
	room_two,level_two,NULL,NULL,NULL,NULL,NULL);


	chamber * level_seven=new_room("A room that hibernate by a giant serpent that can only be killed with the sword of ALL Sword",
	room_two,level_two,NULL,NULL,NULL,NULL,NULL);


	chamber * level_eight=new_room("A room that hibernate by a giant serpent that can only be killed with the sword of ALL Sword",
	room_two,level_two,NULL,NULL,NULL,NULL,NULL);



	return level_one;
}






