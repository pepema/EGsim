#ifndef GEARBOX_H
#define GEARBOX_H
#include <iostream>

enum class Gear {N, D, R};

class Gearbox
{
private:
    Gear gear;
    uint8_t  gearnumber;
    uint16_t speed;

public:
    void updateGear(const uint8_t& gear);
    void updateSpeed(const uint16_t& ARPM);
    void updateGearnumber();
    Gear getGear();
    uint16_t getSpeed();

    Gearbox();
 
    ~Gearbox()=default;
};

#endif
