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
  int pumped;
  timer.tick();
  check_connection();

  switch(state) {
    case WAIT:
      if (minutes == check_time)
        state = IR_START;
      break;
    case IR_START:
      pumped = irigate();
      if (pumped)
        state = IR_SEQ;
      else
        state = WAIT;
      break;
    case IR_SEQ:
      if ((minutes - last_check) > 15) {
        pumped = irigate();
        if (!pumped)
          state = WAIT;
      }
      break;
    case IR_END:
      break;
  }
}
