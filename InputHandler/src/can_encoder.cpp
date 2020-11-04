#include "can_encoder.hpp"

void CanEncoder::Encode(int input, uint8_t* data){
  if(input == 'S'){
    data[7] = 1;
  } else if(input == 's'){
    data[7] = 0;
  } else if(input == 'a'){
    if (data[6]>0) data[6]-=0x10;
  } else if(input == 'A'){
    if(data[6]<0xA0) data[6]+=0x10;
  } else {
    //std::cout << "this key was pressed: " << ch << std::endl;
  }
}