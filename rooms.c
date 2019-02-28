#include <stdio.h>
#include <string.h>
#include "items.h"
#include "rooms.h"
#include <stdbool.h>


chamber * new_room(char* desc, char* tool, Item *item_list, bool blocked, chamber *north, chamber *south,
	chamber *east, chamber *west, chamber *up, chamber *down){ //creates new room

	chamber*new_room = (chamber*)malloc(sizeof(chamber)); //allocates memory for the room
		
	new_room->desc = desc; //sets description
	new_room->reqItem = tool; //sets item required to get to the room
	new_room->item = item_list; //sets item list
	new_room->isBlocked = blocked; //sets true or false if the room is blocked by something

	new_room->south = south; //sets room to the south
	new_room->north = north; //sets room to the north
	new_room->east = east; //sets room to the east
	new_room->west = west; //sets room to the west
	new_room->up = up; //sets room up
	new_room->down = down; //sets room down

	return new_room;
}

bool contain(char*search, Item*curr_room){ //checks whether or not item is in room
	curr_room = curr_room->next; //skips summy head
	while(curr_room != NULL){
		if(strncmp(search, curr_room->name, strlen(curr_room->name))==0){ //item found
			return true;
		}
		curr_room = curr_room->next; //checks next item in the list
	}
	return false;
}




void set_north(chamber* current,chamber* other){ //sets the room north of current room
	current->north = other;
}

void set_south(chamber* current,chamber* other){ //sets the room south of current room
	current->south = other;
}

void set_east(chamber* current,chamber* other){ //sets the room east of current room
	current->east = other;
}

void set_west(chamber* current,chamber* other){ //sets the room west of current room
	current->west = other;
}

void set_up(chamber* current,chamber* other){ //sets the room above the current room
	current->up = other;
}

void set_down(chamber* current,chamber* other){ //sets the room below the current room
	current->down = other;
}

void set_item(chamber* current,Item* new){ //sets the room below the current room
	current->item = new;
}


void set_description(chamber* current,char* new){ //sets the room below the current room
	current->desc = new;
}

bool toggleBlocked(chamber* current){ //changes the blocked status of the room
	bool result=false;
	if(current->north !=NULL && current->north->isBlocked == true){
  		current->north->isBlocked = false; //unblocks north room
  		result=true;
   	}
  	else if(current->south !=NULL && current->south->isBlocked == true){
  		current->south->isBlocked = false; //unblocks south room
  		result=true;
  	}
  	else if(current->east !=NULL && current->east->isBlocked == true){
  		current->east->isBlocked = false; //unblocks east room
  		result=true;
  	}
  	else if(current->west !=NULL && current->west->isBlocked == true){
  		current->west->isBlocked = false; //unblocks west room
  		result=true;
  	}
  	else if(current->up !=NULL && current->up->isBlocked == true){
  		current->up->isBlocked = false; //unblocks above room
  		result=true;
  	}
 	else if(current->down !=NULL && current->down->isBlocked == true){
  		current->down->isBlocked = false; //unblocks lower room
  		result=true;
  	}
  	return result; 
}


void display_room(chamber* ptr){ //prints the description of the room
	printf("%s", ptr->desc);
}

void useItem(char* new, chamber* ptr){ //prints the description of the room
	printf("%s", new);
	if( strcmp(new, " FIRE FLOWER\n") == 0 && strcmp(ptr->reqItem, " FIRE FLOWER\n") == 0 ){
		printf("You hold the FIRE FLOWER in front of the wooden door and the FLOWER shoots out a fireball.\nThe fireball crashes into the door, combusting it instantly.\n" );
		set_description(ptr, "ROOM 1-2. The room's walls are smokey and dark. Metal sconces are chained to the walls and their flames lick up at crumbling ceiling.\nOne of the sconces is unlit. You see a way WEST and NORTH of you where a door used to be.\n");
		ptr->north->isBlocked = false;
	}
	else if( strcmp(new, " KOOPA SHELL\n") == 0 && strcmp(ptr->reqItem, " KOOPA SHELL\n") == 0 ){
		printf("You kick the KOOPA SHELL into the suspicious pile of blocks. They break one by one and reveal a MUSHROOM that was hidden beneath.\n" );
		set_description(ptr, "ROOM 2-3. Where there used to be a pile of blocks there is a MUSHROOM.\nThe room is a dead-end. You see only the way you came from WEST of you.\n");
		Item* mush = item("","", item(" MUSHROOM\n", "a red fungi", NULL));
		set_item ( ptr, mush );

	}
	else if( strcmp(new, " MUSHROOM\n") == 0 && strcmp(ptr->reqItem, " MUSHROOM\n") == 0 ){
		printf("You eat the MUSHROOM and grow bigger. Your bigger form lets you jump into the ceiling and break the ceiling open.\n" );
		set_description(ptr, "ROOM 1-3. The ceiling in this room is busted open.\nHeat pours from it. You see a way SOUTH and WEST of you. You can just reach a way UP.\n");
		ptr->up->isBlocked = false;
	}
	else if( strcmp(new, " AXE\n") == 0 && strcmp(ptr->reqItem, " AXE\n") == 0 ){
		printf("You grab the AXE and swing it against the chains of the bridge. The bridge cracks violently and collapse into the lava.\nThe giant lizard tumbles into the lava with a roar that shakes the entire room.\n \"Oh, thank you Mario!\", you hear someone say. You turn around to find Princess Toadstool safe and sound. You decide to quickly leave the castle with her to return her to her kingdom.\n 	T H E   E N DN\" );
	}






}



chamber* load_rooms(){ //creates all the rooms and connects them

	chamber* room_11 = new_room("ROOM 1-1. The room is dim with no lighting except light pouring from the outside of the front gate you've entered from. The stone brick walls surrounds you.\nYou see a rectangular opening EAST of you.\n",
	NULL,NULL,false,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 1-1, the starting room

	chamber* room_12 = new_room("ROOM 1-2. The room's walls are smokey and dark. Metal sconces are chained to the walls and their flames lick up at crumbling ceiling.\nOne of the flames behaves differently from the others and doesn't burn you as you approach.\nOn further inspection, it isn't real fire but a FIRE FLOWER emitting a shining light. An old wooden door NORTH of you blocks your way NORTH. It does not budge. You see a way WEST of you.\n",
	" FIRE FLOWER\n", NULL,false,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 1-2

	chamber* room_13 = new_room("ROOM 1-3. The first thing you notice are stones and dust falling from the rooms ceiling.\nThe ceiling in this room is falling apart and would most likely give if you even touched it, but you are too short as you are.\nThe room's floor gives way to dirt instead of stone. You see a way SOUTH and WEST of you.\n",
	" MUSHROOM\n", NULL,true,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 1-3

	chamber* room_14 = new_room("ROOM 1-4. Intricate stone stairs spiral up into the ceiling. Small specks of dust and dirt float down from the floor above.\nYou can climb the stairs UP and you see a way EAST of you.\n",
	NULL, NULL,false,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 1-4

	chamber* room_21 = new_room("ROOM 2-1. The floor is littered with discarded KOOPA SHELLs and their putrid smell makes your eyes water.\nSome of the KOOPA SHELLs still have skelettons inside them while other skeletons are chained to the wall.\nYou can't help but feel bad. There are stairs that lead DOWN and a way to continue SOUTH of you.\n",
	NULL, NULL,false,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 2-1

	chamber* room_22 = new_room("ROOM 2-2. The room is empty except for crumbled and ripped up paper all over the floor. No writing desk is in the room.\nYou pick up a paper and inspect it, but it is indecipherable plans.\nThe poorly drawn plumber and dinosaur remind you of someone. You see a way NORTH and EAST.\n",
	NULL, NULL,false,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 2-2

	chamber* room_23 = new_room("ROOM 2-3. Blocks cover the ground and there is suspicious mound of them in the corner of the room.\nThe blocks cannot be lifted and there's no way to break them on your own. \nThe room is a dead-end. You see only the way you came from WEST of you.\n",
	" KOOPA SHELL\n", NULL,false,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 2-3

	chamber* room_24 = new_room("ROOM 2-4. The room is huge and completely black. You're standing on the edge of a bridge that is chained above a lake of lava.\nA huge green lizard with a spiked shell looms on the other side of the bridge.\nFire pours from his unhinged mouth. Behind him is an AXE as well as where the bridge is precariously chained.\n",
	" AXE\n", NULL,true,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 2-4
 
	set_east(room_11, room_12); //connects room 1-1 and 1-2

	set_north(room_12, room_13); //connects room 1-2 with 1-3
	set_west(room_12, room_11); //connects room 1-2 with 1-1

	set_south(room_13, room_12); //connects room 1-3 with 1-2
	set_up(room_13, room_24); //connects room 1-3 with 2-4
	set_west(room_13, room_14); //connects room 1-3 with 1-4

	set_up(room_14, room_21); //connects room 1-4 with 2-1
	set_east(room_14, room_13); //connects room 1-4 with 1-3
 
	set_south(room_21, room_22); //connects room 2-1 with 2-2
	set_down(room_21, room_14); //connects room 2-1 with 1-4

	set_north(room_22, room_21); //connects room 2-2 with 2-1
	set_east(room_22, room_23); //connects room 2-2 with 2-3

	set_west(room_23, room_22); //connects room 2-3 with 2-2

	Item* fireflower = item("","", item(" FIRE FLOWER\n", "a Fiery Flower", NULL));

	Item* koopashell = item("","", item(" KOOPA SHELL\n", "a Koopa's Shell", NULL));

	Item* axe = item("","", item(" AXE\n", "an axe that's on a bridge?", NULL));

	set_item ( room_12, fireflower );

	set_item ( room_21, koopashell );

	set_item ( room_24, axe );



	return room_11;
}
