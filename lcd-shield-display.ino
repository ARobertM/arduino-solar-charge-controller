#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int lcd_key = 0;
int adc_key_in = 0;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Made by Robert");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Solar Manager");
  lcd.setCursor(0, 1);
  lcd.print("   Controller   ");
  delay(2000);
}

void loop() {
  fadeEffect("Solar Manager", 0, 0); // Animăm primul rând
  fadeEffect("   Controller   ", 0, 1); // Animăm al doilea rând
}

// Funcție pentru efectul de "fade"
void fadeEffect(String text, int x, int y) {
  for (int i = 0; i < text.length(); ++i) {
    lcd.setCursor(x + i, y);
    lcd.print("_");
    delay(100); // Pauză pentru efectul de "fade"
    lcd.setCursor(x + i, y);
    lcd.print(text.charAt(i));
  }
}
