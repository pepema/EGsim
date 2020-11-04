#include "can_encoder.hpp"

void CanEncoder::Encode(int input){
  if (input == 0) {
    } else {
      if(this->ch == 49){
        data[7] = 1;
      } else if(ch == 50){
        data[7] = 0;
      } else if(ch == 97){
        if (data[6]>0) data[6]-=0x10;
      } else if(ch == 65){
        if(data[6]<0xA0) data[6]+=0x10;
      }
       else {
        //std::cout << "this key was pressed: " << ch << std::endl;
      }
    }
}