cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME DroneProject)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 14)

add_executable(Test main.cpp src/core/io/command/CommandParser.cpp src/core/io/command/CommandParser.hpp src/core/io/command/Command.cpp src/core/io/command/Command.hpp src/core/io/command/internal/ConfigCommand.cpp src/core/io/command/internal/ConfigCommand.hpp src/core/io/command/internal/HelpCommand.cpp src/core/io/command/internal/HelpCommand.hpp src/core/io/command/CommandWrapper.cpp src/core/io/command/CommandWrapper.hpp src/core/io/reader/FileStream.cpp src/core/io/reader/FileStream.hpp src/util/TypeUtil.hpp src/util/StringUtil.cpp src/util/StringUtil.hpp src/util/ArrayUtil.cpp src/util/ArrayUtil.hpp)