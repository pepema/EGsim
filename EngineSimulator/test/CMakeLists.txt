cmake_minimum_required(VERSION 3.10)
project(EngineSimulatorTest)

find_package(GTest REQUIRED)
enable_testing()
include_directories(../include)
include_directories(include)
# Add test cpp files
add_executable(EngineSimulatorTest 
                main.cpp 
                engine_test.cpp
                ../src/engine.cpp)
# Link test executable against gtest & gtest_main
#set(GMOCK_INCLUDE_DIRS /usr/local/include/gmock)
#set(GMOCK_BOTH_LIBRARIES /usr/local/lib/libgmock.a /usr/local/lib/libgmock_main.a /usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a)

target_link_libraries(EngineSimulatorTest gtest gtest_main gmock gmock_main pthread)
add_test(EngineSimulatorTest runUnitTests )

set_target_properties(EngineSimulatorTest
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/test"
)