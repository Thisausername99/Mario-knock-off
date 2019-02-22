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
  free(current);
}


Item*item(char* name1, char* description1, struct Item* input){
  struct Item*temp=(struct Item*)malloc(sizeof(struct Item));
  temp->name=name1;
  temp->description=description1;
  temp->next=input;
  return temp;
}



Item* item_take(char*name,Item *head){
  Item* result=NULL;
  Item* previous=head;
  
    /*if(head->next==NULL){  // nothing in the list
      return NULL;
    }

    else if(head->next->next==NULL && strcmp(head->next->name,name)==0){
      result=head->next;
      head->next=NULL;  //only one
      return result;
    }*/

    Item*curr=head->next; // skip the dummy node
    while(curr!=NULL){ 
      if(strcmp(name,curr->name)==0){
        //if(previous==head){ //remove first
        result=curr;
        previous->next=curr->next;
        
        result->next=NULL;
            /*char*temp_name=head->name;
            char*temp_desc=head->description;
            
            current=*current->next;
            head->name=head->next->name;
            head->description=head->next->description;
            head->next=head->next->next;
            
            result->name=temp_name;
            result->description=temp_desc;*/
        break;
      }
      
        /*else if(previous->next==curr){
          if(curr->next==NULL){ //at the end
            result=head;
            previous->next=NULL;
            break;
            }
          /*else // in the middle
            result=head;
            previous->next=previous->next->next;
            head=previous->next;
            break;
      }
    }*/
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