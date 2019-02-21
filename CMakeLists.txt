#=============================================================================#
# Author: Gregory DEPUILLE                                                    #
# Date:   13/05/2016                                                          #
# Description: Arduino CMake librairie robot                                  #
#=============================================================================#

# Contrôle de la version minimale de CMake
cmake_minimum_required(VERSION 3.8.2)

# Définition de la tool chain de build
set(CMAKE_TOOLCHAIN_FILE ../arduino-cmake-ng/cmake/Arduino-Toolchain.cmake)

# Compilateur flags
#set(ARDUINO_C_FLAGS      "-ffunction-sections -fdata-sections")
#set(ARDUINO_CXX_FLAGS    "${ARDUINO_C_FLAGS} -fno-exceptions")
#set(ARDUINO_LINKER_FLAGS "-Wl,--gc-sections")

set(ARDUINO_CXX_FLAGS    "-std=c++11")

#add_definitions(-DDEBUG_MODE)

#====================================================================#
#  Setup Project                                                     #
#====================================================================#
project(RobotSystemLib C CXX ASM)

# Récupération des sources
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")
file(GLOB_RECURSE HEADERS "src/*.h")

# Génération de la lib
add_library(RobotSystem STATIC ${SOURCES} ${HEADERS})
target_include_directories(RobotSystem PUBLIC src)

find_library_header_files("${ARDUINO_CMAKE_PLATFORM_LIBRARIES_PATH}/Wire/src" wire_lib_headers)
find_library_source_files("${ARDUINO_CMAKE_PLATFORM_LIBRARIES_PATH}/Wire/src" wire_lib_source_files)
set(wire_lib_sources ${wire_lib_headers} ${wire_lib_source_files})
target_include_directories(RobotSystem PUBLIC ${ARDUINO_CMAKE_PLATFORM_LIBRARIES_PATH}/Wire/src)

# Example
get_board_id(board_id mega atmega2560)

add_arduino_executable(RobotExample ${board_id} examples/main.cpp examples/define.h)
link_platform_library(RobotExample Wire ${board_id})
link_arduino_library(RobotExample RobotSystem ${board_id})
