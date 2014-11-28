/*
Ejemplo para uso del modulo IR Reciver.
 
Conecciones:
1- La señal del modulo Ir Reciver al pin digial 2 del arduino que es donde esta la interrupcion 0 de Arduino Uno


Creado Noviembre 2014 
por 
Julio Aguirre
Para
MakerColombia

Este ejemplo es de dominio publico
Usa la libreria : https://github.com/NicoHood/IRLremote
En este video de youtube puden ver una buena explicacion de como funciona un control remoto infrarojo http://youtu.be/BUvFGTxZBG8
 */

#include "IRLremote.h"

const int interruptIR = 0;   //definimos en que pin esta conectado la señal del modulo IR Arduino uno interrup0 = pin digital 2

void setup() {
  Serial.begin(9600);  //abre puerto serial para mostrar la informacion
  Serial.println("Inicializado Receptor Ir......");  // para inidcar al usuario que el programa inicializo.

  
  IRLbegin<IR_ALL>(interruptIR);  //definimos la interrupcion a moniotear con todos los protocolos reconocidos por la libreria
}

void loop() {
  
  if (IRLavailable()) {    //Verifica si se recibio algun codigo valido y desabilita las interrupciones mientras se procesa la señal
    
    Serial.print("Protocolo:");
    Serial.println(IRLgetProtocol());  //Identifica e imprime el protocolo de la señal recibida
    Serial.print("identificador de control remoto que envia el codigo:");
    Serial.println(IRLgetAddress(), HEX);//Identifica e imprime el codigo de dispositivo usado, lo muesta en notacion Hexadecimal
    Serial.print("Comando recibido:");
    Serial.println(IRLgetCommand(), HEX);//Identifica e imprime el codigo del comando recibido, lo muesta en notacion Hexadecimal

    
    IRLreset();  //Reactiva las interrupciones para decodificar el proximo comando que reciba
  }
}
