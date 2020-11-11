#include "input_handler.hpp"

InputHandler::InputHandler(){
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, FALSE);
}

int InputHandler::GetPressedKey(){
  this->ch = getch();
  return this->ch;
}

int InputHandler::GetPressedKey(std::string s){
  this->ch = s[count];
  count++;
  return this->ch;
}

void InputHandler::Run(uint8_t* data, bool& exit){
  while(1){
    key_pressed = this->GetPressedKey();
    if(encoder.ValidKey(key_pressed,data)){    
      {
        std::lock_guard<std::mutex> lk(m);
        input_ready = true;
        if(key_pressed == 27){
          exit = 1;
        }
        encoder.Encode(key_pressed,data);
      }
    cv.notify_all();
    }
    if(exit) break;
  }
}

InputHandler::~InputHandler(){
  endwin();
}