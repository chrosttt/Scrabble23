## Description
This program is full-fledged Scrabble game in C++ with multiple different classes like Bag, Board, Dictionary, Player,
Square, and UserInterface to divide up the work involved.
All of the .cpp files are located in the src folder, and all of the .h files
are located in the lib folder. Additionally, some files have been included that were involved with making a GUI for the game in Qt, and images will be shown below.

## How to Run

### Command-Line Version
1.  **make**
2.  **./bin/Scrabble config/config.txt**

Additional notes: make clean will remove all files from the bin folder. The program compiles with no warnings, and has
no valgrind errors/memory leaks.

### GUI Version
All of the files necessary for making the GUI for Scrabble in Qt have been included, however, the game will not compile unless Qt is installed on your machine. Unfortunately, Qt is quite time-intensive to set up, so for now I have simply included screenshots of what the GUI looks like.

### Select the number of players
![alt text][Player_Selection]
### Initial Board State
![alt text][First_Turn]
### First Turn
![alt text][First_Turn_Played]
### Second Turn
![alt text][Second_Turn]
### How to Play
![alt text][How_To_Play]

[Player_Selection]: /images/Player_Selection.png "Logo Title Text 2"
[First_Turn]: /images/First_Turn.png "Logo Title Text 2"
[First_Turn_Played]: /images/First_Turn_Played.png "Logo Title Text 2"
[Second_Turn]: /images/Second_Turn.png "Logo Title Text 2"
[How_To_Play]: /images/How_To_Play.png "Logo Title Text 2"


