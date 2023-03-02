#define TRIG_PIN_1 3
#define ECHO_PIN_1 4
#define TRIG_PIN_2 5
#define ECHO_PIN_2 6

void setup() {
  Serial.begin(14400);

  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
}

void loop() {
  float duration1, height1, duration2, height2;
  float theta;

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
  height1 = (duration1 / 2) * 0.0343 * sin(theta);
  height2 = (duration2 / 2) * 0.0343 * sin(theta);

  // Print the values to the serial monitor
  String heights = String(height1) + " " + String(height2);
  Serial.println(heights);
  delay(500);
}
