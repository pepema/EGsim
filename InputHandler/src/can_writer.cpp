#include "can_writer.hpp"

CanWriter::CanWriter(int id, int length){

  if (socket_can.open("vcan0") != scpp::STATUS_OK) {
  std::cout << "Cannot open vcan0." << std::endl;
  std::cout << "Check whether the vcan0 interface is up!" << std::endl;
  exit (-1);
  }

  this->cf_to_write.id = id;
  this->cf_to_write.len = length;
  this->cf_to_write.data[length] = {};
  for(int i =0;i<length;i++){
    cf_to_write.data[i]=0;
  }
}

scpp::CanFrame CanWriter::GetFrame(){
  return this->cf_to_write;
}

uint8_t* CanWriter::GetFrameData(){
  return this->cf_to_write.data;
}

void CanWriter::SendFrame(int id, uint8_t* data){
  cf_to_write.id = id;
  
  for(int i =0;i<8;i++){
    cf_to_write.data[i]=data[i];
  }
  auto write_sc_status = socket_can.write(cf_to_write);
}