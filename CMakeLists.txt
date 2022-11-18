# Just a recent number
cmake_minimum_required(VERSION 3.18)

# Determine the Arduino path, with all Arduino related libraries and generic cmake stuff
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    set(ARDUINO_PATH $ENV{HOME}/Arduino)
    set(AVR_PORT /dev/ttyACM0)
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(ARDUINO_PATH "$ENV{HOMEDRIVE}$ENV{HOMEPATH}/Arduino")
    set(AVR_PORT COM6)
endif()

# the toolchain to use
set(CMAKE_TOOLCHAIN_FILE ${ARDUINO_PATH}/etc/toolchain-avr.cmake)

# include standard extra targets, like 'upload'
set(CMAKE_PROJECT_INCLUDE ${ARDUINO_PATH}/etc/extratargets-avr.cmake)

# Project name (also the name of the target)
project(croaker)

include_directories(
    lib
)

# Create one target. To generate a list of source files: `find src -name \*.c\*`
add_executable(${PROJECT_NAME}
    src/main.cpp
)

# Add libraries: mind the order!
target_include_directories(${PROJECT_NAME}
    PRIVATE "${ARDUINO_PATH}/include/arduino"
)
target_link_directories(${PROJECT_NAME}
    PRIVATE "${ARDUINO_PATH}/lib"
)
target_link_libraries(${PROJECT_NAME}
    ILI9341
    GFX
    BusIO
    SPI
    Nunchuk
    Wire
    ArduinoCore
)

# Rename the output to .elf as we will create multiple files
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}.elf)