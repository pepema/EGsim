cmake_minimum_required(VERSION 3.15)
project(InputHandler)

include_directories(include)

add_executable(InputHandler 
               src/input_handler.cpp
               src/socketcan_cpp.cpp
               src/main.cpp
               src/can_writer.cpp
               )

target_link_libraries(InputHandler ncurses)