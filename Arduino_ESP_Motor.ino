const int controlPin1 = 4;        //Output to H-bridge. Drives motor.
const int controlPin2 = 5;

const int bridgeEnable = 6;       //H-Bridge Enable

int motorSpeed = 6;               //Initialize motor speed at about 2.5 percent speed

const int inputPin1 = A0;         //Initialize input pins coming from ESP8266 to Arduino Analog pins
const int inputPin2 = A1;         //Utilize Analog pins because ESP8266 only provides 3.3V. Might be too low for digital input.

void setup() {

  pinMode(inputPin1, INPUT);                        //Initialize input pins from ESP8266 as inputs to the Arduino
  pinMode(inputPin2, INPUT);
  
  pinMode(controlPin1, OUTPUT);                     //Initialize motor control, H-Bridge pins as outputs
  pinMode(controlPin2, OUTPUT);
  pinMode(bridgeEnable, OUTPUT);

  digitalWrite(bridgeEnable, LOW);                  //Initialize motor control and H-Bridge pins Low
  digitalWrite(controlPin1, LOW);
  digitalWrite(controlPin2, LOW);

  Serial.begin(9600);

}

void motor_forward() {                      //Function to move our motor forward for an amount of time input by the user

  digitalWrite(bridgeEnable, HIGH);         //H bridge enable on
  digitalWrite(controlPin1, HIGH);          //Pin1 high, Pin2 low. Motor will spin forward
  digitalWrite(controlPin2, LOW);
  
}

void motor_backwards() {                    //Function to move our motor forward for an amount of time input by the user

  digitalWrite(bridgeEnable, HIGH);         //H bridge enable on
  digitalWrite(controlPin1, LOW);           //Pin1 low, Pin2 high. Motor will spin backwards
  digitalWrite(controlPin2, HIGH);
  
}

void motor_stop() {                         //Function to move our motor forward for an amount of time input by the user

  digitalWrite(bridgeEnable, HIGH);         //H bridge enable on
  digitalWrite(controlPin1, LOW);           //Pin1 low, Pin2 low. Motor will stop spinning
  digitalWrite(controlPin2, LOW);
  
}

void loop() {

  if (analogRead(inputPin1) > 410) {        //If analog read of inputPin1 > 2V --> ((410/1023 = .4)*5V)
    motor_forward();                        //Run motor_forward() function
    Serial.println("forward");
  }

  else if (analogRead(inputPin2) > 410) {   //If analog read of inputPin2 > 2V
    motor_backwards();                      //Run motor_backwards() function
    Serial.println("backwards");
  }
  
  else {                                    //If neither inputPins are > 2V
    motor_stop();                           //Run motor_stop() function
  }
  
}
