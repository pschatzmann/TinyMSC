# TinyMSC

[![arduino-library-badge](https://img.shields.io/badge/Arduino-Library-00979D?logo=arduino&logoColor=white)](https://www.arduino.cc/reference/en/libraries/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

USB **Mass Storage** for Arduino -- the "USB stick" protocol, in both directions:

- **USB host:** your board is the computer. Plug a USB flash drive into the
  board and read/write its files (FAT, exFAT, ext2/3/4), no SD card slot needed.
- **USB device:** your board is the USB stick. Plug it into a PC and it shows
  up as a drive, backed by RAM, an SD card or any storage you provide.

A board's USB port does one role at a time; pick it in the board's USB menu.

This library does the USB part only. The filesystems are
[TinyFATFS](https://github.com/pschatzmann/TinyFATFS) (FAT12/16/32, exFAT)
and [TinyEXT4](https://github.com/pschatzmann/TinyEXT4) (ext2/3/4), used
with their own API. Both directions meet at their block driver interface:

- **Host:** `USBHostMscFatIO` / `USBHostMscExt4IO` are block drivers for a
  plugged-in USB drive, like the SD card drivers of those libraries.
- **Device:** `USBDeviceMSC` exports any block driver of those libraries
  (RAM disk, SD card, NBD export, ...) or your own to the PC.

A sketch only needs `#include "TinyMSC.h"`: it pulls in the host and/or device
classes, depending on what the selected board and USB mode support.

On ESP32 and RP2040, `fatfs::ArduinoFS` / `tinyext4::ArduinoFS` turn a
mounted volume into an Arduino `fs::FS`.

## Documentation

- [Class documentation (Doxygen)](https://pschatzmann.github.io/TinyMSC/annotated.html)
- [Installation and supported boards](https://github.com/pschatzmann/TinyMSC/wiki/BOARDS)
- [Host vs. device overview](https://github.com/pschatzmann/TinyMSC/wiki/OVERVIEW)
- Host mode: 
  - [quick start](https://github.com/pschatzmann/TinyMSC/wiki/HOST_QUICKSTART) 
  - [block API](https://github.com/pschatzmann/TinyMSC/wiki/BLOCK_API) 
  - [filesystems](https://github.com/pschatzmann/TinyMSC/wiki/FILESYSTEMS) 
  - [hubs](https://github.com/pschatzmann/TinyMSC/wiki/MULTIPLE_DEVICES) 
  - [ESP32](https://github.com/pschatzmann/TinyMSC/wiki/ESP32_NATIVE) 
  - [STM32](https://github.com/pschatzmann/TinyMSC/wiki/STM32) 
  - [MAX3421E](https://github.com/pschatzmann/TinyMSC/wiki/MAX3421E) 
  - [single-port wiring](https://github.com/pschatzmann/TinyMSC/wiki/SINGLE_PORT)
- Device mode: 
  - [quick start](https://github.com/pschatzmann/TinyMSC/wiki/DEVICE_QUICKSTART) 
  - [API](https://github.com/pschatzmann/TinyMSC/wiki/DEVICE_API)
- [NBD (network block device) storage](https://github.com/pschatzmann/TinyMSC/wiki/NBD): mount a remote disk, or export it over USB
- [Examples](https://github.com/pschatzmann/TinyMSC/wiki/EXAMPLES) 
- [Testing](https://github.com/pschatzmann/TinyMSC/wiki/TESTING)

## Installation in Arduino

You can download the library as zip and call include Library -> zip library. Or you can git clone this project into the Arduino libraries folder e.g. with

```
cd  ~/Documents/Arduino/libraries
git clone https://github.com/pschatzmann/TinyMSC.git
```

The filesystems come from two separate libraries, which you need to install the same way:

```
git clone https://github.com/pschatzmann/TinyFATFS.git
git clone https://github.com/pschatzmann/TinyEXT4.git
```

I recommend to use git because you can easily update to the latest version just by executing the ```git pull``` command in the project folders.

Then add `#include "TinyMSC.h"` to your sketch and select the USB mode in the board's Tools menu. See [Installation and supported boards](https://github.com/pschatzmann/TinyMSC/wiki/BOARDS) and the [examples](https://github.com/pschatzmann/TinyMSC/wiki/EXAMPLES).

For desktop builds and tests with CMake, see [Testing](https://github.com/pschatzmann/TinyMSC/wiki/TESTING).

## License

MIT. See [Licensing](https://github.com/pschatzmann/TinyMSC/wiki/LICENSING).
