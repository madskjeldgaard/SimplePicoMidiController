# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add CPM support for package management Add CPM
set(CPM_DOWNLOAD_VERSION 0.36.0)
set(CPM_DOWNLOAD_LOCATION
    "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
  message(STATUS "Downloading CPM.cmake")
  file(
    DOWNLOAD
    https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
    ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

# cpmaddpackage(NAME picosdkpackage GITHUB_REPOSITORY "raspberrypi/pico-sdk"
# GIT_TAG 1.5.0)

cpmaddpackage(NAME rp2040button GITHUB_REPOSITORY "TuriSc/RP2040-Button")

# Initialise pico_sdk from installed location (note this can come from
# environment, CMake cache etc) set(PICO_SDK_PATH ${picosdkpackage_SOURCE_DIR})
set(PICO_SDK_PATH "~/picosdk")

message(STATUS "PICO_SDK_PATH: ${PICO_SDK_PATH}")

set(PICO_BOARD
    pico_w
    CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)
#
# if(PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0") message( FATAL_ERROR
# "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is
# ${PICO_SDK_VERSION_STRING}" ) endif()

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
