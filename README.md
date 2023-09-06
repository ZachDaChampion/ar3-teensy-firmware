# ar3-teensy-firmware

Firmware for a Teensy microcontroller to control the Annin Robotics AR3

## TODO

- Send error when interrupting a move

# Flatbuffers

The firmware uses [Flatbuffers](https://google.github.io/flatbuffers/) to communicate with the
host computer. The Flatbuffers schema is defined in the `messages` folder, which is a submodule
pointing to the [firmware-messages](https://github.com/COBOT-Team/firmware-messages) repository.

# PlatformIO

## Building

This project uses the [PlatformIO](https://platformio.org/) build system. To build the project,
install PlatformIO and run `pio run` in the project directory.

## Uploading

To upload the firmware to the Teensy, run `pio run -t upload`. This will build the project and
upload the firmware to the Teensy.

## VSCode

Alternatively, you can use the [PlatformIO VSCode extension](https://platformio.org/platformio-ide)
to build and upload the project. This is recommended if you plan to make changes to the firmware.
