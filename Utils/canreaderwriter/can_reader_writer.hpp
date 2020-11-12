#ifndef CANREADERWRITER_HPP
#define CANREADERWRITER_HPP

#include "socketcan_cpp.h"
#include <iostream>
#include <future>
#include <mutex>

struct FrameData{
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
  void SendFrame(int id,const  uint8_t* data);
  void read();
  FrameData getData();
  void SendShutdownCommand(int id,const  uint8_t* data);
  void updateReadData();
  uint8_t* getWriteData();
private:
  scpp::CanFrame cf_to_write;
  scpp::SocketCan socket_can;
  scpp::CanFrame cf_to_read;
  DataBuffer read_data_buffer;
  FrameData write_data;
};

#endif //CANREADERWRITER_HPP