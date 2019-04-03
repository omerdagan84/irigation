#include "defines.h"


void setup_pump_and_sensor() {
  digitalWrite(BUILTIN_LED, HIGH);
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output

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
}

void pump_seq(int pump, int sDuration){
    digitalWrite(pump, LOW);
    delay(sDuration * 1000);
    digitalWrite(pump, HIGH);
}

int read_humidity(int sensor) {
    int temp;
    
    digitalWrite(sensor, HIGH);
    delay(500);
    temp = analogRead(0);
    Serial.print("Analog value ");
    Serial.print(sensor);
    Serial.print(": ");
    Serial.println(temp);
    digitalWrite(sensor, LOW);
    delay(1000);

    return temp;
}

int irigate(){
  int pumped = 0;
  
  Serial.println("starting irigation sequance inner");
  
  sense_B_read = read_humidity(S_PWR_B);
  if (sense_B_read > SENSE_B_THR) {
    pump_seq(PUMPB, PUMP_TIME);
    pumped++;
  }

  sense_C_read = read_humidity(S_PWR_C);
  if (sense_C_read > SENSE_C_THR) {
    pump_seq(PUMPC, PUMP_TIME);
    pumped++;
  }

  sense_D_read = read_humidity(S_PWR_D);
  if (sense_D_read > SENSE_D_THR) {
    pump_seq(PUMPD, PUMP_TIME);
    pumped++;
  }

  last_check = minutes;

  Serial.print("currnt time: ");
  Serial.print(minutes);
  Serial.print(" last_check time: ");
  Serial.print(last_check);
  Serial.print(" pumped: ");
  Serial.println(pumped);
  
  return (pumped);
}
