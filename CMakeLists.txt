# if PICO_SDK_PATH isn't defined, do not proceed
message(STATUS "PICO_SDK_PATH: ${PICO_SDK_PATH}")

cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD
    pico_w
    CACHE STRING "Board type")

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# ##############################################################################
# Install CPM if not already installed
set(CPM_DOWNLOAD_VERSION 0.38.1)
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
# ##############################################################################

# Export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ##############################################################################

# Pull in Raspberry Pi Pico SDK (must be before project)
include(cmake/pico_sdk_import.cmake)
project(SimplePicoMidiController CXX C ASM)
pico_sdk_init()
add_executable(SimplePicoMidiController SimplePicoMidiController.cpp usb_descriptors.c)

# Initialise the Raspberry Pi Pico SDK
pico_set_program_name(SimplePicoMidiController SimplePicoMidiController)
pico_set_program_version(SimplePicoMidiController "0.1")
pico_enable_stdio_uart(SimplePicoMidiController 1)
pico_enable_stdio_usb(SimplePicoMidiController 0)
pico_add_extra_outputs(SimplePicoMidiController)

# Add the standard include files to the build
target_include_directories(
  SimplePicoMidiController
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
          ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other
                                       # standard includes, if required
          ${CMAKE_SOURCE_DIR}/include)

# Add the standard library to the build
target_link_libraries(SimplePicoMidiController pico_stdlib tinyusb_device
                      tinyusb_board hardware_adc)

# ##############################################################################
# CPM Packages
# ##############################################################################

# Add the pico sdk as a CPM package
# cpmaddpackage(
#   NAME
#   pico-sdk
#   GITHUB_REPOSITORY
#   raspberrypi/pico-sdk
#   GIT_TAG
#   master
#   VERSION
#   1.5.0)

# Add Debounce
cpmaddpackage("gh:madskjeldgaard/PicoDebounceButton#main")
target_link_libraries(SimplePicoMidiController
                      PicoDebounceButton::PicoDebounceButton)

# Add PicoResponsiveAnalogRead
cpmaddpackage("gh:madskjeldgaard/PicoResponsiveAnalogRead#main")
target_link_libraries(SimplePicoMidiController
                      PicoResponsiveAnalogRead::PicoResponsiveAnalogRead)
