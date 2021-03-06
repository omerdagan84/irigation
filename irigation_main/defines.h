#ifndef _DEFINES_
#define _DEFINES_
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <timer.h>

#define PUMP_TIME 10
#define RETRY_LIMIT 10

#define PUMPB D3
#define PUMPC D2
#define PUMPD D1

#define S_PWR_A D5

#define S_PWR_B D8
#define S_PWR_C D7
#define S_PWR_D D6

const char* ssid = "dagan";
const char* password = "dagan123";
const char* mqtt_server = "192.168.1.102";
const char* dev_name = "irg1";


int minutes = 0;
int last_check = 0;
int check_time = (10 * 60) + 0;
int led_time_on = (6 * 60) + 0;
int led_time_off = (22 * 60) + 0;
int led_state = LOW;
bool connection_state = false;

int SENSE_B_THR = 700;
int SENSE_C_THR = 700;
int SENSE_D_THR = 700;

int sense_B_read = 2121;
int sense_C_read = 2121;
int sense_D_read = 2121;

void mqtt_callback(char* topic, byte* payload, unsigned int length);
void setup_pump_and_sensor();
void pump_seq(int pump, int sDuration);
int read_humidity(int sensor_pwr);
void setup_wifi();
bool reconnect( void * );
void send_msg(char *msg);
int irigate();
bool check_connection( void *);

void send_status( void );
void update_time(char *param);
void update_thr(char *parama, char *paramb);
void update_check(char *parama, char *paramb);
void update_start( void );

void send_time( void );
void send_thr(char *param);


enum t_state {
  WAIT,
  IR_START,
  IR_SEQ,
  IR_END  
};
enum t_state state = WAIT;

#endif
