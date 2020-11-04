#include <iostream>

class CanEncoder{
public:
  void Encode(int input, uint8_t* data);
  CanEncoder() = default;
  ~CanEncoder() = default;
};