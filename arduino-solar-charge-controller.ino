// Battery Analog Read - 3.7V - A0 pin
#define batteryPin A0 
const float batteryVoltageMax = 3.7; 
const float voltageConversionFactor = 5.0 / 1023.0; 

float analogReading = 0; 
float batteryVoltage = 0; 

void setup() {
  Serial.begin(9600);
}

void loop() {
  analogReading = analogRead(batteryPin); 
  batteryVoltage = analogReading * voltageConversionFactor * (batteryVoltageMax / 3.7); 
  
  Serial.print("Battery Voltage: "); 
  Serial.print(batteryVoltage, 2); 
  Serial.println(" V"); 
  
  delay(1000); 
}

