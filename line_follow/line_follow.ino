/*  
  Line Follower using:
  - QTR Sensor Array
  - L298N Motor Driver
  - PID Controller
*/

#include <QTRSensors.h>

// Motor driver pins (L298N)
#define IN1 5
#define IN2 4
#define IN3 7
#define IN4 8
#define ENA 3   // PWM for Motor A
#define ENB 9   // PWM for Motor B

QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
int max_speed = 225;
int L = 0;
int R = 0;
int error = 0;
int adj = 0;

float Kp = 1;
float Ki = 0.0090;
float Kd = 1.5;

int P;
int I;
int D;
int lastError = 0;

uint16_t position;

void setup() {
  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);
  
  // Initialize QTR sensor
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ A0, A1, A2, A3, A4, A5, 10, 11 }, SensorCount);
  qtr.setEmitterPin(6);

  for (uint16_t i = 0; i < 200; i++) {
    qtr.calibrate();
  }
  Serial.println("Calibration Done");
}

void loop() {
  PID_control();
}

void PID_control() {
  position = qtr.readLineWhite(sensorValues);
  Serial.print("QTR::");
  Serial.println(position);

  error = 3500 - position;

  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;

  adj = P * Kp + I * Ki + D * Kd;

  L = max_speed + adj;
  R = max_speed - adj;

  L = constrain(L, 0, max_speed);
  R = constrain(R, 0, max_speed);

  forward(L, R);
}

void forward(int speedL, int speedR) {
  // Left Motor (Motor A)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speedL);

  // Right Motor (Motor B)
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speedR);
}

void sharp_right() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 255);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 255);
}

void sharp_left() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 255);
}
