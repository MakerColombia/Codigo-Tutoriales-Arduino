/*
 Boton Con Filtrado de rebotes
 
Conecciones:
1- Un interruptor normalmente cerrado conectado al pin digital 2 del arduino
2- Un Modulo led conectado al pin 13 del Arduino o en su defecto el led que trae el arduino Uno revision 3

Creado Octubre 2014 
por 
Julio Aguirre
Para
MakerColombia

Este ejemplo es de dominio publico
 */


// Definimos las constantes y variables para nuestro programa:
const int pinBoton = 2;     // Pin al cual esta conectado el boton
const int pinLed =  13;      // Pin al cual esta conectado el LED
int estado=HIGH;                  //variable donde se almacena el estado actual del led, prendio HIGH apagao LOW
int ultimoEstadoBoton = HIGH;   //LOW equivale a 0V o GND. Esta variable se usa para detectar un cambio en el estado del boton. Cambio de estado se produce cuando UltimoEstadoBoton!=estadoBoton

int estadoBoton;         //Varible donde almacenamos el estado actual del boton al ser leido con digitalRead(pinBoton)
int lectura;

long tiempoUltimoRebote = 0;  // Variable para almacenar tiempo transcurrido desde la primera transicion del switch
long tiempoFiltroRebote = 10;    // tiempo de espera de estabilizacion de la señal del switch


void setup() { //Donde inicalizamos el sketch
  
  pinMode(pinLed, OUTPUT);      //Informamos que el pinLed es un pin de salida.
  pinMode(pinBoton, INPUT);    //Informamos que el pinBoton es un pin de entrada
  digitalWrite(pinLed, LOW);    //Ordenamos al arduino a poner en 0V o GND el pinLed lo cual apaga el led
  Serial.begin(9600);           //Inicializamos el puerto serial para poder visualizar informacion de debug de nuestro programa en tiempo real.
}

void loop(){
  /* Enviamos porpuerto serial la informacion de debug del estadod e las diferentes variables.
  Serial.print(ultimoEstadoBoton);
  Serial.print(",");
  Serial.print(estadoBoton);
  Serial.print(",");
  Serial.println(estado);
  */
  
  lectura = digitalRead(pinBoton); //leemos el estado del boton. 1 o HIGH para pulsado, 0 o LOW para no pulsado


  
  
  
  
  if (lectura!=ultimoEstadoBoton){ // con esta comparacion detectamos si hubo un cambio en el estado del boton
   //Serial.println("cambioestadosinfiltro");
    tiempoUltimoRebote=millis();  //Reseteamos el contador que permite controlar que pase suficiente tiempo para que la señal
                                  //del switch se estabilice. 
  }
   
   if ((millis() - tiempoUltimoRebote) > tiempoFiltroRebote) { //en este condicional verificamos que efectivamente pase el tiempo de estabilizacion del boton.
     if (lectura!=estadoBoton){ // con esta comparacion detectamos si hubo un cambio en el estado del boton  
       estadoBoton = lectura; //leemos el estado del boton que ya debe estar estabilzado
      
        
        if (estadoBoton == LOW) {     //si el boton esta pulsado 
          estado=!estado;   //cambiamos el estado de LED al estado Contrario. 
          //Serial.println("cambioestadoconfiltro");
        } 
     }
  
   }
  
  digitalWrite(pinLed,estado); //ordenamos al arduino a poner el estado en el pin del led.
  ultimoEstadoBoton=lectura; 
}
