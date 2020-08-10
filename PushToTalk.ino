#include <Arduino_APDS9960.h>

/*
 * protocole (arduino to pc):
 *   1 = Ready
 *   2 = Detected
 * protocole (pc to arduino):
 *   1 = Update settings
 */
byte minActivationValue = 50;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
  }
  Serial.println(1);
  
}

void loop() {
  byte updatePacket = 0;
  if (APDS.proximityAvailable()) {
    int proximity = APDS.readProximity();
    if(proximity <= minActivationValue) Serial.println(4);
  }
  if(Serial.read() == 0) return;
  if(updatePacket == 1){
    minActivationValue = Serial.read();
    updatePacket = 0;
    return;
  }
  updatePacket++;
  
  // wait a bit before reading again
  delay(100);
}
