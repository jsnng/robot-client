#define MAX_MESSAGE_LEN 256

#include <Servo.h>
Servo esc;

// PINS
static byte kickOutputPin = 8;
static byte dribbleOutputPin = 9;
static byte irInputPin = 14;

// KICKER PARAMETERS

uint32_t kickPreviousTime = 0; // in milliseconds
uint32_t kickPulseTime = 200; // in milliseconds
bool kickPinStatus = LOW;
bool kickOn = LOW;
bool kickOff = HIGH;

// DRIBBLE PARAMETERS
uint32_t dribblePreviousTime = 0; // in milliseconds
uint32_t dribblePulseTime = 20000; // in milliseconds
int dribblePinStatus = 0;
int dribbleOn = 1600;
int dribbleOff = 1500;

// IR SENSOR PARAMETERS

// function statement for compiling
bool checkPinStatusBool(bool, uint32_t, uint32_t, uint32_t); 
int checkPinStatusInt(int, uint32_t, uint32_t, uint32_t);
void parseMessage(char *, int, uint32_t);

void setup() {
  Serial.begin(115200); // set baudrate to 19200
  pinMode(irInputPin, INPUT);
  pinMode(kickOutputPin, OUTPUT); // set kickOutputPin mode to output

  esc.attach(dribbleOutputPin);
  esc.writeMicroseconds(dribbleOff);
  dribblePinStatus = dribbleOff;
}

void loop() {
  uint32_t currentTime = millis();

  kickPinStatus = checkPinStatusBool(kickPinStatus, currentTime, kickPreviousTime, kickPulseTime);
  dribblePinStatus = checkPinStatusInt(dribblePinStatus, currentTime, dribblePreviousTime, dribblePulseTime);

  static char message[MAX_MESSAGE_LEN];
  static unsigned int position = 0;

  if(Serial.available() > 0) { // check if there is something in the serial buffer to be read
    char inByte = Serial.read(); // Serial.read() reads 1 byte at a time
    if(inByte == '\n' || position > MAX_MESSAGE_LEN) { // if this condition occurs, assume that this is the whole message
      message[position] = '\0'; // add an EOF character for Serial.println()
      parseMessage(message, position, currentTime);
      position = 0; // reset the position to start filling up buffer with new message
    } else { // keep filling buffer if not
      message[position] = inByte; 
      position++;
    }
  }

  int sensorValue = digitalRead(irInputPin);
  Serial.println(sensorValue);
  
  digitalWrite(kickOutputPin, kickPinStatus);
  esc.writeMicroseconds(dribblePinStatus);
}

void parseMessage(char * message, int length, uint32_t currentTime) {
  /*
  * parseMessage(char *, char, int)
  *    converts the serial input buffer into digital outputs
  * args:
  *   message (char *): entire serial input buffer
  *   length (int): length of the buffer
  *   currentTime (uint32_t): now (in milliseconds)
  */

  char response[256];
  char command = message[0];
  // if the message is 'K'
  if(command == 'K' && length == 1) { // if the message is a single "K"
    sprintf(response, "kick in progress");
    if(kickPinStatus == kickOff) { // check if a kick is in progress
      sprintf(response, "performing kick at %d until %d", currentTime, currentTime + kickPulseTime);
      kickPinStatus = kickOn;
      kickPreviousTime = currentTime;
    }
    Serial.println(response);
  }

  // if the message is 'D[0-9]*'
  if(command == 'D' && length == 1) { // if the message starts with a "D"
    sprintf(response, "Dribble in progress");
    if (dribblePinStatus == dribbleOff) {
      dribblePinStatus = dribbleOn;
    }
  }

  if(command == 'S' && length == 1) {
    sprintf(response, "Dribble halted");
    if (dribblePinStatus == dribbleOn) {
      dribblePinStatus = dribbleOff;
    }
  }
  sprintf(response, "action finished");
  Serial.println(response);
}

bool checkPinStatusBool(bool pinStatus, uint32_t currentTime, uint32_t previousTime, uint32_t pulseTime) {
  /*
  * checkPulse(bool, uint32_t, uint32_t, uint32_t)
  *    timer for a pin producing a bool output
  * args:
  *   pinStatus: what outputPin's output is: HIGH or LOW
  *   previousTime: time when the digital output pin was changed from LOW to HIGH (in milliseconds)
  *   currentTime: now (in milliseconds)
  *   pulseTime: maximum time the output pin remains in a HIGH state (in milliseconds)
  * returns:
  *   bool: output of pin, either HIGH or LOW
  */
  // if `previousTime` has been updated, check it has been longer than `pulseTime`
  if(currentTime - previousTime >= pulseTime) { // pulseTime is greater than interval, turn it off
    pinStatus = kickOff;
  }
  return pinStatus;
}

int checkPinStatusInt(int pinStatus, uint32_t currentTime, uint32_t previousTime, uint32_t pulseTime) {
  /*
  * checkPulse(bool, uint32_t, uint32_t, uint32_t)
  *    timer for a pin producing a int output
  * args:
  *   pinStatus: what outputPin's output is: HIGH or LOW
  *   previousTime: time when the digital output pin was changed from LOW to HIGH (in milliseconds)
  *   currentTime: now (in milliseconds)
  *   pulseTime: maximum time the output pin remains in a HIGH state (in milliseconds)
  * returns:
  *   int: output of pin
  */
  // if `previousTime` has been updated, check it has been longer than `pulseTime`
  if(currentTime - previousTime >= pulseTime) { // pulseTime is greater than interval, turn it off
    pinStatus = dribbleOff;
  }
  return pinStatus;
}


