#define relay1 3  // Connect relay1 to pin D3

String readString = "";

void setup() {
  Serial.begin(9600);           // Set baud rate for communicating with phone
  pinMode(relay1, OUTPUT);      // Set relay1 as an output
  digitalWrite(relay1, LOW);    // Switch relay1 off initially
}

void loop() {
  while (Serial.available()) {  // Check if there are available bytes to read
    delay(10);                  // Delay to make it stable
    char c = Serial.read();     // Conduct a serial read

    if (c == '#') {             // Stop the loop once # is detected
      break;
    }

    readString += c;            // Means readString = readString + c
  }

  if (readString.length() > 0) {
    Serial.println(readString);        // Print the received string

    if (readString == "f success") {
      digitalWrite(relay1, HIGH);      // Turn relay ON
      delay(3000);                     // Wait for 3 seconds
      digitalWrite(relay1, LOW);       // Turn relay OFF
    }

    readString = "";  // Clear the string for next command
  }
}
