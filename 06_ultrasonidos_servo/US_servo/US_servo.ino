#include <Servo.h>
#define TRIG_PIN 26         //Salida del sensor de ultrasonidos. Con esto le damos la señal al sensor para que empiece a actuar.
#define ECHO_PIN 28         //Entrada del sensor. Nos dará la señal con la que calculamos la distancia.

Servo myservo;  // create servo object to control a servo
long duracion, distancia;
int ang = 90;    // variable to store the servo position
int distdata[2] = {0,0};
int dmedia[10] = {0,0,0,0,0,0,0,0,0,0};
int i=0;
int j=0;
int maximo=0;

void setup() {
   Serial.begin(9600);
   myservo.attach(10);  // attaches the servo on pin 9 to the servo object
   pinMode(TRIG_PIN, OUTPUT);
   pinMode(ECHO_PIN, INPUT);
   //pinMode(13,1);                  //Define el pin 13 como salida
}

void loop() {
  i=1;                                //iniciamos el loop en i=1
  j=1;
  ang=90;                             //inicialmente, el angulo es recto
  myservo.write(ang);           //''
  delay(100);

   digitalWrite(TRIG_PIN, LOW);   //Nos aseguramos que no emitimos
   delayMicroseconds(2);          //Esperamos
   digitalWrite(TRIG_PIN, HIGH);  //Damos un pulso 
   delayMicroseconds(10);         //dura 10 microsegundos
   digitalWrite(TRIG_PIN, LOW);   //cerramos el pulso 

   duracion = pulseIn(ECHO_PIN, HIGH);    
   distancia = (duracion/58);

   if (distancia >=500 || distancia <=0){     //Tenemos en cuenta si la medición es incorrecta
    Serial.print("-----");
   }
   else {                                     //Si la medición es correcta...
    Serial.print(distancia);                  //Representamos distancia
    Serial.println(" cm");
   // digitalWrite(13,0);                       //Apagamos led
   }
  if (distancia <=5 && distancia >=1){       //Si la distancia es corta además de correcta, alarma y bucle
   // digitalWrite(13,1);
    Serial.println("Alarma!!");
    i=1;
    for (i = 1; i <= 2; i++){                 //Recorremos 160º en saltos de 20º
      ang=30+120*(i-1);
      myservo.write(ang);
      delay(700);                               //Tiempo de barrido de angulo
      j=1;
      for (j=1;j<=10;j++){
        digitalWrite(TRIG_PIN, LOW);      //Nos aseguramos que no emitimos
        delayMicroseconds(2);             //Esperamos
        digitalWrite(TRIG_PIN, HIGH);     //Damos un pulso 
        delayMicroseconds(10);
        digitalWrite(TRIG_PIN, LOW);

        duracion = pulseIn(ECHO_PIN, HIGH);
        dmedia[j] = (duracion/58);
      }
      distdata[i]=(dmedia[1]+dmedia[2]+dmedia[3]+dmedia[4]+dmedia[5]+dmedia[6]+dmedia[7]+dmedia[8]+dmedia[9]+dmedia[10])/10;
    
  }
  //Representamos el array de datos de distancia según el ángulo
  Serial.print(distdata[1]);Serial.print(", ");
  Serial.println(distdata[2]);
  delay(100);

  //Escogemos la dirección que debería tomar el coche
  maximo=max(distdata[1],distdata[2]);
  Serial.print("maximo");Serial.println(maximo);
}

}
