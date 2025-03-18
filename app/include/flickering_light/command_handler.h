#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <future>
#include <chrono>
#include <thread>
#include <string>

class CommandHandler {
  public: 
    CommandHandler(int bpm);

    int check_arguments(int argc, char* argv[]);
    int handle_command(const std::string& command);

  private:
    void terminal_flicker();
    void update_clock();

    void handle_event();
    void handle_close();
    void handle_mouse();

    int beats_per_minute;
    int colorIndex = 0;
    bool useTerminal;
    bool cursorHidden;

    sf::Clock clock;
    sf::Clock mouseClock;
    sf::Time flickerDuration;
    sf::Time cursorHideDelay;
    sf::Vector2i currentMousePos;
    sf::Vector2i lastMousePos;
    sf::Color colors[2] = {sf::Color::Blue, sf::Color::Black};

    sf::VideoMode desktopMode;
    sf::RenderWindow window;
    sf::Event event;
};
#endif
