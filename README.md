# Simple Raspberry Pi Pico Midi Controller

A simple Raspberry Pi Pico based midi controller that uses the Pico-SDK to make a simple midi controller that reads a button and sends out a midi note when that button is pressed.

The project includes a simple Debounce library that will debounce the button presses to remove jitter.

It expects the button to be connected to pin 1 (GP0) and pin3 (GND) but you can change this in the code.

The project also includes a simple SuperCollider script set up to receive midi notes from this controller and play a synth accordingly.

## Features

- TinyUSB setup ready to use
– Preconfigured libraries automatically included with this project:
    - [PicoDebounceButton](https://github.com/madskjeldgaard/PicoDebounceButton) – allowing to do debounced button reads
    - [PicoResponsiveAnalogRead](https://github.com/madskjeldgaard/PicoResponsiveAnalogRead) – make analog readings of potentiometers etc. less noisy
    - [PicoOSC](https://github.com/madskjeldgaard/PicoOSC) - Send/Receive OSC communication (_WORK IN PROGRESS_)
- Use [CPM](https://github.com/cpm-cmake/CPM.cmake) as an automatic package manager, simply run the cmake config step and it will download dependencies
- A Github Action to automatically build the firmware and release it on your repo. All you need to do is add a git tag prefixed with `v` and push it, eg. `git tag v0.1.0 && git push --tags`

## Build

Before building, you need to clone the pico sdk to your computer somewhere, eg:

```bash
git clone https://github.com/raspberrypi/pico-sdk $HOME/pico-sdk
```
Then build the project:

```bash
# Change path to pico sdk if you cloned it somewhere else
export PICO_SDK_PATH=$HOME/pico-sdk; cmake -B build -G Ninja 
cmake --build build
```

