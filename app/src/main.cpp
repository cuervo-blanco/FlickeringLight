#include <string>
#include "flickering_light/command_handler.h"

int main(int argc, char* argv[]){
    CommandHandler commandHandler(490);
    int result = commandHandler.check_arguments(argc, argv);
    if (result != 0) {
      return result;
    }
    std::string command(argv[1]);
    return commandHandler.handle_command(command);
}

