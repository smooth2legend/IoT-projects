 #define SENSOR_PIN 2
 #define RELAY_PIN 3
 void setup() 
{
 pinMode(RELAY_PIN, OUTPUT);
 pinMode(SENSOR_PIN, INPUT);  
}
 void loop() 
{
 int sensorValue = digitalRead(SENSOR_PIN);
 if (sensorValue == HIGH)
 {
 digitalWrite(RELAY_PIN, LOW);  
}
 else
 {
 digitalWrite(RELAY_PIN, HIGH);    
}
 } 
