#define TRIG_PIN 12         //Salida del sensor de ultrasonidos. Con esto le damos la señal al sensor para que empiece a actuar.
#define ECHO_PIN 11         //Entrada del sensor. Nos dará la señal con la que calculamos la distancia.
long duracion, distancia;

void setup() {
   Serial.begin(9600);
   pinMode(TRIG_PIN, OUTPUT);
   pinMode(ECHO_PIN, INPUT);
   pinMode(13,1);                  //Define el pin 13 como salida
}

void loop() {
   digitalWrite(TRIG_PIN, LOW);   //Nos aseguramos que no emitimos
   delayMicroseconds(2);          //Esperamos
   digitalWrite(TRIG_PIN, HIGH);  //Damos un pulso 
   delayMicroseconds(10);
   digitalWrite(TRIG_PIN, LOW);

   duracion = pulseIn(ECHO_PIN, HIGH);
   distancia = (duracion/58);

   if (distancia >=500 || distancia <=0){
    Serial.print("-----");
   }
   else {
    Serial.print(distancia);
    Serial.println(" cm");
    digitalWrite(13,0);
   }
   if (distancia <=30 && distancia >=1){
    digitalWrite(13,1);
    Serial.print("Alarma!!");
   }

  delay(100);

   
}
