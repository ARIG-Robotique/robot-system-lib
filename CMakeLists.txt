#=============================================================================#
# Author: Gregory DEPUILLE                                                    #
# Date:   13/05/2016                                                          #
# Description: Arduino CMake librairie robot                                  #
#=============================================================================#

# Récupération des sources
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")
file(GLOB_RECURSE HEADERS "src/*.h")

#message(STATUS "Robot System lib sources : ${SOURCES}")
#message(STATUS "Robot System lib headers : ${HEADERS}")

# Génération de la lib pour Arduino Nano
generate_arduino_library(RobotNano SRCS ${SOURCES} HDRS ${HEADERS} BOARD nano328)

# Génération de la lib pour Arduino Mega 2560 ou Mega ADK
generate_arduino_library(RobotMega SRCS ${SOURCES} HDRS ${HEADERS} BOARD mega2560)
