#include "input_handler.hpp"
#include <thread>

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
  count++;
  if (count >= s.length()) {
    std::this_thread::sleep_for(std::chrono::seconds(3)); 
    return 27;
  }
  this->ch = s[count-1];
  if(isdigit(this->ch)) std::this_thread::sleep_for(std::chrono::seconds(this->ch-'0'));
  return this->ch;
}

void InputHandler::Run(uint8_t* data, bool& exit){
  while(1){
    key_pressed = this->GetPressedKey();
    if (sequence.length() != 0 && count < sequence.length()) key_pressed = this->GetPressedKey(sequence);
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