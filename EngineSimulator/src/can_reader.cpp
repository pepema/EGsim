#include "can_reader.h"
#include <iostream>
CANReader::CANReader()
{
    if (socket_can.open("vcan0") != scpp::STATUS_OK) {
        //std::cout << "Cannot open vcan0." << std::endl;
        //std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit (-1);
    }
}

CANReader::~CANReader()
{
}

void CANReader::read()
{
    if (socket_can.read(can_frame) == scpp::STATUS_OK) 
    {
        //Notify all subscribers
        //Update Frame data
    }
    else 
    {
        for (size_t i = 0; i < 9999; i++); //STUPID SLEEP?
    }
}

FrameData CANReader::getData()
{
    FrameData frameDataToPass;
    for (size_t i = 0; i < 8; i++)
    {
        frameDataToPass.data[i] = can_frame.data[i];    //Should we do this tcopy by ref?
    }
    return frameDataToPass;
}