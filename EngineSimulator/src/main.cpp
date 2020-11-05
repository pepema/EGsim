#include "can_reader.h"
#include "transmition.h"
#include "can_encoder.h"
#include "../../InputHandler/include/can_writer.hpp"

int main()
{
    // Read
    //Reader and read
    CANReader my_reader;
    Transmition my_transmition;
    CANEncoder my_encoder;
    CanWriter my_writer;
    FrameData output_data;

    my_reader.read();
    //my_reader.getData();

    my_transmition.setIpFrame(my_reader.getData());
    my_transmition.updateEngineStatus();
    //Set Values Tran

    my_encoder.encodeEngineStatus(my_transmition.getEngineStatus());

    //CW send frame

    output_data = my_encoder.get_frame_data_op();

    my_writer.SendFrame(123,output_data.data);

    return 0;
}