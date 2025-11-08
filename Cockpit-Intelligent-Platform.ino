// --- Cockpit Intelligent Platform ---
// Components: US-100 Ultrasonic Sensor, IR Sensor, Accelerometer, Arduino Uno

// Pin definitions
#define TRIG 9
#define ECHO 8
#define IR_SENSOR A0
#define X_PIN A1
#define Y_PIN A2
#define Z_PIN A3

long duration;
float distance;
int irValue;
float xVal, yVal, zVal;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(IR_SENSOR, INPUT);
  delay(1000);
  Serial.println("Cockpit Intelligent Platform Monitoring Started...");
}

void loop() {
  // --- Ultrasonic Sensor: Distance Measurement ---
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2; // Convert to cm

  // --- IR Sensor: Obstacle Detection ---
  irValue = analogRead(IR_SENSOR);

  // --- Accelerometer Sensor: Motion Detection ---
  xVal = analogRead(X_PIN);
  yVal = analogRead(Y_PIN);
  zVal = analogRead(Z_PIN);

  // --- Display Results ---
  Serial.print("Distance (cm): ");
  Serial.print(distance);
  Serial.print(" | IR Value: ");
  Serial.print(irValue);
  Serial.print(" | Accel X: ");
  Serial.print(xVal);
  Serial.print(" Y: ");
  Serial.print(yVal);
  Serial.print(" Z: ");
  Serial.println(zVal);

  // --- Safety Alerts ---
  if (distance < 15) {
    Serial.println("⚠️ Warning: Object too close! Maintain safe distance.");
  }

  if (irValue > 500) {
    Serial.println("⚠️ Obstacle detected via IR sensor!");
  }

  if (abs(xVal - 512) > 150 || abs(yVal - 512) > 150 || abs(zVal - 512) > 150) {
    Serial.println("⚠️ Sudden movement detected — Possible driver jerk or imbalance!");
  }

  delay(1000); // Wait 1 second before next reading
}
