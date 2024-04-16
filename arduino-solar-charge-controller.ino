#include <LiquidCrystal.h>

#define batteryPin A0 
#define solarPanelPin A1 

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const float batteryVoltageMax = 3.7; 
const float voltageConversionFactor = 5.0 / 1023.0; 

void setup() {
  lcd.begin(16, 2);
  Serial.begin(115200);
  displayTitle("Made by", "ARobertM");
  delay(2000);
  displayTitle("Solar Power", "Manager");
  delay(2000);
}

void loop() {
  float batteryAnalogReading = analogRead(batteryPin);
  float batteryVoltage = batteryAnalogReading * voltageConversionFactor * (batteryVoltageMax / 3.7); 
  float solarPanelAnalogReading = analogRead(solarPanelPin);
  float solarPanelVoltage = solarPanelAnalogReading * voltageConversionFactor;
  float batteryPercentage = (batteryVoltage / batteryVoltageMax) * 100;

  // Trimitere date către ESP via Serial
  Serial.print(batteryVoltage, 2);
  Serial.print(",");
  Serial.print(batteryPercentage, 1);
  Serial.print(",");
  Serial.println(solarPanelVoltage, 2);

  // Afișare valori pe LCD
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

  delay(10000); // Delay între citiri
}

void displayTitle(String line1, String line2) {
  lcd.clear();
  int start1 = (16 - line1.length()) / 2;
  int start2 = (16 - line2.length()) / 2;
  for (int i = 0; i < line1.length(); ++i) {
    lcd.setCursor(start1 + i, 0);
    lcd.print(line1.charAt(i));
    delay(200);
  }
  for (int i = 0; i < line2.length(); ++i) {
    lcd.setCursor(start2 + i, 1);
    lcd.print(line2.charAt(i));
    delay(200);
  }
}
