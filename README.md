# Modus ArduGo
Inspired by [EVADE](https://moduscreate.com/blog/announcing-evade-our-first-arduboy-game/), ArduGo implements a Go board with some simple game rules. It is designed to be forked and create custom games that use a goban.

The board has nine columns and rows, which is the right size for learning to play Go, and for fitting into the Arduino's limited resources.

You make the first play by moving the cursor with the arrow keys and pressing the **A**  button to place a black stone on the board.

The game will respond by placing a white stone on the board and then it is your turn again. You continue to alternate turns until one player wins.

For each player, two scores update on the game display. The one to the right of the player color is the number of living stones. Just below is the count of prisoners that player has captured.

Pressing the **B** button restarts the game.

![Modus ArduGo](https://raw.githubusercontent.com/ModusCreateOrg/go-arduboy-game/master/images/web/ModusCreat-ArduGo-1-MODUS-article-featured.jpg "Modus ArduGo")

# Serial Shell
ArduGo contains an optional command shell for developers and external automated testing. 

The interpreter polls one command-line on each iteration of the event loop. Events injected using the shell will activate in a different event loop. Multiple physical buttons may activate in one event loop, so the behavior is different.

### Arguments
Since the board has nine columns and rows, their argument values below range from 0 to 8. The address for the **mem** command is a 16-bit hexadecimal value with no leading **0x**. The second argument to the **mem** command is optional and causes the memory to render as the type. If the integer types **(i,l)** are uppercase, they will dusplay in hexadecimal.

### Commands
The interpreter evaluates these commands:

* system
* dmp-brd
* board
* dmp-vars
* vars
* stone *row column (b|w)*
* clear
* cursor *row column*
* up
* down
* left
* right
* a
* b
* mem *address [(i|l|f|d)]*




 





