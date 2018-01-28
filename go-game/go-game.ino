#include "ArduGo.h"
#include "Shell.h"
#include "Board.h"
#include "sidebar.h"

/*
 *  File: go-game.ino
 *  Purpose: Implementation of Arduino entry-points.
 *  Author: Don Anderson
 */

void setup() {
  arduboy.start();
  ardugo_setup();

#if defined(ARDUGO_SHELL) || defined(ARDUGO_SERIAL) || defined(ARDUGO_DEBUG)
  Serial.begin(9600);
  Serial.println("Setup is finished.");
#endif

}

void loop() {
  previousButtonState = currentButtonState;
  currentButtonState = arduboy.buttonsState();

#ifdef ARDUGO_SHELL
  if(shell)
    shell->loop();
#endif

  board.loop();
  arduboy.clear();
  board.render();
  render_sidebar(cur_sidebar);
  arduboy.display();

  injectButtonState = 0;
}
