#include "can_reader.h"
#include "signal_decoder.h"
#include "can_encoder.h"
#include "can_writer.hpp"
#include <thread>

int main()
{
    // Read
    //Reader and read
    CANReader my_reader;
    SignalDecoder my_signal_decoder;
    CANEncoder my_encoder;
    CanWriter my_writer;
    FrameData output_data;

    while(true){
        my_reader.read();
        //my_reader.getData();

        my_signal_decoder.setIpFrame(my_reader.getData());
        //Set Values Tran

        my_encoder.encodeEngineStatus(my_signal_decoder.getEngineStatus());

        //CW send frame

        output_data = my_encoder.get_frame_data_op();

        my_writer.SendFrame(123,output_data.data);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        uint16_t print_rpm = output_data.data[2] << 8 | output_data.data[1];
        std::cout << " Speed: "               << static_cast<int>(output_data.data[0])
                  << " RPM: "                 << static_cast<int>(print_rpm)
                  << " EngineStatus: "        << static_cast<int>(output_data.data[3])
                  << " Gear: "                << static_cast<int>(output_data.data[4])
                  << '\r' << std::flush;
    }
    return 0;
}