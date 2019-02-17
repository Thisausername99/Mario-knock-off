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
  
    if(head->next==NULL){  // nothing in the list
      return NULL;
    }

    else if(head->next->next==NULL && strcmp(head->next->name,name)==0){
      result=head->next;
      head->next=NULL;  //only one
      return result;
    }

    head=head->next; // skip the dummy node
    while(head!=NULL){ 
      if(strcmp(name,head->name)==0){
        if(previous==NULL){ //remove first
            result=head->next;
            char*temp_name=head->name;
            char*temp_desc=head->description;
            
            //*current=*current->next;
            head->name=head->next->name;
            head->description=head->next->description;
            head->next=head->next->next;
            
            result->name=temp_name;
            result->description=temp_desc;
          break;
        }
        else if(previous->next==head){
          if(head->next==NULL){ //at the end
            result=head;
            head->next=NULL;
            break;
            }
          else // in the middle
            result=head;
            previous->next=previous->next->next;
            head=previous->next;
            break;
      }
    }
    previous=head;
    head=head->next;
  }
  	free(previous);
  	//free(current);
    return result;
}
