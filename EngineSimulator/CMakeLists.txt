cmake_minimum_required(VERSION 3.15)
project(EngineSimulator)

include_directories(include)
include_directories(../InputHandler/include)

add_executable(EngineSimulator 
               src/signal_decoder.cpp
               src/can_encoder.cpp
               src/main.cpp
               ../InputHandler/src/can_reader_writer.cpp
               ../InputHandler/src/socketcan_cpp.cpp
               #src/can_reader.cpp
               src/engine.cpp
               src/gearbox.cpp
               )

set_target_properties(EngineSimulator
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)