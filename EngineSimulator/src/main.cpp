#include "control_module.h"

void readUpdate(CanReaderWriter& can_r_w, std::promise<bool> * app_start)
{
    std::future<bool> start_cond_f = app_start->get_future();

    while(start_cond_f.wait_for(std::chrono::milliseconds(10)) != std::future_status::ready)
    {
        can_r_w.read();
        can_r_w.updateReadData();
    }
}

int main()
{
    CanReaderWriter reader_writer;
    ControlModule control_module(&reader_writer);
    std::promise<bool> start_cond_ru_p;

    //Thread to read the input CAN message
    std::thread read_thread (readUpdate, std::ref(reader_writer), &start_cond_ru_p);
 
    //Simulating Engine and Writing CAN frames on main thread
    control_module.Run();

    start_cond_ru_p.set_value(false);
    read_thread.join();

    return 0;
}