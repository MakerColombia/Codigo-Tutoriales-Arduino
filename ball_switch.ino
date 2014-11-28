/*
Sensor por movimiento esfera interna, enciende el led conectado en el pin 13 al detectar pasar de un valor de inclinacion
Conecciones:
1- Pin OUT del sensor conectado al pin 7 del arduino.

Este sensor normalmente emite señal en alto, cuando detecta inclinacion superior 75º pone la señal en bajo.

Creado Octubre 2014 
por 
Julio Aguirre
Para
MakerColombia

Este ejemplo es de dominio publico
 */


int ledPin = 13; // Pin donde esta conectado el led 
int Pinsensor = 7; // pin donde esta conectado la salida del modulo sensor esfera; 
int valor = 0; // Variable donde se almacena la lectura del pin del sensor para verificar su estado alto o bajo 

void setup () { 
  pinMode (Pinsensor, INPUT); // define el puerto de entrada donde esta conectado el sensor.
  pinMode (ledPin, OUTPUT);   //define como puerto de salida el pin donde esta conectado el led
} 

void loop () { 
  valor = digitalRead (Pinsensor); // Lee el estado de la señal presente en el pin del sensor y lo almacena en la variable valor; 
  if (HIGH == valor){ // verifico si valor esta en alto 
 
    digitalWrite (ledPin, LOW); // detecto inclinacion, enciendo el led. 
  } 
  else { 
    digitalWrite (ledPin, HIGH); // no hay inclinacion, apago el led 
  } 
} 
