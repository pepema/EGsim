#include <iostream>
#include <curses.h>
#include "socketcan_cpp.h"
#include <thread>

// https://github.com/siposcsaba89/socketcan-cpp

int main() {
  int can_id = 1;
  int can_length = 8;
  bool key_pressed = 0;

  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  int ch;
  nodelay(stdscr, TRUE);


  scpp::CanFrame cf_to_write;
  cf_to_write.id = can_id;
  cf_to_write.len = can_length;
  cf_to_write.data[can_length] = {};
  for(int i =0;i<8;i++){
    cf_to_write.data[i]=0;
  }
  scpp::SocketCan sockat_can;
  if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit (-1);
  }

  while (true) {

    if ((ch = getch()) == ERR) {
    } else {
      if(ch == 49){
        cf_to_write.data[7] = 1;
      } else if(ch == 50){
        cf_to_write.data[7] = 0;
      } else if(ch == 97){
        if (cf_to_write.data[6]>0) cf_to_write.data[6]-=0x10;
      } else if(ch == 65){
        if(cf_to_write.data[6]<0xA0) cf_to_write.data[6]+=0x10;
      }
       else {
        std::cout << "this key was pressed: " << ch << std::endl;
      }
    }
    auto write_sc_status = sockat_can.write(cf_to_write);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }


  return 0;
}