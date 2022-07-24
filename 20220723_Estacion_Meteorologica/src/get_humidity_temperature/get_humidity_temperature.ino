/*
 * IMPORTACIONES
 */
#include <DHT.h>
#include <LiquidCrystal.h>


/*
 * DECLARACIONES DE VARIABLES
 */
#define TRIG_PIN 10         //Salida del sensor de ultrasonidos. Con esto le damos la señal al sensor para que empiece a actuar.
#define ECHO_PIN 12         //Entrada del sensor. Nos dará la señal con la que calculamos la distancia.
int dhtPin = 2; // Sensor de meteo
int lcdLightPin = 13; // Control de luz del LCD
long duracion, distancia;
boolean lcdOn = false;

static float meteoData[2];

DHT dht = DHT(dhtPin, DHT11);
LiquidCrystal lcd(8,9,4,5,6,7);

/*
 * DECLARACIONES DE FUNCIONES
 */
 
/*
 * Esta función obtiene los datos del sensor de meteo
 */
void getMeteoData()
{
  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  if(isnan(humidity) || isnan(temp))
  {
    Serial.println("Error de lectura del sensor");
    return NULL;
  }
  meteoData[0] = humidity;
  meteoData[1] = temp;
  
  float heatIndex = dht.computeHeatIndex(temp, humidity, false);  

  Serial.print("Humedad: ");
  Serial.print(humidity);
  Serial.print("% - Temperatura: ");
  Serial.print(temp);
  Serial.print("ºC - Índice de calor: ");
  Serial.print(heatIndex);
  Serial.println("ºC");
  
  //return meteoData;
}

/*
 * Esta función muestra los datos de meteo por el LCD.
 * Mostrará error si no puede obtener datos de humedad y temperatura.
 * El LCD se enciende indefinidamente. 
 */
void showMeteoData()
{
  if(meteoData != NULL && sizeof(meteoData) != 0)
  {
    float humidity = meteoData[0];
    float temp = meteoData[1];
    lcd.setCursor(0,1);
    lcd.print("H: ");
    lcd.print((int)humidity);
    lcd.print("%  T: ");
    lcd.print((int)temp);
    lcd.print("\xDF" "C");
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print("*Error sensor*");
  }
  digitalWrite(lcdLightPin, HIGH);
  lcdOn = true;
}

/*
 * Esta función lanza un pulso con el sensor de ultrasonidos y obtiene la distancia
 */
void getDistance()
{
  digitalWrite(TRIG_PIN, LOW);   //Nos aseguramos que no emitimos
  delayMicroseconds(2);          //Esperamos
  digitalWrite(TRIG_PIN, HIGH);  //Damos un pulso 
  delayMicroseconds(10);         //dura 10 microsegundos
  digitalWrite(TRIG_PIN, LOW);   //cerramos el pulso 

  duracion = pulseIn(ECHO_PIN, HIGH);    
  distancia = duracion * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distancia);                  //Representamos distancia
  Serial.println(" cm");
}


/*
 * SETUP Y LOOP
 */
void setup() 
{
  // El pin que controla la luz del lcd es de salida.
  pinMode(lcdLightPin, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.begin(9600); //Empieza el monitor
  dht.begin();  // Empieza el sensor de meteo
  lcd.begin(16,2);  // Empieza el LCD
  lcd.setCursor(0,0); // Setea el cursor del LCD al principio de la primera línea
  lcd.print("Estacion Meteo");  // Escribe en LCD

  delay(5000);  // Espera 10 seg para obtener datos del sensor meteo
  
  getMeteoData(); // Obtiene datos sensor meteo
  showMeteoData();   // Enseña datos de meteo por pantalla
  delay(4000);
  digitalWrite(lcdLightPin, LOW);
  lcdOn = false;
}

/*
 * En cada loop, se obtiene el resultado del sensor de presencia.
 * Si hay alguien Y se está mostrando los datos de meteo: no hace nada
 * Si hay alguien Y no está mostrando los datos de meteo: muestra datos de meteo
 * Si no hay nadie Y se están mostrando los datos de meteo: cuenta 5 segundos y apaga el LCD
 * Si no hay nadie Y no está mostrando los datos de meteo: no hace nada
 */
void loop() 
{
  getDistance();

  if (distancia != NULL && distancia < 35)
  {
    Serial.println("Presencia detectada");
    if (lcdOn == false)
    {
      Serial.println("Me enciendo...");
      getMeteoData();
      showMeteoData();   // Enseña datos de meteo por pantalla
    }
  }
  
  if (distancia != NULL && distancia >= 35)
  {
    Serial.println("Nadie cerca...");
    if (lcdOn == true)
    {
      Serial.println("Me apago pues!");
      digitalWrite(lcdLightPin, LOW);
      lcdOn = false;
    }
  }
  delay(800);
  
}


