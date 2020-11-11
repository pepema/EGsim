#include <thread>
#include <iomanip>
#include <future>
#include "signal_decoder.h"
#include "can_encoder.h"
#include "can_reader_writer.hpp"
#include "engine.h"
#include "gearbox.h"


void readUpdate(CanReaderWriter& can_r_w, std::promise<bool>* app_start, bool * start_cond_ru)
{
    std::future<bool> start_cond_f = app_start->get_future();

    while(start_cond_f.wait_for(std::chrono::milliseconds(10)) != std::future_status::ready)
    {
        can_r_w.read();
        can_r_w.updateReadData();
    }
}

void processWrite(CanReaderWriter& can_r_w, bool app_start)
{
    SignalDecoder my_signal_decoder;
    CANEncoder my_encoder;
    FrameData output_data;
    Engine my_engine;
    Gearbox my_gearbox;
    FrameData test;

    while(app_start)
    {
        my_signal_decoder.setIpFrame(can_r_w.getData());

        my_engine.setHazard(my_signal_decoder.getHazard());

        if(my_engine.getHazard() == true)
        {
            app_start = false;
        }
        my_engine.setEngineStatus(my_signal_decoder.getEngineStatus());
        my_gearbox.updateGear(my_signal_decoder.getGearinput(), my_signal_decoder.getBrakeinput());
        my_engine.updateTRPM(my_signal_decoder.getAcceleration(), my_signal_decoder.getBrakeinput());
        my_engine.updateARPM(my_signal_decoder.getBrakeinput());
        my_gearbox.updateSpeed(my_engine.getARPM());
        
        my_encoder.encodeEngineStatus(my_engine.getEngineStatus());
        my_encoder.encodeRPM(my_engine.getARPM());
        my_encoder.encodeSpeed(my_gearbox.getSpeed());
        my_encoder.encodeGear(my_gearbox.getGear());

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
    std::promise<bool> start_cond_ru_p;
    bool start_cond_ru = true; 

    std::thread read_thread (readUpdate, std::ref(my_reader_writer), &start_cond_ru_p, &start_cond_ru);
 
    processWrite(my_reader_writer,app_start);

    start_cond_ru_p.set_value(false);
    read_thread.join();

    return 0;
}