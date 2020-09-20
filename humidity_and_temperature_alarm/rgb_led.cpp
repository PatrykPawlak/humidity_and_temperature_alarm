#include "rgb_led.hpp"

rgb_led::rgb_led(unsigned char p_red_pin, unsigned char p_green_pin, unsigned char p_blue_pin, const unsigned long p_interval) :
  m_red(p_red_pin, MAX_LED), m_green(p_green_pin, MIN_LED),
  m_blue(p_blue_pin, MIN_LED), m_state(STATE::OFF), m_interval(p_interval), m_timer(0)
{
  m_red.initialize();
  m_green.initialize();
  m_blue.initialize();
};

rgb_led::rgb_led(
  unsigned char p_red_pin, int p_red_brightness, unsigned char p_green_pin,
  int p_green_brightness, unsigned char p_blue_pin, int p_blue_brightness, const unsigned long p_interval) :
  m_red(p_red_pin, p_red_brightness), m_green(p_green_pin, p_green_brightness),
  m_blue(p_blue_pin, p_blue_brightness), m_state(STATE::OFF), m_interval(p_interval), m_timer(0)
{
  m_red.initialize();
  m_green.initialize();
  m_blue.initialize();
};

void rgb_led::set_color(String p_red_value, String p_green_value, String p_blue_value)
{
  int red_val = p_red_value.toInt();
  int green_val = p_green_value.toInt();
  int blue_val = p_blue_value.toInt();

  if (
    (red_val >= MIN_COLOR && red_val <= MAX_COLOR) &&
    (green_val >= MIN_COLOR && green_val <= MAX_COLOR) &&
    (blue_val >= MIN_COLOR && blue_val <= MAX_COLOR))
  {
    //    m_red.set_brightness(map(255 - red_val, 0, 255, LED_ON, LED_OFF));
    //    m_green.set_brightness(map(255 - green_val, 0, 255, LED_ON, LED_OFF));
    //    m_blue.set_brightness(map(255 - blue_val, 0, 255, LED_ON, LED_OFF));
    Serial.printf("R: %s\tG: %s\tB: %s\n", String(MIN_ANALOG - red_val).c_str(), String(MIN_ANALOG - green_val).c_str(), String(MIN_ANALOG - blue_val).c_str());

    m_red.set_brightness(MIN_ANALOG - red_val);
    m_green.set_brightness(MIN_ANALOG - green_val);
    m_blue.set_brightness(MIN_ANALOG - blue_val);
  }
  //  else if (
  //    (red_val >= LED_ON && red_val <= LED_OFF) &&
  //    (green_val >= LED_ON && green_val <= LED_OFF) &&
  //    (blue_val >= LED_ON && blue_val <= LED_OFF))
  //  {
  //    m_red.set_brightness(map(255 - red_val, LED_ON, LED_OFF, 0, 255));
  //    m_green.set_brightness(map(255 - green_val, LED_ON, LED_OFF, 0, 255));
  //    m_blue.set_brightness(map(255 - blue_val, LED_ON, LED_OFF, 0, 255));
  //  }
};

String rgb_led::get_color(void)
{
  String color = "rgb(";
  //  color += (255 - map(m_red.get_brightness(), LED_ON, LED_OFF, 0, 255));
  //  color += ", ";
  //  color += (255 - map(m_green.get_brightness(), LED_ON, LED_OFF, 0, 255));
  //  color += ", ";
  //  color += (255 - map(m_blue.get_brightness(), LED_ON, LED_OFF, 0, 255));

  //  color += String(MIN_ANALOG - m_red.get_brightness()).c_str();
  //  color += ", ";
  //  color += String(MIN_ANALOG - m_green.get_brightness()).c_str();
  //  color += ", ";
  //  color += String(MIN_ANALOG - m_blue.get_brightness()).c_str();

  color += (MIN_ANALOG - m_red.get_brightness());
  color += ", ";
  color += (MIN_ANALOG - m_green.get_brightness());
  color += ", ";
  color += (MIN_ANALOG - m_blue.get_brightness());
  color += ")";
  Serial.println(color);
  return color;
}

void rgb_led::toggle(void)
{
  if ((millis() - m_timer) >= m_interval)
  {
    //    Serial.printf("R: %s\tG: %s\tB: %s\n", String(m_red.get_brightness()).c_str(), String(m_green.get_brightness()).c_str(), String(m_blue.get_brightness()).c_str());
    if (m_state == STATE::OFF)
    {
      turn_on();
      m_state = STATE::ON;
    }
    else if (m_state == STATE::ON)
    {
      turn_off();
      m_state = STATE::OFF;
    }
    m_timer = millis();
  }
};

void rgb_led::turn_on(void)
{
  m_red.turn_on();
  m_green.turn_on();
  m_blue.turn_on();
  m_state = STATE::ON;
}

void rgb_led::turn_off(void)
{
  m_red.turn_off();
  m_green.turn_off();
  m_blue.turn_off();
  m_state = STATE::OFF;
}
