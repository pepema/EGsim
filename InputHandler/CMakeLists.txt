cmake_minimum_required(VERSION 3.15)
project(InputHandler)

include_directories(include)

add_executable(InputHandler 
               src/input_handler.cpp
               src/socketcan_cpp.cpp
               src/main.cpp
               src/can_reader_writer.cpp
               src/can_encoder.cpp
               )

target_link_libraries(InputHandler ncurses)

set_target_properties(InputHandler
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)