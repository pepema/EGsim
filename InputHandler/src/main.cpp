#include <iostream>
#include <thread>
#include <future>
#include "can_reader_writer.hpp"
#include "input_handler.hpp"
#include "can_encoder.hpp"

int main(){
  CanReaderWriter reader_writer;
  InputHandler handler;
  uint8_t data [8] = {0,0,0,0,0,0,0,0};
  bool exit = 0;
  std::thread t(&InputHandler::Run,&handler,data,std::ref(exit));
  
  while(!exit){
    reader_writer.SendFrame(1, data);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  t.join();
  return 0;
}