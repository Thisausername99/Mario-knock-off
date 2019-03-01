#include <stdio.h>
#include "items.h"
#include <string.h>


char* item_name(Item* input){ //gets item name
  return input->name;
}

char* item_description(Item* input){ //gets item description
  return input->description;
}


/**
  * @desc print every elements and their description in Item LinkedList
  * @param Item*head - head of the LinkedList
  * @param chamber*start - starting room
*/
void print_list(Item*head){ //prints list
  if(head->next == NULL){ //head is the dummy node, so next is first in list
    printf("NO ITEMS\n"); //room is empty if next thing is null
    return;
  }
 Item*current = head->next; //pointer to first item in list (skips dummy head)
  int i = 1; //item number
  while(current != NULL){ //traversing the item list
    printf("*Item %i is:%s*Description: %s \n", i, current->name, current->description);
    ++i; //increment the item number
    current = current->next;
  }
}


/**
  * @desc Initiate a LinkedList of Item
  * @param char*name - given name of Item
  * @param char*description - description of the item
  * @param Item*input- the nex Item of the LinkedList
  * @return head pointer of LinkedList
*/
Item*item(char* name, char* description, Item* input){ //creates new item
  struct Item*temp = (struct Item*)malloc(sizeof(struct Item)); //allocates space for item
  temp->name = name; //assigns
  temp->description = description; //the item's
  temp->next = input; //information
  
  return temp;
}



/**
  * @desc take an item out of a LinkedList of item
  * @param char*name - name of choosen Item
  * @param Item*head - head of the LinkedList
  * @return pointer to Item or NULL
*/
Item* item_take(char*name, Item *head){ //take an item from the room or bag
    Item* result = NULL; //pointer to the item we're taking
    Item* previous = NULL; //previous item in the list
    previous = head; //head will become curr's previous node
    Item* curr = head->next; // skip the dummy node
    while(curr != NULL){ //traversing item list
      if(strncmp(curr->name, name, strlen(curr->name)) == 0){ //item found
        result = curr; //result updated
        previous->next = previous->next->next; //removes item from list
        result->next = NULL; //removes item from the list
        break;
      }
      else{ //item was not the one we're taking
        previous = curr; //updates previous item
        curr = curr->next; //next item in list
      }
    }
    return result;
}



/**
  * @desc add an item to avatar inventory or room
  * @param Item * bag - pointer to head of LinkedList item will be added into 
  * @param Item * new - pointer to new item
*/
void add_item(Item*bag, Item*new){ //adds item to player's bag or room
  if(bag->next == NULL){ //nothing else in list
    bag->next = new; //adds new item to the player's bag
    return;
  }
  else{
    while(bag->next != NULL){ //finds last thing in list
      bag = bag->next; 
    } 
    bag->next = new; //adds new item to the player's bag
  }
}
