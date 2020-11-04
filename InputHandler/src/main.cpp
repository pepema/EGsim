#include <iostream>
#include <thread>
#include "can_writer.hpp"
#include "input_handler.hpp"

// https://github.com/siposcsaba89/socketcan-cpp

int main() {
  CanWriter writer(1,8);
  InputHandler keypresshandler;
  uint8_t data [8] = {0,0,0,0,0,0,0,3};

  while (true) {
    //keypresshandler.EncodeKeyPresses(writer.GetFrameData());
    writer.SendFrame(1, data);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  return 0;
}