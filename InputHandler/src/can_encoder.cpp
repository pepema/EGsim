#include "can_encoder.hpp"

CanEncoder::CanEncoder(){
  valid_keys.insert({'S',{7,1}});
  valid_keys.insert({'s',{7,0}});
  valid_keys.insert({'A',{6,10}});
  valid_keys.insert({'a',{6,-10}});
}

bool CanEncoder::ValidKey(int a, uint8_t* data){
  bool returnvalue = false;
  if(valid_keys.contains(a)){
    auto search = valid_keys.find(a);
    if(search->first == 'A' || search->first == 'B')
      if(data[search->second.first]  >= 100 )
        returnvalue = false;
      else
        returnvalue = true;
    else if (search->first == 'a' || search->first == 'b')
      if(data[search->second.first]  <= 0 )
        returnvalue = false;
      else
        returnvalue = true;
    else
      returnvalue = true;
  } else {
    returnvalue = false;
  }
  return returnvalue;
}

void CanEncoder::Encode(int input, uint8_t* data){
  auto search = valid_keys.find(input);
  if(search->first == 'A' || search->first == 'B' || search->first == 'a' || search->first == 'b')
    data[search->second.first] += search->second.second;
  else
    data[search->second.first] = search->second.second;

  
  /*
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
  } else if(input == 'B'){
    if (data[4]< 100) data[4] += 10;
  } else if(input  == 'b'){
    if (data[4]> 0) data[4] -= 10;
  } else if(input == 27){
    data[0] = 1; 
  }*/
}
