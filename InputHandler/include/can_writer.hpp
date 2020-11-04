#include "socketcan_cpp.h"
#include <iostream>

class CanWriter{
public:
  CanWriter();
  void SendFrame(int id, uint8_t* data);
private:
  scpp::CanFrame cf_to_write;
  scpp::SocketCan socket_can;
};