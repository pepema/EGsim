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

void InputHandler::Run(uint8_t* data, bool& exit){
  while(1){
    key_pressed = this->GetPressedKey();
    if(key_pressed != -1 && key_pressed != 27)
      encoder.Encode(key_pressed,data);
    else if (key_pressed == 27) {
      exit = 1;
      break;
    }
    exit = 0;
  }
}

InputHandler::~InputHandler(){
  endwin();
}