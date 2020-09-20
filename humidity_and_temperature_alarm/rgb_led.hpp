#ifndef RGB_LED_H
#define RGB_LED_H

#include "led.hpp"

enum STATE {
  OFF,
  ON
};

class rgb_led {
  public:
    rgb_led(
      unsigned char p_red_pin, unsigned char p_green_pin, 
      unsigned char p_blue_pin, const unsigned long p_interval
    );
    rgb_led(
      unsigned char p_red_pin, int p_red_brightness, unsigned char p_green_pin, 
      int p_green_brightness, unsigned char p_blue_pin, int p_blue_brightness, 
      const unsigned long p_interval
    );
    void set_color(String p_red_value, String p_green_value, String p_blue_value);
    String get_color(void);
    void toggle(void);
    void turn_on(void);
    void turn_off(void);

  private:
    led m_red;
    led m_green;
    led m_blue;
    const unsigned long m_interval;
    unsigned long m_timer;
    STATE m_state;
};

#endif
