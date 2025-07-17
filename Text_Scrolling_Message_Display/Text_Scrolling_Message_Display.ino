#include <Adafruit_GFX.h>
 #include <Adafruit_NeoMatrix.h>
 #include <Adafruit_NeoPixel.h>
 #ifndef PSTR
 #define PSTR 
#endif
 #define PIN 8
 #define mw 10
 #define mh 5
 Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(mw, mh, PIN,
 NEO_MATRIX_ZIGZAG, 
NEO_GRB            
+ NEO_KHZ400);
 const uint16_t colors[] = {
 matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
 };
 void setup() {
 matrix.begin();
 matrix.setTextWrap(false);
 matrix.setBrightness(40);
 matrix.setTextColor(colors[0]);
 }
 int x    
= matrix.width();
 int pass = 0;
 void loop() {
 matrix.fillScreen(0);
 matrix.setCursor(x,0);
 matrix.print(F("enter your text"));
 if(--x < -50) {
 x = matrix.width();
 if(++pass >= 3) pass = 0;
 matrix.setTextColor(colors[pass]);
 }
 matrix.show();
 delay(70);
 }
