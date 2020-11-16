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
  //uint8_t frame_data[8];
  std::mutex mtx;
};


class CanReaderWriter{
public:
  CanReaderWriter();
  void SendFrame(int id,const  uint8_t* data);
  void read();
  FrameData getData();
  //uint8_t* getData();
  void SendShutdownCommand(int id,const  uint8_t* data);
  void updateReadData();
  //void updateWrite(FrameData);
  uint8_t* getWriteData();
private:
  scpp::CanFrame cf_to_write;
  scpp::SocketCan socket_can;
  scpp::CanFrame cf_to_read;
  DataBuffer read_data_buffer;
  FrameData write_data;
  //uint8_t read_data_buffer[8];
};

#endif //CANREADERWRITER_HPP