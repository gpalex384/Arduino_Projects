//www.elegoo.com
//2016.12.09
#include <Servo.h>
#include <AFMotor.h>

Servo servoInstance;  // create servo object to control a servo

//Initialize motors
AF_DCMotor motorRH(1);
AF_DCMotor motorLH(4);

// Arduino pin numbers
int  ledPin  =  13;   // select the pin for  the LED
const int SW_pin = 40; // digital pin connected to switch output
const int X_pin = 8; // analog pin connected to X output
const int Y_pin = 9; // analog pin connected to Y output
#define ENABLE 5
#define DIRB 4
//Variables de diseño
int x_dir=0;
int y_dir=0;
int ang = 0;    // variable to store the servo position
double mago = 0;  //variable para calcular el angulo de servo
float magopot = 0; //variable para calcular la potencia del motor
int potencia = 0;  //variable de potencia del motor


void setup() {
  //pinMode(ledPin,OUTPUT);
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
//Servos
  servoInstance.attach(10);  // attaches the servo on pin 10 to the servo object
  servoInstance.write(110);
  Serial.begin(9600);
//Motores
  motorRH.setSpeed(250);     //encendemos motores
  motorLH.setSpeed(250);
  motorRH.run(RELEASE);      //apagamos motores
  motorLH.run(RELEASE);  
//Delay
  delay(5000);
  }


void loop() {
//Sacamos en el monitor informacion del joystick, del angulo del servo y de la potencia
  Serial.print("Switch:  ");
  Serial.println(digitalRead(SW_pin));
  Serial.print("X-axis: ");
  Serial.println(x_dir);                //direccion X
  Serial.print("Y-axis: ");
  Serial.println(y_dir);                //direccion Y
//leemos los datos del joystick y se lo asignamos a las variables
  x_dir=analogRead(X_pin);  
  y_dir=analogRead(Y_pin);
  
//Calculo del angulo del servo segun entrada de joystick
  mago=70+x_dir*0.0782;
  ang=int(mago);
//Damos el valor de ang al servo solo si está en un rango seguro
  if (ang>65 && ang<155){
  servoInstance.write(ang);
  delay(50);
  }
//Calculo de la potencia de motor segun eje y
  magopot=0.510*y_dir-270;
  potencia=int(magopot);
//Encendemos el led si vamos hacia atrás
  //if (y_dir < 480){
    //digitalWrite(ledPin,HIGH);
    //delay(30);
  //}
  //else {
    //digitalWrite(ledPin,LOW);    
  //}
//Ponemos en marcha el motor si la potencia esta dentro del rango
  if (y_dir>530 && potencia>=30 && potencia<=255) {
    //motorRH.run(FORWARD);     //Palante
    motorLH.run(FORWARD); 
    //motorRH.setSpeed(potencia);
    motorLH.setSpeed(potencia);
  }
  else {
    motorLH.run(RELEASE);
    motorLH.setSpeed(0);
  }


  //Serial.print("Angulo de mago: ");
  //Serial.println(mago);
  Serial.print("Angulo de servo: ");
  Serial.println(ang);                  //angulo servo
  //Serial.print("Magopot: ");
  //Serial.println(magopot);
  Serial.print("Potencia motor: ");
  Serial.println(potencia);             //potencia motor de 0 a 255
  //Serial.print("\n");

}
