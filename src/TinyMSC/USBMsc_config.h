#pragma once
// Decides whether the host-mode translation units of this library are
// compiled. Arduino builds every .cpp in src/, so without this a sketch that
// only uses USB *device* mode (USBDeviceMSC) would fail on the host-mode
// #error checks in USBHostMSC.h. TinyMSC.h only includes the parts that
// the board can build; sketches that include TinyMSC/USBHostMSC.h directly
// still get those errors. Define USBHOSTMSC_DISABLE=1 (build flag) to force the
// host code off on boards where it cannot be detected automatically.
#ifndef USBHOSTMSC_COMPILE
#if defined(USBHOSTMSC_DISABLE)
#define USBHOSTMSC_COMPILE 0
#elif defined(ARDUINO_ARCH_RP2040) && !defined(USE_TINYUSB_HOST)
#define USBHOSTMSC_COMPILE 0
#elif defined(ARDUINO_ARCH_STM32) && !defined(CFG_TUH_ENABLED)
#define USBHOSTMSC_COMPILE 0
#else
#define USBHOSTMSC_COMPILE 1
#endif
#endif

// Same idea for device mode: skip USBDeviceMSC.cpp when the selected USB
// stack has no device side (e.g. RP2040 "Adafruit TinyUSB Host (native)")
// or the chip has no native USB at all (classic ESP32, ESP32-C3/C6/H2,
// which can only be a USB host through a MAX3421E chip).
#if defined(ARDUINO_ARCH_ESP32)
#include "soc/soc_caps.h"
#endif
#ifndef USBDEVMSC_COMPILE
#if defined(USBDEVMSC_DISABLE)
#define USBDEVMSC_COMPILE 0
#elif defined(ARDUINO_ARCH_RP2040) && defined(USE_TINYUSB_HOST)
#define USBDEVMSC_COMPILE 0
#elif defined(ARDUINO_ARCH_ESP32) && !SOC_USB_OTG_SUPPORTED
#define USBDEVMSC_COMPILE 0
#else
#define USBDEVMSC_COMPILE 1
#endif
#endif
