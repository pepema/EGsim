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
    ~CANEncoder() = default;
    void encodeEngineStatus(const bool &);
    FrameData get_frame_data_op();
};


#endif