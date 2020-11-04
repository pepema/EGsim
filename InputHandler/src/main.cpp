#include <iostream>
#include <thread>
#include "can_writer.hpp"
#include "input_handler.hpp"

// https://github.com/siposcsaba89/socketcan-cpp

int main() {
  scpp::SocketCan sockat_can;
  if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit (-1);
  }

  CanWriter writer(1,8);
  /*int length = 8;
  int id = 1;
  scpp::CanFrame cf_to_write;
  cf_to_write.id = id;
  cf_to_write.len = length;
  cf_to_write.data[length] = {};
  for(int i =0;i<length;i++){
    cf_to_write.data[i]=0;
  }*/
  InputHandler keypresshandler;;

  while (true) {
    //scpp::CanFrame f = writer.GetFrame();
    keypresshandler.EncodeKeyPresses(writer.GetFrameData());
    auto write_sc_status = sockat_can.write(writer.GetFrame());
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  return 0;
}