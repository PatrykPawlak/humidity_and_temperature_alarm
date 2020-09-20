/*

   Humidity and temperature alarm
   SMiW Project
   Author: Patryk Pawlak (patrykpawlak.pl@gmail.com)

*/

#include "humidity_and_temperature_alarm.hpp"

U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2(OLED_ROTATION, OLED_PIN_SCK, OLED_PIN_SDA, OLED_PIN_CS, OLED_PIN_DC, OLED_PIN_RES);
oled_screen screen(u8g2);

DHT dht(DHT_PIN, DHT_TYPE);

rgb_led led_rgb(PIN_LED_R, MAX_LED, PIN_LED_G, MIN_LED, PIN_LED_B, MIN_LED, 1000);

WiFiClient  client;
AsyncWebServer server(80);

float humidity = 0.0;
float temperature = 0.0;

float humidity_threshold = 70.0;
float temperature_threshold = 27.0;

unsigned char display_state = 0;

// invtervals
const unsigned long sensor_interval = 1500;
const unsigned long display_interval = 3000;
const unsigned long alarm_interval = 1000;
const unsigned long thing_speak_interval = 1000 * 60;

// timers
unsigned long sensor_timer = 0;
unsigned long display_timer = 0;
unsigned long alarm_timer = 0;
unsigned long thing_speak_timer = 0;

void setup()
{
  Serial.begin(115200);
  init_wifi();
  screen.initialize();
  dht.begin();
  ThingSpeak.begin(client);
  init_web_server();
  handle_read_from_thing_speak();
}

void loop()
{
  handle_update_sensor_values();
  handle_update_display();
  handle_alarm();
  handle_write_to_thing_speak();
}

void handle_read_from_thing_speak(void)
{
  int statusCode = 0;
  float init_humidity_threshold = -1.0;
  float init_temperature_threshold = -1.0;
  
  init_humidity_threshold = ThingSpeak.readFloatField(SECRET_CH_ID, 3, SECRET_READ_API_KEY);
  init_temperature_threshold = ThingSpeak.readFloatField(SECRET_CH_ID, 4, SECRET_READ_API_KEY);

  statusCode = ThingSpeak.getLastReadStatus();

  if (statusCode == 200)
  {
    if (init_humidity_threshold != -1.0 && init_temperature_threshold != -1.0)
    {
      humidity_threshold = init_humidity_threshold;
      temperature_threshold = init_temperature_threshold;
    }
  }
  else
  {
   Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }
}

void handle_write_to_thing_speak(void)
{
  if ((millis() - thing_speak_timer) >= thing_speak_interval)
  {
    ThingSpeak.setField(1, humidity);
    ThingSpeak.setField(2, temperature);
    ThingSpeak.setField(3, humidity_threshold);
    ThingSpeak.setField(4, temperature_threshold);
    ThingSpeak.setStatus("Update values");
    int res = ThingSpeak.writeFields(SECRET_CH_ID, SECRET_WRITE_API_KEY);

    if (res == 200) {
      Serial.println("Channel update successful.");
    }
    else {
      Serial.println("Problem updating channel. HTTP error code " + String(res));
    }

    thing_speak_timer = millis();
  }
}

void handle_alarm(void)
{
  if ((millis() - alarm_timer) >= alarm_interval)
  {
    if (humidity >= humidity_threshold || temperature >= temperature_threshold) led_rgb.toggle();
    else led_rgb.turn_off();
    alarm_timer = millis();
  }
}

void handle_update_display(void)
{
  if ((millis() - display_timer) >= display_interval)
  {
    if (display_state == 0)
    {
      screen.draw(display_state, temperature);
      display_state = 1;
    }
    else
    {
      screen.draw(display_state, humidity);
      display_state = 0;
    }
    display_timer = millis();
  }
}

void handle_update_sensor_values(void)
{
  if ((millis() - sensor_timer) >= sensor_interval)
  {
    float new_humidity = dht.readHumidity();
    float new_temperature = dht.readTemperature();

    if (isnan(new_humidity))
    {
      Serial.println("Failed to read humidity from DHT sensor!");
    }
    else
    {
      humidity = new_humidity;
    }

    if (isnan(new_temperature))
    {
      Serial.println("Failed to read temperature from DHT sensor!");
    }
    else
    {
      temperature = new_temperature;
    }

    sensor_timer = millis();
  }
}

void not_found(AsyncWebServerRequest * request)
{
  request->send(404, "text/html", request_failed_html);
}

String push_values_to_website(const String &p_var)
{
  if (p_var == "humidity")
  {
    return String(humidity);
  }
  else if (p_var == "humidity-threshold")
  {
    return String(humidity_threshold);
  }
  else if (p_var == "temperature")
  {
    return String(temperature);
  }
  else if (p_var == "temperature-threshold")
  {
    return String(temperature_threshold);
  }
  else if (p_var == "rgb-color")
  {
    return String(led_rgb.get_color());
  }
  return String();
}

void init_web_server(void)
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send_P(200, "text/html", index_html, push_values_to_website);
  });

  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send_P(200, "text/plain", String(humidity).c_str());
  });

  server.on("/humidity-threshold", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send_P(200, "text/plain", String(humidity_threshold).c_str());
  });

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send_P(200, "text/plain", String(temperature).c_str());
  });

  server.on("/temperature-threshold", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send_P(200, "text/plain", String(temperature_threshold).c_str());
  });

  server.on("/rgb-color", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send_P(200, "text/plain", led_rgb.get_color().c_str());
  });

  server.on("/set", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    String input_value;
    String input_red, input_green, input_blue;

    if (request->hasParam("humidity")) {
      input_value = request->getParam("humidity")->value();
      humidity_threshold = input_value.toFloat();
      request->send(200, "text/html", request_success_html);
    }
    else if (request->hasParam("temperature")) {
      input_value = request->getParam("temperature")->value();
      temperature_threshold = input_value.toFloat();
      request->send(200, "text/html", request_success_html);
    }
    else if (request->hasParam("red") && request->hasParam("green") && request->hasParam("blue")) {
      input_red = String(request->getParam("red")->value());
      input_green = String(request->getParam("green")->value());
      input_blue = String(request->getParam("blue")->value());
      
      led_rgb.set_color(input_red, input_green, input_blue);
      request->send(200, "text/html", request_success_html);
    }
    else {
      input_value = "No message sent";
      request->send(200, "text/html", request_failed_html);
    }
  });

  server.onNotFound(not_found);
  server.begin();
}

void init_wifi(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(SECRET_SSID, SECRET_PASS);

  Serial.print("\nConnecting ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }

  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
