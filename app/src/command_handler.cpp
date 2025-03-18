#include "flickering_light/command_handler.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

CommandHandler::CommandHandler(int bpm) 
  : useTerminal(false), 
    colorIndex(0), 
    cursorHideDelay(sf::seconds(2)), 
    beats_per_minute(490), 
    cursorHidden(false) {

  beats_per_minute = bpm;

  desktopMode = sf::VideoMode::getDesktopMode();
  flickerDuration = sf::milliseconds(1000 * 60 / beats_per_minute / 2);

  window.create(desktopMode, "Flickering Light", sf::Style::Default);
  window.setMouseCursorVisible(true);
}

int CommandHandler::check_arguments(int argc, char* argv[]){
  if (argc < 2 || argc > 3) {
    std::cerr << "Usage: " << argv[0] << " start [terminal]\n";
    return 1;
  } else if (argc == 3 && std::string(argv[2]) == "terminal") {
    useTerminal = true;
    return 0;
  }
  return 0;
}

int CommandHandler::handle_command(const std::string& command) {
    if (command == "start") {
        if (useTerminal) {
            terminal_flicker(); 
        } else {
            handle_event(); 
        }
        return 0;
    } else {
        std::cerr << "Invalid command. Use 'start' or 'start terminal'.\n";
        return 1;
    }
}

void CommandHandler::handle_event() {
  while (window.isOpen()){
    while (window.pollEvent(event)){
      handle_close();
      handle_mouse();
    }
    update_clock();
    window.clear(colors[colorIndex]);
    window.display();
    sf::sleep(sf::milliseconds(10));
  }
}

void CommandHandler::handle_close() {
  if (event.type == sf::Event::Closed){
    window.close();
  } else if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Escape){
      window.close();
    }
  }
}
void CommandHandler::update_clock() {
    if (clock.getElapsedTime() >= flickerDuration){
      colorIndex = 1 - colorIndex;
      clock.restart();
    }
}
void CommandHandler::handle_mouse() {
  currentMousePos = sf::Mouse::getPosition(window);
  lastMousePos = sf::Mouse::getPosition(window);
  if (currentMousePos != lastMousePos){
    lastMousePos = currentMousePos;
    mouseClock.restart();
    if (cursorHidden) {
      window.setMouseCursorVisible(true);
      cursorHidden = false;
    }
  } else if (!cursorHidden && mouseClock.getElapsedTime() >= cursorHideDelay) {
    window.setMouseCursorVisible(false);
    cursorHidden = true;
  }
}

void CommandHandler::terminal_flicker(){
    std::int32_t sleep_time = flickerDuration.asMilliseconds();
    while (true){
        std::cout << "\033[44m\033[2J" << std::flush; // Blue background
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
        std::cout << "\033[40m\033[2J" << std::flush; // Black background
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }
}
