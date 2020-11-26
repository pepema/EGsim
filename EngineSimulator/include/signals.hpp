#ifndef Signals_HPP
#define Signals_HPP
#include <iostream>
#include "can_reader_writer.hpp"

namespace defaultstate
{
    static const uint kOpCanId = 2;
    static const uint kDataLength = 8;
    static const uint kSpeed = 0;        //Default value for speed is 0 kmph
    static const uint kLRpm = 0;         //LSB for RPM
    static const uint kMRpm = 0;         //MSB for RPM
    static const uint kEngineStatus = 0; //Engine Off = 0
    static const uint kGear = 0;         // Gear in Neutral = 0
} // namespace defaultstate

class Signals
{
private:
    FrameData frame_data_ip;

public:
    Signals();
    void setFrame(const FrameData &);
    bool getEngineStatus();
    uint8_t getAcceleration();
    uint8_t getGearinput();
    uint8_t getBrakeinput();
    bool getHazard();
};

#endif