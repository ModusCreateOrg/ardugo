# ArduGo

ArduGo is an implementation of a board for playing the game of Go. It is designed to run on the Arduboy game console.

The board has nine columns and rows, which is the right size for learning to play Go, and for fitting into the Arduino's limited resources.

You make the first play by moving the cursor with the arrow keys and pressing the "A"  button to place a black stone on the board.

The game will respond by placing a white stone on the board and then it is your turn again. You continue to alternate turns until one player wins.

For each player, two scores update on the game display. The one to the right of the player color is the number of living stones. Just below the is the count of prisoners that player has captured.

Pressing the "B" button restarts the game.

# ToDo

* Complete the rules for valid moves.
* Add end-game detection and scoring.
* Improve the algorithm for computer plays.

The release build of the game uses 45% of the flash and 55% of the ram. That should be enough resources to implement an engaging algorithm for computer play on the small 9x9 board. 

# Serial Shell

The shell is used to remotely control and monitor the application while it is running on the Arduboy. It communicates over the serial connection, helps find defects during development, and supports automated testing. The interpreter polls one command-line on each iteration of the event loop.  

Events injected using the shell will each activate in a different event loop. Multiple physical buttons may activate in one event loop, so the behavior is different.

Since the board has nine columns and rows, their argument values below range from 0 to 8. The address for the get-mem command is a 16-bit hexadecimal value with no leading '0x'. The second argument to the get-mem command is optional and causes the memory to render as the type. If the integer types (i,l) are uppercase, they will render in hexadecimal.

The interpreter evaluates these commands:

* dump-board
* print-board
* dump-vars
* print-vars
* place-stone row column (B|W)
* clear-board
* set-cursor row column
* button-up
* button-down
* button-left
* button-right
* button-A
* button-B
* get-mem address [(i|l|f|d)]

# Automated Testing

The automated test suite, written in Python, is used to test the application on the Arduboy using the shell over the serial connection. 

![Modus ArduGo](https://raw.githubusercontent.com/ModusCreateOrg/go-arduboy-game/master/images/web/ModusCreat-ArduGo-1-MODUS-article-featured.jpg "Modus ArduGo")

 





