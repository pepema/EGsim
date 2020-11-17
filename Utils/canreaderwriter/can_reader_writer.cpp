#include <cstring>
#include "can_reader_writer.hpp"

CanReaderWriter::CanReaderWriter(){
  if (socket_can.open("vcan0") != scpp::STATUS_OK){
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit (-1);
  }
  int length = 8;
  can_frame.len = length;
  std::memset(can_frame.data, 0, length);
}

void CanReaderWriter::writeData(uint8_t id, const FrameData & output_data){
  this->can_frame.id = id;
  std::memcpy(can_frame.data,output_data.data, 8*sizeof(FrameData));
  auto write_sc_status = this->socket_can.write(this->can_frame);
}

void CanReaderWriter::readData(uint8_t id, DataBuffer &read_data_buffer)
{
  if (socket_can.read(can_frame) == scpp::STATUS_OK);
  if(can_frame.id == id)
  {
    std::lock_guard<std::mutex> lk_grd(read_data_buffer.mtx);
    std::memcpy(read_data_buffer.frame_data.data, can_frame.data, sizeof(read_data_buffer.frame_data));
  }
}