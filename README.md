# ar3-teensy-firmware

Firmware for a Teensy microcontroller to control the Annin Robotics AR3

# Binary Protocol

Each message begins with a 3-byte header followed by a payload.

| Byte | Description                |
| ---- | -------------------------- |
| 0    | Start byte (0x24)          |
| 1    | Payload length             |
| 2    | CRC of payload (crc8ccitt) |
| 3... | Payload                    |

## Outgoing Message Payloads

### Log

| Byte | Description    |
| ---- | -------------- |
| 0    | Log level      |
| 1    | Message length |
| 2... | Message        |

### Response

| Byte | Description      |
| ---- | ---------------- |
| 0    | Response type    |
| 1... | Response payload |

#### Ack Response

| Byte | Description |
| ---- | ----------- |
| 0-3  | Command ID  |

#### Done Response

| Byte | Description |
| ---- | ----------- |
| 0-3  | Command ID  |

### Error Response

| Byte | Description          |
| ---- | -------------------- |
| 0-3  | Command ID           |
| 4    | Error code           |
| 5    | Error message length |
| 6... | Error message        |

#### Joints Response

| Byte    | Description                              |
| ------- | ---------------------------------------- |
| 0       | Number of joints                         |
| N + 1-4 | Joint N angle (int32) (deg \* 10^-3)     |
| N + 5-8 | Joint N speed (int32) (deg \* 10^-3) / s |

## Incoming Message Payloads

| Byte | Description  |
| ---- | ------------ |
| 0    | Request type |
| 1-4  | Command ID   |

### Init

| Byte  | Description               |
| ----- | ------------------------- |
| 0 - 3 | Expected firmware version |

### Calibrate

| Byte | Description                     |
| ---- | ------------------------------- |
| 0    | Bitfield of joints to calibrate |

### Override

| Byte    | Description                      |
| ------- | -------------------------------- |
| N + 0   | Joint ID                         |
| N + 1-4 | New angle (int32) (deg \* 10^-3) |

### Move To

| Byte    | Description                      |
| ------- | -------------------------------- |
| N + 0   | Joint ID                         |
| N + 1-4 | New angle (int32) (deg \* 10^-3) |
| N + 5-8 | Speed (int32) (deg \* 10^-3) / s |

### Move Speed

| Byte    | Description                      |
| ------- | -------------------------------- |
| N + 0   | Joint ID                         |
| N + 1-4 | Speed (int32) (deg \* 10^-3) / s |

### Stop

| Byte | Description                |
| ---- | -------------------------- |
| 0    | Stop immediately?          |
| 1    | Bitfield of joints to stop |

### Go Home

| Byte | Description                   |
| ---- | ----------------------------- |
| 0    | Bitfield of joints to go home |

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
