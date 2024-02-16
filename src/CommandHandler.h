#ifndef CommandHandler_h
#define CommandHandler_h

#include <Arduino.h>
#include <Wire.h>

class CommandHandler {
  public:
    enum Mode {MASTER, SLAVE};
    
    CommandHandler(Mode mode, uint8_t address = 0);
    void begin();
    void handleCommands();
    void addCommandHandler(String command, void (*function)(String) = NULL);
    void sendCommand(uint8_t slaveAddress, String command, String parameter = "");
  
  private:
    static const uint8_t MAX_COMMANDS = 10;
    struct Command {
      String command;
      void (*function)(String);
    } commands[MAX_COMMANDS];
    uint8_t numCommands = 0;
    uint8_t address;
    Mode mode;
};

#endif
