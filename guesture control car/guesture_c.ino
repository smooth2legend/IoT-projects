#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int motor1Pin1 = 8;
int motor1Pin2 = 9;
int motor2Pin1 = 10;
int motor2Pin2 = 11;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  // Initialize motor pins
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  } else {
    Serial.println("MPU6050 connected");
  }
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  // Read raw data from MPU6050
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Debugging: show raw values
  Serial.print("AX: "); Serial.print(ax);
  Serial.print(" AY: "); Serial.print(ay);
  Serial.print(" GZ: "); Serial.println(gz);

  // Tilt thresholds (adjust as needed)
  if (ay > 10000) {
    moveForward();
  } else if (ay < -10000) {
    moveBackward();
  } else if (ax > 10000) {
    turnLeft();
  } else if (ax < -10000) {
    turnRight();
  } else {
    stopMotors();
  }

  delay(100);
}

// Movement Functions
void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}
