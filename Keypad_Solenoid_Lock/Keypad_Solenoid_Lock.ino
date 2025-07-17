 #include <Keypad.h>
 char* password = "123";  // change the password here, just pick any 3numbers
 int position = 0;
 const byte ROWS = 4;
 const byte COLS = 4;
 char keys[ROWS][COLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
 };
 byte rowPins[ROWS] = { 9, 8, 7, 6 };
 byte colPins[COLS] = { 5, 4, 3, 2 };
 Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
 int Lock = 13;
 void setup()
 {
 pinMode(Lock, OUTPUT);
 LockedPosition(true);
 }
 void loop()
 {
 char key = keypad.getKey();
 if (key == '*' || key == '#')
 {
 position = 0;
 LockedPosition(true);
 }
 if (key == password[position])
 {
 position ++;
 }
 if (position == 3)
 {
 LockedPosition(false);
 }
 delay(100);
 }
 void LockedPosition(int locked)
 {
 if (locked)
 {
 digitalWrite(Lock, LOW);
 }
 else
 {
 digitalWrite(Lock, HIGH);
 }
 }
