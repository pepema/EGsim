#ifndef CANREADER_H
#define CANREADER_H

#include "socketcan_cpp.h"
// https://github.com/siposcsaba89/socketcan-cpp
//#include <vector>

struct FrameData{
    //std::vector<uint8_t> data[64];
    public:
    uint8_t data[8];
};

class CANReader
{
private:
    scpp::SocketCan socket_can;
    scpp::CanFrame can_frame;
public:
    CANReader();
    ~CANReader();
    void read();
    FrameData getData();
    /*static CANReader& getInstance()
    {
        static CANReader instance;
        return instance;
    }*/
    //CANReader(CANReader const&)       = delete;
    //void operator=(CANReader const&)  = delete;
};

#endif