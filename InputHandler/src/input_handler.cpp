#include "input_handler.hpp"

InputHandler::InputHandler(){
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
}

int InputHandler::GetPressedKey(){
  this->ch = getch();
  return this->ch;
}
InputHandler::~InputHandler(){
  endwin();
}