
#include "ArduGo.h"

void setup() {
  Serial.begin(9600);
  Serial.print("Setup\n");
  pinMode(LED_BUILTIN, OUTPUT);
  shell.exec("arg0 arg1 arg2 arg3 arg4");
}

void loop() {
  Serial.print("High\n");
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  Serial.print("Low\n");
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second

  shell.execSerial();

}
