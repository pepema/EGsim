#include "can_encoder.hpp"

using index_and_data = std::pair<int, int>;
using keymap = std::unordered_map<char, index_and_data>;
const keymap CanEncoder::valid_keys = create_keymap();

bool CanEncoder::ValidKey(const int &key, uint8_t *const data)
{
  bool returnvalue = false;
  if (valid_keys.count(key) != 0)
  {
    auto search = valid_keys.find(key);
    if (search->first == 'A' || search->first == 'B')
      if (data[search->second.first] >= 100)
        returnvalue = false;
      else
        returnvalue = true;
    else if (search->first == 'a' || search->first == 'b')
      if (data[search->second.first] <= 0)
        returnvalue = false;
      else
        returnvalue = true;
    else
      returnvalue = true;
  }
  else
  {
    returnvalue = false;
  }
  return returnvalue;
}

void CanEncoder::Encode(const int &input, uint8_t *const data)
{
  auto search = valid_keys.find(input);
  if (search->first == 'A' || search->first == 'B' || search->first == 'a' || search->first == 'b')
    data[search->second.first] += search->second.second;
  else if (search->first >= 43 && search->first <= 57)
    data[search->second.first] ^= 1 << search->second.second;
  else
    data[search->second.first] = search->second.second;
}
