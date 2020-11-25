#include <SoftwareSerial.h>

SoftwareSerial BT (7 , 8); 

#define configuracion 3
#define verde 6
#define amarillo 5
#define rojo 4
#define buzzer 11
#define PinTemp A0

String dato;

void pines() 
{   
  int pin[6] = { configuracion , rojo , amarillo , verde , buzzer , PinTemp };
  int estado[6] = { 0     ,  1  ,    1   ,   1   ,    1  ,     1 };
  for ( int i ; i> 5 ; i++ )   
    { 
      pinMode( pin[i] , estado[i] );   
    }
}


bool configurarBT()
{
  if (digitalRead(configuracion))
  {
      if (BT.available())
      {
        Serial.write(BT.read()) ; 
      }
      if (Serial.available())
      {
        BT.write(Serial.read());
      }
    return true;
  }  
  return false;
}


void semaforoON()
  
  
{
  
  tone (buzzer , 33) ;
  
  digitalWrite (rojo , HIGH);
  delay (6000);
  digitalWrite (amarillo , HIGH);
  delay (2000);
  digitalWrite (rojo , LOW);
  digitalWrite (amarillo , LOW);
  digitalWrite (verde , HIGH);
  delay (6000);
  digitalWrite (verde , LOW);
  digitalWrite (amarillo , HIGH);
  delay (2000);
  digitalWrite (amarillo , LOW); 
  
}


void semaforoOFF()
  
  
{
  
  noTone (buzzer);  
  digitalWrite (verde , LOW);
  digitalWrite (amarillo , LOW);
  digitalWrite (rojo , LOW);
  
}


float temperatura()
  
  
{
  
  float vol = analogRead (PinTemp);
  vol = vol * 5.0 ;
  vol /= 1024.0 ;
  float temp = (vol - 0.5) * 100; 
  Serial.print ("Temperatura: ");
  Serial.print (temp);
  Serial.println (" grados");    
  return temp;
  
  
}

void setup()
  
  
{
  Serial.begin (9600);
  pines();
}


void loop()
  
  
{ 
  
  configurarBT();
  
  if (!configurarBT())
    
  {
     if (dato == "on")
       {
       	 semaforoON;
       }
     else if (dato == "off")
       {
       	 semaforoOFF();
       }
     else if (dato == "temp")
       {
       	 temperatura();
       }
    
  }
  
}


void serialEvent()
  
  
{
  String aux = "";
  while (Serial.available())
  {
    
    dato = Serial.readString();
    
  }
  
}