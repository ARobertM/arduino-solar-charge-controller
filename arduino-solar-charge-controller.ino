#include <LiquidCrystal.h>

#define batteryPin A0 
#define solarPanelPin A1 

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const float batteryVoltageMax = 3.7; 
const float voltageConversionFactor = 5.0 / 1023.0; 

float batteryAnalogReading = 0; 
float batteryVoltage = 0; 

float solarPanelAnalogReading = 0;
float solarPanelVoltage = 0;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  
  displayTitle("Made by","Robert");
  delay(2000);
  displayTitle("Solar Power", "Manager");
  delay(2000);
}

void loop() {
  // analog
  batteryAnalogReading = analogRead(batteryPin);
  batteryVoltage = batteryAnalogReading * voltageConversionFactor * (batteryVoltageMax / 3.7); 
  
  solarPanelAnalogReading = analogRead(solarPanelPin);
  solarPanelVoltage = solarPanelAnalogReading * voltageConversionFactor;

  
  float batteryPercentage = (batteryVoltage / batteryVoltageMax) * 100;
  
  // Display values on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Bat:");
  lcd.print(batteryVoltage, 2);
  lcd.print("V (");
  lcd.print(batteryPercentage, 1);
  lcd.print("%)");

  lcd.setCursor(0, 1);
  lcd.print("Sol:");
  lcd.print(solarPanelVoltage, 2);
  lcd.print("V");
  
  // Display values on Serial Monitor
  Serial.print("Battery Voltage: "); 
  Serial.print(batteryVoltage, 2); 
  Serial.println(" V"); 

  Serial.print("Battery Percentage: "); 
  Serial.print(batteryPercentage, 1); 
  Serial.println(" %");

  Serial.print("Solar Panel Voltage: "); 
  Serial.print(solarPanelVoltage, 2); 
  Serial.println(" V"); 
  
  delay(1000); 
}

void displayTitle(String line1, String line2) {
  lcd.clear();
  int length1 = line1.length();
  int length2 = line2.length();
  int start1 = (16 - length1) / 2;
  int start2 = (16 - length2) / 2;
  for (int i = 0; i < length1; ++i) {
    lcd.setCursor(start1 + i, 0);
    lcd.print(line1.charAt(i));
    delay(200);
  }
  for (int i = 0; i < length2; ++i) {
    lcd.setCursor(start2 + i, 1);
    lcd.print(line2.charAt(i));
    delay(200);
  }
}
