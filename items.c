#include <stdio.h>
#include "items.h"
#include <string.h>


char* item_name(struct Item* input){
	return input->name;
}

char* item_description(struct Item* input){
	return input->description;
}


void print_list(struct Item*head){
	struct Item*current=head->next;
  int i=1;
  while(current!=NULL){
		printf("*Item %i is: %s \n*Description: %s \n",i,current->name,current->description);
		++i;
		current=current->next;
	}
  free(current);
}


struct Item*item(char* name1, char* description1, struct Item* input){
    struct Item*temp=(struct Item*)malloc(sizeof(struct Item));
    temp->name=name1;
    temp->description=description1;
    temp->next=input;
    return temp;
}



struct Item* item_take(char*name,struct Item *head){
	  struct Item* result=NULL;
    struct Item* previous=NULL;
    struct Item* current=head->next;
    if(head->next==NULL){  // nothing in the list
      return head->next;
    }

    else if(head->next->next==NULL && strcmp(head->next->name,name)==0){
      result=head->next;
      head->next=NULL;  //only one
      return result;
    }

    while(current!=NULL){ 
      if(strcmp(name,current->name)==0){
        if(previous==NULL){ //remove first
            result=current->next;
            char*temp_name=current->name;
            char*temp_desc=current->description;
            
            current->name=current->next->name;
            current->description=current->next->description;
            current->next=current->next->next;
            
            result->name=temp_name;
            result->description=temp_desc;
          break;
        }
        else if(previous->next==current){
          if(current->next==NULL){ //at the end
            result=current;
            previous->next=NULL;
            break;
            }
          else // in the middle
            result=current;
            previous->next=previous->next->next;
            current=previous->next;
            break;
      }
    }
    previous=current;
    current=current->next;
  }
  	free(previous);
  	free(current);
    return result;
}
