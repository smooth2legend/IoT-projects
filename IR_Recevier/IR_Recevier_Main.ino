#include <IRremote.h>
#include <IRremoteInt.h>
#define irPin 2
IRrecv irrecv(irPin);
decode_results results;
#define r1 3
int relay1 = LOW;
 void setup()
{
irrecv.enableIRIn();
pinMode(r1, OUTPUT);
}
 void loop() {
if (irrecv.decode(&results)) {
switch (results.value) {
case 4039382595:   //change the hex code
 relay1 = ~ relay1;
digitalWrite(r1,relay1);
delay(250);
break;
}
irrecv.resume();
 }
}