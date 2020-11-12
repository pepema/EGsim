#include <cstring>
#include "signal_decoder.h" 

SignalDecoder::SignalDecoder()
{ 
    for(auto i = 0 ; i < 8 ; i++)
    {
        //frame_data_ip.data[i] = 0;
        frame_data_ip[i] = 0;
    }
}

SignalDecoder::~SignalDecoder()
{
}

uint8_t SignalDecoder::getAcceleration()
{
    //return frame_data_ip.data[6];
    return frame_data_ip[6];
}

//void SignalDecoder::setIpFrame(const FrameData & frame_data_val)
void SignalDecoder::setIpFrame(const uint8_t * frame_data_val)
{
    std::memcpy(frame_data_ip, frame_data_val, 8*sizeof(uint8_t));
    //frame_data_ip = frame_data_val;
}

bool SignalDecoder::getEngineStatus()
{

    //if(frame_data_ip.data[7] == 0)
    if(frame_data_ip[7] == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
uint8_t SignalDecoder::getGearinput(){
    //return frame_data_ip.data[5];
    return frame_data_ip[5];
}

uint8_t SignalDecoder::getBrakeinput(){
    //return frame_data_ip.data[4];
    return frame_data_ip[4];
}

bool SignalDecoder::getHazard()
{   
    //if(frame_data_ip.data[0] == 0)
    if(frame_data_ip[0] == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}