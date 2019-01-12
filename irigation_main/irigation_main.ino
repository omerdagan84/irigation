/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "dagan";
const char* password = "dagan123";
const char* mqtt_server = "192.168.1.102";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int temp;
bool status = false;
#define PUMPA D8
#define PUMPB D7
#define PUMPC D6
#define PUMPD D5

#define S_PWR_A D1
#define S_PWR_B D2
#define S_PWR_C D3
#define S_PWR_D D4

void setup() {
  digitalWrite(BUILTIN_LED, LOW);
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output

  digitalWrite(PUMPA, HIGH);
  pinMode(PUMPA, OUTPUT);
  digitalWrite(PUMPB, HIGH);
  pinMode(PUMPB, OUTPUT);
  digitalWrite(PUMPC, HIGH);
  pinMode(PUMPC, OUTPUT);
  digitalWrite(PUMPD, HIGH);
  pinMode(PUMPD, OUTPUT);
  
  pinMode(S_PWR_A, OUTPUT);
  pinMode(S_PWR_B, OUTPUT);
  pinMode(S_PWR_C, OUTPUT);
  pinMode(S_PWR_D, OUTPUT);
  
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("test", "hello world");
      // ... and resubscribe
      client.subscribe("test");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
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
    digitalWrite(S_PWR_A, HIGH);
    delay(500);
    temp = analogRead(0);
    Serial.print("Analog value 1: ");
    Serial.println(temp);
    digitalWrite(S_PWR_A, LOW);
    delay(1000);

    digitalWrite(S_PWR_B, HIGH);
    delay(500);
    temp = analogRead(0);
    Serial.print("Analog value 2: ");
    Serial.println(temp);
    digitalWrite(S_PWR_B, LOW);
    delay(1000);
    
    digitalWrite(S_PWR_C, HIGH);
    delay(500);
    temp = analogRead(0);
    Serial.print("Analog value 3: ");
    Serial.println(temp);
    digitalWrite(S_PWR_C, LOW);
    delay(1000);
    
    digitalWrite(S_PWR_D, HIGH);
    delay(500);
    temp = analogRead(0);
    Serial.print("Analog value 4: ");
    Serial.println(temp);
    digitalWrite(S_PWR_D, LOW);
    delay(1000);

    digitalWrite(PUMPA, LOW);
    delay(3000);
    digitalWrite(PUMPA, HIGH);
}
