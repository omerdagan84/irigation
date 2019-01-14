#ifndef _DEFINES_
#define _DEFINES_
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define PUMPA D8
#define PUMPB D7
#define PUMPC D6
#define PUMPD D5

#define S_PWR_A D1
#define S_PWR_B D2
#define S_PWR_C D3
#define S_PWR_D D4

const char* ssid = "dagan";
const char* password = "dagan123";
const char* mqtt_server = "192.168.1.102";
const char* dev_name = "ir1";

int SENSE_A_THR = 700;
int SENSE_B_THR = 700;
int SENSE_C_THR = 700;
int SENSE_D_THR = 700;

void mqtt_callback(char* topic, byte* payload, unsigned int length);
void setup_pump_and_sensor();
void pump_seq(int pump, int sDuration);
int read_humidity(int sensor_pwr);
void setup_wifi();
void reconnect();
void send_msg(char *msg);
void irigate();
void check_connection();

enum t_state {
  WAIT,
  IR_START,
  IR_SEQ,
  IR_END  
};
enum t_state state = WAIT;

#endif
