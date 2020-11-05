#ifndef ENGINE_H
#define ENGINE_H
#include <iostream>
using namespace std;


// Defining class and it's members(variables and functions)

class Engine
{
private:
    bool engine_STC;
    uint16_t  ARPM, TRPM;

public:
    void setEngineStatus(const bool& ES);
    void updateTRPM(const uint8_t& accel);
    void updateARPM(const uint8_t& accel);

    bool getEngineStatus();

    uint16_t getARPM();

    Engine();
 
    ~Engine()=default;
};

#endif
