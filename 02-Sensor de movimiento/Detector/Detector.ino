//www.elegoo.com
//2016.12.9

int ledPin = 13;  // LED on Pin 13 of Arduino
int pirPin = 7; // Input for HC-S501
int mov = 0; // variable que guarda el cambio de estado del PIR
int buzz = 8;


void setup() {
  Serial.begin(9600);  //iniciamos el monitor serie
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(buzz, OUTPUT);
 
  
}

void loop() {
  mov = digitalRead(pirPin);
  delay(50);
  if (mov == HIGH)  {
    Serial.print("Deteccion S/N: ");
    Serial.println(mov);
    digitalWrite(ledPin, HIGH);
    tonos();
    delay(500);
    digitalWrite(ledPin, LOW);
    mov = 0;
    delay(30);
   
  }
  else {
    Serial.print("Deteccion S/N: ");
    Serial.println(mov);
    delay(300);
  }

}
void tonos(){
  tone(buzz,8.18); // C | octava - 2;
  delay(150);
  tone(buzz,9.72); // D# | octava - 2;
  delay(150);
  tone(buzz,14.57); // A# | octava - 2;
  delay(150);
  noTone(buzz);
  delay(1000);
  
  tone(buzz,13.75); // A | octava - 2;
  delay(150);
  tone(buzz,9.72); // D# | octava - 2;
  delay(150);
  tone(buzz,8.18); // C | octava - 2;
  delay(150);
  noTone(buzz);
  delay(1000);     
}
