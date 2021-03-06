#include <cstring>
#include "signals.hpp"

Signals::Signals()
{
    std::memset(frame_data_ip.data, 0, sizeof(frame_data_ip.data));
}

uint8_t Signals::getAcceleration()
{
    return frame_data_ip.data[6];
}

void Signals::setFrame(const FrameData &frame_data_val)
{
    frame_data_ip = frame_data_val;
}

bool Signals::getEngineStatus()
{
    return (frame_data_ip.data[7] == 0) ? false : true;
}
uint8_t Signals::getGearinput()
{
    return frame_data_ip.data[5];
}

uint8_t Signals::getBrakeinput()
{
    return frame_data_ip.data[4];
}

bool Signals::getHazard()
{
    if (frame_data_ip.data[0] == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}