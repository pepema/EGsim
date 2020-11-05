#include "can_reader.h"
#include "transmition.h"
#include "can_encoder.h"
<<<<<<< HEAD
#include "can_writer.hpp"
#include <thread>
=======
#include "../../InputHandler/include/can_writer.hpp"
>>>>>>> 9a590215f4f070bcde0ec526e72724d8bdb1514e

int main()
{
    // Read
    //Reader and read
    CANReader my_reader;
    Transmition my_transmition;
    CANEncoder my_encoder;
    CanWriter my_writer;
    FrameData output_data;

    while(true){
        my_reader.read();
        //my_reader.getData();

        my_transmition.setIpFrame(my_reader.getData());
        my_transmition.updateEngineStatus();
        //Set Values Tran

        my_encoder.encodeEngineStatus(my_transmition.getEngineStatus());

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