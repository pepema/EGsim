#include "signal_decoder.h" 

SignalDecoder::SignalDecoder(/* args */)
{  
}

SignalDecoder::~SignalDecoder()
{
}

uint8_t SignalDecoder::getAcceleration()
{
    return frame_data_ip.data[6];
}

/*void SignalDecoder::setFrameData(const uint8_t (&frameDataVal)[8])
{
    for (size_t i = 0; i < 8; i++)
    {
        frameDataIp.data[i] = frameDataVal[i];
    }
}*/
void SignalDecoder::setIpFrame(const FrameData & frame_data_val)
{
    for (size_t i = 0; i < 8; i++)
    {
        frame_data_ip.data[i] = frame_data_val.data[i];
    }
}

bool SignalDecoder::getEngineStatus()
{
    if(frame_data_ip.data[7] == 0)
    {
        return false;
        //frame_data_op.data[3] = 0;
    }
    else
    {
        //frame_data_op.data[3] = 1;
        return true;
    }
}
uint8_t SignalDecoder::getGearinput(){
    return frame_data_ip.data[5];
}

/*
void SignalDecoder::updateFrameData()
{
    CANReader *myReader = &CANReader::getInstance();
    frameDataIp = myReader->getData();
}

frameData SignalDecoder::getData()
{
    return frameDataOp;
}


getData()
{
    CANReader myReader;
    frameDataIp.data = myReader.getData();
}
*/