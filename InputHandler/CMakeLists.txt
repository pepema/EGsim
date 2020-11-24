cmake_minimum_required(VERSION 3.15)
project(InputHandler)

include_directories(include)
include_directories(../Utils/socketcan)
include_directories(../Utils/canreaderwriter)

add_executable(InputHandler 
               src/main.cpp
               src/can_encoder.cpp
               src/input_handler.cpp
               ../Utils/socketcan/socketcan_cpp.cpp
               ../Utils/canreaderwriter/can_reader_writer.cpp
               )

target_link_libraries(InputHandler ncurses pthread)

set(CMAKE_BUILD_TYPE Debug)

set_target_properties(InputHandler
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)