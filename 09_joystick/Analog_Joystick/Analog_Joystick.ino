//www.elegoo.com
//2016.12.09
#include <Servo.h>
Servo servoInstance;  // create servo object to control a servo
// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output
int x_dir=0;
int y_dir=0;
int ang = 0;    // variable to store the servo position

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  servoInstance.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  ang=90;
  servoInstance.write(ang);
  delay(200);
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  x_dir=analogRead(X_pin);
  while (x_dir>800){
    ang=165;
    servoInstance.write(ang);
    delay(100);
    x_dir=analogRead(X_pin);
  }
  while (x_dir<300) {
    ang=15;
    servoInstance.write(ang);
    delay(100);
    x_dir=analogRead(X_pin);
  }
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");
  Serial.print(ang);
  delay(200);
}
