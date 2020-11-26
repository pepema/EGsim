#include "control_module.hpp"
#include <cstring>

void readUpdate(DataBuffer &input_frame_buffer, std::promise<bool> *app_start)
{
    CanReaderWriter reader;
    std::future<bool> start_cond_f = app_start->get_future();
    while (start_cond_f.wait_for(std::chrono::milliseconds(10)) != std::future_status::ready)
    {
        reader.readData(1, input_frame_buffer);
    }
}

int main()
{
    DataBuffer input_frame_buffer;
    std::memset(input_frame_buffer.frame_data.data, 0, sizeof(DataBuffer));
    CanReaderWriter writer;
    ControlModule control_module(&writer);
    std::promise<bool> start_cond_ru_p;
    std::thread read_thread(readUpdate, std::ref(input_frame_buffer), &start_cond_ru_p);
    control_module.Run(input_frame_buffer);
    start_cond_ru_p.set_value(false);
    read_thread.join();

    return 0;
}