#include "signal_decoder.h" 

SignalDecoder::SignalDecoder(/* args */)
{
    engine_status = false;
    acc_p = 0;

    
}

SignalDecoder::~SignalDecoder()
{
}


void SignalDecoder::updateEngineStatus()
{
    if(frame_data_ip.data[7] == 0)
    {
        engine_status = false;
        //frame_data_op.data[3] = 0;
    }
    else
    {
        //frame_data_op.data[3] = 1;
        engine_status = true;
    }
}

void SignalDecoder::updateAccP()
{
    acc_p=frame_data_ip.data[6];
}

uint8_t SignalDecoder::getAccP()
{
    return acc_p;
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
    return engine_status;
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