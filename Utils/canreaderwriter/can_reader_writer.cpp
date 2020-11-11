#include <cstring>
#include "can_reader_writer.hpp"

CanReaderWriter::CanReaderWriter(){
  if (socket_can.open("vcan0") != scpp::STATUS_OK){
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit (-1);
  }
  int length = 8;
  cf_to_write.len = length;
  cf_to_write.data[length] = {};
  for(int i =0;i<length;i++){
    cf_to_write.data[i]=0;
    cf_to_read.data[i]=0;
    read_data_buffer.frame_data.data[i]=0;
  }
}

void CanReaderWriter::SendFrame(int id, const uint8_t* data){
  this->cf_to_write.id = id;

  //for(int i =0;i<8;i++){
  //  this->cf_to_write.data[i]=data[i];
  //}

  std::memcpy(cf_to_write.data,data, 8*sizeof(uint8_t));

  auto write_sc_status = this->socket_can.write(this->cf_to_write);

}

void CanReaderWriter::read()
{
    if (socket_can.read(cf_to_read) == scpp::STATUS_OK) 
    {
        //Notify all subscribers
        //Update Frame data
        
    }
    /*else 
    {
       // for (size_t i = 0; i < 9999; i++); //STUPID SLEEP?
    }*/
}

FrameData CanReaderWriter::getData()
{
  std::lock_guard<std::mutex> lk_grd(read_data_buffer.mtx);
  return read_data_buffer.frame_data;
}

void CanReaderWriter::SendShutdownCommand(int id,const uint8_t* data){
  for(int i =0;i<4;i++){
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    this->SendFrame(id,data);
  }
}

void CanReaderWriter::updateReadData()
{
  if(cf_to_read.id == 1)
    {
        std::lock_guard<std::mutex> lk_grd(read_data_buffer.mtx);

        std::memcpy(read_data_buffer.frame_data.data, cf_to_read.data, sizeof(read_data_buffer.frame_data.data));

        //8*(sizeof(uint8_t))
    }
}