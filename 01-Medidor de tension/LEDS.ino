// Pines para los led
#define LEDVERDE 2
#define LEDAMARILLO 3
#define LEDROJO 4
#define ANALOGPILA A0

//VARIABLES
int analogvalor = 0;
float voltaje = 0;
int ledDelay = 800;

//Umbrales
float maximo = 1.5;
float medio = 1;
float minimo = 0.1;



void setup() {
  // Iniciamos el monitor serie
  Serial.begin(9600);

  // Los pines de led en modo salida
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAMARILLO, OUTPUT);
  pinMode(LEDROJO, OUTPUT);
 
}

void loop() {
  // lEER ENTRADA ANALOGICA
  analogvalor = analogRead(ANALOGPILA);

  // OBTENEMOS EL VOLTAJE
  voltaje = 0.0048 * analogvalor;
  Serial.print("Voltaje: ");
  Serial.println(voltaje);

  // dependiendo del voltaje, encendemos un led
  if (voltaje >= maximo)
  {
    digitalWrite(LEDVERDE, HIGH);
    delay(ledDelay);
    digitalWrite(LEDVERDE, LOW);
  }

  else if (voltaje < maximo && voltaje > medio)
  {
    digitalWrite(LEDAMARILLO, HIGH);
    delay(ledDelay);
    digitalWrite(LEDAMARILLO, LOW);
  }
  
  else if (voltaje <= medio && voltaje > minimo)
  {
    digitalWrite(LEDROJO, HIGH);
    delay(ledDelay);
    digitalWrite(LEDROJO, LOW);
  }

  //Apagamos todos los leds
  digitalWrite(LEDROJO, LOW);
  digitalWrite(LEDVERDE, LOW);
  digitalWrite(LEDAMARILLO, LOW);
}
  
  

