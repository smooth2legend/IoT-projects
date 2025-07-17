//RFID Pin	Arduino Pin
//SDA	10
//SCK	13
//MOSI	11
//MISO	12
//IRQ	Not connected
//GND	GND
//RST	9
//3.3V	3.3V

//Don't use 5V with the RFID module — it requires 3.3V only.
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10        // RFID SS/SDA pin      
#define RST_PIN 9        // RFID RST pin
#define LED_G 4          // Green LED pin
#define LED_R 5          // Red LED pin
#define BUZZER 2         // Buzzer pin

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
Servo myServo;                    // Create servo object

void setup() {
  Serial.begin(9600);     // Start serial communication
  SPI.begin();            // Init SPI bus
  mfrc522.PCD_Init();     // Init MFRC522 RFID module
  myServo.attach(3);      // Attach servo to pin 3
  myServo.write(0);       // Set initial servo position

  pinMode(LED_G, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);

  Serial.println("Place your RFID card near the reader...");
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Read the UID
  Serial.print("UID tag: ");
  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  Serial.println();
  content.toUpperCase();  // Convert UID to uppercase

  // Match the UID with your card (modify UID below)
  if (content.substring(1) == "83 23 38 BB") {
    Serial.println("Authorized Access");
    digitalWrite(LED_G, HIGH);
    tone(BUZZER, 500);
    delay(300);
    noTone(BUZZER);
    myServo.write(180);     // Open door
    delay(5000);
    myServo.write(0);       // Close door
    digitalWrite(LED_G, LOW);
  } else {
    Serial.println("Access Denied");
    digitalWrite(LED_R, HIGH);
    tone(BUZZER, 300);
    delay(1000);
    digitalWrite(LED_R, LOW);
    noTone(BUZZER);
  }

  // Halt PICC (to prevent multiple reads)
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
