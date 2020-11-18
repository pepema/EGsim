#ifndef Signals_HPP
#define Signals_HPP
#include <iostream>
//#include <vector>
#include "can_reader_writer.hpp"

namespace cnsts
{
     //Constant Values

    static const uint kOpCanId = 2;
    static const uint kDataLength = 8;
    static const uint kSpeed = 0; //Default value for speed is 0 kmph
    
    //Default value for RPM is 0 rpm
    static const uint kLRpm = 0;  //LSB for RPM
    static const uint kMRpm = 0;  //MSB for RPM

    //Default value for Engine status 

    static const uint kEngineStatus = 0; //Engine Off = 0

    //Default value for Gear

    static const uint kGear = 0; // Gear in Neutral = 0
}

class Signals
{
private:
    FrameData frame_data_ip;
    //uint8_t frame_data_ip[8];
public:
    Signals();
    ~Signals();
    void setFrame(const FrameData &);
    //void setIpFrame(const uint8_t *);
    bool getEngineStatus();
    uint8_t getAcceleration();
    uint8_t getGearinput();
    uint8_t getBrakeinput();
    bool getHazard();
};

#endif