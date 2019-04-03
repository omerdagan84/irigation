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

bool grow_led(bool state) {
	if (state) {
		led_state = HIGH;
	} else {
		led_state = LOW;
	}
	digitalWrite(LED_BUILTIN, led_state);

  return true; // keep timer active? true
}

int sequance;
bool check_status (void *)
{
  int pumped;
  
  
  minutes++;
  if (minutes == (60 * 24))
    minutes = 0;
  
  Serial.print("checking system status after (");
  Serial.print(minutes);
  Serial.println(") minutes from reset");

switch(state) {
    case WAIT:
      if (minutes >= led_time_on && minutes <= led_time_off)
          grow_led( true );
	  else
		  grow_led( false );

      if (minutes == check_time)
        state = IR_START;
      break;
    case IR_START:
      Serial.println("starting irigation sequance");
      pumped = irigate();
      if (pumped) {
        Serial.println("Irigated first sequance");
        state = IR_SEQ;
        sequance = 0;
      } else {
        Serial.println("No need to irigate");
        state = WAIT;
      }
      break;
    case IR_SEQ:
      Serial.println("irigation seq state");
      sequance++;
      if (((minutes - last_check) > 15) && (sequance < 5)) {
        
        Serial.println("rechecking irigation seq");
        pumped = irigate();
        if (!pumped) {
          Serial.println("No need to irigate - moving back to WAIT");
          state = WAIT;
        }
      } else {
        sequance = 0;
        state = WAIT;
      }
      break;
    case IR_END:
      break;
  }
  return true;
}

void setup() {
  Serial.begin(115200);
  
  setup_pump_and_sensor();
  setup_wifi();
  timer.every(60 * 1000 , check_status);  
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(mqtt_callback);

  check_connection( NULL );
}

int ir_seq = 0;
void loop() {
  timer.tick();
}
