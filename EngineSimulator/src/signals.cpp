#include <cstring>
#include "signals.hpp" 

Signals::Signals()
{ 
    for(auto i = 0 ; i < 8 ; i++)
    {
        frame_data_ip.data[i] = 0;
        //frame_data_ip[i] = 0;
    }
}

Signals::~Signals()
{
}

uint8_t Signals::getAcceleration()
{
    return frame_data_ip.data[6];
    //return frame_data_ip[6];
}

void Signals::setFrame(const FrameData & frame_data_val)
//void SignalDecoder::setIpFrame(const uint8_t * frame_data_val)
{
    //std::memcpy(frame_data_ip, frame_data_val, 8*sizeof(uint8_t));
    frame_data_ip = frame_data_val;
}

bool Signals::getEngineStatus()
{
    return (frame_data_ip.data[7] == 0)?false: true;
}
uint8_t Signals::getGearinput(){
    return frame_data_ip.data[5];
    //return frame_data_ip[5];
}

uint8_t Signals::getBrakeinput(){
    return frame_data_ip.data[4];
    //return frame_data_ip[4];
}

bool Signals::getHazard()
{   
    if(frame_data_ip.data[0] == 0)
    //if(frame_data_ip[0] == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}