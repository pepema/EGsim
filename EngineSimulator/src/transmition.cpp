#include "transmition.h" 

Transmition::Transmition(/* args */)
{
    engine_status = false;

    
}

Transmition::~Transmition()
{
}


void Transmition::updateEngineStatus()
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

/*void Transmition::setFrameData(const uint8_t (&frameDataVal)[8])
{
    for (size_t i = 0; i < 8; i++)
    {
        frameDataIp.data[i] = frameDataVal[i];
    }
}*/
void Transmition::setIpFrame(const FrameData & frame_data_val)
{
    for (size_t i = 0; i < 8; i++)
    {
        frame_data_ip.data[i] = frame_data_val.data[i];
    }
}

bool Transmition::getEngineStatus()
{
    return engine_status;
}

/*
void Transmition::updateFrameData()
{
    CANReader *myReader = &CANReader::getInstance();
    frameDataIp = myReader->getData();
}

frameData Transmition::getData()
{
    return frameDataOp;
}


getData()
{
    CANReader myReader;
    frameDataIp.data = myReader.getData();
}
*/