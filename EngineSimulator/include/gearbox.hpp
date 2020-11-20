#ifndef GEARBOX_HPP
#define GEARBOX_HPP
#include <iostream>
#include <cmath>
#include <array>

enum class GearMode {N, D, R};

namespace gearboxparams
{
    static const uint16_t kGearUpRpmHi = 7000;
    static const uint16_t kGearUpRpmLo = 4700;
    static const uint16_t kGearDownRpm = 1500;
}

class Gearbox
{
private:
    GearMode gear_mode;
    uint8_t  gear;
    uint16_t speed;

public:
    void setGearMode(const GearMode&);
    void updateSpeed(const uint16_t& ARPM);
    void gearShiftUp();
    void gearShiftDown();
    GearMode getGearMode();
    uint16_t getSpeed();
    uint8_t getGear();

    Gearbox();
    std::array<double,7> gear_ratio = {
        0,
        1.2/250,
        1.2/150,
        1.2/100,
        1.2/70,
        1.2/55,
        1.2/50
    };
    ~Gearbox()=default;
};

#endif
