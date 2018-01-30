# Modus ArduGo
Inspired by [EVADE](https://moduscreate.com/blog/announcing-evade-our-first-arduboy-game/), ArduGo implements a board for playing the game of Go. It is designed to run on the Arduboy game console.

The board has nine columns and rows, which is the right size for learning to play Go, and for fitting into the Arduino's limited resources.

You make the first play by moving the cursor with the arrow keys and pressing the "A"  button to place a black stone on the board.

The game will respond by placing a white stone on the board and then it is your turn again. You continue to alternate turns until one player wins.

For each player, two scores update on the game display. The one to the right of the player color is the number of living stones. Just below is the count of prisoners that player has captured.

Pressing the "B" button restarts the game.

![Modus ArduGo](https://raw.githubusercontent.com/ModusCreateOrg/go-arduboy-game/master/images/web/ModusCreat-ArduGo-1-MODUS-article-featured.jpg "Modus ArduGo")


# Technical
ArduGo contains an optional command shell for developers and external automated testing. The project includes an automated test suite, written in Python, primarily for testing the game rules and heuristics. 

### Serial Shell
The shell is used to remotely control and monitor the application while it is running on the Arduboy. It communicates over the serial connection, helps find defects during development, and supports automated testing. The interpreter polls one command-line on each iteration of the event loop.  

#### Events
Events injected using the shell will each activate in a different event loop. Multiple physical buttons may activate in one event loop, so the behavior is different.

#### Arguments
Since the board has nine columns and rows, their argument values below range from 0 to 8. The address for the get-mem command is a 16-bit hexadecimal value with no leading '0x'. The second argument to the get-mem command is optional and causes the memory to render as the type. If the integer types (i,l) are uppercase, they will render in hexadecimal.

#### Commands
The interpreter evaluates these commands:

* system
* dup-brd
* board
* dup-vars
* vars
* stone row column (b|w)
* clear
* cursor row column
* up
* down
* left
* right
* a
* b
* mem address [(i|l|f|d)]

# Development
The release build of the game uses 45% of the flash and 53% of the ram. There should be enough remaining resources to implement an engaging algorithm for computer play on the small 9x9 board.

### ToDo
* Complete the rules for valid moves.
* Add end-game detection and scoring.
* Improve the algorithm for computer plays.




 





