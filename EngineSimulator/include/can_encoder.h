#ifndef CANENCODER_H
#define CANENCODER_H

#include "transmition.h"

class CANEncoder
{
private:
    /* data */
    FrameData frame_data_op;
public:
    CANEncoder(/* args */);
    ~CANEncoder();
    void encodeEngineStatus(const bool &);
    FrameData get_frame_data_op();
};

CANEncoder::CANEncoder(/* args */)
{
}

CANEncoder::~CANEncoder()
{
}


#endif