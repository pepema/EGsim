#ifndef ENGINE_H
#define ENGINE_H
#include <iostream>
#include "gearbox.h"
#include "fuel_calculator.hpp"
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

    int fuel_level = 100000000, fuel_used_last_cycle=0, fuel_age=0;
public:
    void setEngineStatus(const bool& ES);
    void updateTRPM(const uint8_t& accel);
    void updateARPM(const uint8_t& brake, const GearMode& gear);
    bool getEngineStatus();
    uint16_t getARPM();
    void setHazard(const bool& hazard);
    bool getHazard();
    inline int getFuelLevel() {return fuel_level/1000000;}
    inline int GetFuelUsed() {return fuel_used_last_cycle;}
    inline int GetFuelAge() {return fuel_age;}
    FuelCalculator* fuel_calculator;

    Engine();
 
    ~Engine()=default;
};

#endif
