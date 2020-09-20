#ifndef HUMIDITY_AND_TEMPERATURE_ALARM_H
#define HUMIDITY_AND_TEMPERATURE_ALARM_H

#include "DHT.h"
#include "ESP8266WiFi.h"
#include "ESPAsyncTCP.h"
#include "ESPAsyncWebServer.h"
#include "ThingSpeak.h"

#include "secrets.hpp"

#include "index_html.hpp"
#include "request_success_html.hpp"
#include "request_failed_html.hpp"

#include "oled_screen.hpp"
#include "rgb_led.hpp"

#define OLED_ROTATION U8G2_R0 //Rotation 0-3
#define OLED_PIN_SCK D5 // 14
#define OLED_PIN_SDA D7 // 13
#define OLED_PIN_RES D0 // 16
#define OLED_PIN_DC D6 // 12
#define OLED_PIN_CS D8 // 15

#define DHT_PIN D1 // 5
#define DHT_TYPE DHT22

#define PIN_LED_R D2
#define PIN_LED_G D3
#define PIN_LED_B D4

#endif
