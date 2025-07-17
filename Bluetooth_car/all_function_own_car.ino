#include <AFMotor.h>
AF_DCMotor MotorFR(1);   // Front right motor
AF_DCMotor MotorFL(2);   // Front left motor
AF_DCMotor MotorBL(3);   // Back left motor
AF_DCMotor MotorBR(4);   // Back right motor

const int buzPin = 2;  // Buzzer pin
const int ledPin = A5; // LED FRONT pin
const int ledPin1 = A4; // LED BACK pin
int valSpeed = 255;    // Default motor speed

void setup() {
    Serial.begin(9600);
    pinMode(buzPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(ledPin1, OUTPUT);

    // Set initial motor speed
    MotorFL.setSpeed(valSpeed);
    MotorFR.setSpeed(valSpeed);
    MotorBL.setSpeed(valSpeed);
    MotorBR.setSpeed(valSpeed);

    // Stop all motors at the beginning
    MotorFL.run(RELEASE);
    MotorFR.run(RELEASE);
    MotorBL.run(RELEASE);
    MotorBR.run(RELEASE);
}

void loop() {
    while (Serial.available() > 0) {
        char command = Serial.read(); // Read command from serial
        //Serial.println("BAT:75,SPEED:25"); // Set Battery and speed

        switch(command) {
            case 'F':   // Move forward
                SetSpeed(valSpeed);
                MotorFL.run(FORWARD);
                MotorFR.run(FORWARD);
                MotorBL.run(FORWARD);
                MotorBR.run(FORWARD);
                break;

            case 'B':   // Move backward
                SetSpeed(valSpeed);
                MotorFL.run(BACKWARD);
                MotorFR.run(BACKWARD);
                MotorBL.run(BACKWARD);
                MotorBR.run(BACKWARD);
                break;

            case 'R':   // Turn right
                SetSpeed(valSpeed);
                MotorFL.run(FORWARD);
                MotorFR.run(BACKWARD);
                MotorBL.run(FORWARD);
                MotorBR.run(BACKWARD);
                break;

            case 'L':   // Turn left
                SetSpeed(valSpeed);
                MotorFL.run(BACKWARD);
                MotorFR.run(FORWARD);
                MotorBL.run(BACKWARD);
                MotorBR.run(FORWARD);
                break;

            case 'G':   // Forward left
                MotorFL.setSpeed(valSpeed/4);
                MotorBL.setSpeed(valSpeed/4);
                MotorFL.run(FORWARD);
                MotorFR.run(FORWARD);
                MotorBL.run(FORWARD);
                MotorBR.run(FORWARD);
                break;

            case 'H':   // Forward right
                MotorFR.setSpeed(valSpeed/4);
                MotorBR.setSpeed(valSpeed/4);
                MotorFL.run(FORWARD);
                MotorFR.run(FORWARD);
                MotorBL.run(FORWARD);
                MotorBR.run(FORWARD);
                break;

            case 'I':   // Backward left
                MotorFL.setSpeed(valSpeed/4);
                MotorBL.setSpeed(valSpeed/4);
                MotorFL.run(BACKWARD);
                MotorFR.run(BACKWARD);
                MotorBL.run(BACKWARD);
                MotorBR.run(BACKWARD);
                break;

            case 'J':   // Backward right
                MotorFR.setSpeed(valSpeed/4);
                MotorBR.setSpeed(valSpeed/4);
                MotorFL.run(BACKWARD);
                MotorFR.run(BACKWARD);
                MotorBL.run(BACKWARD);
                MotorBR.run(BACKWARD);
                break;

            case 'S':   // Stop all motors
                MotorFL.run(RELEASE);
                MotorFR.run(RELEASE);
                MotorBL.run(RELEASE);
                MotorBR.run(RELEASE);
                break;

            case 'Y':   // Honk horn
                digitalWrite(buzPin, HIGH);
                delay(200);
                digitalWrite(buzPin, LOW);
                delay(80);
                digitalWrite(buzPin, HIGH);
                delay(300);
                digitalWrite(buzPin, LOW);
                break;

            case 'U':   // Turn headlight ON
                digitalWrite(ledPin, HIGH);
                break;

            case 'u':   // Turn headlight OFF
                digitalWrite(ledPin, LOW);
                break;
            case 'V':
                 digitalWrite(ledPin1, HIGH);
                break;
            case 'v':
                 digitalWrite(ledPin1, LOW);
               break;
             case 'W':
                 digitalWrite(ledPin, HIGH);
                 digitalWrite(ledPin1, HIGH);
                break;
             case 'w':
                digitalWrite(ledPin, LOW);
                digitalWrite(ledPin1, LOW);
              break;
            case 'X':
             for (int i = 0; i < 5; i++) {
                digitalWrite(ledPin, HIGH);
                digitalWrite(ledPin1, HIGH);
                delay(600);
                digitalWrite(ledPin, LOW);
                digitalWrite(ledPin1, LOW);
                delay(600);
               
            }
            break;
        case 'x':
            break;
        case 'Z':
            Serial.println("Some Other Function");
            break;
        default:
            Serial.println(">__");
            break;
            // Setting motor speed using function buttons you can do anything you want (1-4)
            case '1': SetSpeed(65); break;
            case '2': SetSpeed(130); break;
            case '3': SetSpeed(195); break;
            case '4': SetSpeed(255); break;
        }
    }
}

// Function to update motor speed
void SetSpeed(int val) {
    valSpeed = val;
    MotorFL.setSpeed(val);
    MotorFR.setSpeed(val);
    MotorBL.setSpeed(val);
    MotorBR.setSpeed(val);
}