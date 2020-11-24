#ifndef CANENCODER_HPP
#define CANENCODER_HPP

#include "signals.hpp"
#include "gearbox.hpp"

class CANEncoder
{
private:
    /* data */
    FrameData frame_data_op;
    //uint8_t frame_data_op[8];
public:
    CANEncoder(/* args */);
    ~CANEncoder() = default;
    void encodeEngineStatus(const bool &);
    void encodeGauges(const bool &engine_status,const uint8_t  &Fuel_level,const uint8_t &oil_level,const uint8_t &temp_level);
    void encodeRPM(const uint16_t&);
    void encodeSpeed(const uint16_t&);
    void encodeGearMode(const GearMode&);
    inline void encodeGear(const uint8_t& gear){frame_data_op.data[5]=gear;}
    FrameData get_frame_data_op();
    //uint8_t * get_frame_data_op();
};
#endif