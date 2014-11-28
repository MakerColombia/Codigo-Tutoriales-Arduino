/*
Foto resistencia, Ilumina el led de modulo piranha  en el pin 11 de acuerdo a la luz que recibe la fotoresistencia 
 
Conecciones:
1- Modoulo fotoresistencia conetado al pin A0 del arduino
2- Modulo piranha conectado al pin 11

Creado Octubre 2014 
por 
Julio Aguirre
Para
MakerColombia

Este ejemplo es de dominio publico
 */


int pinLed = 11;// Pin en el que esta conectado modulo led
int potPin =0;  // Pin en el que esta conectado la foto resistencia
int val=0;      //Donde almacenamos el valor del mapeado 
int lectura=0;  //Donde almacenamos la lectura digital obtenida de la fotoresistencia  por el ADC canal A0

  void setup () {
  pinMode (pinLed, OUTPUT); //Inidcamos que donde esta el buzzer conectado es pin de salida
  pinMode(potPin, INPUT);   //Indicamos que donde esta conectado el potenciometro es una entrada
  Serial.begin(9600);       //Inicializamos el puerto serial 
}
  
  
  void loop () {
    
  lectura=analogRead(potPin);              //Leemos el pin del potenciometro con el ADC A0
  val = map(lectura, 0, 1023, 0, 255);  //Mapeamos este valor al rango 0 255 que puede recibir el pwm
  Serial.print("valor leido fotoresistencia ");         //Imprimimos al puerto serial la informacion 
  Serial.print(lectura);
  Serial.print(" - valor mapeado = ");
  Serial.println(val);
  analogWrite(pinLed,val);                        //Enviamos el valor pwm al led para variar su nivel de brillo
  delay(100);
}


  
