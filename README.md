Dede Korkut Adventures
A text-based adventure game where you explore rooms, collect items, battle enemies, and more. This game is built in C and provides a rich and interactive experience with various features such as inventory management, combat, and room navigation.

Features
Explore Rooms: Navigate through different rooms and interact with the environment.
Inventory System: Pick up, drop, and use items found in each room.
Combat: Fight enemies using weapons and manage your health.
Game State Saving & Loading: Save the game state to a file and load it later.
Command Menu: Use in-game commands to interact with the game world (e.g., look, inventory, move, help, save, load).

Getting Started
Prerequisites:
C Compiler (e.g., GCC)
A text editor (e.g., Visual Studio Code, Sublime Text, etc.)
Installation
Clone the repository to your local machine:

git clone https://github.com/yourusername/dede-korkut-adventures.git
cd dede-korkut-adventures
Compile the code:

bash
Copy code
gcc -o dede_korkut_adventures main.c
Run the game:

bash
Copy code
./dede_korkut_adventures
Game Commands
Here are the commands you can use in the game:

look: View the description of the current room.
inventory: View the items in your inventory.
status: View the player's current health and strength.
map: View a map of the game world.
move <direction>: Move to a new room in the specified direction (up, down, left, right).
pickup <item>: Pick up an item from the current room.
drop <item>: Drop an item from your inventory into the current room.
use <item>: Use an item from your inventory.
attack <item>: Use a weapon to attack an enemy in the current room.
save <filepath>: Save the current game state to a file.
load <filepath>: Load the game state from a saved file.
exit: Exit the game.
Example:
vbnet
Copy code
>> look
Room: room1_start
Description: A dark and eerie room with cobwebs and strange noises.
Item: key, value: 1, description: Key to open 7th door

>> inventory
Number of items: 1
Item: key, value: 1, description: Key to open 7th door
Saving and Loading Game State
You can save and load your progress in the game:

save <filepath>: Saves the current game state to the specified file.
load <filepath>: Loads the game state from a previously saved file.
Example:
ruby
Copy code
>> save savegame.dat
Game saved successfully!

>> load savegame.dat
Game loaded successfully!
Contributing
Feel free to fork the repository and create pull requests for any improvements, bug fixes, or new features. All contributions are welcome!

License
This project is open-source and available under the MIT License.
