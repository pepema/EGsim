#include "can_writer.hpp"

CanWriter::CanWriter(){
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

void CanWriter::SendFrame(int id, uint8_t* data){
  this->cf_to_write.id = id;

  for(int i =0;i<8;i++){
    this->cf_to_write.data[i]=data[i];
  }
  auto write_sc_status = this->socket_can.write(this->cf_to_write);
}