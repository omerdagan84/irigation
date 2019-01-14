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

void setup() {
  Serial.begin(115200);
  
  setup_pump_and_sensor();
  setup_wifi();
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(mqtt_callback);
}

void loop() {
  digitalWrite(BUILTIN_LED,!(digitalRead(BUILTIN_LED)));
  delay(500);



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
    case IR_SEQ:
    case IR_END:
    irigate();
  }
}
