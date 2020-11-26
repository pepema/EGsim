#include<iostream>
#include<unordered_map>
#include<functional>

/*---------------------------------------------------------------------
This is a super nice program for practicing stuff
----------------------------------------------------------------------*/
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
void GenericEncode(void* obj, void* input, uint8_t* data){
  auto t = static_cast<T*>(obj);
  auto it = static_cast<typename T::inputType*>(input);
  t->Encode(*it,data);
}

void PrintData(uint8_t* data){
  for(int i=0;i<8;i++){
    std::cout << static_cast<int>(data[i]) << std::endl;
  }
}

struct EncodingList{
  void EncodeEngine(void* engine_status, uint8_t* data){
    auto a = static_cast<bool*>(engine_status);
    data[0] = static_cast<bool>(*a);
  }
  void EncodeRpm(void* rpm, uint8_t* data){
    auto actual_rpm = static_cast<uint16_t*>(rpm);
    data[2] = *actual_rpm >> 8;
    data[1] = *actual_rpm & 255;
  }
};

int main(){
  uint8_t data [8] = {0,1,2,3,4,5,6,7};
  EngineStatus ES;
  RPM rpm;
  bool b = true;
  uint16_t new_rpm = 1337;

  GenericEncode<EngineStatus>(&ES, &b, data);
  GenericEncode<RPM>(&rpm, &new_rpm, data);

  using EncodingFunction = void(EncodingList::*)(void*,uint8_t*);
  EncodingFunction Engine = &EncodingList::EncodeEngine;
  EncodingFunction Rpm = &EncodingList::EncodeRpm;
  EncodingList list;

  std::function<void(void*,uint8_t*)> cool_name = [&](void* p,uint8_t* data){
    (list.*Engine)(&b,data);
  };

  std::function<void(void*,uint8_t*)> cool_name_2 = [&](void* p,uint8_t* data){
    (list.*Rpm)(&new_rpm,data);
  };

  PrintData(data);

}
