#include "engine.h"

void Engine::updateTRPM(const uint8_t& acceleration){
    if(this->engine_STC)
        if (acceleration==0)
            this->TRPM=700;  
        else
            this->TRPM=700+(10000-700)*acceleration/100;
    else
        this->TRPM=0;
    }
    

void Engine::updateARPM(const uint8_t& acceleration){
    double vroom=static_cast<double>(this->TRPM-this->ARPM)/400;
    this->ARPM+=vroom;
    }


Engine::Engine(){
    engine_STC = false;
    ARPM = 0;
    TRPM = 0;
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
