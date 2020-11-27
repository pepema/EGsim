#!/usr/bin/env bash
 
if [ "$1" == "rebuild" ]
then
 rm -r build
 mkdir build
 cd build
 cmake ..
 cd ..
fi
vcanUp=$(ip link show | grep -c "vcan0: <NOARP,UP")
 
if [ $vcanUp -eq 0 ]; then ./Scripts/vcanStart.sh ; fi
if [ "$1" == "can" ]
then
gnome-terminal --window --geometry 50x20+0+0 --title=CAN_001 -- candump vcan0,001:FFFFFFFF
gnome-terminal --window --geometry 50x20+10000+0 --title=CAN_002 -- candump vcan0,002:FFFFFFFF
fi
cd build
make
cd ..
gnome-terminal --title=Engine_Simulator_State --geometry 100x5+500+1000 -- ./build/bin/EngineSimulator
gnome-terminal -- ./build/bin/avic -c vcan0
gnome-terminal --title=Input --geometry 3x3+50+1000 -- ./build/bin/InputHandler