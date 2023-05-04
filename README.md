# Big Blinking Button

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

