 #include <IRremote.h>
 //Right motor
 int enableRightMotor=5; 
int rightMotorPin1=7;
 int rightMotorPin2=8;
 //Left motor
 int enableLeftMotor=6;
 int leftMotorPin1=9;
 int leftMotorPin2=10;
 #define RECV_PIN 2
 IRrecv irrecv(RECV_PIN);
 decode_results results;
 #define MAX_MOTOR_SPEED 200
 void setup()
 {
  // put your setup code here, to run once:
  pinMode(enableRightMotor,OUTPUT);
  pinMode(rightMotorPin1,OUTPUT);
  pinMode(rightMotorPin2,OUTPUT);
  
  pinMode(enableLeftMotor,OUTPUT);
  pinMode(leftMotorPin1,OUTPUT);
  pinMode(leftMotorPin2,OUTPUT);
  rotateMotor(0,0);
    
  irrecv.enableIRIn(); // Start the receiver
 }
 void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
 {
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed >= 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);    
  }
  else if (leftMotorSpeed >= 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
}
 void loop() 
{
  if (irrecv.decode(&results)) 
  {
    irrecv.resume(); // Receive the next value
    
    //40BD649B  FORWARD
    //40BD14EB  BACKWARD
    //40BDA45B  LEFT
    //40BDE41B  RIGHT
    //40BDB04F  STOP                                   use chatgpt to find code for hex 
    
    if (results.value == 0x40BD649B)
    {
      rotateMotor(MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);      
    }
    else if (results.value == 0x40BD14EB)
    {
      rotateMotor(-MAX_MOTOR_SPEED, -MAX_MOTOR_SPEED);       
    }
    else if (results.value == 0x40BDA45B)
    {
      rotateMotor(MAX_MOTOR_SPEED, -MAX_MOTOR_SPEED);       
    }
    else if (results.value == 0x40BDE41B)
    {
      rotateMotor(-MAX_MOTOR_SPEED, MAX_MOTOR_SPEED);       
    }
    delay(200);
  }
  else
  {
    rotateMotor(0, 0);           
  }
 }
