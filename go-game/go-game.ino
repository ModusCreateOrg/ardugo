#include "ArduGo.h"
#include "Shell.h"
#include "Board.h"
#include "sidebar.h"

/*
 *  File: go-game.ino
 *  Purpose: Implementation of Arduino entry-points.
 *  Author: Don Anderson
 */

#if defined(ARDUGO_SHELL)
  Shell shell;
#endif

void setup() {

  arduboy.start();
  ardugo_setup();

#if defined(ARDUGO_SHELL)
  Serial.begin(9600);
  Shell shell;
#endif

}

void loop() {
  previousButtonState = currentButtonState;
  currentButtonState = arduboy.buttonsState();

#if defined(ARDUGO_SHELL)
    shell.loop();
#endif

  board.loop();
  arduboy.clear();
  board.render();
  render_sidebar(cur_sidebar);
  arduboy.display();

  injectButtonState = 0;
}
