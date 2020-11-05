#include "engine.h"

void Engine::updateTRPM(uint8_t acceleration){
    if (acceleration==0){
        this->TRPM=700;
    }
    else
        this->TRPM=700+(10000-700)*acceleration/100;
    }

void Engine::updateARPM(uint8_t acceleration){
    if (this->ARPM<this->TRPM){
        this->ARPM=this->ARPM+10*acceleration/100;
    }
}