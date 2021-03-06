#ifndef DATABUFFER_HPP
#define DATABUFFER_HPP

#include <iostream>
#include <mutex>

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
    }output;

    uint8_t data[8];
}frame_data_structure;

struct DataBuffer{
  public:
  FrameData frame_data; 
  std::mutex mtx;
};

namespace ntwrk
{
    static const std::string CHANNEL = "vcan0";
    static const uint8_t DATALENGTH = 8;
}

#endif