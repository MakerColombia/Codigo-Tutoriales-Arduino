/*
Lectura analoga en los puertos A0- A5 Arduino Uno
 
Conecciones:
1- Sensor Analogo pin A0


Creado Octubre 2014 
por 
Julio Aguirre
Para
MakerColombia

Este ejemplo es de dominio publico
 */


void setup() {
  pinMode(A0,INPUT);  // pint donde se conecta el sensor
  pinMode(3,OUTPUT); // pin 3 pwm de salida brillo led
  Serial.begin(9600);// inicializamos puerto serial
}

void loop() {
  analogWrite(3,map(analogRead(A0),0,1023,0,255));
  Serial.print(map(analogRead(A0),0,1023,0,255));
  Serial.print(",");
  Serial.println(analogRead(A0));//leemos ad e imprimimos su valor por serial
}
