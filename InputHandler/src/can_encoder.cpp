#include "can_encoder.hpp"

CanEncoder::CanEncoder(){
  valid_keys.insert({'S',{7,1}});
  valid_keys.insert({'s',{7,0}});
  valid_keys.insert({'A',{6,10}});
  valid_keys.insert({'a',{6,-10}});
  valid_keys.insert({'d',{5,1}});
  valid_keys.insert({'n',{5,0}});
  valid_keys.insert({'r',{5,2}});
  valid_keys.insert({'B',{4,10}});
  valid_keys.insert({'b',{4,-10}});
  valid_keys.insert({27,{0,1}});

  //icons
  valid_keys.insert({'1',{1,0}});
  valid_keys.insert({'2',{1,1}});
  valid_keys.insert({'3',{1,2}});
  valid_keys.insert({'4',{1,3}});
  valid_keys.insert({'5',{1,4}});
  valid_keys.insert({'6',{1,5}});
  valid_keys.insert({'7',{1,6}});
  valid_keys.insert({'8',{1,7}});

  valid_keys.insert({'9',{2,0}});
  valid_keys.insert({'0',{2,1}});
  valid_keys.insert({'+',{2,2}});
}

bool CanEncoder::ValidKey(int a, uint8_t* data){
  bool returnvalue = false;
  if(valid_keys.count(a)!=0){
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
  else if(search->first >=43 && search->first<=57)
    data[search->second.first] ^= 1 << search->second.second;
  else
    data[search->second.first] = search->second.second;
}
