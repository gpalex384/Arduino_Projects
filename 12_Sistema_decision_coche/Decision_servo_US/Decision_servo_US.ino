#include <Servo.h>
#include <AFMotor.h>

AF_DCMotor motorRH(4);
AF_DCMotor motorLH(1);
Servo myservo;  // create servo object to control a servo

#define TRIG_PIN 26         //Salida del sensor de ultrasonidos. Con esto le damos la señal al sensor para que empiece a actuar.
#define ECHO_PIN 28         //Entrada del sensor. Nos dará la señal con la que calculamos la distancia.


long duracion, distancia;
int ang = 90;    // variable to store the servo position
int distdata[2] = {0,0};
int dmedia[10] = {0,0,0,0,0,0,0,0,0,0};
int i=0;
int j=0;
int maximo=0;
int duda=0;
int brk=0;

void setup() {
   Serial.begin(9600);
   pinMode(TRIG_PIN, OUTPUT); // Trigger en modo output. Manda la señal.
   pinMode(ECHO_PIN, INPUT);  // ECHO en modo input. Recoge la señal de distancia.
   motorRH.setSpeed(200);     //encendemos motores
   motorLH.setSpeed(200);
   motorRH.run(RELEASE);      //apagamos motores
   motorLH.run(RELEASE);
   myservo.attach(10);        // attaches the servo on pin 10 to the servo object
   myservo.write(90);         //direccion recto
   delay(10000);

}

void loop() {

  //Hacemos funcionar el detector ultrasónico
  digitalWrite(TRIG_PIN, LOW);              //Nos aseguramos que no emitimos
  delayMicroseconds(2);                     //Esperamos
  digitalWrite(TRIG_PIN, HIGH);             //Damos un pulso 
  delayMicroseconds(10);                    //dura 10 microsegundos
  digitalWrite(TRIG_PIN, LOW);              //cerramos el pulso
  duracion = pulseIn(ECHO_PIN, HIGH);   //Medimos la duración hasta que llega el eco del pulso
  distancia = (duracion/58);            //Calculamos la distancia

  //Diferenciamos entre 3 casos
  
  if (distancia >=500 || distancia <=0){     //1. LA MEDICION ES INCORRECTA O DEMASIADO LARGA
    Serial.print("-----");
    // EL COCHE CORRE HACIA ADELANTE
    motorRH.run(FORWARD);
    motorLH.run(FORWARD);
    motorRH.setSpeed(150);
    motorLH.setSpeed(150);
    delay(100);
  }
  
  if (distancia <500 && distancia >50){      //2. LA MEDICION ES CORRECTA Y SEGURA
    Serial.print(distancia);                    //Representamos distancia
    Serial.println(" cm");
    // EL COCHE CORRE HACIA ADELANTE
    motorRH.run(FORWARD);
    motorLH.run(FORWARD);
    motorRH.setSpeed(150);
    motorLH.setSpeed(150);
    delay(100);
  }
  
  if (distancia <=50 && distancia >=1){       //3. LA MEDICION ES CORRECTA PERO PELIGROSA
    Serial.print(distancia);                    //Representamos distancia
    Serial.println(" cm");
    // EL COCHE SE DETIENE
    motorRH.run(RELEASE);
    motorLH.run(RELEASE);
    delay(600);                             //Este tiempo es necesario para parar el coche antes de comenzar a ver dónde vamos.

    //Dentro de este bucle entraría el control para determinar hacia dónde va el coche.
    i=1;
    for (i = 1; i <= 2; i++){                 //Recorremos 160º. Miramos a dos bandas.
      ang=28+120*(i-1);                       //PRIMERO A LA DERECHA
      myservo.write(ang);
      delay(500);                             //Tiempo de barrido de angulo
      j=1;
      for (j=1;j<=10;j++){
        digitalWrite(TRIG_PIN, LOW);      //Nos aseguramos que no emitimos
        delayMicroseconds(2);             //Esperamos
        digitalWrite(TRIG_PIN, HIGH);     //Damos un pulso 
        delayMicroseconds(10);            //dura 10 microsegundos
        digitalWrite(TRIG_PIN, LOW);      //cerramos el pulso
        duracion = pulseIn(ECHO_PIN, HIGH);
        dmedia[j] = (duracion/58);        //medimos la distancia 10 veces para asegurarnos de que la hemos medido bien.
      }
      distdata[i]=(dmedia[1]+dmedia[2]+dmedia[3]+dmedia[4]+dmedia[5]+dmedia[6]+dmedia[7]+dmedia[8]+dmedia[9]+dmedia[10])/10;  //calculamos la media de todas las medidas en un ángulo
    }
    //Representamos el array de datos de distancia según el ángulo
    myservo.write(88);
    Serial.print(distdata[1]);Serial.print(" , ");
    Serial.println(distdata[2]);
    delay(100);

    //Escogemos la dirección que debería tomar el coche
    maximo=max(distdata[1],distdata[2]);
    Serial.print("maximo ");Serial.println(maximo);

    //Actuamos en consecuencia
    
    //A LA DERECHA HAY CAMPO LIBRE
    if (distdata[1] > 50 && distdata[2] < 50) {
      
      //Giramos a la derecha
      motorRH.run(BACKWARD);
      motorLH.run(BACKWARD); 
      motorRH.setSpeed(180);
      motorLH.setSpeed(180);
      delay(350);
      motorRH.run(FORWARD);
      motorLH.run(FORWARD); 
      motorRH.setSpeed(100);
      motorLH.setSpeed(180);
      myservo.write(30); 
      delay(1100);
      myservo.write(90);
    }
    //A LA IZQUIERDA HAY CAMPO LIBRE
    if (distdata[1] < 50 && distdata[2] > 50) {
      
      //Giramos a la izquierda
      motorRH.run(BACKWARD);
      motorLH.run(BACKWARD); 
      motorRH.setSpeed(180);
      motorLH.setSpeed(180);
      delay(1000);
      motorRH.run(FORWARD);
      motorLH.run(FORWARD); 
      motorRH.setSpeed(180);
      motorLH.setSpeed(100);
      myservo.write(150); 
      delay(1100);
      myservo.write(90);
    }
    //AMBAS DISTANCIAS DEMASIADO CORTAS
    if (distdata[1] < 50 && distdata[2] < 50) {
      
      //vamos hacia atrás, pensamos un poco y volvemos a la carga
      motorRH.run(BACKWARD);
      motorLH.run(BACKWARD); 
      motorRH.setSpeed(200);
      motorLH.setSpeed(200);
      delay(2000);
      motorRH.run(RELEASE);
      motorLH.run(RELEASE); 
      delay(3500);
    }

    //POR DEFECTO
    //pensamos 3 segundos
    if (distdata[1] > 50 && distdata[2] > 50) {
      motorRH.run(RELEASE);
      motorLH.run(RELEASE);
      delay(3000);
      
    }
  }
}


