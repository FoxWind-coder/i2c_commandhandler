/*
To switch between Master and Slave mode, define the MASTER_MODE macro as 1 to enable Master mode,
or as 0 to enable Slave mode. Uncomment the desired mode and comment out the other one.
*/

#define MASTER_MODE 1

#ifdef MASTER_MODE
  #include <Arduino.h>
  #include <Wire.h>
  #include "CommandHandler.h"

  CommandHandler commandHandler(CommandHandler::MASTER); // Set the library to Master mode

  void setup() {
    Serial.begin(9600);
    commandHandler.begin();
  }

  void loop() {
    // Master mode example code
    commandHandler.sendCommand(8, "toggle");
    delay(1000);
    commandHandler.sendCommand(8, "on");
    delay(1000);
    commandHandler.sendCommand(8, "off");
    delay(1000);
  }
#else
  #include <Arduino.h>
  #include <Wire.h>
  #include "CommandHandler.h"

  const int ledPin = LED_BUILTIN;

  CommandHandler commandHandler(CommandHandler::SLAVE, 8); // Set the library to Slave mode with address 8

  void setup() {
    pinMode(ledPin, OUTPUT);
    commandHandler.begin();
    commandHandler.addCommandHandler("toggle", toggleLED);
    commandHandler.addCommandHandler("on", turnOnLED);
    commandHandler.addCommandHandler("off", turnOffLED);
    Serial.begin(9600);
  }

  void loop() {
    // Slave mode example code
    commandHandler.handleCommands();
  }

  void toggleLED(String parameter) {
    digitalWrite(ledPin, !digitalRead(ledPin));
  }

  void turnOnLED(String parameter) {
    digitalWrite(ledPin, HIGH);
  }

  void turnOffLED(String parameter) {
    digitalWrite(ledPin, LOW);
  }
#endif
