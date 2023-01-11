#include <Wire.h>
#include <MPU6050_tockn.h>
#define I2C_SLAVE_ADDR 0x08
#define MPU_6050_ADDR 0x68
#define SOUND_SPEED 0.034
MPU6050 mpu6050(Wire);
int trigPin = 5;
int echoPin = 18;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
  float duration;
  float distanceCm = 30;
  Wire.beginTransmission(0x08);   // transmit to slave device address 8
  Wire.write("Forwards1second");  // send five bytes, one for each character
  Wire.endTransmission();// end transmission, Sends Forwards1second to Arduino, which will activate Forwards1second
  delay(1000);
  mpu6050.calcGyroOffsets(true);        

  Wire.beginTransmission(0x08);  //transmit to slave device
  Wire.write("Turn180");         //Sends 'Turn180' to Arduino, which will activate the Turn180 function
  Wire.endTransmission();        //End transmission
  float Z = mpu6050.getAngleZ(); //Assign variable Z to angle of rotation of MPU
  while (Z <= 180)               //While Z<=180 degrees the car will keep turning left until MPU is at 180 degrees from Starting position
  { Z = mpu6050.getAngleZ(); }   //While loop willl make the MPU keep checking constantly until angle is reached
  Wire.beginTransmission(0x08);
  Wire.write("stopMotors");  //Car will then stop
  Wire.endTransmission();
  delay(1000);
  mpu6050.calcGyroOffsets(true);
   
  Wire.beginTransmission(0x08);
  Wire.write("GoBackwards");  //Car will then reverse
  Wire.endTransmission();
  while (distanceCm <= 10) {     //Check distance until it is less than or equal to 10cm
    digitalWrite(trigPin, LOW);  //Clear Trig Pin
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);  //Emit Ultrasonic signal
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);  //Clear trig pin again
    duration = pulseIn(echoPin, HIGH);        // Activate EchoPin to recieve Signal
    distanceCm = duration * SOUND_SPEED / 2;  //Calculate Distance
    Serial.print("Distance (cm): ");          //Print out distance to serial Monitor
    Serial.println(distanceCm);
  }
  Wire.beginTransmission(0x08);
  Wire.write("stopMotors");  //Once distance is equal to 10cm Car will stop
  Wire.endTransmission();
  delay(1000);
  mpu6050.calcGyroOffsets(true);

  Wire.beginTransmission(0x08);
  Wire.write("Turn90");
  Wire.endTransmission();
  while (Z >= 90) { Z = mpu6050.getAngleZ(); }
  Wire.beginTransmission(0x08);
  Wire.write("stopMotors");
  Wire.endTransmission();
  mpu6050.calcGyroOffsets(true);
     
  Wire.beginTransmission(0x08);
  Wire.write("GoBackwards");  //Car will then reverse
  Wire.endTransmission();
  distanceCm = 30;
  while (distanceCm <= 10) {     //Check distance until it is less than or equal to 10cm
    digitalWrite(trigPin, LOW);  //Clear Trig Pin
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);  //Emit Ultrasonic signal
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);  //Clear trig pin again
    duration = pulseIn(echoPin, HIGH);        // Activate EchoPin to recieve Signal
    distanceCm = duration * SOUND_SPEED / 2;  //Calculate Distance
    Serial.print("Distance (cm): ");          //Print out distance to serial Monitor
    Serial.println(distanceCm);
  }
}
