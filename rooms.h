#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


struct Room{
  char*desc;
  char* reqItem;
  Item* item;
  bool isBlocked;
  struct Room* south;
  struct Room* north;
  struct Room* east;
  struct Room* west;
  struct Room* up;
  struct Room* down;
};

typedef struct Room chamber;

chamber * new_room(char* desc, char* tool, Item *item_list, bool blocked, 
chamber *north, chamber *south,  chamber *east, chamber *west, chamber *up, chamber *down); //creates a new room


void display_room(chamber*room); //prints room description

void set_north(chamber*current,chamber*other); //sets other room to current's north

void set_south(chamber*current,chamber*other); //sets other room to current's south

void set_east(chamber*current,chamber*other); //sets other room to current's east

void set_west(chamber*current,chamber*other); //sets other room to current's west

void set_up(chamber*current,chamber*other); //sets other room to current's up

void set_down(chamber*current,chamber*other); //sets other room to current's down

bool contain(char*search,Item*curr_room); //checks if an item is inside a room

chamber* load_room(); //creates the rooms

void useItem(char* item, chamber* ptr); //uses the item, unblocks next room, and changes room description
