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

bool InputHandler::Run(uint8_t* data){
  key_pressed = this->GetPressedKey();
  if(key_pressed != -1 && key_pressed != 27)
    encoder.Encode(key_pressed,data);
  else if (key_pressed == 27) return 0;
  return 1;
}

InputHandler::~InputHandler(){
  endwin();
}