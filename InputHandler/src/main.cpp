#include <iostream>
#include <thread>
#include "can_reader_writer.hpp"
#include "input_handler.hpp"
#include "can_encoder.hpp"

int main(){
  CanReaderWriter reader_writer;
  InputHandler handler;
  uint8_t* data = reader_writer.getWriteData();
  bool exit = 0;
  std::thread t(&InputHandler::Run,&handler,data,std::ref(exit));
  
  while(1){
    {
      std::unique_lock<std::mutex> lk(handler.m);
      handler.cv.wait(lk,[&handler]{return handler.input_ready;});
      if(exit){
        reader_writer.SendShutdownCommand(1,data);
        break;
      }
      reader_writer.SendFrame(1, data);
      handler.input_ready = false;
    }
  }
  t.join();
  return 0;
}