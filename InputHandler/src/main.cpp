#include <iostream>
#include <thread>
#include "can_writer.hpp"
#include "input_handler.hpp"
#include "can_encoder.hpp"

// https://github.com/siposcsaba89/socketcan-cpp

int main(){
  CanWriter& writer = CanWriter::getInstance();
  CanEncoder encoder;
  InputHandler keypresshandler;
  uint8_t data [8] = {0,0,0,0,0,0,0,0};
  int key_pressed;

  while (true) {
    key_pressed = keypresshandler.GetPressedKey();
    if(key_pressed != -1)
      if(key_pressed == 27)
        break;
      encoder.Encode(key_pressed,data);
    writer.SendFrame(1, data);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  return 0;
}