#include "can_encoder.h"

CANEncoder::CANEncoder()
{
    frame_data_op.data[0] = cnsts::SPEED; 
    //frame_data_op[0] = cnsts::SPEED; 
    
    
    frame_data_op.data[1] = cnsts::LRPM;
    frame_data_op.data[2] = cnsts::MRPM;
    /*
    frame_data_op[1] = cnsts::LRPM;
    frame_data_op[2] = cnsts::MRPM;
    */

    frame_data_op.data[3] = cnsts::ENGSTATUS;
    //frame_data_op[3] = cnsts::ENGSTATUS;


    frame_data_op.data[4] = cnsts::GEAR;
    //frame_data_op[4] = cnsts::GEAR;

    //Reserved Data bytes
    
    frame_data_op.data [5] = 0;
    frame_data_op.data [6] = 0;
    frame_data_op.data [7] = 0;
    /*
    frame_data_op[5] = 0;
    frame_data_op[6] = 0;
    frame_data_op[7] = 0;
    */
}

void CANEncoder::encodeEngineStatus(const bool &engine_status)
{
    frame_data_op.data[3] = engine_status;
    //frame_data_op[3] = engine_status;
}
void CANEncoder::encodeRPM(const uint16_t& actual_rpm){
    frame_data_op.data[2] = actual_rpm >> 8;
    frame_data_op.data[1] = actual_rpm & 255;
    //frame_data_op[2] = actual_rpm >> 8;
    //frame_data_op[1] = actual_rpm & 255;
}
void CANEncoder::encodeSpeed(const uint16_t& speed){
        frame_data_op.data[0] = speed;
        //frame_data_op[0] = speed;
 }
void CANEncoder::encodeGearMode(const GearMode& gear){
    if (gear == GearMode::D)
        frame_data_op.data[4] = 3;

    else if (gear == GearMode::R)

        frame_data_op.data[4] = 2;
        //frame_data_op[4] = 'R';
    else
        frame_data_op.data[4] = 0;
        //frame_data_op[4] = 'N';
}

FrameData CANEncoder::get_frame_data_op()
//uint8_t * CANEncoder::get_frame_data_op()
{
    return frame_data_op;
}