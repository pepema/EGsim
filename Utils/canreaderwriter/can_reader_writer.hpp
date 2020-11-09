#ifndef CANREADERWRITER_HPP
#define CANREADERWRITER_HPP

#include "socketcan_cpp.h"
#include <iostream>

struct FrameData{
    //std::vector<uint8_t> data[64];
    public:
    uint8_t data[8];
};


class CanReaderWriter{
public:
  CanReaderWriter();
  void SendFrame(int id, uint8_t* data);
  void read();
  FrameData getData();
private:
  scpp::CanFrame cf_to_write;
  scpp::SocketCan socket_can;
  scpp::CanFrame cf_to_read;
};

#endif //CANREADERWRITER_HPP