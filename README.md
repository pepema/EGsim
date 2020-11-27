# Engine Simulator
Engine simulator is a software which accepts input signals and simulates the behavior of a mechanical Engine by providing output signals. Please refer below picture for an overview of MVP(Minimum Viable Product)

![Alt text](Documentation/EngineSimulatorMVP.png?raw=true "Engine Simulator")

The project has 3 binaries and the sequence diagram for the binaries is explained in the below picture.

![Alt text](Documentation/SequenceDiagram.png?raw=true "Sequence Diagram")

### Input Handler

Input handler is accepting user inputs from a keyboard and encodes it to a CAN frame for Engine simulator.

### Engine Simulator

Engine simulator takes a CAN frame with input signals. It simulates Engine behavior for those inputs. It then encodes a CAN frame with updated values for output signals.

### Instrument Cluster

Instrument cluster is accepting a CAN frame containing signals. It then animates the User interface as an instrument cluster of a car. It updates the animation based on new CAN frames it receives.

## External libraries used

In order to run this program you need to install some external libraries:
1. g++ tools `sudo apt install build-essential gdb`
1. cmake `sudo apt-get install cmake`
1. ncurses `sudo apt-get install ncurses-dev`
2. can utils `sudo apt-get install can-utils`
3. qt5: `sudo apt-get install <command>` with the following commands (put them space separated if you're fancy)
    1. qt5-default
    2. qtdeclarative5-dev
    3. qtquickcontrols2-5-dev
    4. libgles2-mesa-dev
    5. qtquickcontrols2-5-dev
    6. qml-module-qtquick-controls
    7. qml-module-qtquick-extras
4. google test: https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/


## Build and run

We have a shell script to do the following:
1) Initialize and start the socket
2) Build the binaries
3) Launch the executables

It is called runAll.sh.  
So, in order to build and run our program:  
`./Sripts/runAll.sh rebuild`  
**Note: CMAKE version 3.10 minimum required**

Alternatively you could of course use cmake files for the binaries to launch them separately of use a common cmake for all binaries.

## Unit test

We have some test cases in gtest framework for Engine class which is a part of Engine Simulator.
Using the cmake file you can build the tests and run them:  
`./Scripts/testsRun.sh`

## Backlog

We documented the backlog using the scrum board tool and the link to it is as below.

http://scrumblr.ca/BOOTCAMP%20TEAM%20B
