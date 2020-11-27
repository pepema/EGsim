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
  CanEncoder() = default;
  ~CanEncoder() = default;
  bool ValidKey(const int &key, uint8_t *const data);
  static keymap create_keymap()
  {
    keymap vk;
    vk['S'] = {7,1};
    vk['s'] = {7,0};
    vk['A'] = {6,10};
    vk['a'] = {6,-10};
    vk['d'] = {5,1};
    vk['n'] = {5,0};
    vk['r'] = {5,2};
    vk['B'] = {4,10};
    vk['b'] = {4,-10};
    vk[27] = {0,1};

    //icons
    vk['1'] = {1,0};
    vk['2'] = {1,1};
    vk['3'] = {1,2};
    vk['4'] = {1,3};
    vk['5'] = {1,4};
    vk['6'] = {1,5};
    vk['7'] = {1,6};
    vk['8'] = {1,7};

    vk['9'] = {2,0};
    vk['0'] = {2,1};
    vk['+'] = {2,2};
    return vk;
  }
  static const keymap valid_keys;
};

#endif