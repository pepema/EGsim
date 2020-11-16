#!/usr/bin/env bash

if [ $1 == "rebuild" ]
then
  rm -r build
  cmake -S . -B build
fi
vcanUp=$(ip link show | grep -c "vcan0: <NOARP,UP")

if [ $vcanUp -eq 0 ]; then ./vcanStart.sh ; fi
if [ $1 == "can" ]
then
gnome-terminal --window --geometry 50x20+0+0 --title=CAN_001 -x candump vcan0,001:FFFFFFFF
gnome-terminal --window --geometry 50x20+10000+0 --title=CAN_002 -x candump vcan0,002:FFFFFFFF
fi
cmake --build build
gnome-terminal --title=Engine_Simulator_State --geometry 100x5+500+1000 -e ./build/bin/EngineSimulator
gnome-terminal -x ./build/bin/avic -c vcan0
gnome-terminal --title=Input --geometry 3x3+50+1000 -e ./build/bin/InputHandler

