/*
Buzzer PASIVO, es necesaro generar la señal que osicla para que el buzzer emita sonido en la frecuencia deseada

Conecciones:
1- Buzzer Pasivo con su pin IN conectado al pin 6 digital de arduino.ed que trae el arduino Uno revision 3
2- Modulo Potenciometro conectado al pin A0 del arduino.
Creado Octubre 2014 
por 
Julio Aguirre
Para
MakerColombia

Este ejemplo es de dominio publico
 */
int buzzer = 6 ;// Pin en el que esta conectado el buzzer
int potPin =0;  // Pin en el que esta conectado el potenciometro
int val=0;      //Donde almacenamos el valor del mapeado 
int lectura=0;  //Donde almacenamos la lectura digital obtenida del potenciometro por elADC canal A0

  void setup () {
  pinMode (buzzer, OUTPUT); //Inidcamos que donde esta el buzzer conectado es pin de salida
  pinMode(potPin, INPUT);   //Indicamos que donde esta conectado el potenciometro es una entrada
  Serial.begin(9600);       //Inicializamos el puerto serial 
}
  
 void loop () {
    
  lectura=analogRead(potPin);              //Leemos el pin del potenciometro con el ADC A0
  val = map(lectura, 0, 1023, 20, 20000);  //Mapeamos este valor al rango que puede detectar el oido humano 20Hz a 20.000 Hz
  Serial.print("valor leido pot ");         //Imprimimos al puerto serial la informacion 
  Serial.print(lectura);
  Serial.print(" - valor mapeado = ");
  Serial.println(val);
  tone(buzzer,val);                        //Enviamos el valor del tono al buzzer
  delay(100);
}
