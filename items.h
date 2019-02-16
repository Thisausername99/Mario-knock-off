#include<stdio.h>
#include <stdlib.h>


struct Item{
  char*name;
  char*description;
  struct Item*next;
};

typedef struct Item Item;

struct Item*item(char* name1, char* description1, struct Item*input);
  
char* item_name(struct Item*ptr);
 
void print_list(struct Item*ptr);

char* item_description(struct Item*ptr);
 
struct Item* item_take(char*name, struct Item*head);
    