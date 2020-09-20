#include "led.hpp"

led::led(const unsigned char p_pin, int p_brightness) : m_pin(p_pin), m_brightness(p_brightness) {};

void led::initialize(void)
{
  pinMode(m_pin, OUTPUT);
  turn_off();
}

void led::turn_on(void)
{
  analogWrite(m_pin, m_brightness);
}

void led::turn_off(void)
{
  analogWrite(m_pin, MIN_LED);
}

void led::set_brightness(int p_brightness)
{
  Serial.printf("Setter2.0: %s\n", p_brightness);
  if (p_brightness >= MIN_LED && p_brightness <= MAX_LED)
  {
    Serial.printf("Setter2.1: %s\n???", p_brightness);
    m_brightness = p_brightness;
  }
}

int led::get_brightness(void)
{
  return m_brightness;
}
