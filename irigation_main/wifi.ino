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
      snprintf(topic, sizeof(topic), "%s", dev_name);
      Serial.print("Sending msg on topic: ");
      Serial.println(topic);
      Serial.print("msg: ");
      Serial.println(msg);
      client.publish(topic, msg);
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  //String sTopic = String(topic);
  char * msg = (char *)malloc((length + 1) * sizeof(char));
  strncpy(msg, (char *)payload, length);
  msg[length] = '\0';
  char *p1, *p2, *p3, *i;
  
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print(" , ");
  Serial.print(msg);
  Serial.println("]");
  
  if (strstr(topic, "STATUS")) {
    Serial.println("recived a STATUS message");
    send_status();
  } else if (strstr(topic, "SET")) {
    p1 = strtok_r(msg," ",&i);
    p2 = strtok_r(NULL," ",&i);
    if (strstr(p1, "TIME")) {
      p3 = strtok_r(NULL," ",&i);
      update_time(p2, p3);
    } else if (strstr(p1, "THR")) {
      p3 = strtok_r(NULL," ",&i);
      update_thr(p2, p3);
    } else if (strstr(p1, "CHECK")) {
      p3 = strtok_r(NULL," ",&i);
      update_check(p2, p3);
    } else if (strstr(p1, "START_REQ")) {
      update_start();
    }
  } else if (strstr(topic, "GET")) {
    p1 = strtok_r(msg," ",&i);
    p2 = strtok_r(NULL," ",&i);
    if (strstr(p1, "TIME")) {
      send_time();
    } else if (strstr(p1, "THR")) {
      send_thr(p2);
    }
  }
  free(msg);
}

void check_connection() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
