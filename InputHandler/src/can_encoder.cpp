#include "can_encoder.hpp"

void CanEncoder::Encode(int input, uint8_t* data){
  if (input == -1) {
    } else {
      if(input == 49){
        data[7] = 1;
      } else if(input == 50){
        data[7] = 0;
      } else if(input == 97){
        if (data[6]>0) data[6]-=0x10;
      } else if(input == 65){
        if(data[6]<0xA0) data[6]+=0x10;
      } else {
        //std::cout << "this key was pressed: " << ch << std::endl;
      }
    }
}