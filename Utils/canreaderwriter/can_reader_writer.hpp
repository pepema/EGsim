#ifndef CANREADERWRITER_HPP
#define CANREADERWRITER_HPP

#include "socketcan_cpp.h"
#include "data_buffer.hpp"

class CanReaderWriter{
public:
  CanReaderWriter();
  void writeData(uint8_t id,const FrameData&);
  void readData(uint8_t id, DataBuffer &);
private:
  scpp::CanFrame can_frame;
  scpp::SocketCan socket_can;
};

#endif //CANREADERWRITER_HPP