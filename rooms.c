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



void set_description(chamber* current,char* new){ //sets the room below the current room
	current->desc = new;
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



void toggleBlocked(chamber* current){ //changes the blocked status of the room
	
	if(current->north !=NULL && current->north->isBlocked == true){
  		current->north->isBlocked = false; //unblocks north room
  		
   	}
  	else if(current->south !=NULL && current->south->isBlocked == true){
  		current->south->isBlocked = false; //unblocks south room
  		
  	}
  	else if(current->east !=NULL && current->east->isBlocked == true){
  		current->east->isBlocked = false; //unblocks east room
  		
  	}
  	else if(current->west !=NULL && current->west->isBlocked == true){
  		current->west->isBlocked = false; //unblocks west room
  		
  	}
  	else if(current->up !=NULL && current->up->isBlocked == true){
  		current->up->isBlocked = false; //unblocks above room
  		
  	}
 	else if(current->down !=NULL && current->down->isBlocked == true){
  		current->down->isBlocked = false; //unblocks lower room
  	}
  }

void display_room(chamber* ptr){ //prints the description of the room
	printf("%s", ptr->desc);
}


void useItem(char* new, chamber* ptr){ //prints the description of the room
	printf("%s",new);
	if(strcmp("Fire Flower\n",new) == 0 ){
		printf("You hold the FIRE FLOWER in front of the wooden door and the FLOWER shoots out a fireball.\nThe fireball crashes into the door, combusting it instantly.\n" );
		set_description(ptr, "ROOM 1-2. The room's walls are smokey and dark. Metal sconces are chained to the walls and their flames lick up at crumbling ceiling.\nOne of the sconces is unlit. You see a way WEST and NORTH of you where a door used to be.\n");	
	}

	else if( strcmp("Koopa Shell\n", new) == 0  ){
		printf("You kick the KOOPA SHELL into the suspicious pile of blocks. They break one by one and reveal a MUSHROOM that was hidden beneath.\n" );
		set_description(ptr, "Where there used to be a pile of blocks there is a MUSHROOM.\n");
	}

	else if( strcmp(new, "Mushroom\n") ==0 ){
		printf("You hold the FIRE FLOWER in front of the wooden door and the FLOWER shoots out a fireball.\nThe fireball crashes into the door, combusting it instantly.\n" );
		set_description(ptr, "ROOM 1-2. The room's walls are smokey and dark. Metal sconces are chained to the walls and their flames lick up at crumbling ceiling.\nOne of the flames behaves differently from the others and doesn't burn you as you approach.\nOn further inspection, it isn't real fire but a FIRE FLOWER emitting a shining light. You see a way WEST and NORTH of you where a door used to be.\n");
	}

	else if( strcmp(new, "Axe\n") == 0 ){
		printf("You hold the FIRE FLOWER in front of the wooden door and the FLOWER shoots out a fireball.\nThe fireball crashes into the door, combusting it instantly.\n" );
		set_description(ptr, "ROOM 1-2. The room's walls are smokey and dark. Metal sconces are chained to the walls and their flames lick up at crumbling ceiling.\nOne of the flames behaves differently from the others and doesn't burn you as you approach.\nOn further inspection, it isn't real fire but a FIRE FLOWER emitting a shining light. You see a way WEST and NORTH of you where a door used to be.\n");
	}

}






chamber* load_rooms(){ //creates all the rooms and connects them

	Item*item_12 = item("","", item("Fire Flower", "A VITAL WEAPON", item("Mushroom","To ENLARGE",NULL))); //creates fire flower for room 1-2

	 //creates fire flower for room 1-2

	//Item*item_11 = item("","", item("Mushroom", "TO ENLARGE", NULL)); //creates mushroom for room 1-1

	chamber* room_11 = new_room("ROOM 1-1. The room is dim with no lighting except light pouring from the outside of the front gate you've entered from. The stone brick walls surrounds you.\nYou see a rectangular opening EAST of you.\n",
	NULL,NULL,false,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 1-1, the starting room

	chamber* room_12 = new_room("ROOM 1-2. The room's walls are smokey and dark. Metal sconces are chained to the walls and their flames lick up at crumbling ceiling.\nOne of the flames behaves differently from the others and doesn't burn you as you approach.\nOn further inspection, it isn't real fire but a Fire Flower emitting a shining light. An old wooden door NORTH of you blocks your way NORTH. It does not budge. You see a way WEST of you.\n",
	"Fire Flower", item_12,false,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 1-2

	chamber* room_13 = new_room("ROOM 1-3. The first thing you notice are stones and dust falling from the rooms ceiling.\nThe ceiling in this room is falling apart and would most likely give if you even touched it, but you are too short as you are.\nThe room's floor gives way to dirt instead of stone, needed MUSHROOM. You see a way SOUTH and WEST of you.\n",
	"Mushroom", NULL,true,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 1-3

	chamber* room_14 = new_room("ROOM 1-4. Intricate stone stairs spiral up into the ceiling. Small specks of dust and dirt float down from the floor above.\nYou can climb the stairs UP and you see a way EAST of you.\n",
	NULL, NULL,true,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 1-4

	chamber* room_21 = new_room("ROOM 2-1. The floor is littered with discarded koopa shells and their putrid smell makes your eyes water.\nSome of the koopa shells still have skelettons inside them while other skeletons are chained to the wall.\nYou can't help but feel bad. There are stairs that lead DOWN and a way to continue SOUTH of you.\n",
	NULL, NULL,false,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 2-1

	chamber* room_22 = new_room("ROOM 2-2. The room is empty except for crumbled and ripped up paper all over the floor. No writing desk is in the room.\nYou pick up a paper and inspect it, but it is indecipherable plans.\nThe poorly drawn plumber and dinosaur remind you of someone. You see a way NORTH and EAST.\n",
	NULL, NULL,true,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 2-2

	chamber* room_23 = new_room("ROOM 2-3. Blocks cover the ground and there is suspicious mound of them in the corner of the room.\nThe blocks cannot be lifted and there's no way to break them with a Mushroom since you can't get under them.\nThe room is a dead-end. You see only the way you came from WEST of you.\n",
	"Koopa Shell", NULL,true,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 2-3

	chamber* room_24 = new_room("ROOM 2-4. The room is huge and completely black. You're standing on the edge of a bridge that is chained above a lake of lava.\nA huge green lizard with a spiked shell looms on the other side of the bridge.\nFire pours from his unhinged mouth. Behind him is an axe as well as where the bridge is precariously chained.\n",
	"Axe", NULL,false,NULL,NULL,NULL,NULL,NULL,NULL); //creates room 2-4
 	

	room_11->item=item("","", item("Fire Flower", "A VITAL WEAPON", item("Mushroom","To ENLARGE",NULL)));
	room_12->item=item("","",item("Koopa Shell","Bouncy stuff",NULL));
	room_22->item=item("","",item("Axe","Mysterious Obj",NULL));


	set_east(room_11, room_12); //connects room 1-1 and 1-2

	set_north(room_12, room_13); //connects room 1-2 with 1-3
	set_west(room_12, room_11); //connects room 1-2 with 1-1

	set_south(room_13, room_12); //connects room 1-3 with 1-2
	set_up(room_13, room_24); //connects room 1-3 with 2-4
	set_west(room_13, room_14); //connects room 1-3 with 1-4

	set_up(room_14, room_21); //connects room 1-4 with 2-1
	set_west(room_14, room_13); //connects room 1-4 with 1-3
 
	set_south(room_21, room_22); //connects room 2-1 with 2-2
	set_down(room_21, room_14); //connects room 2-1 with 1-4

	set_north(room_22, room_21); //connects room 2-2 with 2-1
	set_east(room_22, room_23); //connects room 2-2 with 2-3

	set_west(room_23, room_22); //connects room 2-3 with 2-2

	return room_11;
}
