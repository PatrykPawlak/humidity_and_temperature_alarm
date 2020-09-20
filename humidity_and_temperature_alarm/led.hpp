#ifndef LED_H
#define LED_H

#include <Arduino.h>

#define MAX_ANALOG 0
#define MIN_ANALOG 1023
#define MAX_COLOR 255
#define MIN_COLOR 0
#define MIN_LED 1023
#define MAX_LED 768

class led
{
  public:
    led(const unsigned char p_pin, int p_brightness);
    void initialize(void);
    void turn_on(void);
    void turn_off(void);
    void set_brightness(int p_brightness);
    int get_brightness(void);
  
  private:
    const unsigned char m_pin;
    int m_brightness;
};

#endif
