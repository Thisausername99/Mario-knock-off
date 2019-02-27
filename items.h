#include <stdio.h>
#include <stdlib.h>


struct Item{
  char*name;
  char*description;
  struct Item*next;
};

typedef struct Item Item;

struct Item*item(char* name1, char* description1, struct Item*input); //creates new item
  
char* item_name(struct Item*ptr); //gets item name
 
void print_list(struct Item*ptr); //prints the list of items in the room

char* item_description(struct Item*ptr); //gets item description
 
struct Item* item_take(char*name,Item *head); //takes an item from a list of items

void add_item(struct Item*bag, struct Item*new); //adds an item to another list
