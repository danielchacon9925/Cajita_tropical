//#############################################################
//######### Primer prototipo de lógica de estados #############
//#############################################################
//  Daniel Chacón Mora
//  Código de prueba para la cajita tropical. Lleva el conteo 
// de la satisfacción de los clientes.
//  Se utilizan 4 condiciones: muy malo, malo, bueno y muy bueno.
//  Para asegurar el ingreso de una entrada a la vez se usa una
// variable de estado previo para cada caso.

#include <SparkFunDS1307RTC.h>
#include <Wire.h>
#include <SparkFun_Alphanumeric_Display.h> //Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_Alphanumeric_Display by SparkFun
HT16K33 display;


// Comment out the line below if you want month printed before date.
// E.g. October 31, 2016: 10/31/16 vs. 31/10/16
#define PRINT_USA_DATE

#define SQW_INPUT_PIN 2   // Input pin to read SQW
#define SQW_OUTPUT_PIN 13 // LED to indicate SQW's state


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
//_________Configuración de RTC______________________________
  Serial.begin(9600);
  pinMode(SQW_INPUT_PIN, INPUT_PULLUP);
  pinMode(SQW_OUTPUT_PIN, OUTPUT);
  digitalWrite(SQW_OUTPUT_PIN, digitalRead(SQW_INPUT_PIN));
  // Llamado de inicio de RTC
  rtc.begin(); 
  rtc.writeSQW(SQW_SQUARE_1);
  rtc.autoTime();
  
  //_________Pantalla LCD_____________________
  Serial.begin(9600);
  Wire.begin(); //Join I2C bus
  if (display.begin() == false)
  {
    Serial.println("Device did not acknowledge! Freezing.");
    while (1);
  }
  Serial.println("Display acknowledged."); 
}

void loop()
{
  //___________Lectura digital del pin_______________________
  int estado_button_muy_malo = digitalRead(button_muy_malo); 
  int estado_button_malo = digitalRead(button_malo);
  int estado_button_bueno = digitalRead(button_bueno);
  int estado_button_muy_bueno = digitalRead(button_muy_bueno);

  //___________Read/Update RTC_______________________________
  static int8_t lastSecond = -1;
  rtc.update();
  if (rtc.second() != lastSecond)
  {
    lastSecond = rtc.second(); 
  }


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
    printTime();  // Imprime Tiempo
    display.print(String(cuenta_muy_mala) + "MM");

    
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
    printTime();  // Imprime tiempo
    display.print(String(cuenta_mala) + "M");
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
    printTime();  // Imprime tiempo 
    display.print(String(cuenta_buena) + "B");

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
    printTime();  // Imprime
    display.print(String(cuenta_muy_buena) + "MB");
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
}
void printTime()
{
  Serial.print(String(rtc.hour()) + ":"); // Print hour
  if (rtc.minute() < 10)
    Serial.print('0'); // Print leading '0' for minute
  Serial.print(String(rtc.minute()) + ":"); // Print minute
  if (rtc.second() < 10)
    Serial.print('0'); // Print leading '0' for second
  Serial.print(String(rtc.second())); // Print second

  if (rtc.is12Hour()) // If we're in 12-hour mode
  {
    // Use rtc.pm() to read the AM/PM state of the hour
    if (rtc.pm()) Serial.print(" PM"); // Returns true if PM
    else Serial.print(" AM");
  }
  
  Serial.print(" | ");

  // Few options for printing the day, pick one:
  Serial.print(rtc.dayStr()); // Print day string
  //Serial.print(rtc.dayC()); // Print day character
  //Serial.print(rtc.day()); // Print day integer (1-7, Sun-Sat)
  Serial.print(" - ");
#ifdef PRINT_USA_DATE
  Serial.print(String(rtc.month()) + "/" +   // Print month
                 String(rtc.date()) + "/");  // Print date
#else
  Serial.print(String(rtc.date()) + "/" +    // (or) print date
                 String(rtc.month()) + "/"); // Print month
#endif
  Serial.println(String(rtc.year()));        // Print year
}
