#include "string.h"
#include "EspMQTTClient.h"
#include <DHT.h>

#define DHTPIN 2        //D4
#define DHTTYPE DHT11   // DHT 11

void onConnectionEstablished();

/*
  EspMQTTClient client(
  "ssid",                 // Wifi ssid
  "pass",                 // Wifi password
  onConnectionEstablished,// Connection established callback
  "ip",                   // MQTT broker ip
  1883,                   // MQTT broker port
  "mqttusr",              // MQTT username
  "mqttpass",             // MQTT password
  "test",                 // Client name
  true,                   // Enable web updater
  true                    // Enable debug messages
  );
*/

EspMQTTClient client(
  "main",                                // Wifi ssid
  "12312311",                               // Wifi password
  onConnectionEstablished,                  // MQTT connection established callback
  "icja6ac.mqtt.iot.gz.baidubce.com",       // MQTT broker ip
  1884,                                     // MQTT broker port
  "icja6ac/esp8266_test",                 // MQTT username
  "7HHTBK9OSYzUhR7M",                       // MQTT password
  "baiduIoT-esp8266-device1",               // Client name
  false,
  false
);
DHT dht(DHTPIN, DHTTYPE);

long lastMsg = 0;
char msg[23];


void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  dht.begin();
  digitalWrite(LED_BUILTIN, HIGH);
}

void LED_Control_Callback(const String & payload) {
  const char* p = payload.c_str();
  Serial.println("LED callback");
  Serial.println(p);
  if (strstr(p, "On")) {
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on
  }
  if (strstr(p, "Off")) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED off
  }
}
void Temp_Humd_Report() {
  float humd = dht.readHumidity();
  float temp = dht.readTemperature();
  sprintf (msg, "Temp:%.2f'C  Humd:%.0f% ", temp, humd);

  Serial.println("======Temp Humd Report======");
  Serial.println(msg);

  client.publish("/wechat_esp8266/switch", String(humd));
  client.publish("/wechat_esp8266/switch", String(temp));
}

void onConnectionEstablished()
{
  // Subscribe to "mytopic/test" and display received message to Serial
  client.subscribe("/wechat_esp8266/switch", LED_Control_Callback);
}

void loop()
{
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    Temp_Humd_Report();
  }
}
