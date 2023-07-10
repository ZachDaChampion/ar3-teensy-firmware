# ar3-teensy-firmware

Firmware for a Teensy microcontroller to control the Annin Robotics AR3

# Message Protocol

This firmware communicates with a serial port using a simple binary messaging protocol. Messages
begin with a 2-byte header which contains the `START` character (`0x24`) followed by the `MSG_TYPE`:
a single byte indicating the type of message. The header is followed by the message payload, which
depends on the message type. The message ends with a 1-byte checksum, which is calculated on the
`MSG_TYPE` and payload.

| `START` | `MSG_TYPE` | `<payload>` | `CHECKSUM` |
| ------- | ---------- | ----------- | ---------- |
| `0x24`  | 1 byte     | n bytes     | 1 byte     |

## Checksum

These messages are relatively short, so a simple 8-bit checksum is used. We use the standard CRC-8
CCITT polynomial `0x07`. The checksum is calculated on the `MSG_TYPE` and payload bytes.

## Commands

### Error (`ERR`) - `0x00`

This message is sent any time an error occurs. It contains an error code and an error message that
should be displayed to the user.

| Byte | Description           |
| ---- | --------------------- |
| 0    | Start (`0x24`)        |
| 1    | Message type (`0x00`) |
| 2    | Error code            |
| 3    | Error message length  |
| 4    | Error message         |
| n+4  | Checksum              |

### Acknowledgement (`ACK`) - `0x01`

This message is sent in response to a command. It indicates that a command was received
successfully, but does not contain any additional information.

| Byte | Description           |
| ---- | --------------------- |
| 0    | Start (`0x24`)        |
| 1    | Message type (`0x01`) |
| 2    | Checksum              |

### Complete (`DONE`) - `0x02`

This message is used to indicate that the current operation has been completed. This is different
from an `ACK` message, which only tells you that a command was received and parsed successfully.

| Byte | Description           |
| ---- | --------------------- |
| 0    | Start (`0x24`)        |
| 1    | Message type (`0x02`) |
| 2    | Checksum              |

### Initialize (`INIT`) - `0x03`

Initialize the robot. This command must be sent before any other commands are sent. It is used to
ensure that the robot is running the correct firmware and that the serial connection is working.

| Byte | Description           |
| ---- | --------------------- |
| 0    | Start (`0x24`)        |
| 1    | Message type (`0x03`) |
| 2    | Major version         |
| 3    | Minor version         |
| 4    | Checksum              |

The robot will respond with an `ACK` message if the firmware version is correct, or an `ERR` message
if the firmware version is incorrect.

### Calibrate (`CAL`) - `0x04`

Calibrate the robot. This command must be sent before the robot can be used. It moves each joint to
its limit swith and then back to the home position.

| Byte | Description           |
| ---- | --------------------- |
| 0    | Start (`0x24`)        |
| 1    | Message type (`0x04`) |
| 2    | Checksum              |

The robot will respond with an `ACK` or `ERR` message immediately. Once the calibration is complete,
the robot will send `DONE`.

### Set Joint Position (`SET`) - `0x05`

Set the current position of one or more joints (in steps). This command does not move the joints, it
only updates the internal state of the robot. Each joint is represented by a 16-bit signed integer
in little-endian format. The first joint is joint 0, the second joint is joint 1, and so on.

A value of `0x7FFF` (`32767`) indicates that a joint should not be updated.

| Byte | Description           |
| ---- | --------------------- |
| 0    | Start (`0x24`)        |
| 1    | Message type (`0x05`) |
| 2    | Joint 0 position      |
| 4    | Joint 1 position      |
| 6    | Joint 2 position      |
| 8    | Joint 3 position      |
| 10   | Joint 4 position      |
| 12   | Joint 5 position      |
| 14   | Checksum              |

The robot will respond with an `ACK` message if the position was set successfully, or an `ERR`
message if the position could not be set.

### Get Joint Position (`GET`) - `0x06`

Get the current position of all joints (in steps). Each joint is represented by a 16-bit signed
integer in little-endian format. The first joint is joint 0, the second joint is joint 1, and so on.

| Byte | Description           |
| ---- | --------------------- |
| 0    | Start (`0x24`)        |
| 1    | Message type (`0x06`) |
| 2    | Checksum              |

The robot will respond with a `POS` message containing the current position of all joints.

### Move Joints to Position (`MOV`) - `0x07`

Move the joints to a given position (in steps). Each joint consists of a position (in steps) and a
speed (in steps per second). The position is a 16-bit signed integer in little-endian format. The
speed is a IEEE 754 single-precision floating-point number in little-endian format.

If the position is `0x7FFF` (`32767`), the joint will not be moved. If the speed is `NaN`, the speed
will be calculated automatically.

| Byte | Description           |
| ---- | --------------------- |
| 0    | Start (`0x24`)        |
| 1    | Message type (`0x07`) |
| 2    | Joint 0 position      |
| 4    | Joint 0 speed         |
| 8    | Joint 1 position      |
| 10   | Joint 1 speed         |
| 14   | Joint 2 position      |
| 16   | Joint 2 speed         |
| 20   | Joint 3 position      |
| 22   | Joint 3 speed         |
| 26   | Joint 4 position      |
| 28   | Joint 4 speed         |
| 32   | Joint 5 position      |
| 34   | Joint 5 speed         |
| 38   | Checksum              |

The robot will respond with an `ACK` message if the move was started successfully, or an `ERR`
message if the move could not be started. Once the move is complete, the robot will send `DONE`.

### Stop All Joints (`STP`) - `0x08`

This command will stop all movement. A single parameter is used to indicate how smoothly the robot
should stop. A value of `0x00` indicates that the robot should stop as quickly as possible. Any
other value indicates that the robot should stop smoothly.

| Byte | Description           |
| ---- | --------------------- |
| 0    | Start (`0x24`)        |
| 1    | Message type (`0x08`) |
| 2    | Smooth stop           |
| 3    | Checksum              |

The robot will respond with an `ACK` message immediately. Once the stop is complete, the robot will
send `DONE`.

### Reset (`RST`) - `0x09`

Reset the robot. This command resets the robot's internal state, but does not move the joints.

| Byte | Description           |
| ---- | --------------------- |
| 0    | Start (`0x24`)        |
| 1    | Message type (`0x09`) |
| 2    | Checksum              |

The robot will respond with an `ACK` message if the reset was successful, or an `ERR` message if the
reset failed. When the reset is complete and all joints have stopped, the robot will send `DONE`.

### Home (`HOM`) - `0x0A`

Move all joints to their home position.

| Byte | Description           |
| ---- | --------------------- |
| 0    | Start (`0x24`)        |
| 1    | Message type (`0x0A`) |
| 2    | Checksum              |

The robot will respond with an `ACK` message if the move was started successfully, or an `ERR`
message if the move could not be started. Once the move is complete, the robot will send `DONE`.

### Position (`POS`) - `0x0B`

Sent by the robot in response to a `GET` command. Contains the current position of all joints (in
steps). Each joint is represented by a 16-bit signed integer in little-endian format. The first
joint is joint 0, the second joint is joint 1, and so on.

| Byte | Description           |
| ---- | --------------------- |
| 0    | Start (`0x24`)        |
| 1    | Message type (`0x0B`) |
| 2    | Joint 0 position      |
| 4    | Joint 1 position      |
| 6    | Joint 2 position      |
| 8    | Joint 3 position      |
| 10   | Joint 4 position      |
| 12   | Joint 5 position      |
| 14   | Checksum              |

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
