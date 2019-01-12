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
