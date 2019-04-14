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
		state_ctx.led_state = HIGH;
	} else {
		state_ctx.led_state = LOW;
	}
	digitalWrite(LED_BUILTIN, state_ctx.led_state);

  return true; // keep timer active? true
}

int sequance;
bool check_status (void *)
{
  int pumped;
  
  
  time_ctx.minutes++;
  if (time_ctx.minutes == (60 * 24))
    time_ctx.minutes = 0;
  
  Serial.print("checking system status after (");
  Serial.print(time_ctx.minutes);
  Serial.println(") minutes from reset");

switch(state) {
    case WAIT:
      if (time_ctx.minutes >= time_ctx.led_time_on && time_ctx.minutes <= time_ctx.led_time_off)
          grow_led( true );
	  else
		  grow_led( false );

      if (time_ctx.minutes == time_ctx.check_time)
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
      if (((time_ctx.minutes - time_ctx.last_check) > 15) && (sequance < 5)) {
        
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
  
  check_connection( NULL );
}

int ir_seq = 0;
void loop() {
  timer.tick();
}
