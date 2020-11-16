#ifndef CONTROL_MODULE_H
#define CONTROL_MODULE_H
#include <thread>
#include <iomanip>
#include <future>
#include "signal_decoder.h"
#include "can_encoder.h"
#include "can_reader_writer.hpp"
#include "engine.h"
#include "gearbox.h"


class ControlModule{
    public:
    void Run(DataBuffer &);
    void PowertrainControl();
    void EvaluateEngineStatus();
    void CalculateGear();
    void ShiftGear();
    bool EvaluateHazard();
    void Encode();
    void SetOutputFrame();
    void SetGearMode();
    void SendCANFrame();
    void DummyDim();
    //inline void DecodeInputCan(DataBuffer& input_frame_buffer){signal_decoder.setIpFrame(can_r_w->getData());}
    void DecodeInputCan(DataBuffer& input_frame_buffer);

    ControlModule(CanReaderWriter*);
    
    private:
    bool shift_up, shift_down;
    Engine engine;
    Gearbox gearbox;
    SignalDecoder signal_decoder;
    CANEncoder encoder;
    FrameData output_data;
    CanReaderWriter* can_r_w;
};
#endif // CONTROL_MODULE_H