#include "can_reader.h"
#include "signal_decoder.h"
#include "can_encoder.h"
#include "can_writer.hpp"
#include <thread>
#include <iomanip>
#include "engine.h"
#include "gearbox.h"

int main()
{
    // Read
    //Reader and read
    CANReader my_reader;
    SignalDecoder my_signal_decoder;
    CANEncoder my_encoder;
    CanWriter my_writer;
    FrameData output_data;
    Engine my_engine;
    Gearbox my_gearbox;
    FrameData test;

    while(true){
        my_reader.read();
        test = my_reader.getData();
        my_signal_decoder.setIpFrame(my_reader.getData());
        //Set Values Tran
        my_engine.setEngineStatus(my_signal_decoder.getEngineStatus());
        my_gearbox.updateGear(my_signal_decoder.getGearinput());
        my_engine.updateTRPM(my_signal_decoder.getAcceleration());
        my_engine.updateARPM(my_signal_decoder.getAcceleration());
        my_gearbox.updateSpeed(my_engine.getARPM());
        
        my_encoder.encodeEngineStatus(my_engine.getEngineStatus());
        my_encoder.encodeRPM(my_engine.getARPM());
        my_encoder.encodeSpeed(my_gearbox.getSpeed());
        //CW send frame

        output_data = my_encoder.get_frame_data_op();

        my_writer.SendFrame(2,output_data.data);
        
        std::this_thread::sleep_for(std::chrono::nanoseconds(100));

       uint16_t print_rpm = output_data.data[2] << 8 | output_data.data[1];
        std::cout << " Speed: "               << std::setfill(' ') << std::setw(3) << static_cast<int>(output_data.data[0])
                  << " RPM: "                 << std::setfill(' ') << std::setw(5) << static_cast<int>(print_rpm)
                  << " EngineStatus: "        << static_cast<int>(output_data.data[3])
                  << " Acceleration: "        << std::setfill(' ') << std::setw(3) << static_cast<int>(my_signal_decoder.getAcceleration()) << "%"
                  << '\r' << std::flush;
    }
    return 0;
}