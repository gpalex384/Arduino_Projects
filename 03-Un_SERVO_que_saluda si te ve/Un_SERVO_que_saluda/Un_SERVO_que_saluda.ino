//www.elegoo.com
//2016.12.08
#include <Servo.h>

Servo servoInstance;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int ang = 90;    // variable to store the servo position

int pirPin = 7; // Input for HC-S501
int mov = 0; // variable que guarda el cambio de estado del PIR

void setup() {
  servoInstance.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(pirPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  mov = digitalRead(pirPin);
  delay(50);
  if (mov == HIGH)  {
    Serial.print("Deteccion S/N: ");
    Serial.println(mov);
    ang=30;
    Serial.println(ang);
    servoInstance.write(ang);
    delay(250);
      if (ang<=1) {
        ang=1;
        delay(100);
      }
      if (ang>=180) {
        ang=180;
        delay(100);
      }    
    ang=175;
    Serial.println(ang);
    servoInstance.write(ang);
    delay(350);
      if (ang<=1) {
        ang=1;
        delay(100);
      }
      if (ang>=180) {
        ang=180;
        delay(100);
      }
    ang=30;
    Serial.println(ang);
    servoInstance.write(ang);
    delay(350);
      if (ang<=1) {
        ang=1;
        delay(100);
      }
      if (ang>=180) {
        ang=180;
        delay(100);
      }    
    ang=175;
    Serial.println(ang);
    servoInstance.write(ang);
    delay(350);
      if (ang<=1) {
        ang=1;
        delay(100);
      }
      if (ang>=180) {
        ang=180;
        delay(100);
      }
    ang=95;
    servoInstance.write(ang);
    delay(250);
    mov = 0;
    delay(1200);
     }
  else {
    Serial.print("Deteccion S/N: ");
    Serial.println(mov);
    Serial.println(ang);
    delay(300);
  }

}
  
  //for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
   // myservo.write(pos);              // tell servo to go to position in variable 'pos'
   // delay(15);                       // waits 15ms for the servo to reach the position
  //}
  //for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //  myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //  delay(15);                       // waits 15ms for the servo to reach the position
//  }
//}

