#include "CommandHandler.h"

CommandHandler::CommandHandler(Mode mode, uint8_t address) {
  this->mode = mode;
  this->address = address;
}

void CommandHandler::begin() {
  if (mode == MASTER) {
    Wire.begin();
  } else if (mode == SLAVE) {
    Wire.begin(address);
    Wire.onReceive([this](int numBytes) {
      this->handleCommands();
    });
  }
}

void CommandHandler::handleCommands() {
  if (mode == SLAVE && Wire.available()) {
    String command = Wire.readStringUntil('\0');
    for (uint8_t i = 0; i < numCommands; i++) {
      if (commands[i].command == command) {
        String parameter = "";
        if (Wire.available()) {
          parameter = Wire.readStringUntil('\0');
        }
        commands[i].function(parameter);
        break;
      }
    }
  }
}

void CommandHandler::addCommandHandler(String command, void (*function)(String)) {
  if (numCommands < MAX_COMMANDS) {
    commands[numCommands].command = command;
    commands[numCommands].function = function;
    numCommands++;
  }
}

void CommandHandler::sendCommand(uint8_t slaveAddress, String command, String parameter) {
  if (mode == MASTER) {
    Wire.beginTransmission(slaveAddress);
    Wire.write(command.c_str());
    if (parameter != "") {
      Wire.write(parameter.c_str());
    }
    Wire.endTransmission();
  }
}
