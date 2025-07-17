// Segment pins for common cathode display (a to g)
int segPins[] = {2, 3, 4, 5, 6, 7, 8}; 

// Traffic light LED pins
int redLED = 10;
int yellowLED = 11;
int greenLED = 12;

// Segment patterns for numbers 0-9 (1 = ON for common cathode)
byte digits[10][7] = {
  {0,0,0,0,0,0,1}, // 0
  {1,0,0,1,1,1,1}, // 1
  {0,0,1,0,0,1,0}, // 2
  {0,0,0,0,1,1,0}, // 3
  {1,0,0,1,1,0,0}, // 4
  {0,1,0,0,1,0,0}, // 5
  {0,1,0,0,0,0,0}, // 6
  {0,0,0,1,1,1,1}, // 7
  {0,0,0,0,0,0,0}, // 8
  {0,0,0,0,1,0,0}  // 9
};

// Segment encoding for digits 0–9 (common cathode)
byte digits[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};
void setup() {
  // Set segment pins and LED pins as OUTPUT
  for (int i = 0; i < 7; i++) pinMode(segPins[i], OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
}

// Display digit on 7-segment
void showDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digits[num][i]);
  }
}

// Countdown with LED ON
void countdown(int sec, int ledPin) {
  digitalWrite(ledPin, HIGH);
  for (int i = sec; i >= 0; i--) {
    showDigit(i);
    delay(1000);
  }
  digitalWrite(ledPin, LOW);
}

void loop() {
  countdown(9, greenLED);   // Green for 9 seconds
  countdown(3, yellowLED);  // Yellow for 3 seconds
  countdown(6, redLED);     // Red for 6 seconds
}
