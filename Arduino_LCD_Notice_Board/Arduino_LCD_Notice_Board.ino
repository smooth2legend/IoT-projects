#include <LiquidCrystal_I2C.h>
 LiquidCrystal_I2C lcd(0x3C,16,2);  //Change the HEX address
 #include <SoftwareSerial.h>
 SoftwareSerial mySerial (2, 3);   
String val = "No Data";
 String oldval;
 String newval = "No Data";
 int i = 0;
 //(RX, TX);
 void setup() 
{
 // put your setup code here, to run once:
 //lcd.begin();
 lcd.init();      // Initializes the LCD
 lcd.backlight(); // Turns on the backlight
 mySerial.begin(9600);
 Serial.begin(9600);
 lcd.setCursor(0, 0);
 lcd.print("Digital");
 lcd.setCursor(0, 1);
 lcd.print(" Notice  Board ");
 delay(3000);
 lcd.clear();
 }
 void loop() 
{
 val = mySerial.readString();
 val.trim();
 Serial.println(val);
 if(val != oldval)
 {
 newval = val;
 }
 val = oldval;
 Serial.println(val);
 lcd.clear();
 lcd.setCursor(16, 1);
 lcd.print(newval);
 lcd.setCursor(16, 0);
 lcd.print("Notice:");
 for(int counter = 0; counter < 24; counter++)
 {
 lcd.scrollDisplayLeft();
 delay(500);
 }
 }
