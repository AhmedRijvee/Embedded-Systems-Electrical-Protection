
#include "EmonLib.h"   // Include Emon Library
EnergyMonitor emon1;   // Create an instance

// include the library code: 
#include <LiquidCrystal_I2C.h>  //library for LCD including I2C
#include <math.h> //library for mathematical calculation


LiquidCrystal_I2C lcd(0x27, 16, 2); // initialize the library with the LCD I2C display interface

int X;
int Y;
int Voltage = 0;
float Time;
float frequency;
const int input = A1; //Frequency input pin
const int test = 9;
const int Relay_PIN = 7;
const int LED_PIN = 6;


void setup()
{
  Serial.begin(9600);
  pinMode(Relay_PIN, OUTPUT);  // Set the pin as OUTPUT 
  pinMode(LED_PIN, OUTPUT);  // Set the LED pin as OUTPUT 
  pinMode(input,INPUT);
  pinMode(test, OUTPUT);
  analogWrite(test,127);
  
  emon1.voltage(A0,187, 1.7); // Voltage: input pin, calibration, phase_shift
  
  lcd.begin();
  lcd.backlight();
  
  
}

void loop()
{
  emon1.calcVI(20,2000); // Calculate all. No.of half wavelengths (crossings), time-out
  Voltage   = emon1.Vrms;  //extract Vrms into Variable

  X=pulseIn(input,HIGH);
  Y=pulseIn(input,LOW);
  Time = X+Y;
  frequency=1000000/Time;
  
  if (Time == 0) 
  {
   frequency = 0; 
  }
  
  lcd.setCursor(0,0);
  lcd.print("V=");
  lcd.print(Voltage);
  lcd.print("V, ");
  lcd.print("F=");
  lcd.print(frequency);
  lcd.print("Hz");


//NV=Normal Voltage, NF=Normal Frequency, UV=Under Voltage, UF=Under Frequency, OV=Over Voltage, OF=Over Frequency

if(200<=Voltage<=220 && 49<=frequency<=52)
{
    digitalWrite(Relay_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);
    lcd.setCursor(0,1);
    lcd.print("NV, NF");
}

if(200<=Voltage<=220 && frequency>52)
{
    digitalWrite(Relay_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    lcd.setCursor(0,1);
    lcd.print("NV, OF");
}

if(200<=Voltage<=220 && frequency<49)
{
    digitalWrite(Relay_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    lcd.setCursor(0,1);
    lcd.print("NV, UF");
}

if(Voltage<200 && 49<=frequency<=52)
{
    digitalWrite(Relay_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    lcd.setCursor(0,1);
    lcd.print("UV, NF");
}

if(Voltage>220 && 49<=frequency<=52)
{
    digitalWrite(Relay_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    lcd.setCursor(0,1);
    lcd.print("OV, NF");
}

if(Voltage>220 && frequency>52)
{
    digitalWrite(Relay_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    lcd.setCursor(0,1);
    lcd.print("OV, OF");
}

if(Voltage>220 && frequency<49)
{
    digitalWrite(Relay_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    lcd.setCursor(0,1);
    lcd.print("OV, UF");
}

if(Voltage<200 && frequency<49)
{
    digitalWrite(Relay_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    lcd.setCursor(0,1);
    lcd.print("UV, UF");
}

if(Voltage<200 && frequency>52)
{
    digitalWrite(Relay_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    lcd.setCursor(0,1);
    lcd.print("UV, OF");
}

  delay(200);
}


