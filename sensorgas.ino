/*
Sensor Gas, imprime en el puerto serial el valor detectado por el sensor conectado al pin A0 de arduino.
 
Conecciones:
1- Modulo de gas MQ2 o MQ3 conectado a canal A0 de arduino


Creado Octubre 2014 
por 
Julio Aguirre
Para
MakerColombia

Este ejemplo es de dominio publico
 */




int sensorgas = A0; // Pin donde esta conectado el sensor de gas

void setup(){
  pinMode(sensorgas,INPUT);
  Serial.begin(9600); // inicializa el puerto serial
}

void loop()
{
  // hay que esperar un tiempo de calentamiento para que la lectura se estabilice

  int valor = analogRead(sensorgas);
  Serial.println(valor);

  delay(1000); //una lectura por segundo
}
