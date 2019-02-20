#include <stdio.h>
#include <string.h>
#include "items.h"
#include "rooms.h"
#include <stdbool.h>



chamber * new_room(char* desc, char* tool, Item *item_list, bool blocked, chamber *north, chamber *south,
	chamber *east, chamber *west, chamber *up, chamber *down){

	chamber*new_room=(chamber*)malloc(sizeof(chamber));
		
	new_room->desc=desc;
	new_room->reqItem=tool;
	new_room->item=item_list;
	new_room->isBlocked= blocked;
	

	new_room->south=south;
	new_room->north=north;
	new_room->east=east;
	new_room->west=west;
	new_room->up=up;
	new_room->down=down;

	return new_room;
}

void set_north(chamber* current,chamber* other){
	current->north=other;
}

void set_south(chamber* current,chamber* other){
	current->south=other;
}

void set_east(chamber* current,chamber* other){
	current->east=other;
}

void set_west(chamber* current,chamber* other){
	current->west=other;
}

void set_up(chamber* current,chamber* other){
	current->up=other;
}

void set_down(chamber* current,chamber* other){
	current->down=other;
}

void toggleBlocked(chamber* current){
	current->isBlocked=!(current->isBlocked);
}


void display_room(chamber* ptr){
	printf("%s",ptr->desc);
}



chamber* load_rooms(){

	chamber* room_11 = new_room("ROOM 1-1. The room is dim with no lighting except light pouring from the outside of the front gate you've entered from. The stone brick walls surrounds you.\nYou see a rectangular opening EAST of you.\n",
	NULL, NULL,false,NULL,NULL,NULL,NULL,NULL,NULL);

	chamber* room_12 = new_room("ROOM 1-2. The room's walls are smokey and dark. Metal sconces are chained to the walls and their flames lick up at crumbling ceiling.\nOne of the flames behaves differently from the others and doesn't burn you as you approach.\nOn further inspection, it isn't real fire but a Fire Flower emitting a shining light. An old wooden door NORTH of you blocks your way NORTH. It does not budge. You see a way WEST of you.\n",
	"Fire Flower", NULL,false,NULL,NULL,NULL,NULL,NULL,NULL);

	chamber* room_13 = new_room("ROOM 1-3. The first thing you notice are stones and dust falling from the rooms ceiling.\nThe ceiling in this room is falling apart and would most likely give if you even touched it, but you are too short as you are.\nThe room's floor gives way to dirt instead of stone. You see a way SOUTH and WEST of you.\n",
	"Mushroom", NULL,true,NULL,NULL,NULL,NULL,NULL,NULL);

	chamber* room_14 = new_room("ROOM 1-4. Intricate stone stairs spiral up into the ceiling. Small specks of dust and dirt float down from the floor above.\nYou can climb the stairs UP and you see a way EAST of you.\n",
	NULL, NULL,false,NULL,NULL,NULL,NULL,NULL,NULL);

	chamber* room_21 = new_room("ROOM 2-1. The floor is littered with discarded koopa shells and their putrid smell makes your eyes water.\nSome of the koopa shells still have skelettons inside them while other skeletons are chained to the wall.\nYou can't help but feel bad. There are stairs that lead DOWN and a way to continue SOUTH of you.\n",
	NULL, NULL,false,NULL,NULL,NULL,NULL,NULL,NULL);

	chamber* room_22 = new_room("ROOM 2-2. The room is empty except for crumbled and ripped up paper all over the floor. No writing desk is in the room.\nYou pick up a paper and inspect it, but it is indecipherable plans.\nThe poorly drawn plumber and dinosaur remind you of someone. You see a way NORTH and EAST.\n",
	NULL, NULL,false,NULL,NULL,NULL,NULL,NULL,NULL);

	chamber* room_23 = new_room("ROOM 2-3. Blocks cover the ground and there is suspicious mound of them in the corner of the room.\nThe blocks cannot be lifted and there's no way to break them with a Mushroom since you can't get under them.\nThe room is a dead-end. You see only the way you came from WEST of you.\n",
	"Koopa Shell", NULL,false,NULL,NULL,NULL,NULL,NULL,NULL);

	chamber* room_24 = new_room("ROOM 2-4. The room is huge and completely black. You're standing on the edge of a bridge that is chained above a lake of lava.\nA huge green lizard with a spiked shell looms on the other side of the bridge.\nFire pours from his unhinged mouth. Behind him is an axe as well as where the bridge is precariously chained.\n",
	"Axe", NULL,true,NULL,NULL,NULL,NULL,NULL,NULL);

	set_east(room_11,room_12);

	set_north(room_12,room_13);
	set_west(room_12,room_11);

	set_south(room_13,room_12);
	set_up(room_13,room_24);
	set_west(room_13,room_14);

	set_up(room_14,room_21);
	set_west(room_14,room_13);

	set_south(room_21,room_22);
	set_down(room_21,room_14);

	set_north(room_22,room_21);
	set_east(room_22,room_23);

	set_west(room_23,room_22);

	room_12->item_list = item("",""item("Fire Flower", "a Fire Flower", NULL));
	room_21->item_list = item("",""item("Koopa Shell", "a Koopa Shell", NULL));
	room_24->item_list = item("",""item("Axe", "an Axe", NULL));
	room_12->item_list = item("",""item("Mushroom", "a Mushroom", NULL));


	return room_11;
	

}






