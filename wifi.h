// This file only forwards to the ESP32's real WiFi.h.
// Windows treats "wifi.h" and "WiFi.h" as the same name, so without this
// the library would pick up this file instead of the real one.
#include_next <WiFi.h>