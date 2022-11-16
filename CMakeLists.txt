# Just a recent number
cmake_minimum_required(VERSION 3.18)

# Use AVR GCC toolchain definition in your HOME/Arduino directory
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    set(ARDUINO_PATH $ENV{HOME}/Arduino)
    set(AVR_PORT /dev/ttyACM0)
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(ARDUINO_PATH "C:/Users/{USER_PATH}/Arduino")
    set(AVR_PORT COM3)
endif()

# the toolchain to use
set(CMAKE_TOOLCHAIN_FILE ${ARDUINO_PATH}/etc/toolchain-avr.cmake)

# include standard extra targets, like 'upload'
set(CMAKE_PROJECT_INCLUDE ${ARDUINO_PATH}/etc/extratargets-avr.cmake)

# Project name
project("Croaker")

# Create one target
# (Linux) `find src -name \*.c\*`
add_executable(${PROJECT_NAME}
    src/main.cpp
)

# Add arduino core library
target_include_directories(${PROJECT_NAME} PRIVATE
    "${ARDUINO_PATH}/include/arduino"
)
target_link_directories(${PROJECT_NAME} PRIVATE
    "${ARDUINO_PATH}/lib"
)
target_link_libraries(${PROJECT_NAME}
    Nunchuk
    Wire
    ArduinoCore
)

# Rename the output to .elf as we will create multiple files
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}.elf)