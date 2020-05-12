#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>
/* this is a controller for Evacuated solar heater*/
//Author: Vuyani Daweti
// This Code is creates to read Three temperature sensors and tranfer them to the Serial monitor
//This code runs along with Python code Named: Arduino_to_Python.
#include <Metro.h>

//VARIABLE ASSINGMENT--------------
int ledPinGreen1 =  A4;
int ledPinRed1 = A3;
int PumpSwitch = A5;
int brightness;
const int chipSelect = 4;
Sd2Card card;
//int switch1 = 7;
int i = 0;
int j = 0;
int k = 0;
int m = 0;
int oldcelT = 0 ;
float analogOutputHeaterPin;
File myFile;
unsigned long time;
Metro serialMetro = Metro(1000);

LiquidCrystal lcd(A11, A10, A9, A8, A7, A6);

void setup()
{
      pinMode(ledPinGreen1, OUTPUT);
      pinMode(ledPinRed1, OUTPUT);
      pinMode(PumpSwitch, OUTPUT);
      Serial.begin(9600);
      lcd.begin(16, 2);
      
//      pinMode(switch1, INPUT);

}


void loop()
{
SD_CARD();
m=0;
   int analogOutputHeaterPin = analogRead(A0); //READ TEMPERATURE OF THE HEADER PIPE INPUT
  float voltageOH = analogOutputHeaterPin *(3300/ 1024.0);
  float celOH = voltageOH/10;
  int analogInputHeaterPin = analogRead(A1);   //READ TEMPERATURE OF THE HEADER PIPE OUTPUT
  float voltageIH = analogInputHeaterPin * (3300/ 1024.0);
  float celIH = voltageIH/10;
  int analogTankPin = analogRead(A2);   //READ TEMPERATURE OF THE TANK
  float voltageT= analogTankPin * (3300/ 1024.0);
  float celT = voltageT/10;
  //float work = celT;
 // boolean SwitchMode = analogRead(A3);
//  Serial.print("TEMPRATURE = ");
//  Serial.print(celT);
//  Serial.print("*C");
//  Serial.println();
 
 

  if (celT  < 30.0 ) {  //IF THE TEPMARATURE IS LESS THAN 30 DEGREES TURN THE PUMP ON.
    digitalWrite(ledPinGreen1,HIGH);
    digitalWrite(ledPinRed1,LOW);
    digitalWrite(PumpSwitch,HIGH);

   LDC_SCREEN(celT);
    PUMP(celT);

    }
  if (celT >= 30.0)  {    //IF THE TEMPERATURE IS MORE THAN 30 DEGREES TURN OFF THE PUMP
    digitalWrite(ledPinRed1,HIGH);
    digitalWrite(ledPinGreen1,LOW);
    digitalWrite(PumpSwitch,LOW);
    LDC_SCREEN(celT);
  }

//  }
//  if ( i < 210)  {
//      EEPROM.write(i , celT);
//      i = i + 1;
//   }

  if (serialMetro.check() == 1 && j != 30){
//      EEPROM.write(i, celT);
      Serial.print(celT);
      Serial.print(";");
      Serial.print(celIH);
      Serial.print(";");
      
      j = j + 1;
      if (j == 10){
        Serial.print(celOH);
      }
      //if (SwitchMode != 1){
       // Serial.print(celOH);
      //}
      else {
        Serial.println(celOH);
      }
    }
    if (j == 30){
      Serial.println(0);
      j = 0;
    //if (SwitchMode == 1 ){
     // Serial.println(00);
    }

  }
int LDC_SCREEN(float value)
{ 
  if (k==0)
  {
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.println("TANK_TEMPERATURE");
  lcd.setCursor(0, 1);
  lcd.print(value);
  k=1;
  oldcelT = value;
  }
  if (k!= 0)
  {
     if (oldcelT != value)
     {
      lcd.setCursor(0,1);
      lcd.print(value);
     }
  }
}

int PUMP(int number)
{
  brightness = -51*number +1530;
  if (number <25)
  {
    analogWrite(PumpSwitch,255);
  }
  if (number >= 30)
  {
    analogWrite(PumpSwitch,0);
  }
  else 
  {
    analogWrite(PumpSwitch,brightness);
  }
}

int SD_CARD (void)
{ 
  while (!card.init(SPI_HALF_SPEED, chipSelect)) {
  if (m==0)
    {
      
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.print("INSERT CARD!");
      lcd.setCursor(0,1);
      lcd.clear();
      m =1;
      k = 0;
    }
    else
    {
      lcd.setCursor(0,0);
      lcd.print("INSERT CARD!");
    }
  }  
}


