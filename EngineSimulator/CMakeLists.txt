cmake_minimum_required(VERSION 3.15)
project(EngineSimulator)

include_directories(include)
include_directories(../InputHandler/include)

add_executable(EngineSimulator 
               src/transmition.cpp
               src/can_encoder.cpp
               src/main.cpp
               ../InputHandler/src/can_writer.cpp
               ../InputHandler/src/socketcan_cpp.cpp
               src/can_reader.cpp
               )