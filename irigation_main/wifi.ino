#include "defines.h"

void setup_wifi() {

  delay(1000);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(dev_name, "hello world");
      // ... and resubscribe
      char topic[128];
      snprintf(topic, sizeof(topic), "%s/#", dev_name);
      client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void send_msg(char *msg) {
      char topic[128];
      snprintf(topic, sizeof(topic), "%s/#", dev_name);
      client.publish(dev_name, msg);
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  String sTopic = String(topic);
  Serial.print("Message arrived [");
  Serial.print(sTopic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  /*
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW); 
  } else {
    digitalWrite(BUILTIN_LED, HIGH);
  }
  */

}

void check_connection() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
