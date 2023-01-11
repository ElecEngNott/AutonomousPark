#include <Wire.h>   // include Wire library
#include <Servo.h>  //include the servo library
#define servoPin 4
Servo myservo;          // create servo object to control a servo
float steeringAngle;    // variable to store the servo position
#define enA 5           //EnableA command line - should be a PWM pin
#define enB 6           //EnableB command line - should be a PWM pin
#define INa A0          //Channel A direction
#define INb A1          //Channel A direction
#define INc A2          //Channel B direction
#define INd A3          //Channel B direction
byte speedSetting = 0;  //initial speed = 0
String message;

void receiveEvent() {
  message = "";
  while (Wire.available()) {  // loop whilst bus is busy
    char c = Wire.read();     // receive data byte by byte
    message += c;             // form complete string
  }
  Serial.println(message);  // write string to serial monitor
  delay(500);
}

void setup() {
  Wire.begin(0x08);              // join i2c bus with address 8
  Wire.onReceive(receiveEvent);  // create a receive event
  Serial.begin(9600);            // start serial to visualise data
  myservo.attach(servoPin); // Attach steering pin
  pinMode(INa, OUTPUT); // Set all control pins as outputs
  pinMode(INb, OUTPUT);
  pinMode(INc, OUTPUT);
  pinMode(INd, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);                     
  speedSetting = 255;
}

 void loop() {
  if (message = "Forwards1second") { 
    Forwards1second(); }

  if (message = "Turn180") {
     Turn180(); }

  if (message = "stopMotors") {
     stopMotors(); }

  if (message = "GoBackwards") {
     goBackwards(); }

  if (message = "Turn90") {
     Turn90(); }
     
}

void Forwards1second() {
  digitalWrite(INa, HIGH);
  digitalWrite(INb, LOW);
  digitalWrite(INc, HIGH);
  digitalWrite(INd, LOW);
  delay(1000);
  stopMotors();
}  

void goBackwards() {
  digitalWrite(INa, LOW);
  digitalWrite(INb, HIGH);
  digitalWrite(INc, LOW);
  digitalWrite(INd, HIGH);
}
void stopMotors() {
  digitalWrite(INa, LOW);
  digitalWrite(INb, LOW);
  digitalWrite(INc, LOW);
  digitalWrite(INd, LOW);
}
void goForwards() {
  digitalWrite(INa, HIGH);
  digitalWrite(INb, LOW);
  digitalWrite(INc, HIGH);
  digitalWrite(INd, LOW);
}

void Turn180() {
  myservo.write(20);
  goForwards();
}
void Turn90() {
  myservo.write(160);
  goForwards();
}
