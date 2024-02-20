#include <iostream>
#include <chrono>
#include <thread>
#include <string>

// Function to set the terminal background color
void setBackgroundColor(bool isBlue) {
    if (isBlue) {
        std::cout << "\033[44m";
        std::cout << std::flush;
    } else {
        std::cout << "\033[40m";
        std::cout << std::flush;
    }
    std::cout << "\033[2J";
}

int main(int argc, char* argv[]) {

    if (argc != 2){
        std::cerr << "Usage: " << argv[0] << " start|stop\n";
        return 1;
    }

    std::string command(argv[1]);

    if (command == "start") {
        auto flickerDuration = std::chrono::milliseconds(1000 * 60 / 490 / 2);

        while (true) {
            setBackgroundColor(true);
            std::this_thread::sleep_for(flickerDuration);
            setBackgroundColor(false);
            std::this_thread::sleep_for(flickerDuration);
        }

    } else if (command == "stop") {

        setBackgroundColor(false);

    } else {
        std::cerr << "Invalid command.\n";
        return 1;
    }

    return 0;
}
