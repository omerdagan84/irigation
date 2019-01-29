#include "defines.h"


void setup_pump_and_sensor() {
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

void irigate(){
  int sRead;
  
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
