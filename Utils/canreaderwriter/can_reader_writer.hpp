#ifndef CANREADERWRITER_HPP
#define CANREADERWRITER_HPP

#include "socketcan_cpp.h"
#include <iostream>
#include <future>
#include <mutex>


/*struct FrameData{
    public:
    uint8_t data[8];
};*/


typedef union FrameData{
    struct __attribute__((packed)) ip_bits{
    unsigned int speed:8;
    unsigned int l_rpm:8;
    unsigned int m_rpm:8;
    unsigned int engine_status:1;
    unsigned int RESERVED_PADDING_1:7;
    unsigned int gear:1;
    unsigned int gear_number:1;
    unsigned int RESERVED_PADDING_2:6;
    //
    unsigned int RESERVED_PADDING_3:24;
    }input;
    struct __attribute__((packed)) op_bits{
    unsigned int hazard:1;
    unsigned int RESERVED_PADDING_1:7;
    unsigned int RESERVED_PADDING_2:24;
    unsigned int brake:8;
    unsigned int accel:8;
    unsigned int gear:1;
    unsigned int RESERVED_PADDING_3:7;
    unsigned int engine_status:1;
    unsigned int RESERVED_PADDING_4:7;
    //
    }output;

    uint8_t data[8];
};


/*struct DataBuffer{
  public:
  FrameData frame_data;
  //uint8_t frame_data[8];
  std::mutex mtx;
};*/


struct DataBuffer{
  public:
  FrameData frame_data; 
  std::mutex mtx;
};


class CanReaderWriter{
public:
  CanReaderWriter();
  void writeData(uint8_t id,const FrameData&);
  
  //FrameData getData(DataBuffer&);
  //uint8_t* getData();
  //void SendShutdownCommand(int id,const  FrameData & data);
  void readData(uint8_t id, DataBuffer &);
  //void updateWrite(FrameData);
  //uint8_t* getWriteData();
private:
  //void read();
  scpp::CanFrame cf_to_write;
  scpp::SocketCan socket_can;
  scpp::CanFrame cf_to_read;
  //DataBuffer read_data_buffer;
  //DataBuffer read_data_buffer;
  //FrameData write_data;
  //FrameData write_data;
  //uint8_t read_data_buffer[8];
};

#endif //CANREADERWRITER_HPP