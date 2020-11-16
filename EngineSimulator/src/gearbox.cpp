#include "gearbox.h"

Gearbox::Gearbox(){
    gear_mode=GearMode::N;
    gear=0;
    speed=0;
 }

void Gearbox::updateGear(const GearMode& gear_mode){
    this->gear_mode = gear_mode;
}

void Gearbox::updateSpeed(const uint16_t& ARPM){
    double tempspeed;
    if (gear_mode==GearMode::D)
        if(ARPM>700)
            if(gear==1)
                tempspeed = (ARPM-700)*gear_ratio[gear];
            else if(gear > 1)
                tempspeed = ARPM*gear_ratio[gear];
        else
            tempspeed = 0;
        
    else if (gear_mode==GearMode::N)
        tempspeed = 0;

    else if (gear_mode==GearMode::R)
        if(ARPM>700)
            tempspeed = (ARPM-700)/150;
        else
            tempspeed = 0;

    speed = tempspeed;
}


void Gearbox::gearShiftUp(){

    //std::cout << "shifting up" << std::endl;
    gear +=1;
}

void Gearbox::gearShiftDown(){

    std::cout << "shifting down" << std::endl;
    gear -=1;
}

GearMode Gearbox::getGearMode(){
    return gear_mode;
}


uint16_t Gearbox::getSpeed(){
    return speed;

}


uint8_t Gearbox::getGear(){
    return gear;
}
