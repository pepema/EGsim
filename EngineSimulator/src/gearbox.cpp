#include "gearbox.h"

Gearbox::Gearbox(){
    gear_mode=GearMode::N;
    gear=0;
    speed=0;
 }

void Gearbox::updateGear(const uint8_t& gearin, const uint8_t& brake){
    
    if(speed==0 && brake>0)
        if(gearin==1)
            gear_mode=GearMode::D;
        else if(gearin==2)
            gear_mode=GearMode::R;
        else
            gear_mode=GearMode::N;
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
    gear +=1;
}

void Gearbox::gearShiftDown(){
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
