/*
  Based on arduino example code: Basic ESP8266 MQTT example
*/

#include "defines.h"

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int temp;
bool status = false;
auto timer = timer_create_default(); // create a timer with default settings

bool toggle_led(void *) {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // toggle the LED
  return true; // keep timer active? true
}


bool check_status (void *)
{
  minutes++;
  if (minutes == (60 * 24))
    minutes = 0;
  
  Serial.print("checking system status after (");
  Serial.print(minutes);
  Serial.println(") minutes from reset");

  return true;
}

void setup() {
  Serial.begin(115200);
  
  setup_pump_and_sensor();
  setup_wifi();
  timer.every(500, toggle_led);  
  timer.every(60 * 1000, check_status);  
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(mqtt_callback);
}

void loop() {
  timer.tick();
  check_connection();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    send_msg(msg);
  }

  switch(state) {
    case WAIT:
      break;
    case IR_START:
      irigate();
      break;
    case IR_SEQ:
      break;
    case IR_END:
      break;
  }
}
