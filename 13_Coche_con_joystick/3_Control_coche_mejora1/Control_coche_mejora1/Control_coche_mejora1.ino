  #include <Servo.h>
  #include <AFMotor.h>

  // Crear un objeto "servo" para controlar un servo.
  Servo servoInstance;

  //Inicializar motores y asignar el nombre de cada motor a los pins del SHIELD
  AF_DCMotor motorRH(1);
  AF_DCMotor motorLH(4);

  //Asignación de pins de la placa a los elementos
  const int X_pin = 8; // pin analógico 8 conectado a salida X del joystick
  const int Y_pin = 9; // pin analógico 9 conectado a salida Y del joystick
  const int SW_pin = 40; // digital pin connected to switch output

  //Variables de diseño
  int x_dir=0;
  int y_dir=0;
  int ang = 0;    // variable de posición del servo, que se asigna directamente al servo
  int potRH = 0;  //variable de potencia del motor derecho, que se asigna directamente al motor
  int potLH = 0;  //variable de potencia del motor izquierdo, que se asigna directamente al motor
  double magoang = 0;  //variable para calcular el angulo de servo
  double magopot = 0; //variable para calcular la potencia del motor
  double pot = 0;    //potencia INTERMEDIA, para calcular la potencia de la rueda de dentro

void setup() {

  //Asignamos el objeto servo al pin 10 (SHIELD; SERVO 1)
  servoInstance.attach(10);
  //Inicializamos la posición del servo
  servoInstance.write(110);

  //Inicializamos los motores (encendido y apagado)
  motorRH.setSpeed(250);     //encendemos motores
  motorLH.setSpeed(250);
  motorRH.run(RELEASE);      //apagamos motores
  motorLH.run(RELEASE);

  //Dejamos un tiempo hasta que empiece el loop
  delay(2000);

  //Comenzamos la monitorización
  Serial.begin(9600);
}

void loop() {

  //LECTURA DE LAS ENTRADAS DEL JOYSTICK
  //Leemos los datos del joystick y se lo asignamos a las variables
  x_dir=analogRead(X_pin);  
  y_dir=analogRead(Y_pin);  
  
  //Comprobamos entradas
  Serial.print("X-axis: ");
  Serial.println(x_dir);                          //direccion X
  Serial.print("Y-axis: ");
  Serial.println(y_dir);                          //direccion Y
  
  // POSICIÓN DEL SERVO
 
  //Calculo del angulo del servo segun entrada de joystick
  magoang=70+x_dir*0.0782;

  
  //Comprobamos rango seguro del servo
  if (magoang>65 && magoang<155){                 //Es seguro
    if (magoang<108 || magoang>112) {             //Seguro, y se detecta que hay un giro
      ang=int(magoang);                           //Convertimos el valor del ángulo en entero
      servoInstance.write(ang);                   //Asignamos el ángulo al servo
      delay(50);
    }
    else {                                        //Seguro, pero no hay giro
      switch (ang){
        case 110:
          Serial.println("No hay giro, no actuamos sobre el servo");          //Sacamos en pantalla que no hay giro.
          break;
        default:
          ang=110;                                //Asignamos angulo neutro a 'ang', para que lo lea después y no actúe sobre el servo.
          servoInstance.write(ang);               //Asignamos el ángulo NEUTRO al servo
          delay(50);
          Serial.println("No hay giro pero vamos al reposo"); //Sacamos en pantalla que no hay giro.
          break;
      }
    }
    Serial.print("Ángulo actual: ");              //Sacamos en pantalla el ángulo actual.
    Serial.println(ang);
    delay(50);
  }
  else {                                          //No es seguro
  servoInstance.write(110);                       //Posición de reposo para el servo
  Serial.print("Ángulo no seguro: ");             //Sacamos en pantalla que el ángulo no es seguro.
  Serial.println(ang);
  Serial.println("Rectificar software");
  delay(10000);
  }


  //POTENCIA A LAS RUEDAS (VAMOS HACIA ATRÁS)
  
  if (y_dir>550){
    Serial.println("Vamos hacia atrás");          //Sacamos en pantalla la dirección que tomamos.
    //Cálculo de la potencia demandada
    magopot=0.510*y_dir-265;
    Serial.print("Magopot: ");
    Serial.println(magopot);


    //Entramos en rango seguro de potencia
    if (magopot<=255 && magopot >=30){
      if (ang>=108 && ang<=112){                  //Vamos en RECTO. Toda la potencia a las dos ruedas.  
         
        potRH=int(magopot);                       //Transformamos en entero el valor de la potencia.
        motorRH.run(BACKWARD);                    //Motor derecho va hacia atrás a tope
        motorRH.setSpeed(potRH);
        
        potLH=int(magopot);                       //Transformamos en entero el valor de la potencia.
        motorLH.run(BACKWARD);                    //Motor izquierdo va hacia atrás a tope
        motorLH.setSpeed(potLH);

        Serial.println("TODO HACIA ATRÁS");       //Sacamos en pantalla que vamos a tope hacia atrás.
        delay(50);
      }
      else if (ang<108){                          //GIRAMOS A IZQUIERDA.
        potRH=int(magopot);                       //Motor derecho a tope
        motorRH.run(BACKWARD);                    //Motor derecho va hacia atrás a tope
        motorRH.setSpeed(potRH);

        pot=magopot*(1-125/38*(108-ang)/255);     //calculamos la potencia, menor cuanto más giremos a la izquierda.
        potLH=int(pot);                           //Convertimos la potencia calculada en entero
        motorLH.run(BACKWARD);                    //Motor izquierdo va hacia atrás...
        motorLH.setSpeed(potLH);                  //con la potencia calculada
        
        Serial.println("ATRÁS-IZQUIERDA");        //ATRAS-IZQUIERDA en pantalla
        Serial.print("Potencia reducida: ");      //Valor potencia reducida en pantalla
        Serial.println(potLH);  
        delay(50);
      }
      else if (ang>112){                          //Giramos a la DERECHA.
        potLH=int(magopot);                       //Potencia motor izquierdo a tope
        motorLH.run(BACKWARD);                    //Motor izquierdo va hacia atrás a tope
        motorLH.setSpeed(potLH);

        pot=magopot*(1-125/38*(ang-112)/255);     //calculamos la potencia, menor cuanto más giremos a la derecha.
        potRH=int(pot);                           //Convertimos la potencia calculada en entero
        motorRH.run(BACKWARD);                    //Motor derecho va hacia atrás...
        motorRH.setSpeed(potRH);                  //con la potencia calculada
        
        Serial.println("ATRÁS-DERECHA");          //ATRAS-DERECHA en pantalla
        Serial.print("Potencia reducida: ");      //Valor potencia reducida en pantalla
        Serial.println(potRH);  
        delay(50);
      }
    }
    else if (magopot > 255){                                        //Si la potencia no es segura
      Serial.print("Potencia no segura: ");       //Sacamos en pantalla que la potencia no es segura.
      Serial.println(magopot); 
      motorRH.run(RELEASE);                       //Paramos los motores
      motorRH.setSpeed(0);                    
      motorLH.run(RELEASE);                
      motorLH.setSpeed(0);                         
      delay(1000);
    }
    else {
      Serial.print("No hay potencia: ");       //Sacamos en pantalla que la potencia no es segura.
      Serial.println(magopot); 
    }
  }

  //POTENCIA A LAS RUEDAS (VAMOS HACIA ADELANTE)
  
  else if (y_dir<500){
    Serial.println("Vamos hacia adelante");      //Sacamos en pantalla la dirección que tomamos.
    //Cálculo de la potencia demandada
    magopot=255-0.5*y_dir;
    Serial.print("Magopot: ");
    Serial.println(magopot);
    //delay(500); 
    //Entramos en rango seguro de potencia
    if (magopot<=255 && magopot >=30){
      if (ang>=108 && ang<=112){                //Vamos en RECTO. Toda la potencia a las dos ruedas.  
         
        potRH=int(magopot);                     //Transformamos en entero el valor de la potencia.
        motorRH.run(FORWARD);                   //Motor derecho va hacia adelante a tope
        motorRH.setSpeed(potRH);
        
        potLH=int(magopot);                     //Transformamos en entero el valor de la potencia.
        motorLH.run(FORWARD);                   //Motor izquierdo va hacia adelante a tope
        motorLH.setSpeed(potLH);

        Serial.println("TODO HACIA ADELANTE");  //Sacamos en pantalla que vamos a tope hacia adelante.
        delay(50);
      }
      else if (ang<108){                        //Giramos a la IZQUIERDA.
        potRH=int(magopot);                     //Motor derecho a tope
        motorRH.run(FORWARD);                   //Motor derecho va hacia adelante a tope
        motorRH.setSpeed(potRH);

        pot=magopot*(1-125/38*(108-ang)/255);   //Motor izquierdo: calculamos la potencia, menor cuanto más giremos a la izquierda.
        potLH=int(pot);                         //Convertimos la potencia calculada en entero
        motorLH.run(FORWARD);                   //Motor izquierdo va hacia adelante...
        motorLH.setSpeed(potLH);                //con la potencia calculada
        
        Serial.println("ADELANTE-IZQUIERDA");   //ADELANTE-IZQUIERDA en pantalla
        Serial.print("Potencia reducida: ");    //Valor potencia reducida en pantalla
        Serial.println(potLH);
        delay(50);
      }
      else if (ang>112){                        //Giramos a la DERECHA.
        potLH=int(magopot);                     //Potencia motor izquierdo a tope
        motorLH.run(FORWARD);                   //Motor izquierdo va hacia adelante a tope
        motorLH.setSpeed(potLH);

        pot=magopot*(1-125/38*(ang-112)/255);   //Motor derecho: calculamos la potencia, menor cuanto más giremos a la derecha.
        potRH=int(pot);                         //Convertimos la potencia calculada en entero
        motorRH.run(FORWARD);                   //Motor derecho va hacia adelante...
        motorRH.setSpeed(potRH);                //con la potencia calculada
        
        Serial.println("ADELANTE-DERECHA");     //ATRAS-DERECHA en pantalla
        Serial.print("Potencia reducida: ");    //Valor potencia reducida en pantalla
        Serial.println(potRH);
        delay(50);
      }
    }
    else if (magopot > 255){                                        //Si la potencia no es segura
      Serial.print("Potencia no segura: ");       //Sacamos en pantalla que la potencia no es segura.
      Serial.println(magopot); 
      motorRH.run(RELEASE);                       //Paramos los motores
      motorRH.setSpeed(0);                    
      motorLH.run(RELEASE);                
      motorLH.setSpeed(0);                           
      delay(1000);
    }
    else {
      Serial.print("No hay potencia: ");       //Sacamos en pantalla que la potencia no es segura.
      Serial.println(magopot); 
    }
  }
  else {
    Serial.print("No hay potencia: ");       //Sacamos en pantalla que la potencia no es segura.
    Serial.println(magopot);
    motorRH.run(RELEASE);                       //Paramos los motores
    motorRH.setSpeed(0);                    
    motorLH.run(RELEASE);                
    motorLH.setSpeed(0);  
    delay(50);
  }
}
