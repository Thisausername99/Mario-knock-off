# project-2
Text Adventure by Huy Hoang, Veronica Gusev, and Nhan Le

https://youtu.be/Wf6B7o8bhrY

-game has exactly 8 rooms
-rooms can contain items
-an avatar with an inventory is made
-players can "look" at the room
-avatar can move rooms by using "go DIRECTION" where DIRECTION is NORTH, SOUTH, EAST, WEST, UP, DOWN
-avatar can pick up items with "take ITEM" where ITEM is MUSHROOM, FIRE FLOWER, KOOPA SHELL, AXE
-using items change the state of the room (unblocking them and changing their descriptions)
-avatar can drop items in their inventory and put them in the room
-the winning state is getting the AXE in room 2-4 and using it be defeat Bowser


The important details:
  play_game is the main driver in our code. It employs a while loop that takes in user input
  and doles out what to do with conditionals. If the input is take, then run the necessary
  functions for taking an item to occur. The loop ends when the game is over by user choice 
  (end) by quitting or is over by beating Bowser (completing the 4 ingame tasks).
  The other important part of play_game is that its initialized with a pointer to the user structure
  which houses a lot of important information such as where the user is located, his/her bag,
  along with other relvant information. With this pointer, changes to the current room, bag, etc 
  are able to be made. Such changes include putting an item into a room and removing it from the player's
  bag (dropping), or vice versa (taking). When a player uses an item, it's removed permanently from the game.
  A variety of effects can occur when a player uses an item that range from changing the room's description,
  to opening up a new pathway, to putting a new item into the room. 
  Less important details include the room functions and structure which allow for description changing.
  The rooms are initalized in the beginning with their items inside as well as what items are required
  for their challenges. 
  The items are also implemented as a linked list that would point to another. This is used in the
  user's bag and in the rooms. 
  If you get stuck, there's also a help option!


Function descriptions in adventure.c:
  initialize: creates the player character
  look: prints out the description of the room
  free_room: frees the room and any items in it
  freedom: frees the space after the game is over
  can_access: checks if the direction is blocked or not and moves to that room
  play_game: the user API

Function descriptions in rooms.c:
  new_room: creates a new room
  contain: checks whether or nor an item is in the room
  set_north: sets the room north of current room
  set_south: sets the room south of current room
  set_east: sets the room east of current room
  set_west: sets the room west of current room
  set_up: sets the room above current room
  set_down: sets the room below current room
  set_item: sets the room's item list to a new one
  set_description: sets the room's description to a new one
  display_room: prints the description of the room
  useItem: uses an item from the player's inventory and changes the room
  load_rooms: creates all the rooms and connects them to make the map

Function descriptions in items.c:
  item: creates new items
  item_name: gets item name
  item_description: gets item description
  print_list: prints the list of items
  item_take: takes item out of room or bag
  add_item: adds an item to the player's bag or room
