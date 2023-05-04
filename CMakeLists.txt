# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "PICO_SDK_PATH: ${PICO_SDK_PATH}")

set(PICO_BOARD
    pico_w
    CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(BigBlinkingButton C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(BigBlinkingButton BigBlinkingButton.cpp usb_descriptors.c)

pico_set_program_name(BigBlinkingButton "BigBlinkingButton")
pico_set_program_version(BigBlinkingButton "0.1")

pico_enable_stdio_uart(BigBlinkingButton 1)
pico_enable_stdio_usb(BigBlinkingButton 0)

# Add the standard library to the build
target_link_libraries(BigBlinkingButton pico_stdlib)

# Add the standard include files to the build
target_include_directories(
  BigBlinkingButton
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
          ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other
                                       # standard includes, if required
          ${CMAKE_SOURCE_DIR}/include)

# Add any user requested libraries
target_link_libraries(BigBlinkingButton tinyusb_device tinyusb_board)

pico_add_extra_outputs(BigBlinkingButton)
