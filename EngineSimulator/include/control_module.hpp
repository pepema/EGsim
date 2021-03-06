#ifndef CONTROL_MODULE_HPP
#define CONTROL_MODULE_HPP
#include <thread>
#include <iomanip>
#include <future>
#include "signals.hpp"
#include "can_encoder.hpp"
#include "can_reader_writer.hpp"
#include "engine.hpp"
#include "gearbox.hpp"

class ControlModule
{
public:
    void Run(DataBuffer &);
    void PowertrainControl();
    void CalculateGear();
    void ShiftGear();
    void Encode();
    void SetGearMode();
    void DummyDim();
    ControlModule(CanReaderWriter *);

private:
    bool shift_up, shift_down;
    Engine engine;
    Gearbox gearbox;
    Signals signals;
    CANEncoder encoder;
    FrameData output_data;
    CanReaderWriter *can_r_w;
};
#endif // CONTROL_MODULE_H