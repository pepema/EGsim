#include "control_module.hpp"

ControlModule::ControlModule(CanReaderWriter *can_reader_writer)
{
    this->can_r_w = can_reader_writer;
    shift_down = false;
    shift_up = false;
}

void ControlModule::PowertrainControl()
{
    if (shift_up || shift_down)
        ShiftGear();
    else
    {
        engine.updateTRPM(signals.getAcceleration());
        gearbox.updateSpeed(engine.getARPM());
    }
    engine.updateARPM(signals.getBrakeinput(), gearbox.getGearMode());
}

void ControlModule::SetGearMode()
{
    if (gearbox.getSpeed() == 0 && signals.getBrakeinput() > 0 && engine.getEngineStatus() == 1)
    {

        if (signals.getGearinput() == 1)
            gearbox.setGearMode(GearMode::D);
        else if (signals.getGearinput() == 2)
            gearbox.setGearMode(GearMode::R);
        else
            gearbox.setGearMode(GearMode::N);
    }
    else if (gearbox.getSpeed() == 0 && engine.getEngineStatus() == 0)
    {
        gearbox.setGearMode(GearMode::N);
    }
}

void ControlModule::ShiftGear()
{
    if (shift_up)
    {
        engine.updateTRPM(120);
        if (engine.getARPM() * gearbox.gear_ratio[gearbox.getGear() + 1] <= gearbox.getSpeed())
        {
            gearbox.gearShiftUp();
            shift_up = false;
        }
    }
    else if (shift_down)
    {
        engine.updateTRPM(110);
        if (engine.getARPM() * gearbox.gear_ratio[gearbox.getGear() - 1] >= gearbox.getSpeed())
        {
            gearbox.gearShiftDown();
            shift_down = false;
        }
    }
}

void ControlModule::DummyDim()
{
    uint16_t print_rpm = output_data.data[2] << 8 | output_data.data[1];
    std::cout << " Speed: " << std::setfill(' ') << std::setw(3) << static_cast<int>(output_data.data[0])
              << " Gear: " << std::setfill(' ') << std::setw(1) << static_cast<int>(gearbox.getGear())
              << " RPM: " << std::setfill(' ') << std::setw(5) << static_cast<int>(print_rpm)
              << " EngineStatus: " << static_cast<int>(output_data.data[3])
              << " GearMode: " << std::setfill(' ') << std::setw(1) << static_cast<int>(output_data.data[4])
              << " Brake: " << std::setfill(' ') << std::setw(3) << static_cast<int>(signals.getBrakeinput()) << "%"
              << " Acceleration: " << std::setfill(' ') << std::setw(3) << static_cast<int>(signals.getAcceleration()) << "%"
              << '\r' << std::flush;
}

void ControlModule::Encode()
{
    encoder.encodeEngineStatus(engine.getEngineStatus());
    encoder.encodeRPM(engine.getARPM());
    encoder.encodeSpeed(gearbox.getSpeed());
    encoder.encodeGearMode(gearbox.getGearMode());
    encoder.encodeGear(gearbox.getGear());
    encoder.encodeGauges(engine.getEngineStatus(), 255, 130, 130);
}

void ControlModule::Run(DataBuffer &input_frame_buffer)
{
    while (engine.getHazard() == false)
    {
        //decode input CAN message
        signals.setFrame(input_frame_buffer.frame_data);

        //Crash if Hazard
        engine.setHazard(signals.getHazard());

        //update Signals : Speed, RPM, Engine Status, Gear

        //Evaluate Engine status
        engine.setEngineStatus(signals.getEngineStatus());

        SetGearMode();
        CalculateGear();
        PowertrainControl();

        //Encode output values : Speed, RPM, Engine Status, Gear to CAN
        Encode();

        //Set output frame
        output_data = encoder.get_frame_data_op();

        //Send CAN message
        can_r_w->writeData(2, output_data);

        //Showing the values from output CAN Frame
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        DummyDim(); // Display current internal states
    }
}

void ControlModule::CalculateGear()
{
    if (gearbox.getGearMode() == GearMode::D)
    {
        if (gearbox.getGear() == 0 && signals.getAcceleration() > 0)
        {
            gearbox.gearShiftUp();
        }
        else if (gearbox.getGear() <= 6)
            if (signals.getAcceleration() > 80 && engine.getARPM() >= gearboxparams::kGearUpRpmHi && gearbox.getGear() < 6)
            {
                shift_up = true;
            }
            else if (signals.getAcceleration() < 80 && engine.getARPM() >= gearboxparams::kGearUpRpmLo && gearbox.getGear() < 6)
            {
                shift_up = true;
            }
            else
            {
                if (gearbox.getGear() == 6 && engine.getARPM() < 3500)
                    shift_down = true;
                else if (gearbox.getGear() == 5 && engine.getARPM() < 2700)
                    shift_down = true;
                else if (gearbox.getGear() == 4 && engine.getARPM() < 2500)
                    shift_down = true;
                else if (gearbox.getGear() == 3 && engine.getARPM() < 2000)
                    shift_down = true;
                else if (gearbox.getGear() == 2 && engine.getARPM() < 1500)
                    shift_down = true;
            }
    }
    else if (gearbox.getGear() == 1 && gearbox.getGearMode() == GearMode::N)
    {
        shift_down = true;
    }
    else if (gearbox.getGear() == 0 && signals.getAcceleration() > 0 && gearbox.getGearMode() == GearMode::R)
    {
        gearbox.gearShiftUp();
    }
}