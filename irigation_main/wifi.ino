#include "defines.h"

void setup_wifi() {
  int retry_count = 0;

  if (WiFi.status() == WL_CONNECTED)
    return;

  delay(1000);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while ((WiFi.status() != WL_CONNECTED) && ( retry_count < RETRY_LIMIT *10 )) {
    delay(500);
    Serial.print(".");
	retry_count++;
  }

  if ( retry_count == RETRY_LIMIT ) {
	Serial.println("Failed to connect to server - working standalone");
  } else {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

bool reconnect( void *param ) {
  int retry_count = 0;
  setup_wifi();

  // Loop until we're reconnected
  while ((!client.connected()) && ( retry_count++ < RETRY_LIMIT )) {
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
	    connection_state = true;
      Serial.println("established connection to broker... re-check in 1 hour");
      timer.in(60 * 60 * 1000, check_connection);
	  return true;
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 1 seconds");
      // Wait 5 seconds before retrying
      delay(1000);
    }
  }
  Serial.println("failed to establish connection to broker... reschedualing in 10 min");
  connection_state = false;
  timer.in(10 * 60 * 1000, check_connection);
  return true;
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

bool check_connection( void * ) {
  if (!client.connected()) {
    reconnect( NULL );
  }
  client.loop();
}
