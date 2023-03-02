#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT11.h>
#define TRIG_PIN_1 3
#define ECHO_PIN_1 4
#define TRIG_PIN_2 5
#define ECHO_PIN_2 6

DHT11 dht11(A0);

LiquidCrystal_I2C lcd(0x3F, 16, 2);

unsigned long previousMillis = 0;
const long interval = 500; // interval between sensor readings (in milliseconds)
float initialtemp;

void setup() {
  Serial.begin(19200);

  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("   LIME  FIZZ  ");
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
    String heights = String(height1) + " " + String(height2);
    Serial.println(heights);
  }

  if (res == 0 || initialtemp != temp){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   LIME  FIZZ  ");
    lcd.setCursor(0,1);
    lcd.print(" temp : " + String(temp) + " C");
    Serial.println("temperature : " + String(temp)+"C");
    initialtemp = temp;
  }
}
