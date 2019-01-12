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
  int sRead;
  if (status) {
    digitalWrite(BUILTIN_LED, LOW);
  } else {
    digitalWrite(BUILTIN_LED, HIGH);
  }
  status = !status;
/*
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("test", msg);
  }
  */
  sRead = read_humidity(S_PWR_A);
  if (sRead > SENSE_A_THR)
    pump_seq(PUMPA, 5);

  sRead = read_humidity(S_PWR_B);
  if (sRead > SENSE_B_THR)
    pump_seq(PUMPB, 5);

  sRead = read_humidity(S_PWR_C);
  if (sRead > SENSE_C_THR)
    pump_seq(PUMPC, 5);

  sRead = read_humidity(S_PWR_D);
  if (sRead > SENSE_D_THR)
    pump_seq(PUMPD, 5);

}
