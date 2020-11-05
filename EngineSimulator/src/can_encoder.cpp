#include "can_encoder.h"

CANEncoder::CANEncoder()
{
    frame_data_op.data[0] = cnsts::SPEED; 
        
    frame_data_op.data[1] = cnsts::LRPM;
    frame_data_op.data[2] = cnsts::MRPM;

    frame_data_op.data[3] = cnsts::ENGSTATUS;

    frame_data_op.data[4] = cnsts::GEAR;

    //Reserved Data bytes
    frame_data_op.data [5] = 0;
    frame_data_op.data [6] = 0;
    frame_data_op.data [7] = 0;
}

void CANEncoder::encodeEngineStatus(const bool &engine_status)
{
    frame_data_op.data[3] = engine_status;
}
void CANEncoder::encodeRPM(const uint16_t& actual_rpm){
    frame_data_op.data[2] = actual_rpm >> 8;
    frame_data_op.data[1] = actual_rpm & 255;
}

FrameData CANEncoder::get_frame_data_op()
{
    return frame_data_op;
}