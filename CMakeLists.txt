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

project(SimplePicoMidiController C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(SimplePicoMidiController SimplePicoMidiController.cpp usb_descriptors.c)

pico_set_program_name(SimplePicoMidiController "SimplePicoMidiController")
pico_set_program_version(SimplePicoMidiController "0.1")

pico_enable_stdio_uart(SimplePicoMidiController 1)
pico_enable_stdio_usb(SimplePicoMidiController 0)

# Add the standard library to the build
target_link_libraries(SimplePicoMidiController pico_stdlib)

# Install CPM if not already installed
set(CPM_DOWNLOAD_VERSION 0.38.1)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
	message(STATUS "Downloading CPM.cmake")
	file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

# Add Debounce
CPMAddPackage("gh:madskjeldgaard/PicoDebounceButton#main")
target_link_libraries(SimplePicoMidiController PicoDebounceButton::PicoDebounceButton)

# Add PicoResponsiveAnalogRead
CPMAddPackage("gh:madskjeldgaard/PicoResponsiveAnalogRead#main")
target_link_libraries(SimplePicoMidiController PicoResponsiveAnalogRead::PicoResponsiveAnalogRead)
target_link_libraries(SimplePicoMidiController hardware_adc) # Dependency for PicoResponsiveAnalogRead

# Add the standard include files to the build
target_include_directories(
  SimplePicoMidiController
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
          ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other
                                       # standard includes, if required
          ${CMAKE_SOURCE_DIR}/include)

# Add any user requested libraries
target_link_libraries(SimplePicoMidiController tinyusb_device tinyusb_board)

pico_add_extra_outputs(SimplePicoMidiController)
