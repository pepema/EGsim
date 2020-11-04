#include "socketcan_cpp.h"
#include <iostream>

class CanWriter{
public:
  CanWriter(int id, int length);
  ~CanWriter()=default;
  scpp::CanFrame GetFrame();
  uint8_t* GetFrameData();
  void SendFrame(int id, uint8_t* data);
  scpp::SocketCan socket_can;
private:
  scpp::CanFrame cf_to_write;
};