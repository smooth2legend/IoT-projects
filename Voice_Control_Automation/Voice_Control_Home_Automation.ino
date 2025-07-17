#define relay1 2    //Connect relay1 to pin 2
 #define relay2 3    //Connect relay2 to pin 3
 #define relay3 4    //Connect relay3 to pin 4
 #define relay4 5    //Connect relay4 to pin 5
 String voice;
 void setup()
 {
  Serial.begin(9600);            //Set rate for communicating with phone
  pinMode(relay1, OUTPUT);       //Set relay1 as an output
  pinMode(relay2, OUTPUT);       //Set relay2 as an output
  pinMode(relay3, OUTPUT);       //Set relay3 as an output
  pinMode(relay4, OUTPUT);       //Set relay4 as an output
  digitalWrite(relay1, HIGH);     //Switch relay1 off
  digitalWrite(relay2, HIGH);     //Swtich relay2 off
  digitalWrite(relay3, HIGH);     //Switch relay3 off
  digitalWrite(relay4, HIGH);     //Swtich relay4 off
 }
 void loop() 
{
  while (Serial.available()){ //Check if there is an available byte to read
     delay(10); //Delay added to make thing stable 
    char c = Serial.read(); //Conduct a serial read
    if (c == '#') {break;} //Exit the loop when the # is detected after the word
    voice += c; //Shorthand for voice = voice + c
  }
  if (voice.length() > 0)
 
  {
    if(voice == "*turn on light"){           //Voice Command to ON Relay 01 
      digitalWrite(relay1, LOW);   //Relay 01 ON
      }
    else if(voice == "*turn on LED"){      //Voice Command to ON Relay 02 
      digitalWrite(relay2, LOW);   //Relay 02 ON
      }
    else if(voice == "*turn on alarm") {     //Voice Command to ON Relay 03
      digitalWrite(relay3, LOW);   //Relay 03 ON
    }
    else if(voice == "*turn on fan") {     //Voice Command to ON Relay 04 
      digitalWrite(relay4, LOW);   //Relay 04 ON
    }
    
        
    else if(voice == "*turn off light") {      //Voice Command to OFF Relay 01 
      digitalWrite(relay1, HIGH);   //Relay 01 OFF
    }
    else if(voice == "*turn off LED") {      //Voice Command to OFF Relay 02
      digitalWrite(relay2, HIGH);   //Relay 02 OFF
    }
    else if(voice == "*turn off buzzer") {      //Voice Command to OFF Relay 02
      digitalWrite(relay3, HIGH);   //Relay 03 OFF
    }
    else if(voice == "*turn off fan") {      //Voice Command to OFF Relay 02
      digitalWrite(relay4, HIGH);   //Relay 04 OFF
    }
    
    
    
    else if(voice == "*turn all devices on") {      //Voice Command to ON all Relays
      switchallon();                //All Relays ON
    }
    else if(voice == "*turn all devices off") {      //Voice Command to OFF all Relays
      switchalloff();               //All Relays OFF
    }
    
  voice=""; //Reset the variable after initiating
  }
 }
    
void switchalloff()               //Function for turning OFF all relays
 {
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
 }
 void switchallon()                //Function for turning ON all relays
 {
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
 }
