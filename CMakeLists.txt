#=============================================================================#
# Author: Gregory DEPUILLE                                                    #
# Date:   13/05/2016                                                          #
# Description: Arduino CMake librairie robot                                  #
#=============================================================================#

# Contrôle de la version minimale de CMake
cmake_minimum_required(VERSION 3.8.2)

# Définition de la tool chain de build
set(CMAKE_TOOLCHAIN_FILE ./cmake/Arduino-Toolchain.cmake)

# Compilateur flags
#set(ARDUINO_C_FLAGS      "-ffunction-sections -fdata-sections")
#set(ARDUINO_CXX_FLAGS    "${ARDUINO_C_FLAGS} -fno-exceptions")
#set(ARDUINO_LINKER_FLAGS "-Wl,--gc-sections")

set(ARDUINO_CXX_FLAGS    "-std=c++11")

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message(STATUS "Debug mode ON")
    add_definitions(-DDEBUG_MODE)
endif()

#====================================================================#
#  Setup Project                                                     #
#====================================================================#
project(RobotSystemLib C CXX ASM)
arduino_cmake_project(RobotSystemLib BOARD_NAME megaADK BOARD_CPU atmega2560)

# Récupération des sources
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")
file(GLOB_RECURSE HEADERS "src/*.h")

# Génération de la lib
add_library(RobotSystem STATIC ${SOURCES} ${HEADERS})
target_include_directories(RobotSystem PUBLIC src)

# Wire lib
find_arduino_library(wire Wire)
link_arduino_library(RobotSystem wire)
