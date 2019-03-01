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
chamber *north, chamber *south,  chamber *east, chamber *west, chamber *up, chamber *down);


void display_room(chamber*room);

void set_north(chamber*current,chamber*other);

void set_south(chamber*current,chamber*other);

void set_east(chamber*current,chamber*other);

void set_west(chamber*current,chamber*other);

void set_up(chamber*current,chamber*other);

void set_down(chamber*current,chamber*other);

bool contain(char*search,Item*curr_room);

chamber* load_room();

void useItem(char* item, chamber* ptr);
