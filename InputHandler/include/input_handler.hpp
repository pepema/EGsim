#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP
#include <curses.h>
#include <condition_variable>
#include "can_encoder.hpp"

class InputHandler
{
public:
  InputHandler();
  InputHandler(std::string s) : sequence(s){};
  ~InputHandler();
  int GetPressedKey();
  int GetPressedKey(std::string file);
  void Run(uint8_t *, bool &);
  std::condition_variable cv;
  bool input_ready = false;
  std::mutex m;

private:
  CanEncoder encoder;
  int ch, key_pressed, count = 0;
  std::string sequence;
};

#endif