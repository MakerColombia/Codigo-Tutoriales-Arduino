/*
 Lectura de temperatura usando arduino Uno ADC y modulo termistor,LM35 y DS18B20
 
Conecciones:
1- Señal termistor al pin A0
2- Señal LM35 al pin A2
3- Señal DS18B20 al pin digital 7

Necesita instalar Librerias OneWire y DallasTemperature

Creado Octubre 2014 
por 
Julio Aguirre
Para
MakerColombia

Este ejemplo es de dominio publico
 */

#include <math.h>                     //Libreria en donde se encuentra la funcion de calculo de logaritmo requerida para calciular temp del termistor
#include <OneWire.h>                  //Libreria para poder conectarse al termotetro digital con el protocolo ONE_WIRE
#include <DallasTemperature.h>        //Libreria con varias funsiones para perdir informacion en varios formatos al DS18B20
#define PIN_ONE_WIRE 7                //Definimos a que pin digital del arduino esta conectado el DS18B20

OneWire oneWire(PIN_ONE_WIRE);        // Inicializa un objeto OneWire para comunicarse con el DS18B20 conectado en el pin definido por PIN_ONE_WIRE que en este ejemplo es el pin 7
DallasTemperature sensors(&oneWire);  //Define un objeto de nombre Temeperature comunicado  por el objeto oneWire. A este objeto es el que usamos los metodos .requestTemperatures() y getTempCByIndex()



void setup () {
  Serial.begin (9600);
  sensors.begin();
  
  pinMode(A0,INPUT);
  pinMode(A2,INPUT);
}


void loop () {
  
  
  
  Serial.print("TA0=");
  Serial.print(temptermistor(0));
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.print(" TA2=");
  Serial.print(templm35(2));
  Serial.print(" TD7=");
  Serial.println(sensors.getTempCByIndex(0)); //
}


//Esta funcion recibe un entero que es el valor del la lectura del canal adc al cual esta conectado el termistor y devuelve el valor de la temepreatura en grados centigrados
double temptermistor (int canalAdc) {
  double Temp;    
  Temp = log (((10240000/analogRead(canalAdc)) - 10000));     //Formula para converit la lectura del ADC en grados kelvin ecuacion Steinhart-Hart
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp)) * Temp); //Formula para converit la lectura del ADC en grados kelvin
  Temp = Temp - 273.15; // Convierte Kelvin a Celcius
  return Temp;
}

//Esta funcion recibe un entero que es el pin adc donde esta conectado el LM35. Devuelve un float con el valor del la temp en centigrados

float templm35 (int canalAdc) {
  float Temp;
  Temp = (analogRead(canalAdc) * 0.0048828125 * 100);
  return Temp;
}
