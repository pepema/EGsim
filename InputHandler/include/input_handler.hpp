#include <curses.h>

class InputHandler{
public:
  InputHandler();
  ~InputHandler() = default;
  void EncodeKeyPresses(uint8_t* data);
private:
  int ch;
};