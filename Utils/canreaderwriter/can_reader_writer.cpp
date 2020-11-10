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
  }
}

void CanReaderWriter::SendFrame(int id, uint8_t* data){
  this->cf_to_write.id = id;

  for(int i =0;i<8;i++){
    this->cf_to_write.data[i]=data[i];
  }
  auto write_sc_status = this->socket_can.write(this->cf_to_write);

}

void CanReaderWriter::read()
{
    if (socket_can.read(cf_to_read) == scpp::STATUS_OK) 
    {
        //Notify all subscribers
        //Update Frame data
        
    }
    else 
    {
       // for (size_t i = 0; i < 9999; i++); //STUPID SLEEP?
    }
}

FrameData CanReaderWriter::getData()
{
    /*
    FrameData frameDataToPass;
    if(cf_to_read.id == 1)
    {
        for (size_t i = 0; i < 8; i++)
        {
            frameDataToPass.data[i] = cf_to_read.data[i];    //Should we do this tcopy by ref?
        }
    }
    return frameDataToPass;
    */
  std::lock_guard<std::mutex> lk_grd(read_data_buffer.mtx);
  return read_data_buffer.frame_data;
}

void CanReaderWriter::updateReadData()
{
  if(cf_to_read.id == 1)
    {
        std::lock_guard<std::mutex> lk_grd(read_data_buffer.mtx);
        for (size_t i = 0; i < 8; i++)
        {
            read_data_buffer.frame_data.data[i] = cf_to_read.data[i];    //Should we do this tcopy by ref?
        }
    }
}