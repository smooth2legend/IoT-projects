#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  // Using -1 if no reset pin is connected

// Create the display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Analog input pin
int analogInput = A1;

// Voltage divider resistor values
float R1 = 30000.0;  // 30k ohm
float R2 = 7500.0;   // 7.5k ohm

// Voltage variables
float vout = 0.0;
float vin = 0.0;
int value = 0;

void setup() {
  pinMode(analogInput, INPUT);
  Serial.begin(9600);
  Serial.println("VOLTMETER");

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true); // Infinite loop on failure
  }

  display.clearDisplay();
  
  // Draw title box
  display.drawRect(0, 0, 128, 12, SSD1306_WHITE);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.setTextSize(1);
  display.setCursor(28, 2);
  display.println("VOLTMETER");
  display.display();
  delay(1000);
}

void loop() {
  value = analogRead(analogInput);
  vout = (value * 5.0) / 1024.0;
  vin = vout / (R2 / (R1 + R2));

  if (vin < 0.09) {
    vin = 0.0; // Suppress noise
  }

  Serial.print("INPUT Voltage = ");
  Serial.print(vin, 2);
  Serial.println(" V");

  // Display voltage on OLED
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(15, 20);
  display.print(vin, 2);
  display.print(" V");
  display.display();

  delay(1000);
}
