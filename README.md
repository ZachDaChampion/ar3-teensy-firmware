# ar3-teensy-firmware

Firmware for a Teensy microcontroller to control the Annin Robotics AR3

# Protobuf

The firmware uses [Protobuf](https://developers.google.com/protocol-buffers) to communicate with the
host computer. The protobuf definitions are located in the `proto` submodule and are compiled for
use with the [EmbeddedProto](https://embeddedproto.com/) library. The compiled definitions are
located in `include/proto`.

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
