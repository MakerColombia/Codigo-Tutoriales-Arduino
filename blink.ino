/*
  Blink
  Enciende el led por un segundo, luego lo apaga.
  www.MakerColombia.com
  Noviembre 2013
  */
 
// El pin digital 13 de arduino Uno R3 tiene un led conectado incorporado en la board

int led = 13;

// El codigo dentro de Setup se ejecuta una sola vez despues de inicializada la board Arduino

void setup() {                
  // Configuramos el pin 13 como un pin de salida
  pinMode(led, OUTPUT);     
}

// El codigo dentro loop se ejecuta de forma repetida mientras el arduino tenga alimentacion.

void loop() {
  digitalWrite(led, HIGH);   // Enciende el LED
  delay(1000);               // Espera un segundo
  digitalWrite(led, LOW);    // Apaga el led
  delay(1000);               // Espera un segundo
}
