#include <stdio.h>
#include "items.h"
#include <string.h>


char* item_name(Item* input){
  return input->name;
}

char* item_description(Item* input){
  return input->description;
}


void print_list(Item*head){
  if(head->next==NULL){printf("ROOM IS EMPTY");return;}

  struct Item*current=head->next;
  int i=1;
  while(current!=NULL){
    printf("*Item %i is: %s \n*Description: %s \n",i,current->name,current->description);
    ++i;
    current=current->next;
  }
}


Item*item(char* name, char* description, struct Item* next){
  struct Item*temp=(struct Item*)malloc(sizeof(struct Item));
  temp->name=name;
  temp->description=description;
  temp->next=next;
  return temp;
}



Item* item_take(char*name,Item *head){
  Item* result=NULL;
  Item* previous=head;
  Item*curr=head->next; // skip the dummy node
    
  while(curr!=NULL){ 
    if(strcmp(name,curr->name)==0){
        result=curr;
        previous->next=curr->next;
        result->next=NULL;
        break;
      }

      else{
        previous=curr;
        curr=curr->next;
      }
    }
    return result;
  }


void add_item(struct Item*bag, struct Item*new){ //pass a pointer to add the item
  if(bag->next==NULL){
    bag->next = new;
    return;
  }
  else{
    while(bag->next!= NULL){
      bag=bag->next;
    } 
    bag->next=new;
  }
}