#ifndef SignalDecoder_H
#define SignalDecoder_H
#include <iostream>
//#include <vector>
#include "can_reader_writer.hpp"

namespace cnsts
{
     //Constant Values

    static const uint OPCANID = 123;
    static const uint DATALENGTH = 8;
    static const uint SPEED = 0; //Default value for speed is 0 kmph
    
    //Default value for RPM is 0 rpm
    static const uint LRPM = 0;  //LSB for RPM
    static const uint MRPM = 0;  //MSB for RPM

    //Default value for Engine status 

    static const uint ENGSTATUS = 0; //Engine Off = 0

    //Default value for Gear

    static const uint GEAR = 0; // Gear in Neutral = 0
}

class SignalDecoder
{
private:
    FrameData frame_data_ip;
    //FrameData frame_data_op;
    //CANReader myReader;
public:
    SignalDecoder(/* args */);
    ~SignalDecoder();
    void setIpFrame(const FrameData &);
    bool getEngineStatus();
    uint8_t getAcceleration();
    uint8_t getGearinput();
    //void setOpFrame();
    //void updateFrameData();
    
};

#endif