#include "engine.h"

void Engine::updateTRPM(const uint8_t& acceleration, const uint8_t& brake){
    if(this->engine_STC)
        if (acceleration >= brake)
            this->TRPM=700+(10000-700)*(acceleration-brake)/100;
        else
            this->TRPM=700;
    else
        this->TRPM=0;
    }
    

void Engine::updateARPM(const uint8_t& brake){
    double vroom=static_cast<double>(this->TRPM-this->ARPM)/300;

    if (brake == 0){
        if (vroom > 0){
            this->ARPM+=vroom;
        }
        else if (vroom < 0){
            this->ARPM-=3;
        }
    }
    else if (brake > 0){
        if (vroom > 0){
            this->ARPM+=vroom;
        }
        else if (vroom < 0){
            this->ARPM-=3 + 3*(1+brake/30);
        }
    }       
    
}


Engine::Engine(){
    engine_STC = false;
    ARPM = 0;
    TRPM = 0;
    hazard = false;
}

uint16_t Engine::getARPM(){
    return static_cast<uint16_t>(ARPM);
}

bool Engine::getEngineStatus(){
    return engine_STC;
}
void Engine::setEngineStatus(const bool& ES){
    engine_STC = ES;
}

void Engine::setHazard(const bool& hazard)
{
    if(hazard == true)
    {
        engine_STC = false;
    }
    this->hazard = hazard;
}

bool Engine::getHazard()
{
    return hazard;
}
