#include <Servo.h>
#include <AFMotor.h>

AF_DCMotor motorRH(1);
AF_DCMotor motorLH(4);
Servo myservo;  // create servo object to control a servo

int pos = 120;    // variable to store the servo position


void setup() {
  // put your setup code here, to run once:
   motorRH.setSpeed(250);     //encendemos motores
   motorLH.setSpeed(250);
   motorRH.run(RELEASE);      //apagamos motores
   motorLH.run(RELEASE);
   myservo.attach(10);        // attaches the servo on pin 10 to the servo object
   myservo.write(110);         //direccion recto
   delay (5000);


}

void loop() {
  // put your main code here, to run repeatedly:

  motorRH.run(FORWARD);     //Palante

  motorLH.run(FORWARD); 
  motorRH.setSpeed(250);
  motorLH.setSpeed(250);
  myservo.write(135);
  delay(4000);
  motorRH.run(RELEASE);      //apagamos motores
  motorLH.run(RELEASE);
  delay(2000);
  
  motorRH.run(BACKWARD);    //Patrás
  motorLH.run(BACKWARD); 
  motorRH.setSpeed(0);
  motorLH.setSpeed(0);
  myservo.write(80);
  delay(2000);
  motorRH.run(RELEASE);      //apagamos motores
  motorLH.run(RELEASE);
  delay(1000);
}
