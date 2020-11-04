#include <curses.h>

class InputHandler{
public:
  InputHandler();
  ~InputHandler();
  int GetPressedKey();
private:
  int ch;
};