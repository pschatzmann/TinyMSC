/*
 * TinyMSC -- convenience header
 *
 * Includes every part of the library that the selected board and USB menu
 * settings can build:
 *   - USB host:   USBHostMSC, USBHostMscFatIO, USBHostMscExt4IO
 *   - USB device: USBDeviceMSC
 *
 * The roles are detected from the TinyUSB configuration (CFG_TUH_* /
 * CFG_TUD_*), so a sketch that includes this header builds in host mode
 * as well as in device mode. Force a role on or off with
 * -DTINYMSC_HOST=0/1 or -DTINYMSC_DEVICE=0/1, or include the individual
 * headers instead.
 */
#pragma once

// --- Pull in the TinyUSB configuration of the platform ---------------------
// Same stack selection as USBHostMSC.h / USBDeviceMSC.h: the TinyUSB built
// into the arduino-esp32 core on ESP32-S2/S3, the Adafruit TinyUSB Library
// everywhere else.
#if defined(ARDUINO_ARCH_ESP32)
#include "sdkconfig.h"
#include "soc/soc_caps.h"
#endif

// STM32 enables host mode with a build flag (-DCFG_TUH_ENABLED=1). Remember
// it before the TinyUSB config is read: an unpatched Adafruit TinyUSB
// Library resets it to 0, and USBHostMSC.h should then report the missing
// patch instead of the host classes silently being left out.
#if defined(ARDUINO_ARCH_STM32) && defined(CFG_TUH_ENABLED) && CFG_TUH_ENABLED
#define TINYMSC_STM32_HOST_REQUESTED 1
#endif

#if defined(ARDUINO_ARCH_ESP32) && SOC_USB_OTG_SUPPORTED &&                    \
    CONFIG_TINYUSB_ENABLED &&                                                   \
    !defined(USBHOSTMSC_USE_ADAFRUIT_TINYUSB) &&                               \
    !defined(USBDEVMSC_USE_ADAFRUIT_TINYUSB)
#define TINYMSC_ESP32_CORE 1
#include "tusb.h"
#else
#define TINYMSC_ESP32_CORE 0
// Included unconditionally (no __has_include): the Arduino build only adds a
// library -- also the Adafruit TinyUSB that is bundled with the RP2040 core --
// to the include path when it sees a plain #include of one of its headers.
// Both roles need this library on these boards anyway.
#include <Adafruit_TinyUSB.h>
#endif

// --- Detect the available roles --------------------------------------------
#ifndef TINYMSC_HOST
#if defined(ARDUINO_ARCH_RP2040) && !defined(USE_TINYUSB_HOST)
#define TINYMSC_HOST 0
#elif defined(TINYMSC_STM32_HOST_REQUESTED)
#define TINYMSC_HOST 1
#elif defined(CFG_TUH_ENABLED) && defined(CFG_TUH_MSC) && CFG_TUH_ENABLED &&   \
    CFG_TUH_MSC
#define TINYMSC_HOST 1
#else
#define TINYMSC_HOST 0
#endif
#endif

#ifndef TINYMSC_DEVICE
#if TINYMSC_ESP32_CORE
// The core's USBMSC class only exists with CONFIG_TINYUSB_MSC_ENABLED.
#if CONFIG_TINYUSB_MSC_ENABLED
#define TINYMSC_DEVICE 1
#else
#define TINYMSC_DEVICE 0
#endif
#elif defined(CFG_TUD_ENABLED) && defined(CFG_TUD_MSC) && CFG_TUD_ENABLED &&   \
    CFG_TUD_MSC
#define TINYMSC_DEVICE 1
#else
#define TINYMSC_DEVICE 0
#endif
#endif

#if !TINYMSC_HOST && !TINYMSC_DEVICE
#error \
    "TinyMSC: neither USB host nor USB device Mass Storage is enabled for " \
    "this board. Select a TinyUSB USB stack / USB mode in the Tools menu " \
    "(see the wiki page BOARDS), or include TinyMSC/USBHostMSC.h or TinyMSC/USBDeviceMSC.h " \
    "directly to get the specific error message."
#endif

// --- Include the parts ------------------------------------------------------
#if TINYMSC_HOST
#include "TinyMSC/USBHostMSC.h"
#include "TinyMSC/USBHostMscExt4IO.h"
#include "TinyMSC/USBHostMscFatIO.h"
#endif

#if TINYMSC_DEVICE
#include "TinyMSC/USBDeviceMSC.h"
#endif
