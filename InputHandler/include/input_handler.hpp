#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP
#include <curses.h>
#include "can_encoder.hpp"

class InputHandler{
public:
  InputHandler();
  ~InputHandler();
  int GetPressedKey();
  bool Run(uint8_t*);
private:
  CanEncoder encoder;
  int ch, key_pressed;
};

#endif