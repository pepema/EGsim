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
  }
}

void CanReaderWriter::writeData(uint8_t id, const FrameData & output_data){
  this->cf_to_write.id = id;

  std::memcpy(cf_to_write.data,output_data.data, 8*sizeof(FrameData));

  auto write_sc_status = this->socket_can.write(this->cf_to_write);

}

void CanReaderWriter::readData(uint8_t id, DataBuffer &read_data_buffer)
{
  if (socket_can.read(cf_to_read) == scpp::STATUS_OK);
  if(cf_to_read.id == id)
  {
    std::lock_guard<std::mutex> lk_grd(read_data_buffer.mtx);
    std::memcpy(read_data_buffer.frame_data.data, cf_to_read.data, sizeof(read_data_buffer.frame_data));
  }
}