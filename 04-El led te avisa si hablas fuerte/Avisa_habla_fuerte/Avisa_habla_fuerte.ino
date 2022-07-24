
int  sensorPin  =  A0;     // select the input  pin for  the potentiometer 
int  ledPin  =  13;   // select the pin for  the LED
int  sensorValue =  0;  // variable to  store  the value  coming  from  the sensor

void setup()
{
pinMode(ledPin,OUTPUT);
pinMode(sensorPin,INPUT);
Serial.begin(9600);
}
void loop(){
sensorValue =  analogRead(sensorPin);

if(sensorValue>675)
{
digitalWrite(ledPin,  HIGH); 
delay(30); 
digitalWrite(ledPin,  LOW);
}
else
{
digitalWrite(ledPin,  LOW);
}
delay(30);
Serial.println(sensorValue,  DEC);
}

