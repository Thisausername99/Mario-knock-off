#include <stdio.h>
#include <string.h>
#include "items.h"
#include "rooms.h"




chamber * new_room(char* desc, char*tool, Item *item_list, chamber *north, chamber *south,
	chamber *east, chamber *west, chamber *up, chamber *down){

	chamber*new_room=(chamber*)malloc(sizeof(chamber));
	
	new_room->challenge=false;
	
	new_room->desc=desc;
	new_room->item=item_list;
	new_room->item_req=tool;

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


void display_room(chamber* ptr){
	printf("%s",ptr->desc);
}


bool state_conquered(char* item,chamber* current){
	if(strcmp(item,current->item_req)==0){
		current->challenge=true;
		current->desc="Room mission has been completed";
		return true;
	}
	return false;
}


chamber* load_rooms(){

	chamber* room_11 = new_room("ROOM 1-1. The room is dim with no lighting except light pouring from the outside of the front gate you've entered from. The stone brick walls surrounds you. You see a rectangular opening EAST of you.",
	NULL, NULL,NULL,NULL,NULL,NULL,NULL,NULL);

	chamber* room_12 = new_room("ROOM 1-2. The room's walls are smokey and dark. Metal sconces are chained to the walls and their flames lick up at crumbling ceiling. One of the flames behaves differently from the others and doesn't burn you as you approach. On further inspection, it isn't real fire but a Fire Flower emitting a shining light. An old wooden door NORTH of you blocks your way NORTH. It does not budge. You see a way WEST of you.",
	"Fire Flower", NULL,NULL,NULL,NULL,NULL,NULL,NULL);

	chamber* room_13 = new_room("ROOM 1-3. The first thing you notice are stones and dust falling from the rooms ceiling. The ceiling in this room is falling apart and would most likely give if you even touched it, but you are too short as you are. The room's floor gives way to dirt instead of stone. You see a way SOUTH and WEST of you.",
	"Mushroom", NULL,NULL,NULL,NULL,NULL,NULL,NULL);

	chamber* room_14 = new_room("ROOM 1-4. Intricate stone stairs spiral up into the ceiling. Small specks of dust and dirt float down from the floor above. You can climb the stairs UP and you see a way EAST of you.",
	NULL, NULL,NULL,NULL,NULL,NULL,NULL,NULL);

	chamber* room_21 = new_room("ROOM 2-1. The floor is littered with discarded koopa shells and their putrid smell makes your eyes water. Some of the koopa shells still have skelettons inside them while other skeletons are chained to the wall. You can't help but feel bad. There are stairs that lead DOWN and a way to continue SOUTH of you.",
	NULL, NULL,NULL,NULL,NULL,NULL,NULL,NULL);

	chamber* room_22 = new_room("ROOM 2-2. The room is empty except for crumbled and ripped up paper all over the floor. No writing desk is in the room. You pick up a paper and inspect it, but it is indecipherable plans. The poorly drawn plumber and dinosaur remind you of someone. You see a way NORTH and EAST.",
	NULL, NULL,NULL,NULL,NULL,NULL,NULL,NULL);

	chamber* room_23 = new_room("ROOM 2-3. Blocks cover the ground and there is suspicious mound of them in the corner of the room. The blocks cannot be lifted and there's no way to break them with a Mushroom since you can't get under them. The room is a dead-end. You see only the way you came from WEST of you.",
	"Koopa Shell", NULL,NULL,NULL,NULL,NULL,NULL,NULL);

	chamber* room_24 = new_room("ROOM 2-4. The room is huge and completely black. You're standing on the edge of a bridge that is chained above a lake of lava. A huge green lizard with a spiked shell looms on the other side of the bridge. Fire pours from his unhinged mouth. Behind him is an axe as well as where the bridge is precariously chained.",
	"Axe", NULL,NULL,NULL,NULL,NULL,NULL,NULL);

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


	return room_11;
	

}






