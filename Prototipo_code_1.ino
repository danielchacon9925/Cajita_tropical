//#############################################################
//######### Primer prototipo de lógica de estados #############
//#############################################################
//  Daniel Chacón Mora
//  Código de prueba para la cajita tropical. Lleva el conteo 
// de la satisfacción de los clientes.
//  Se utilizan 4 condiciones: muy malo, malo, bueno y muy bueno.
//  Para asegurar el ingreso de una entrada a la vez se usa una
// variable de estado previo para cada caso.

//_________Definición de pines________________________________
const int ledPin = 13;// Pin LED
const int button_muy_malo = 7;
const int button_malo = 6;
const int button_bueno = 5;
const int button_muy_bueno = 4;

//_________Contadores de satisfacción_________________________
int cuenta_muy_mala =0;
int cuenta_mala =0;
int cuenta_buena =0;
int cuenta_muy_buena = 0;

//_________Estados____________________________________________
int estado_button_muy_malo = 0;
int estado_anterior_button_muy_malo = LOW;

int estado_button_malo = 0;
int estado_anterior_button_malo = LOW;

int estado_button_bueno = 0;
int estado_anterior_button_bueno = LOW;

int estado_button_muy_bueno = 0;
int estado_anterior_button_muy_bueno = LOW;

void setup()
{
//_________Definición de entradas y salidas__________________
  pinMode(ledPin,OUTPUT); 
  pinMode(button_muy_malo,INPUT_PULLUP); 
  pinMode(button_malo,INPUT_PULLUP);
  pinMode(button_bueno,INPUT_PULLUP);
  pinMode(button_muy_bueno,INPUT_PULLUP);
  Serial.begin(9600);

  Serial.begin(115200);
  Serial.println("SparkFun Qwiic Alphanumeric - Example 1: Print String");

  Wire.begin(); //Join I2C bus

  if (display.begin() == false)
  {
    Serial.println("Device did not acknowledge! Freezing.");
    while (1);
  }
  Serial.println("Display acknowledged.");

  display.print("Milk");
}

void loop()
{
  //___________Lectura digital del pin_______________________
  int estado_button_muy_malo = digitalRead(button_muy_malo); 
  int estado_button_malo = digitalRead(button_malo);
  int estado_button_bueno = digitalRead(button_bueno);
  int estado_button_muy_bueno = digitalRead(button_muy_bueno);

  //_____________________Condiciones_________________________

  //_____________________Muy malo____________________________
  if (estado_button_muy_malo != estado_anterior_button_muy_malo && estado_button_muy_malo == LOW)
  {
    // Evita el ingreso seguido de valores
    estado_anterior_button_muy_malo = estado_button_muy_malo;
    // Incrementa contador
    cuenta_muy_mala++ ;
    Serial.print("La cuenta muy mala es: ");
    Serial.println(cuenta_muy_mala);
    digitalWrite(ledPin,HIGH);//Turn the LED on
    delay(1000);
  }
  //_____________________Malo________________________________ 
  else if (estado_button_malo != estado_anterior_button_malo && estado_button_malo == LOW)
  {
    // Evita el ingreso seguido de valores
    estado_anterior_button_malo = estado_button_malo;
    // Incrementa contador
    cuenta_mala++ ;
    Serial.print("La cuenta mala es: ");
    Serial.println(cuenta_mala);
    digitalWrite(ledPin,HIGH);//Turn the LED on
    delay(1000);
  }
  //_____________________Bueno_______________________________ 
  else if (estado_button_bueno != estado_anterior_button_bueno && estado_button_bueno == LOW)
  {
    // Evita el ingreso seguido de valores
    estado_anterior_button_bueno = estado_button_bueno;
    // Incrementa contador
    cuenta_buena++ ;
    Serial.print("La cuenta buena es: ");
    Serial.println(cuenta_buena);
    digitalWrite(ledPin,HIGH);//Turn the LED on
    delay(1000);
  }
  //_____________________Muy bueno___________________________
  else if (estado_button_muy_bueno != estado_anterior_button_muy_bueno && estado_button_muy_bueno == LOW)
  {
    // Evita el ingreso seguido de valores
    estado_anterior_button_muy_bueno = estado_button_muy_bueno;
    // Incrementa contador
    cuenta_muy_buena++ ;
    Serial.print("La cuenta muy buena es: ");
    Serial.println(cuenta_muy_buena);
    digitalWrite(ledPin,HIGH);//Turn the LED on
    delay(1000);
  }
  else
  {
    // Evita el ingreso de varias entradas a la vez
    estado_anterior_button_muy_malo = estado_button_muy_malo;
    estado_anterior_button_malo = estado_button_malo;
    estado_anterior_button_bueno = estado_button_bueno;
    estado_anterior_button_muy_bueno = estado_button_muy_bueno;
     
    digitalWrite(ledPin,LOW); //Turn the LED off
  }
  



void loop()
{
}

}