#include <iostream>
#include <thread>
#include <cstring>
#include "can_reader_writer.hpp"
#include "input_handler.hpp"
#include "can_encoder.hpp"

int main()
{
  InputHandler handler;
  CanReaderWriter reader_writer;
  FrameData op_data;
  std::memset(op_data.data, 0, sizeof(op_data.data));
  uint8_t *data = reinterpret_cast<uint8_t *>(&op_data);
  bool exit = 0;
  std::thread t(&InputHandler::Run, &handler, data, std::ref(exit));

  while (1)
  {
    {
      std::unique_lock<std::mutex> lk(handler.m);
      handler.cv.wait(lk, [&handler] { return handler.input_ready; });
      if (exit)
      {
        for (auto i = 0; i < 4; i++)
        {
          std::this_thread::sleep_for(std::chrono::milliseconds(10));
          reader_writer.writeData(1, op_data);
        }
        break;
      }
      reader_writer.writeData(1, op_data);
      handler.input_ready = false;
    }
  }
  t.join();
  return 0;
}