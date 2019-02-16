#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>

struct Room{
  char*description;
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

struct Room * room(char* description, struct Item* items,struct Room *north, struct Room *south,
	struct Room *east, struct Room *west,struct Room *up, struct Room *down);

//void room_exit(struct Room* current, struct Room* other,char* direction);
  
bool state_conquered(struct Room* current);

void room_item(chamber*room);

chamber*initiate_room();
	