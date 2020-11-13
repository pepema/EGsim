#include "control_module.h"


ControlModule::ControlModule(){
    shift_down_in_progress=false;
    shift_up_in_progress=false;
}

void ControlModule::EvaluateHazard(bool& app_start){       
    engine.setHazard(signal_decoder.getHazard());
    if(engine.getHazard() == true)
    {
        app_start = false;
    }     
}

void ControlModule::Encode(){
    encoder.encodeEngineStatus(engine.getEngineStatus());
    encoder.encodeRPM(engine.getARPM());
    encoder.encodeSpeed(gearbox.getSpeed());
    encoder.encodeGear(gearbox.getGearMode());
}

void ControlModule::Run(CanReaderWriter& can_r_w, bool app_start)
{
    while(app_start)
    {
        //decode input CAN message
        signal_decoder.setIpFrame(can_r_w.getData());
        //Crash if Hazard
        EvaluateHazard(app_start);
        CalculateGear();
        //update Signals : Speed, RPM, Engine Status, Gear
        engine.setEngineStatus(signal_decoder.getEngineStatus());
        gearbox.updateGear(signal_decoder.getGearinput(), signal_decoder.getBrakeinput());
        engine.updateARPM(signal_decoder.getBrakeinput(),gearbox.getGearMode());
        //if(!shift_up_in_progress) gearbox.updateSpeed(engine.getARPM());
        
        //Encode output values : Speed, RPM, Engine Status, Gear to CAN
        Encode();

        output_data = encoder.get_frame_data_op();

        //write CAN message
        can_r_w.SendFrame(2,output_data.data);
        
        //Showing the values from output CAN Frame
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        uint16_t print_rpm = output_data.data[2] << 8 | output_data.data[1];
        std::cout << " Speed: "               << std::setfill(' ') << std::setw(3) << static_cast<int>(output_data.data[0])
                  << " RPM: "                 << std::setfill(' ') << std::setw(5) << static_cast<int>(print_rpm)
                  << " EngineStatus: "        << static_cast<int>(output_data.data[3])
                  << " GearMode: "            << std::setfill(' ') << std::setw(1) << output_data.data[4]
                  << " Brake: "               << std::setfill(' ') << std::setw(3) << static_cast<int>(signal_decoder.getBrakeinput()) << "%"
                  << " Acceleration: "        << std::setfill(' ') << std::setw(3) << static_cast<int>(signal_decoder.getAcceleration()) << "%"
                  << " Gear: "                << std::setfill(' ') << std::setw(1) << static_cast<int>(gearbox.getGear())
                  << '\r' << std::flush;
    }
}

void ControlModule::CalculateGear(){
    if(gearbox.getGearMode() == GearMode::D){
        if(gearbox.getGear() == 0 && signal_decoder.getAcceleration() > 0){
            gearbox.gearShiftUp();
        }
        else if(gearbox.getGear()<6 && engine.getARPM()>=4500){
            shift_up_in_progress = true;
        }
        else if(gearbox.getGear()>1 && engine.getARPM()<=1500){
            shift_down_in_progress = true;
        }
        else if(gearbox.getGear() == 1){
        }


        if(shift_up_in_progress){
            engine.updateTRPM(120);
            //std::cout << "setting TRPM0" << std::endl;
            if(engine.getARPM()*gearbox.gear_ratio[gearbox.getGear()+1] <= gearbox.getSpeed()){
                //std::cout << "Shifting gears" << std::endl;
                gearbox.gearShiftUp();
                shift_up_in_progress = false;
            }
        }
        else if(shift_down_in_progress){
            engine.updateTRPM(110);
            if(engine.getARPM()*gearbox.gear_ratio[gearbox.getGear()-1] >= gearbox.getSpeed()){
                gearbox.gearShiftDown();
                shift_down_in_progress = false;
            }
        }
        else{
            engine.updateTRPM(signal_decoder.getAcceleration());
            gearbox.updateSpeed(engine.getARPM());
        }
    }
    else{
        engine.updateTRPM(signal_decoder.getAcceleration());
    }
}