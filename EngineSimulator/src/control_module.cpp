#include "control_module.h"

ControlModule::ControlModule(CanReaderWriter* can_reader_writer){
    this->can_r_w=can_reader_writer;
    shift_down=false;
    shift_up=false;
}

void ControlModule::PowertrainControl(){
        if(shift_up || shift_down) 
            ShiftGear();
        else {
            engine.updateTRPM(signal_decoder.getAcceleration());
            gearbox.updateSpeed(engine.getARPM());
        }
        engine.updateARPM(signal_decoder.getBrakeinput(),gearbox.getGearMode());
}

void ControlModule::SendCANFrame(){
    can_r_w->SendFrame(2,output_data.data);
}

void ControlModule::EvaluateEngineStatus(){
    engine.setEngineStatus(signal_decoder.getEngineStatus());
}


void ControlModule::SetGearMode(){
    if(gearbox.getSpeed()==0 && signal_decoder.getBrakeinput()>0 && engine.getEngineStatus()==1){

        if(signal_decoder.getGearinput()==1)
            gearbox.updateGear(GearMode::D);
        else if(signal_decoder.getGearinput()==2)
            gearbox.updateGear(GearMode::R);
        else
            gearbox.updateGear(GearMode::N);
        }
    else if(gearbox.getSpeed()==0 && engine.getEngineStatus()==0){
        gearbox.updateGear(GearMode::N);
    }
}

void ControlModule::ShiftGear(){
    if(shift_up){
        engine.updateTRPM(120);
        if(engine.getARPM()*gearbox.gear_ratio[gearbox.getGear()+1] <= gearbox.getSpeed()){
            gearbox.gearShiftUp();
            shift_up = false;
        }
    }
    else if(shift_down){
        engine.updateTRPM(110);
        if(engine.getARPM()*gearbox.gear_ratio[gearbox.getGear()-1] >= gearbox.getSpeed()){
            gearbox.gearShiftDown();
            shift_down = false;
        }
    }
}

void ControlModule::SetOutputFrame(){
    output_data = encoder.get_frame_data_op();
}

void ControlModule::DummyDim(){
    uint16_t print_rpm = output_data.data[2] << 8 | output_data.data[1];
    std::cout << " Speed: "               << std::setfill(' ') << std::setw(3) << static_cast<int>(output_data.data[0])
                << " Gear: "                << std::setfill(' ') << std::setw(1) << static_cast<int>(gearbox.getGear())
                << " RPM: "                 << std::setfill(' ') << std::setw(5) << static_cast<int>(print_rpm)
                << " EngineStatus: "        << static_cast<int>(output_data.data[3])
                << " GearMode: "            << std::setfill(' ') << std::setw(1) << output_data.data[4]
                << " Brake: "               << std::setfill(' ') << std::setw(3) << static_cast<int>(signal_decoder.getBrakeinput()) << "%"
                << " Acceleration: "        << std::setfill(' ') << std::setw(3) << static_cast<int>(signal_decoder.getAcceleration()) << "%"   
                << '\r' << std::flush;
}

bool ControlModule::EvaluateHazard(){       
    engine.setHazard(signal_decoder.getHazard());
    if(engine.getHazard() == true) return true;
    else return false;
}

void ControlModule::Encode(){
    encoder.encodeEngineStatus(engine.getEngineStatus());
    encoder.encodeRPM(engine.getARPM());
    encoder.encodeSpeed(gearbox.getSpeed());
    encoder.encodeGear(gearbox.getGearMode());
}

void ControlModule::Run()
{
    while(1)
    {
        //decode input CAN message
        DecodeInputCan();
        //Crash if Hazard
        if(EvaluateHazard()) break;
        
        //update Signals : Speed, RPM, Engine Status, Gear
        EvaluateEngineStatus();
        SetGearMode();
        CalculateGear();
        PowertrainControl();
     
        //Encode output values : Speed, RPM, Engine Status, Gear to CAN
        Encode();
        SetOutputFrame();

        //Send CAN message
        SendCANFrame();
        
        //Showing the values from output CAN Frame
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        DummyDim(); // Display current internal states
    }   
}

void ControlModule::CalculateGear(){
    if(gearbox.getGearMode() == GearMode::D){
        if(gearbox.getGear() == 0 && signal_decoder.getAcceleration() > 0){
            gearbox.gearShiftUp();
        }
        else if(gearbox.getGear()<6 && engine.getARPM()>=4500){
            shift_up= true;
        }
        else if(gearbox.getGear()>1 && engine.getARPM()<=1500){
            shift_down = true;
        }
    }
    else if(gearbox.getGear() == 1 && gearbox.getGearMode() == GearMode::N){
        shift_down = true;
    }
}