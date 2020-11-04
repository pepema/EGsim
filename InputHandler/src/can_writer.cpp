#include "can_writer.hpp"

CanWriter::CanWriter(int id, int length){
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