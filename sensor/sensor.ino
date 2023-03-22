#include <LiquidCrystal_I2C.h>
#include <LCD.h>
#include <Wire.h>
#include <DHT11.h>
#define TRIG_PIN_1 3
#define ECHO_PIN_1 4
#define TRIG_PIN_2 5
#define ECHO_PIN_2 6

DHT11 dht11(A0);

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);

unsigned long previousMillis = 0;
const long interval = 500; // interval between sensor readings (in milliseconds)
float initialtemp;
float initialhumi;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);

  lcd.begin (20,4); // 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE); // BL, BL_POL
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("    Lime  FiZZIO    ");
  lcd.setCursor(0,3);
  lcd.print("                    ");
}

void loop() {
  unsigned long currentMillis = millis();
  float temp, humi;
  int res = dht11.read(humi, temp);
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    float duration1, height1, duration2, height2;
    float theta = 3.14;

    // Start trigger pulse for all sensors
    digitalWrite(TRIG_PIN_1, LOW);
    digitalWrite(TRIG_PIN_2, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN_1, HIGH);
    digitalWrite(TRIG_PIN_2, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN_1, LOW);
    digitalWrite(TRIG_PIN_2, LOW);

    // Read the echo pulse for each sensor
    duration1 = pulseIn(ECHO_PIN_1, HIGH);
    duration2 = pulseIn(ECHO_PIN_2, HIGH);

    // Calculate the distance for each sensor
    height1 = (duration1 / 2) * 0.0343;
    height2 = (duration2 / 2) * 0.0343;

    // Print the values to the serial monitor
    String values = String(height1) + " " + String(height2) + " " + String(humi) + " " + String(temp);
    Serial.println(values);
    lcd.setCursor(0,0);
    lcd.print("    Lime  FiZZIO    ");
    lcd.setCursor(0,1);
    lcd.print("temperature  " + String(temp) + " C");
    lcd.setCursor(0,2);
    lcd.print("   humidity  " + String(humi) + " %");
    initialtemp = temp;
    initialhumi = humi;
  }
  if (Serial.available()){
    String str;
    str = Serial.readString();
    lcd.setCursor(0,3);
    lcd.print("                    ");
    lcd.setCursor(0,3);
    lcd.print(str);
  }
}
