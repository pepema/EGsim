#!/usr/bin/env bash

if [ $1 == "clean" ]
then
  rm -r build
  cmake -S . -B build
fi
cmake --build build
gnome-terminal --geometry 100x5+500+1000 -e ./build/bin/EngineSimulator
gnome-terminal -x ./build/bin/avic -c vcan0
gnome-terminal --geometry 3x3+50+1000 -e ./build/bin/InputHandler
