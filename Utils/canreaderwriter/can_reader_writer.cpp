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
    //read_data_buffer.frame_data.data[i]=0;
    //write_data.data[i] = 0;
  }
}

void CanReaderWriter::writeData(uint8_t id, const FrameData & output_data){
  this->cf_to_write.id = id;

  std::memcpy(cf_to_write.data,output_data.data, 8*sizeof(FrameData));

  auto write_sc_status = this->socket_can.write(this->cf_to_write);

}

void CanReaderWriter::read()
{
    if (socket_can.read(cf_to_read) == scpp::STATUS_OK) 
    {        
    }
    else
    {
      /* code */
    }
    

}

/*
FrameData CanReaderWriter::getData(DataBuffer &read_data_buffer)
//uint8_t * CanReaderWriter::getData()
{
  std::lock_guard<std::mutex> lk_grd(read_data_buffer.mtx);
  return read_data_buffer.frame_data;
}
*/

/*
void CanReaderWriter::SendShutdownCommand(int id,const FrameData & output_data){
  for(int i =0;i<4;i++){
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    this->SendFrame(id,output_data);
  }
}
*/

void CanReaderWriter::readData(uint8_t id, DataBuffer &read_data_buffer)
{
  read();
  if(cf_to_read.id == id)
    {
        std::lock_guard<std::mutex> lk_grd(read_data_buffer.mtx);
        //for(auto i = 0; i < 8;i++)
        //{
        //  read_data_buffer_ptr->frame_data.data[i] = cf_to_read.data[i];
        //}
        std::memcpy(read_data_buffer.frame_data.data, cf_to_read.data, sizeof(read_data_buffer.frame_data));
    }
}

/*
uint8_t* CanReaderWriter::getWriteData(){
  return write_data.data;
}*/