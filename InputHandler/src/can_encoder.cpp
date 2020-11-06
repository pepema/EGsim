#include "can_encoder.hpp"

void CanEncoder::Encode(int input, uint8_t* data){
  if(input == 'S'){
    data[7] = 1;
  } else if(input == 's'){
    data[7] = 0;
  } else if(input == 'a'){
    if (data[6]>0) data[6]-=10;
  } else if(input == 'A'){
    if(data[6]<100) data[6]+=10;
  } else if(input == 'd'){
    data[5] = 1;
  } else if(input == 'n'){
    data[5] = 0;
  } else if(input == 'r'){
    data[5] = 2;
  }
}