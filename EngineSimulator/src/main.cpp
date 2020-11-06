#include "signal_decoder.h"
#include "can_encoder.h"
#include "can_reader_writer.hpp"
#include <thread>
#include <iomanip>
#include "engine.h"
#include "gearbox.h"

int main()
{
    // Read
    //Reader and read
    //CANReader my_reader;
    SignalDecoder my_signal_decoder;
    CANEncoder my_encoder;
    CanReaderWriter my_reader_writer;
    FrameData output_data;
    Engine my_engine;
    Gearbox my_gearbox;
    FrameData test;

    while(true){
        my_reader_writer.read();
        my_signal_decoder.setIpFrame(my_reader_writer.getData());
        //Set Values Tran
        my_engine.setEngineStatus(my_signal_decoder.getEngineStatus());
        my_gearbox.updateGear(my_signal_decoder.getGearinput(), my_signal_decoder.getBrakeinput());
        my_engine.updateTRPM(my_signal_decoder.getAcceleration(), my_signal_decoder.getBrakeinput());
        my_engine.updateARPM(my_signal_decoder.getBrakeinput());
        my_gearbox.updateSpeed(my_engine.getARPM());
        
        my_encoder.encodeEngineStatus(my_engine.getEngineStatus());
        my_encoder.encodeRPM(my_engine.getARPM());
        my_encoder.encodeSpeed(my_gearbox.getSpeed());
        my_encoder.encodeGear(my_gearbox.getGear());

        //CW send frame

        output_data = my_encoder.get_frame_data_op();

        my_reader_writer.SendFrame(2,output_data.data);
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

       uint16_t print_rpm = output_data.data[2] << 8 | output_data.data[1];
        std::cout << " Speed: "               << std::setfill(' ') << std::setw(3) << static_cast<int>(output_data.data[0])
                  << " RPM: "                 << std::setfill(' ') << std::setw(5) << static_cast<int>(print_rpm)
                  << " EngineStatus: "        << static_cast<int>(output_data.data[3])
                  << " Gear: "                << std::setfill(' ') << std::setw(1) << output_data.data[4]
                  << " Brake: "               << std::setfill(' ') << std::setw(3) << static_cast<int>(my_signal_decoder.getBrakeinput()) << "%"
                  << " Acceleration: "        << std::setfill(' ') << std::setw(3) << static_cast<int>(my_signal_decoder.getAcceleration()) << "%"
                  << '\r' << std::flush;
    }
    return 0;
}