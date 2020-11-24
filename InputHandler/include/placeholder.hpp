#include <iostream>
#include <unordered_map>

using index_and_data = std::pair<int,int>;
using keymap = std::unordered_map<char,index_and_data>;

template <typename KeyboardReader>
class InputReader{
public:
  InputReader() = delete;
  InputReader(const KeyboardReader& );

private:
  keymap valid_keys;
};