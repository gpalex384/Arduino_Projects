// Adafruit Motor shield library
//Este script maneja el coche de forma que vaya hacia delante a la izquierda, y hacia atrás a la derecha.
//Combina motores con el servo de dirección

#include <AFMotor.h>
#include <Servo.h>

AF_DCMotor motorRH(4);
AF_DCMotor motorLH(1);
Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");

  // turn on motor
  motorRH.setSpeed(250);
  motorLH.setSpeed(250);
 
  motorRH.run(RELEASE);
  motorLH.run(RELEASE);
  
// attach the servo on pin 10 to the servo object
  myservo.attach(10);
  myservo.write(90);
  delay(10000);
}

void loop() {
  uint8_t i;

 // Girar a la izquierda 
  Serial.print("Izquierda");
  
  motorRH.run(FORWARD);
  motorLH.run(FORWARD); 
   
  //for (i=0; i<255; i++) {
    motorRH.setSpeed(200);
    motorLH.setSpeed(100);
    myservo.write(150); 
    delay(1000);
    myservo.write(90);
 //}
 
  for (i=150; i!=0; i--) {
    motorRH.setSpeed(i); 
    motorLH.setSpeed(i); 
    delay(10);
 }
  
  Serial.print("tock");

  motorRH.run(BACKWARD);
  motorLH.run(BACKWARD);
 // for (i=0; i<255; i++) {
    motorRH.setSpeed(75);
    motorLH.setSpeed(250);
    myservo.write(30); 
    delay(1000);
    myservo.write(90);
// }
 
  for (i=150; i!=0; i--) {
    motorRH.setSpeed(i);
    motorLH.setSpeed(i);  
    delay(10);
 }
  

  Serial.print("tech");
  motorRH.run(RELEASE);
  motorLH.run(RELEASE);
  delay(1000);
}
