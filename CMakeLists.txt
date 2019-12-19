cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME DroneProject)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

add_executable(Test main.cpp src/model/Drone.cpp src/model/Drone.hpp src/model/Server.cpp src/model/Server.hpp src/model/Position.cpp src/model/Position.hpp src/model/Vector2D.cpp src/model/Vector2D.hpp test/Vector2DTest.cpp)