# CommandHandler Library

This library provides functionality for handling commands over I2C communication between Arduino boards.

## Installation

1. Download the latest version of the CommandHandler library from the [GitHub repository](https://github.com/yourusername/CommandHandler).
2. Extract the downloaded zip file and rename the folder to "CommandHandler".
3. Copy the "CommandHandler" folder into the "libraries" folder in your Arduino sketchbook directory.

## Usage

### For Master Arduino:

```cpp
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

### For Slave Arduino:

```cpp
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


### Supported Commands: 
Here are additional functions of the CommandHandler library that may be useful in your project:

1. `addCommandHandler(String command, void (*function)(String))`: Adds a command handler. When a command is received from the master, this function calls the corresponding function, passing parameters if any.

2. `sendCommand(uint8_t slaveAddress, String command, String parameter = "")`: Sends a command and parameters to the specified slave address over the I2C bus.

3. `begin()`: Initializes the library to operate in master or slave mode, depending on the specified parameters.

4. `handleCommands()`: Handles incoming commands in slave mode. Called in the loop() function to process incoming commands.

These functions provide you with the ability to customize command processing and command sending between the master and slave. You can use them to create more complex logic in your Arduino projects.