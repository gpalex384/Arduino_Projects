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

//Variables de diseño
int x_dir=0;
int y_dir=0;
int ang = 0;    // variable to store the servo position
int potencia = 0;  //variable de potencia del motor
double magoang = 0;  //variable para calcular el angulo de servo
float magopot = 0; //variable para calcular la potencia del motor


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
  magoang=70+x_dir*0.0782;
  ang=int(magoang);
//Damos el valor de ang al servo solo si está en un rango seguro
  if (ang>65 && ang<155){
  servoInstance.write(ang);
  delay(50);
  }

//Encendemos el led si vamos hacia atrás
  //if (y_dir < 480){
    //digitalWrite(ledPin,HIGH);
    //delay(30);
  //}
  //else {
    //digitalWrite(ledPin,LOW);    
  //}
  
//Ponemos en marcha el motor si la potencia esta dentro del rango.

//Movimiento hacia ATRÁS
  if (y_dir>530){
    //Cálculo de la potencia hacia atrás
    magopot=0.510*y_dir-270; 
  Serial.print("MagopoOOOOOOOOOt: ");
  Serial.println(magopot);
  Serial.print("Angulo de servo: ");
  Serial.println(ang);                  //angulo servo

    potencia=int(magopot);
  Serial.print("THE POWER: ");
  Serial.println(potencia);             //potencia motor de 0 a 255
    
    //Hacia atrás en recto
    if (potencia>=30 && potencia<=255 && ang>95 && ang<125) {   
      motorLH.run(FORWARD);               //Motor izquierdo va hacia atrás a tope
      motorLH.setSpeed(potencia);
      motorRH.run(FORWARD);               //Motor derecho va hacia atrás a tope
      motorRH.setSpeed(potencia);
    }
    //Hacia atrás girando a la izquierda
    else if (potencia>=30 && potencia<=255 && ang<95) {   
      motorLH.run(FORWARD);               //Motor izquierdo va hacia atrás, con menos potencia
      motorLH.setSpeed(potencia/1.5);
      motorRH.run(FORWARD);               //Motor derecho va hacia atrás, a tope
      motorRH.setSpeed(potencia);
    }
    //Hacia atrás girando a la derecha
    else if (potencia>=30 && potencia<=255 && ang>125) {   
      motorLH.run(FORWARD);               //Motor izquierdo va hacia atrás, a tope
      motorLH.setSpeed(potencia);
      motorRH.run(FORWARD);               //Motor derecho va hacia atrás, con menos potencia
      motorRH.setSpeed(potencia/1.5);
    }
    else {
      magopot=0;
      potencia=int(magopot);
      motorLH.run(RELEASE);
      motorLH.setSpeed(0);
      motorRH.run(RELEASE);
      motorRH.setSpeed(0);
    }
  }

  //Movimiento hacia ADELANTE
  if (y_dir<500){
    
    //Cálculo de la POTENCIA hacia ADELANTE
    magopot=250-0.5*y_dir;
    potencia=int(magopot);
    
    //Hacia ADELANTE en recto
    if (potencia>=30 && potencia<=255 && ang>95 && ang<125) {   
      motorLH.run(BACKWARD);               //Motor izquierdo va hacia ADELANTE
      motorLH.setSpeed(potencia);
      motorRH.run(BACKWARD);               //Motor derecho va hacia ADELANTE
      motorRH.setSpeed(potencia);
    }
    //Hacia ADELANTE girando a la IZQUIERDA
    else if (potencia>=30 && potencia<=255 && ang<95) {   
      motorLH.run(BACKWARD);               //Motor izquierdo va hacia ADELANTE, con menos potencia
      motorLH.setSpeed(potencia/1.5);
      motorRH.run(BACKWARD);               //Motor derecho va hacia ADELANTE, a tope
      motorRH.setSpeed(potencia);
    }
    //Hacia ADELANTE girando a la DERECHA
    else if (potencia>=30 && potencia<=255 && ang>125) {   
      motorLH.run(BACKWARD);               //Motor izquierdo va hacia ADELANTE, con menos potencia
      motorLH.setSpeed(potencia);
      motorRH.run(BACKWARD);               //Motor derecho va hacia ADELANTE, a tope
      motorRH.setSpeed(potencia/1.5);
    }
    else {
      magopot=0;
      potencia=int(magopot);
      motorLH.run(RELEASE);
      motorLH.setSpeed(0);
      motorRH.run(RELEASE);
      motorRH.setSpeed(0);
    }
  }
  
  if (y_dir>=500 && y_dir <=530){
      magopot=0;
      potencia=int(magopot);
      motorLH.run(RELEASE);
      motorLH.setSpeed(0);
      motorRH.run(RELEASE);
      motorRH.setSpeed(0);
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
