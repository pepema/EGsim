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
    void Run(CanReaderWriter&);
    void CalculateGear();
    bool EvaluateHazard();
    void Encode();
    void SetOutputFrame();
    void SetGearMode();
    void SendFrame();
    void DummyDim();
    ControlModule();
    
    private:
    bool shift_up_in_progress, shift_down_in_progress;
    Engine engine;
    Gearbox gearbox;
    SignalDecoder signal_decoder;
    CANEncoder encoder;
    FrameData output_data;



};