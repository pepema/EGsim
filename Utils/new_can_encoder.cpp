#include<iostream>

struct EngineStatus{
  void Encode(const bool& engine_status, uint8_t* data){
    data[0] = engine_status;
  }
  using inputType = bool;
};

struct RPM{
  void Encode(const uint16_t& actual_rpm, uint8_t* data){
    data[2] = actual_rpm >> 8;
    data[1] = actual_rpm & 255;
  }
  using inputType = uint16_t;
};

struct Encoder{
  EngineStatus es;
  RPM rpm;
};

template <typename T>
void cc(void* obj, void* input, uint8_t* data){
  T* t = static_cast<T*>(obj);
  typename T::inputType* it =static_cast<typename T::inputType*>(input);
  t->Encode(*it,data);
}

void PrintData(uint8_t* data){
  for(int i=0;i<8;i++){
    std::cout << static_cast<int>(data[i]) << std::endl;
  }
}

int main(){
  uint8_t data [8] = {0,1,2,3,4,5,6,7};
  EngineStatus ES;
  RPM rpm;
  bool b = true;
  uint16_t new_rpm = 1337;
  cc<EngineStatus>(&ES, &b, data);
  cc<RPM>(&rpm, &new_rpm, data);
  PrintData(data);
}
