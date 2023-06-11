# ar3-teensy-firmware

Firmware for a Teensy microcontroller to control the Annin Robotics AR3

# Message Protocol

This firmware communicates with a serial port using a simple ASCII messaging protocol. Messages
consist of a single line of text, terminated by a newline character (`\n`). Each message follows the
format:

```text
$<command>;[<arg1>;[<arg2>;...]]*<checksum>
```

The `$` character indicates the start of a message. The `<command>` is a string of characters
indicating the command to execute. The `<arg>`s are optional arguments to the command. At the end of
the message is a two-digit hexadecimal checksum, which is calculated on all the bytes after the `$`
and before the `*`. In place of a checksum, you may also send `XX` to indicate that the checksum
should be ignored. For more information, see the [Checksum](#checksum) section.

Arguments are separated by semicolons (`;`). The number and type of arguments depends on the
command. Some arguments are optional. Every argument has a label, which can be used to identify it:
`<label>:<value>`. Arguments may also be identified by their position in the argument list. Some
arguments take multiple values, which are separated by commas (`,`).

All whitespace characters (spaces, tabs, newlines, etc.) are ignored.

Examples:

```text
$MV;90;*XX           # Move joint 1 to 90 degrees
$MV;90;45;*XX        # Move joint 1 to 90 degrees and join 2 to 45 degrees
$MV;j2:45;*XX        # Move joint 2 to 45 degrees
$MV;90,5;*XX         # Move joint 1 to 90 degrees at 5 degrees per second
$MV; j2:45,5; *XX    # Move joint 2 to 45 degrees at 5 degrees per second
```

Responses follow a similar format:

```text
$<ack>;[<res1>;[<res2>;...]]*<checksum>
```

The `<ack>` is either `OK` or `ERR`. An `OK` response indicates that the command was executed
successfully, and may be accompanied by results. An `ERR` response indicates that the command was
not executed successfully, and is accompanied by two results: an error code (see
`include/ar3_error.h`) and an error message that should be displayed to the user.

| Code  | Description                                                     |
| ----- | --------------------------------------------------------------- |
| `OOB` | Out of bounds. The given value is outside the acceptable range. |

## Commands

### `INIT` - Start

Initialize the robot. This command must be sent before any other commands are sent. It is used to
ensure that the robot is running the correct firmware and that the serial connection is working.

#### Arguments

| Label | Description      | Format                               |
| ----- | ---------------- | ------------------------------------ |
| `v`   | firmware version | Semver version string (e.g. `1.0.0`) |

#### Results

None

#### Examples

```text
->  $INIT;1.0.0;*XX
<-  $OK;*XX

->  $INIT;1.0.1;*XX
<-  $ERR;2;Running firmware 1.0.0, expected 1.0.1;*XX
```

### `CAL` - Calibrate

Calibrate the robot. This command must be sent before the robot is used. It moves each joint to its
limit switch, then back to the home position.

#### Arguments

None

#### Results

None

#### Examples

```text
->  $CAL;*XX
<-  $OK;*XX
```

### `SET` - Set Current Joint Position

Set the current position of one or more joints (in steps). This command does not move the joints, it
only updates the internal state of the robot.

#### Arguments

| Label | Description                            | Format |
| ----- | -------------------------------------- | ------ |
| `j_`  | positions to set the joints to (steps) | int    |

#### Results

None

#### Examples

```text
-> $SET;100,200,300;*XX
<- $OK;*XX

->  $SET;j2:200;j3:300;*XX
<-  $OK;*XX

->  $SET;j1:999;j2:200;j3:300;*XX
<-  $ER;3,Argument '999' for joint j1' is out of range;*XX
```

### `MV` - Move Joint to Position

Move one or more joints to a given position (in degrees). This command moves the joints to the
specified position at a desired speed. If no speed is specified, the default acceleration and
maximum speed are used.

#### Arguments

| Label | Description                                           | Format     |
| ----- | ----------------------------------------------------- | ---------- |
| `j_`  | target positions (steps), optional speeds (steps/sec) | int, float |

#### Results

None

#### Examples

```text
->  $MV;90;*XX
<-  $OK;*XX

->  $MV;90,5;*XX
<-  $OK;*XX

->  $MV;j2:90;j3:45,5;*XX
<-  $OK;*XX

->  $MV;j1:90;j2:90,5;j3:999,5;*XX
<-  $ER;3;Joint 3 speed out of bounds;*XX
```

### `MVR` - Move Joint Relative to Current Position

Move one or more joints to a given position (in degrees) relative to their current position. This
command moves the joints to the specified position at a desired speed. If no speed is specified, the
default acceleration and maximum speed are used.

#### Arguments

| Label | Description                                     | Format     |
| ----- | ----------------------------------------------- | ---------- |
| `j_`  | target positions (steps), optional speeds (deg) | int, float |

#### Results

None

#### Examples

```text
->  $MVR;90;*XX
<-  $OK;*XX

->  $MVR;90,5;*XX
<-  $OK;*XX

->  $MVR;j2:90;j3:45,5;*XX
<-  $OK;*XX

->  $MVR;j1:90;j2:90,5;j3:999,5;*XX
<-  $ER;3;Joint 3 speed out of bounds;*XX
```

### `STP` - Stop

Stop all movement.

#### Arguments

None

#### Results

None

#### Examples

```text
->  $STP;*XX
<-  $OK;*XX
```

### `GET` - Get Current Joint Position

Get the current position of one or more joints (in steps).

#### Arguments

| Label | Description     | Format |
| ----- | --------------- | ------ |
| `j`   | optional joints | String |

#### Results

| Label | Description        | Format |
| ----- | ------------------ | ------ |
| `j_`  | position of joints | int    |

#### Examples

```text
->  $GET;*XX
<-  $OK;j1:100;j2:200;j3:300;*XX

->  $GET;j1;j2;*XX
<-  $OK;j1:100;j2:200;*XX
```

### `RST` - Reset

Reset the robot. This command resets the robot's internal state, but does not move the joints.

#### Arguments

None

#### Results

None

#### Examples

```text
->  $RST;*XX
<-  $OK;*XX
```

### `HOME` - Move to Home Position

Move the robot to its home position.

#### Arguments

None

#### Results

None

#### Examples

```text
->  $HOME;*XX
<-  $OK;*XX
```

## Checksum Calculation

TODO

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
