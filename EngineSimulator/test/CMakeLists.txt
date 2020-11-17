cmake_minimum_required(VERSION 3.10)
project(EngineSimulatorTest)

################################
# GTest
################################
find_package(GTest REQUIRED)
enable_testing()

# Add test cpp file
add_executable(EngineSimulatorTest main.cpp)
# Link test executable against gtest & gtest_main
target_link_libraries(EngineSimulatorTest gtest gtest_main pthread)
add_test(EngineSimulatorTest runUnitTests )

set_target_properties(EngineSimulatorTest
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/test"
)