#include "oled_screen.hpp"

oled_screen::oled_screen(U8G2& p_screen) : m_screen(&p_screen) {};

void oled_screen::initialize(void)
{
  m_screen->begin();
  m_screen->setDrawColor(1);
  m_screen->setFontPosBaseline();
  m_screen->setFontDirection(0);
  m_screen->setFont(u8g2_font_logisoso16_tf);
  m_screen->enableUTF8Print();
};

void oled_screen::draw_temperature(const float& p_temperature)
{
  m_screen->clearBuffer();
  m_screen->drawXBM(0, 0, TEMPERATURE_ICON_WIDTH, TEMPERATURE_ICON_HEIGHT, TEMPERATURE_ICON_BITS);
  m_screen->setCursor(TEMPERATURE_ICON_WIDTH - 8, TEMPERATURE_ICON_HEIGHT / 1.6);
  m_screen->print(p_temperature);
  m_screen->print("°C");
  m_screen->sendBuffer();
};

void oled_screen::draw_humidity(const float& p_humidity)
{
  m_screen->clearBuffer();
  m_screen->drawXBM(-5, 0, HUMIDITY_ICON_WIDTH, HUMIDITY_ICON_HEIGHT, HUMIDITY_ICON_BITS);
  m_screen->setCursor(HUMIDITY_ICON_WIDTH - 8, HUMIDITY_ICON_HEIGHT / 1.6);
  m_screen->print(p_humidity);
  m_screen->print("%");
  m_screen->sendBuffer();
};

void oled_screen::draw(const byte& p_state, const float& p_value)
{
  switch (p_state) {
    case 0: draw_temperature(p_value); break;
    case 1: draw_humidity(p_value); break;
  }
};
