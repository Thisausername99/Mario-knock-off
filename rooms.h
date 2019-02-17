#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>

struct Room{
  char*desc;
  char*item_req;
  bool challenge;
  struct Item* item;
  struct Room* south;
  struct Room* north;
  struct Room* east;
  struct Room* west;
  struct Room* up;
  struct Room* down;
};

typedef struct Room chamber;

chamber * room(char* desc, char*tool, Item* items, chamber *north, chamber *south,
	chamber *east, chamber *west, chamber *up, chamber *down);

//void room_exit(struct Room* current, struct Room* other,char* direction);
  
bool state_conquered(char*item,chamber* current);

void room_item(chamber*room);

void display_room(chamber*room);

chamber*initiate_room();

void set_north(chamber*current,chamber*other);

void set_south(chamber*current,chamber*other);

void set_east(chamber*current,chamber*other);

void set_west(chamber*current,chamber*other);

void set_up(chamber*current,chamber*other);

void set_down(chamber*current,chamber*other);

void room_desc(chamber*current);
	