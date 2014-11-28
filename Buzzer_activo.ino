/*
Buzzer Activo, emite sonido cuando se pone en alto su puerto IN
 
Conecciones:
1- Buzzer activo con su pin IN conectado al pin 6 digital de arduino.

Creado Octubre 2014 
por 
Julio Aguirre
Para
MakerColombia

Este ejemplo es de dominio publico
 */

int buzzer = 6 ;// Pin en el que esta conectado el buzzer

  void setup () {
  pinMode (buzzer, OUTPUT); //Inidcamos que donde esta el buzzer conectado es pin de salida
  Serial.begin(9600);       //Inicializamos el puerto serial 
}
  
  
void loop () {
    
  Serial.println("Buzzer ON ");       //Imprimimos al puerto serial que el buuzzer esta on para alertar al usuario de forma visual 
  digitalWrite(buzzer,HIGH);          //Poner en alto el pin definido por buzzer
  delay(2000);                        // Espera 2 segundos
  Serial.println("Buzzer OFF ");      //Imprimimos al puerto serial que el buuzzer esta OFF para alertar al usuario de forma visual  
  digitalWrite(buzzer,LOW);           //Poner en alto el pin definido por buzzer
  delay(2000);                        // Espera 2 segundos

}
