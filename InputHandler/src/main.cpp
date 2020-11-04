#include <iostream>
#include <thread>
#include "can_writer.hpp"
#include "input_handler.hpp"
#include "can_encoder.hpp"

int main(){
  CanWriter writer;
  CanEncoder encoder;
  InputHandler key_press_handler;
  uint8_t data [8] = {0,0,0,0,0,0,0,0};
  int key_pressed;

  while (true && key_pressed != 27) {
    key_pressed = key_press_handler.GetPressedKey();
    if(key_pressed != -1)
      encoder.Encode(key_pressed,data);
    writer.SendFrame(1, data);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  return 0;
}