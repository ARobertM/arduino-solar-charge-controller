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

// SolarPanel alg
// #define solarPanelPin A0 // Pinul analogic conectat la panoul solar
// const float voltageConversionFactor = 5.0 / 1023.0; // Factorul de conversie pentru transformarea citirii analogice în tensiune (V pe contor)

// float analogReading = 0; // Variabila pentru stocarea citirii analogice
// float solarPanelVoltage = 0; // Variabila pentru stocarea tensiunii de la panoul solar

// void setup() {
//   Serial.begin(9600); // Inițializarea comunicării seriale
// }

// void loop() {
//   analogReading = analogRead(solarPanelPin); // Citirea valorii analogice de la pinul panoului solar
//   solarPanelVoltage = analogReading * voltageConversionFactor; // Calcularea tensiunii de la panoul solar
  
//   Serial.print("Solar Panel Voltage: "); // Afișarea etichetei pentru tensiunea panoului solar
//   Serial.print(solarPanelVoltage, 2); // Afișarea tensiunii panoului solar cu două zecimale
//   Serial.println(" V"); // Afișarea unității de măsură (volți)
  
//   delay(1000); // Intârziere pentru a reduce frecvența de actualizare
// }


