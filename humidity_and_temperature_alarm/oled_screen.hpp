#ifndef OLED_SCREEN_H
#define OLED_SCREEN_H

#include "U8g2lib.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include "humidity_icon.hpp"
#include "temperature_icon.hpp"

class oled_screen
{
  public:
    oled_screen(U8G2& p_screen);
    void initialize(void);
    void draw_temperature(const float& p_temperature);
    void draw_humidity(const float& p_humidity);
    void draw(const byte& p_state, const float& p_value);

  private:
    U8G2* m_screen;
};

#endif
