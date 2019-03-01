# project-2
Text Adventure

https://youtu.be/Wf6B7o8bhrY



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
