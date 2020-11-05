#ifndef CANENCODER_H
#define CANENCODER_H

#include "signal_decoder.h"

class CANEncoder
{
private:
    /* data */
    FrameData frame_data_op;
public:
    CANEncoder(/* args */);
    ~CANEncoder() = default;
    void encodeEngineStatus(const bool &);
    void encodeRPM(const uint16_t&);
    FrameData get_frame_data_op();
};
#endif