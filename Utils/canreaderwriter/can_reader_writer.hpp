#ifndef CANREADERWRITER_HPP
#define CANREADERWRITER_HPP

#include "socketcan_cpp.h"
#include <iostream>
#include <mutex>

struct FrameData{
    //std::vector<uint8_t> data[64];
    public:
    uint8_t data[8];
};

struct DataBuffer{
  public:
  FrameData frame_data;
  std::mutex mtx;
};


class CanReaderWriter{
public:
  CanReaderWriter();
  void SendFrame(int id, uint8_t* data);
  void read();
  FrameData getData();
  void updateReadData();
  void updateWrite(FrameData);
private:
  scpp::CanFrame cf_to_write;
  scpp::SocketCan socket_can;
  scpp::CanFrame cf_to_read;
  DataBuffer read_data_buffer;
  FrameData write_data;
};

#endif //CANREADERWRITER_HPP