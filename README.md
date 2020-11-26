# Engine Simulator
Engine simulator is a software which accepts input signals and simulates the behaviour of a mechanical Engine by providing output signals. Please refer below picture for an overview of MVP(Minimum Viable Product)

https://github.com/pepema/EGsim/blob/main/EngineSimulatorMVP.png

The project has 3 binaries and the sequence diagram for the binaries is explained in the below picture.

## Input Handler

Input handler is accepting user inputs from a keyboard and encodes it to a CAN frame for Engine simulator.

## Engine Simulator

Engine simulator takes a CAN frame with input signals. It simulates Engine behaviour for those inputs. It then encodes a CAN frame with updated values for output signals.

## Instrument Cluster

Instrument cluster is accepting a CAN frame conatining signals. It then animates the User interface as an instrument cluster of a car. It updates the animation based on new CAN frames it recieves.
