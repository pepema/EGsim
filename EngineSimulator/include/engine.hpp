#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <iostream>
#include "gearbox.hpp"
#include "fuel_calculator.hpp"

namespace engparams
{
    static const uint16_t kIdleRpm = 700;                     //Idle RPM of the engine
    static const uint16_t kMaxRpm = 10000;                    //Maximum RPM of engine
    static const uint16_t kRpmWorkRange = kMaxRpm - kIdleRpm; //Working range of engine
    static const uint16_t kRpmIncrementDivisor = 300;         //Adjusts the acceleration
    static const uint8_t kStandardRpmReduction = 3;           //Rolling resistance
    static const uint8_t kStartStopRpmStep = 15;              //RPM rev up speed from zero to Idle
    static const uint8_t kShiftUpEngineAcc = 120;             //Incoming acceleration request signaling shift up behaviour
    static const uint8_t kShiftDownEngineAcc = 110;           //Incoming acceleration request signaling shift down behaviour
    static const uint16_t kTRPMforShiftDown = 0xFFFF;         //Target RPM used for shifting down
    static const uint16_t kTRPMforShiftUp = 0xFFFE;           //Target RPM used for shifting shift up
    static const uint16_t kRpmCapInDrive = 7525;              //Adjust top speed for 6th gear
} // namespace engparams

class Engine
{
private:
    bool engine_STC;
    uint16_t TRPM;
    double ARPM;
    bool hazard;
    void updateARPM_N();
    void updateARPM_D_R(const uint8_t &brake);
    int fuel_level = 100000000, fuel_used_last_cycle = 0, fuel_age = 0;

public:
    void setEngineStatus(const bool &ES);
    void updateTRPM(const uint8_t &accel);
    void updateARPM(const uint8_t &brake, const GearMode &gear);
    bool getEngineStatus();
    uint16_t getARPM();
    void setHazard(const bool &hazard);
    bool getHazard();
    inline int getFuelLevel() { return fuel_level / 1000000; }
    inline int GetFuelUsed() { return fuel_used_last_cycle; }
    inline int GetFuelAge() { return fuel_age; }
    FuelCalculator *fuel_calculator;
    Engine();
    ~Engine() = default;
};

#endif
