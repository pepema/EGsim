#ifndef ENGINE_H
#define ENGINE_H
#include <iostream>
using namespace std;


class Engine
{
private:
    bool engine_STC;
    uint16_t  TRPM;
    double ARPM;
    bool hazard;

public:
    void setEngineStatus(const bool& ES);
    void updateTRPM(const uint8_t& accel, const uint8_t& brake);
    void updateARPM(const uint8_t& accel);

    bool getEngineStatus();

    uint16_t getARPM();
    void setHazard(const bool& hazard);
    bool getHazard();

    Engine();
 
    ~Engine()=default;
};

#endif
