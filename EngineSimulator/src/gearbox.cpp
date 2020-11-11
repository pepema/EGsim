#include "gearbox.h"

Gearbox::Gearbox(){
    gear=Gear::N;
    gearnumber=0;
    speed=0;
 }

void Gearbox::updateGear(const uint8_t& gearin, const uint8_t& brake){
    
    if(speed==0 && brake>0)
        if(gearin==1)
            gear=Gear::D;
        else if(gearin==2)
            gear=Gear::R;
        else
            gear=Gear::N;
}

void Gearbox::updateSpeed(const uint16_t& ARPM){
    
    if (gear==Gear::D)    
        if(ARPM>700)
            speed = (ARPM-700)/55;
        else
            speed = 0;
        
    else if (gear==Gear::N)
        speed = 0;

    else if (gear==Gear::R)
        if(ARPM>700)
            speed = (ARPM-700)/150;
        else
            speed = 0;
}


void Gearbox::updateGearnumber(){

}
Gear Gearbox::getGear(){
    return gear;
}


uint16_t Gearbox::getSpeed(){
    return speed;

}
