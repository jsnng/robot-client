const int irPin = 2; // Digital pin connected to IR sensor output (S)
const int kickerOutputPin = 5; // Digital pin connected to kicker
const int dribblerPin = 3; 

int dribblerPower = 1600;
int dribblerStopPin = 1500; 
int kickerPulseTime = 10; // Pulse duration for kicker
bool pinStatus = HIGH; // Variable to store the pin status of kicker

char incomingByte; // Variable to store incoming serial data

#include <Servo.h>
Servo esc; 

void setup() {
  pinMode(irPin, INPUT); // Set IR receiver pin as input
  pinMode(kickerOutputPin, OUTPUT); // Set kicker pin as output
  Serial.begin(9600); // Initialize serial communication

  // Attach the dribbler to the pin
  esc.attach(dribblerPin);
  esc.writeMicroseconds(dribblerStopPin); // Initialize dribbler to stop position
}

void loop() {
  // Check for incoming serial data
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 'K') { // If 'K' is typed
      digitalWrite(kickerOutputPin, LOW); // Activate kicker
      delay(kickerPulseTime); // Pulse duration
      digitalWrite(kickerOutputPin, HIGH); // Deactivate kicker
    } else if (incomingByte == 'D') { // If 'D' is typed
      esc.writeMicroseconds(dribblerPower); // Turn on dribbler
    } else if (incomingByte == 'S') { // If 'S' is typed
      esc.writeMicroseconds(dribblerStopPin); // Turn off dribbler
    }
  }

  // Check IR sensor (existing logic)
  int sensorValue = digitalRead(irPin);
  if (sensorValue == LOW) { // Check if IR signal detected (object present)
    esc.writeMicroseconds(dribblerPower); // Turn on dribbler
    Serial.println("Object detected!");
  }
}