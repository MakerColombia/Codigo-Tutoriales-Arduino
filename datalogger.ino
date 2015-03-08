/*
En este sketch pretendemos explicar el funcionamiento de arduino con el ethernet shield
wiz5100 con lector de tarjetas micro SD.

Que necesitamos?
1- Arduino uno R3
2- Ethernet shield con chip wiz5100 y lector de SD
3- Shield Proto Board arduino Uno 
3- Modulo SensorDTH22 de humedad y temperatura
4- Modulo sensor temperatura MCP9700
5- Modulo RTC DS1302

Conecciones:
1- Sobre el arduino insertaremos el shield ethernet.
2- Sobre el shield ethernet insertaremos el shield protoboard.
3- La señal del modulo Sensor DTH22 Lo conectaremos a pin digital 9
4- La señal de modulo sensor MCP9700 la conectaremos al pin A0.
5- El modulo RTC DS1302  se conecta:
   CLK -> pin D7 Arduino
   DAT -> pin D6 Arduino
   RES -> Pin D5 Arduino

Este sketch inicializa  un pequeño servidor accesible enla direccion 192.168.1.11
el cual muestra la fechay hora del Modulo RTC DS1202 el valor de huedad y temperatura
del sensor DTH22 y el valor de temepratura del Sensor MCP9700. Dos sensores de temperatura 
con el objeto de terminar posbiles problemas en los sensores si vemos una discrepancia muy grande
entre las lecturas de los dos sensores.
Adicional graba en un archivo de texto en la tarjeta SD un archivo de nombre temp.txt
donde escribe los mismos datos que muestra el servidor.


Creado Febrero 2015 
por 
Julio Aguirre
Para
MakerColombia

Este ejemplo es de dominio publico 
licencia Creative Commons Public Domain
 */

#include <SPI.h>           //Incluimos libreria para manejo de dispositivos Comunicacion SPI
#include <Ethernet.h>      //Inclumos Libreria para manejo del Ethernet Shield
#include <SD.h>            //Inclumos Libreria para manejo del SD en Ethernet Shield
#include <stdio.h>         //Incluimos Libreria funciones Input Ouptut
#include <DS1302.h>        //Incluimos Libreria para manejo Modulo RTC DS1302
#include "DHT.h"           //Incluimos Libreria para Manejo de Sensor DHT22



#define DHTTYPE DHT22         //Definimos el tipo de senor que tenemos de humedad y temperatura
                              //Es requerido por la libreria DTH.h
                          
#define DHTPIN 9              //Definimos el pin en que esta conectado la señal del sensor
                              //DTH22. Requerido por la libreria DTH.h


#define SS_SD_CARD   4    // Definimos el pin en que esta conectada la señal Slave Select
                          // para el lector de SD en el modulo Ethernet Shield.
                          // Requerido para la correcta comunicacion SPI entre el
                          // Arduino y el modulo ethernet y el modulo SD.
                          
#define SS_ETHERNET 10    // Definimos el pin en que esta conectada la señal Slave Select
                          // para el Ethernet Shield.
                          // Requerido para la correcta comunicacion SPI entre el
                          // Arduino y el modulo ethernet y el modulo SD.
                          



byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};  // Definimos Direcion Mac para el modulo Ethernet. Debe ser Unica en la red.
IPAddress ip(192, 168, 1, 11);                      //Definimos direccion IP del Ethernet en arduino de manera manual. Debe ser unica en la red en que se conecta
EthernetServer server(80);                          //Puerto en que estara rel servidor de datos. Por defetfo el 80 es para servicios http. La informacion viaja sin proteccion en formato texto
                                                    // sin encriptacion. Se puede interceptar con cualquier sniffer de paquetes




const int kCePin   = 5;  // Chip Enable            // Definicion de pines para el RTC DS 1302. Requerida por la libreria DS1302.h
const int kIoPin   = 6;  // Input/Output
const int kSclkPin = 7;  // Serial Clock

DHT dht(DHTPIN, DHTTYPE);                          //Inicializamos un objeto dipo DTH para manejar el sensor DTH22 que tenemos conectado en el pin 9. requerido por la libreria DTH.h

DS1302 rtc(kCePin, kIoPin, kSclkPin);              //Inicializamos un objeto DS1302 para manejar la comunicacion con el modulo RTC DS1302. Requerido por la libreria DS1302.h

File myFile;                                      // puntero para poder manipular archivos en la tarjeta sd

unsigned long pasounminuto=60000;                 // Variable usada para detectar si ya paso un minuto

/***************************************************
 *  Nombre Funcion:        setup
 *
 *  Returns:               Nada.
 *
 *  Parametros:            Ninguno
 *
 *  Descripcion:           Inicializa el arduino y sus modulos conectados
 *
 ***************************************************/

void setup() {
 
  Serial.begin(115200);                              // Inicializamos y abrimos el puerto serial del arduino para poder tener mensajes en la consola.
  
  
  //las siguientes 4 lineas son muy importantes para poder usar en el mismo sketch el ethernet y el lector SD (hay que usarlos de manera secuencial, uno a la vez.)
  pinMode(SS_SD_CARD, OUTPUT);                     //Definimos el pin donde esta conectado el SS(slave Select) del modulo SD como una salida. (si no lo hacemos el lector SD del modulo Ethernet Shield no funcionara).
  pinMode(SS_ETHERNET, OUTPUT);                    //Definimos el pin donde esta conectado el SS(slave Select) del modulo ethernet como una salida. (si no lo hacemos el Ethernet Shield no funcionara).
  digitalWrite(SS_SD_CARD, HIGH);                  // Poniendo este pin en alto se desactiva el lector SD del ethernet shield.
  digitalWrite(SS_ETHERNET, HIGH);                 // Poniendo este pin en alto se desactiva el Ethernet del ethernet shield.
            
  Ethernet.begin(mac, ip);                         //Incializamos el ethernet Shield
  server.begin();                                  //Iniciamos el servidor web en el puerto 80
  Serial.print("Direccion IP Servidor datos ");                   
  Serial.println(Ethernet.localIP());              //Imprimimos en el puerto serial en que direccion esta el servidor web

   
 
  dht.begin();                                     // Inicializamos la comunicacion con el sensor DTH22                   
 
 
  if (!SD.begin(SS_SD_CARD)) {                    // Inicializamos el lector SD
     Serial.println("Fallo inicializacion de tarjeta SD!!!");  // Si la inicializacion es exitosa informamos por el puerto serial
     
  } else {
  
       Serial.println("Tarjeta SD inicializada OK!");    //Si la inicializacion del lector SD no es exitosa informamos por la consola serial
  }

}  

// Termina la funcion SETUP de nuestro Sketch. Ya todo esta inicializado y listo.


/***************************************************
 *  Nombre Funcion:        temperatura
 *
 *  Retorna:               String con humead relativa y temperatura en el formato XX.XX,XX.XX
 *
 *  Parametros:            Apuntador a un String que debe estar inicializado en la instancia en que se invoca la funcion.
 *
 *  Descripcion:           Pregunta al modulo DTH22 la humedad relativa y la temperatura.  si no es posible la comunicacion retorna en el string referenciado NAN,0.00       
 *
 ***************************************************/
void temperatura(String &dest) {
  float h = dht.readHumidity();      // Preguntamos la humedad relativa al modulo DTH22 y la almacenamos en h
  float t = dht.readTemperature();   // Preguntamos la temperatura al modulo DTH22 y la almacenamos en h
   dest = String(float(h));          //Escribimos en el string referenciado por &dest el resultado de convertir el float h a una string.
   dest += String(",");              
   dest += String(float(t));         //Escribimos en el string referenciado por &dest el resultado de convertir el float t a una string.
   //Serial.println(dest);           // Para debug por puerto serial
}



/***************************************************
 *  Nombre Funcion:        mcp9700
 *
 *  Returns:               float con el valor de temperatura leido por un mcp9700 conectado a A0
 *
 *  Parametros:            ninguno
 *
 *  Descripcion:           Lee la temperatura reportada por un mcp9700 conectado a A0 en grados centigrados.        
 *
 ***************************************************/
float mcp9700(void) {
  float temperatura2;
  /*
  En esta primera parte leemos la señal analoga en el 
  pin A0. Despues multiplicamos por 5 que son los 5 volts
  que lee nuestro Arduino y dividimos en 1024 porque 
  recordemos que la señal analoga se guarda en 10 bits
  */
  temperatura2 = analogRead(A0)*5/1024.0; 
  /*Restamos 0.5 para quitar el offset de que
   0ºC es igual a 500mV 
  */
  temperatura2 = temperatura2 - 0.5;
  /*
  Ahora dividimos entre
  0.01 para obtener la 
  equivalencia en valores de ºC
  */
  temperatura2 = temperatura2 / 0.01;
  return temperatura2;
}

/***************************************************
 *  Nombre Funcion:        fechafunc
 *
 *  Returns:               String con fecha hora en el formato YYYY-MM-DD,HH:MM:SS.
 *
 *  Parametros:            Apuntador a un String que debe estar inicializado en la instancia en que se invoca la funcion.
 *
 *  Descripcion:           Pregunta la fecha y hora al modulo RTC DS1302 y regresa el resultado en el string referenciado por el apuntador &stringfecha
 *                         Si el retorno es 2000-00-00,00:00:00 significa que no hubo comunicacion con el modulo RTC DS1302.         
 *
 ***************************************************/
void fechafunc(String &stringfecha){
  Time t = rtc.time();                                          //Inicializamos un objeto Time para almacenar la fecha y hora que preguntamos al modulo RTC DS1302.
  char buf[50];                                                 //Creamos un buffer de texto en que formatearemos el string con la informacion de fecha y hora
  snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d",   //Efectuamos el formateo del texto.
           t.yr, t.mon, t.date,                                 // En t.yr esta almacenado el año. En t.mon esta lamacenado el mes. En t.date esta almacenado el dia
           t.hr, t.min, t.sec);                                 // En t.hr esta almacenada la hora. En t.min los minutos y en t.sec los segundos.

  
  stringfecha = String(buf);                                    // Asignamos al string referenciado por &stringfecha el resultado formateado.
  
  
 // Serial.println(buf);                                        //mensaje debug Para depuracion por puerto serial
}



/***************************************************
 *  Nombre Funcion:        loop()
 *
 *  Returns:               Nada.
 *
 *  Parametros:            Nada.
 *
 *  Descripcion:           Loop principal del programa arduino. Primero inicializamos variables , se pregunta la fecha hora y temperaturas y se verifica si hay cliente conectado al servidor.
 *                         Si hay cliente se le sirve la informacion, se imprime la informacion al pueto serial y finalmente se actializa el archivo temp.txt en la tarjeta SD si esta es accesible
 ***************************************************/
void loop() {
  
  
  String humedad_y_temperatura;
  char c;
  String sfecha;
  fechafunc(sfecha);
  temperatura(humedad_y_temperatura);
  
 
  
  EthernetClient client = server.available();        // Escuchamos si hay clientes http conectados al puerto 80 
  if (client) {
    Serial.println("cliente nuevo");
    
    boolean currentLineIsBlank = true;              // Creamos linea para detectar si ya llego todo el requiemiento del cliente http, pue siempre termina con linea en blanco
    while (client.connected()) {
      if (client.available()) {
        c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // enviar datos en header de respuesto http estandar.
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // La coneccion se cerrara despues de enviar todos los datos
          client.println("Recargar: 5 segundos");  // refresca la pagina cada 5 segundos
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.print("fecha y hora =");
          client.print(sfecha);
          client.print(" humedad relativa y temperatura = ");
          client.print(humedad_y_temperatura);
          client.print(" temp mcp9700 = ");
          client.print(mcp9700());
          client.println("<br />");
          client.println("</html>");
          break;
         }
        if (c == '\n') {
          // esta iniciando una linea nueva
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // ud tiene caracteres en la linea actual
          currentLineIsBlank = false;
        }
      }
    }
    
    // espera para que el cliente pueda recivir la informacion generada
    delay(1);
    client.stop(); 
  }
   // cerramos la coneccion http del cliete desconectandolo
  //Serial.println("cliente desconectado");   //Informamos la desconeccion por puerto serial
  
  
  
  // seccion para grabar la informacion enla tarjeta sd cada minuto.
   if(pasounminuto<millis()){
   
    myFile = SD.open("DATA.TXT",FILE_WRITE);        //abrir para escritura o crear si no existe archivo data.txt
    if(myFile) {                                  //Si se pudo abrir el archivo de datos, escribe en el nuevos datos.
      Serial.print("Escribiendo a data.txt...");
      myFile.print(sfecha);
      myFile.print(",");
      myFile.print(humedad_y_temperatura);
      myFile.print(",");
      myFile.println(mcp9700());
      myFile.close();                              // Se cierra el archivo data.txt
      Serial.println("Listo, archivo cerrado.");
    } else {
      Serial.println("error abriendo archivo de datos para escritura");   // Imprime mensaje de error en el puerto serial si no se puede abrir el archivo de datos
    }
   
   myFile = SD.open("DATA.TXT",FILE_READ);       // re-abrir archivo para leer la informacion que hay en el
   if (myFile) {
     Serial.println("apertura temperatura.txt ok. Contenido:");
     while (myFile.available()) {                // Lee todo el contenido del archivo hasta encontrar EOF
        Serial.write(myFile.read());
    }
    myFile.close();                            // Cierra El archivo
    } else {
    Serial.println("error abriendo archivo para lectura");   // Mensaje de error por serial si no se puede abrir el archivo.
    }

  pasounminuto=millis()+60000;
  
  }
 
 
 
 /*imprime datos de debug
  
  Serial.print("Fecha y hora = ");
  Serial.println(sfecha);
  Serial.print(" Humedad relativa, temperatura = ");
  Serial.print(humedad_y_temperatura);
  Serial.print(" temp mcp9700 ");
  Serial.println(mcp9700());
//*/

  
 
}

