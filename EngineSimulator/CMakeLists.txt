cmake_minimum_required(VERSION 3.15)
project(EngineSimulator)
add_subdirectory(test)

include_directories(include)
include_directories(../Utils/socketcan)
include_directories(../Utils/canreaderwriter)

add_executable(EngineSimulator 
               src/main.cpp
               src/engine.cpp
               src/gearbox.cpp
               src/can_encoder.cpp
               src/signal_decoder.cpp
               src/control_module.cpp
               ../Utils/socketcan/socketcan_cpp.cpp
               ../Utils/canreaderwriter/can_reader_writer.cpp
               )

target_link_libraries(EngineSimulator pthread)

set_target_properties(EngineSimulator
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)