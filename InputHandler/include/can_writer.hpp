#include "socketcan_cpp.h"

class CanWriter{
public:
  CanWriter(int id, int length);
  ~CanWriter()=default;
  scpp::CanFrame GetFrame();
  uint8_t* GetFrameData();
private:
  scpp::CanFrame cf_to_write;
};