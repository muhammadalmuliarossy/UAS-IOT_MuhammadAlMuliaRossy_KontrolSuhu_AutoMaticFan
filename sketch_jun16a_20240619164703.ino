#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int tempPin = A0;
const int relayPin = 3;        // Kipas angin
const int ledRedPin = 4;       // LED merah
const int ledGreenPin = 5;     // LED hijau
int analogValue;
float tempValue;
float temperature;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(0, 1);
  lcd.print("Fan: ");
}

void loop() {
  analogValue = analogRead(tempPin);
  tempValue = (analogValue / 1024.0) * 5000;
  temperature = tempValue / 10;

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" C");

  lcd.setCursor(6, 0); // Position cursor to display temperature
  lcd.print(temperature);
  lcd.print(" C  ");

  if (temperature > 33.0) {
    // Relay menyala
    digitalWrite(relayPin, LOW);
    lcd.setCursor(5, 1);
    lcd.print("ON  "); // Display "ON" for the fan

    // LED merah menyala
    digitalWrite(ledRedPin, HIGH);

    // LED hijau mati
    digitalWrite(ledGreenPin, LOW);
  } else {
    // Relay mati
    digitalWrite(relayPin, HIGH);
    lcd.setCursor(5, 1);
    lcd.print("OFF "); // Display "OFF" for the fan
    

    // LED merah mati
    digitalWrite(ledRedPin, LOW);

    // LED hijau menyala
    digitalWrite(ledGreenPin, HIGH);
  }

  delay(500);
}
