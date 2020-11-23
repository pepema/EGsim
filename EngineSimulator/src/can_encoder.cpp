#include "can_encoder.hpp"

CANEncoder::CANEncoder()
{
    frame_data_op.data[0] = cnsts::kSpeed; 
    //frame_data_op[0] = cnsts::SPEED; 
    
    
    frame_data_op.data[1] = cnsts::kLRpm;
    frame_data_op.data[2] = cnsts::kMRpm;
    /*
    frame_data_op[1] = cnsts::LRPM;
    frame_data_op[2] = cnsts::MRPM;
    */

    frame_data_op.data[3] = cnsts::kEngineStatus;
    //frame_data_op[3] = cnsts::ENGSTATUS;


    frame_data_op.data[4] = cnsts::kGear;
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

void CANEncoder::encodeGauges(const bool &engine_status,const uint8_t  &Fuel_level,const uint8_t &oil_level,const uint8_t &temp_level){

    if (engine_status == 1){
        frame_data_op.data[7] = Fuel_level/10 << 0;
        frame_data_op.data[7] |= oil_level/10 << 5;

        frame_data_op.data[6] = oil_level/10 >> 3;
        frame_data_op.data[6] |= temp_level/10 << 2;
    }
    else {
        frame_data_op.data[6] = 0;
        frame_data_op.data[7] = 0;
    }
}

FrameData CANEncoder::get_frame_data_op()
//uint8_t * CANEncoder::get_frame_data_op()
{
    return frame_data_op;
}