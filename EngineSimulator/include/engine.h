#ifndef ENGINE_H
#define ENGINE_H
#include <iostream>
#include "gearbox.h"
using namespace std;


class Engine
{
private:
    bool engine_STC;
    uint16_t  TRPM;
    double ARPM;
    bool hazard;
    const int idle_rpm = 700, standard_rpm_reduction = 3, start_stop_rpm_step = 15;
    void updateARPM_N();
    void updateARPM_D_R(const uint8_t& brake);
public:
    void setEngineStatus(const bool& ES);
    void updateTRPM(const uint8_t& accel);
    void updateARPM(const uint8_t& brake, const Gear& gear);

    bool getEngineStatus();

    uint16_t getARPM();
    void setHazard(const bool& hazard);
    bool getHazard();

    Engine();
 
    ~Engine()=default;
};

#endif
