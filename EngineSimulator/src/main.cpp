#include "signal_decoder.h"
#include "can_encoder.h"
#include "can_reader_writer.hpp"
#include <thread>
#include <iomanip>
#include "engine.h"
#include "gearbox.h"
#include <future>

void readUpdate(CanReaderWriter& can_r_w, std::promise<bool> app_start_p)
{
    std::future<bool> start_cond_f = app_start_p.get_future();

    while(start_cond_f.get() == true)
    {
        can_r_w.read();
        can_r_w.updateReadData();
    }
}

void processWrite(CanReaderWriter& can_r_w, bool app_start)
{
    SignalDecoder my_signal_decoder;
    CANEncoder my_encoder;
    //CanReaderWriter my_reader_writer;
    FrameData output_data;
    Engine my_engine;
    Gearbox my_gearbox;
    FrameData test;

    while(app_start)
    {
        my_signal_decoder.setIpFrame(can_r_w.getData());
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

        can_r_w.SendFrame(2,output_data.data);
        
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
}

int main()
{
    bool app_start = true;
    CanReaderWriter my_reader_writer;
    std::promise<bool> start_cond_ru_p; //promise for readUpdate
    std::promise<bool> start_cond_pw_p;  //promise for processWrite
    //std::future<bool> start_cond_f = start_cond_p.get_future();

    start_cond_ru_p.set_value(true);
    start_cond_pw_p.set_value(true);

    std::thread read_thread (readUpdate, my_reader_writer, start_cond_ru_p);

    //app_start = false;
    //appstart =false;
    
    //std::thread process_thread (processWrite, my_reader_writer, start_cond_pw_p);
    processWrite(my_reader_writer,app_start);

    //app_start = false in thread 1
    //start_cond_pw_p.set_value(false);
    
    //The below statements will NEVER be called!

    start_cond_ru_p.set_value(false);
    read_thread.join();

    return 0;
}