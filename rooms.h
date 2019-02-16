#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>

struct Room{
  char*desc;
  bool challenge;
  int  score;
  struct Item* item;
  struct Room* south;
  struct Room* north;
  struct Room* east;
  struct Room* west;
  struct Room* up;
  struct Room* down;
};

typedef struct Room chamber;

struct Room * room(char* desc, struct Item* items,struct Room *north, struct Room *south,
	struct Room *east, struct Room *west,struct Room *up, struct Room *down);

//void room_exit(struct Room* current, struct Room* other,char* direction);
  
bool state_conquered(struct Room* current);

void room_item(chamber*room);

void display_room(chamber*room);

chamber*initiate_room();
	