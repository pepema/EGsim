#ifndef CANENCODER_H
#define CANENCODER_H

#include "signal_decoder.h"
#include "gearbox.h"

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
    void encodeSpeed(const uint16_t&);
    void encodeGear(const Gear&);
    FrameData get_frame_data_op();
};
#endif