#ifndef CAN_ENCODER_HPP
#define CAN_ENCODER_HPP

#include <iostream>
#include <unordered_map>

using index_and_data = std::pair<int,int>;
using keymap = std::unordered_map<char,index_and_data>;

class CanEncoder{
public:
  void Encode(int input, uint8_t* data);
  CanEncoder();
  ~CanEncoder() = default;
  bool ValidKey(int, uint8_t* data);
  keymap valid_keys;
};

#endif