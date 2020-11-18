#include "control_module.hpp"
#include <cstring>

//void readUpdate(CanReaderWriter& can_r_w, std::promise<bool> * app_start)
void readUpdate(DataBuffer &input_frame_buffer, std::promise<bool> * app_start)
{
    CanReaderWriter reader;
    std::future<bool> start_cond_f = app_start->get_future();
    //DataBuffer input_frame_buffer;
    //input_frame_buffer.frame_data = input_frame_buffer_ptr->frame_data;
    
    //std::cout<<"I am in read thread"<<std::endl;

    while(start_cond_f.wait_for(std::chrono::milliseconds(10)) != std::future_status::ready)
    {
        //std::cout<<"I am in while"<<std::endl;
        //can_r_w.read();
        //reader.read();
        //std::cout<<"I am before  read"<<std::endl;
        reader.readData(1,input_frame_buffer);
        //std::cout<<"I am infinite read"<<std::endl;
    }
}

int main()
{
    //CanReaderWriter reader;
    DataBuffer input_frame_buffer;
    std::memset(input_frame_buffer.frame_data.data,0,sizeof(DataBuffer));
    //DataBuffer *input_frame_buffer_ptr = &input_frame_buffer;
    CanReaderWriter writer;
    //readb
    //writeb
    ControlModule control_module(&writer);
    std::promise<bool> start_cond_ru_p;
    //std::cout<<"I am in main"<<std::endl;

    //Thread to read the input CAN message
    std::thread read_thread (readUpdate, std::ref(input_frame_buffer), &start_cond_ru_p);
 
    //Simulating Engine and Writing CAN frames on main thread
    control_module.Run(input_frame_buffer);

    //std::cout<<"Run terminates quickly"<<std::endl;

    start_cond_ru_p.set_value(false);
    read_thread.join();

    return 0;
}