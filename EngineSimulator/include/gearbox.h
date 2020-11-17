#ifndef GEARBOX_H
#define GEARBOX_H
#include <iostream>
#include <cmath>
#include <array>




enum class GearMode {N, D, R};

class Gearbox
{
private:
    GearMode gear_mode;
    uint8_t  gear;
    uint16_t speed;

public:
    void updateGearMode(const GearMode&);
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
