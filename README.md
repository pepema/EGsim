# Engine Simulator
Engine simulator is a software which accepts input signals and simulates the behaviour of a mechanical Engine by providing output signals. Please refer below picture for an overview of MVP(Minimum Viable Product)

https://github.com/pepema/EGsim/blob/main/EngineSimulatorMVP.png

The project has 3 binaries and the sequence diagram for the binaries is explained in the below picture.

https://github.com/pepema/EGsim/blob/main/SequenceDiagram.png

### Input Handler

Input handler is accepting user inputs from a keyboard and encodes it to a CAN frame for Engine simulator.

### Engine Simulator

Engine simulator takes a CAN frame with input signals. It simulates Engine behaviour for those inputs. It then encodes a CAN frame with updated values for output signals.

### Instrument Cluster

Instrument cluster is accepting a CAN frame conatining signals. It then animates the User interface as an instrument cluster of a car. It updates the animation based on new CAN frames it recieves.

## Build and run

We have a shell script to do the following:
1) Initialize and start the socket
2) Build the binaries
3) Launch the executables

It is called runAll.sh.

Alternatively you could ofcourse use cmake files for the binaries to launch them seperately of use a commmon cmake for all binaries.

## Unit test

We have some test cases in gtest framework for Engine class which is a part of Engine Simulator.
Using the cmake file you can run the tests.

## Backlog

We documented the backlog using the scrum board tool and the link to it is as below.

http://scrumblr.ca/BOOTCAMP%20TEAM%20B
