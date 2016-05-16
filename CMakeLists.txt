#=============================================================================#
# Author: Gregory DEPUILLE                                                    #
# Date:   13/05/2016                                                          #
#                                                                             #
# Description: Arduino CMake Quadratic Reader                                 #
#                                                                             #
#=============================================================================#
set(CMAKE_TOOLCHAIN_FILE ../arduino-cmake/cmake/ArduinoToolchain.cmake) # Arduino Toolchain

cmake_minimum_required(VERSION 2.8)
#====================================================================#
#  Setup Project                                                     #
#====================================================================#
project(RobotSystemLib C CXX)

print_board_list()
print_programmer_list()

#set(ARDUINO_DEFAULT_BOARD nano328) # Default Board ID, when not specified
#set(ARDUINO_DEFAULT_PORT /dev/ttyUSB0) # Default Port, when not specified

# Ajout des libs Arduino
link_directories(${ARDUINO_SDK_PATH}/libraries)

# Récupération des sources
file(GLOB SOURCES "src/**/*.cpp" "src/**/*.c")
file(GLOB HEADERS "src/**/*.h")

message(STATUS "Robot System lib sources : ${SOURCES}")
message(STATUS "Robot System lib headers : ${HEADERS}")

# Génération de la lib pour Arduino Nano
generate_arduino_library(RobotNano SRCS ${SOURCES} HDRS ${HEADERS} BOARD nano328)

# Génération de la lib pour Arduino Mega 2560 ou Mega ADK
generate_arduino_library(RobotMega SRCS ${SOURCES} HDRS ${HEADERS} BOARD mega2560)

# Génération de la lib pour Arduino Duemilanove w/ ATmega328
generate_arduino_library(RobotATMega328 SRCS ${SOURCES} HDRS ${HEADERS} BOARD atmega328)

# Génération de la lib pour Arduino Uno
generate_arduino_library(RobotUno SRCS ${SOURCES} HDRS ${HEADERS} BOARD uno)

# Génération de la lib pour Arduino Diecimila or Duemilanove w/ ATmega168
generate_arduino_library(RobotDiecimila SRCS ${SOURCES} HDRS ${HEADERS} BOARD diecimila)
