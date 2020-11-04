#include "socketcan_cpp.h"
#include <iostream>

class CanWriter{
public:
static CanWriter& getInstance(){
  static CanWriter instance;
  instance.Init();
  return instance;
}
  void SendFrame(int id, uint8_t* data);
private:
  void Init();
  CanWriter(){};
  CanWriter(CanWriter const &);
  void operator=(CanWriter const&);
  scpp::CanFrame cf_to_write;
  scpp::SocketCan socket_can;
};