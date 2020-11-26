#ifndef CAN_ENCODER_HPP
#define CAN_ENCODER_HPP

#include <iostream>
#include <unordered_map>

using index_and_data = std::pair<int, int>;
using keymap = std::unordered_map<char, index_and_data>;

class CanEncoder
{
public:
  void Encode(const int &input, uint8_t *const data);
  CanEncoder();
  ~CanEncoder() = default;
  bool ValidKey(const int &key, uint8_t *const data);
  keymap valid_keys;
};

#endif