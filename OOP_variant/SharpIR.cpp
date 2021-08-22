

#include "Arduino.h"
#include "SharpIR.h"

//float AverageBuffer[count];
int NextAverage;
unsigned long current_millis=0;
SharpIR::SharpIR(const byte pin)
{
  _pin=pin;
  count=10;
  this->AverageBuffer=new float[count];
  weight=0.8; 
}

float SharpIR::getDistance()
{
  float suma=0;
  for(int i=0;i<10;i++){
    int voltaj=analogRead(_pin);
    voltaj=constrain_analog(voltaj);
    float distanta=187754*pow(voltaj,-1.51);
    suma=suma+distanta;
    delay(1);
  }

  return suma/10.0;
  
}

float SharpIR::getDistanceAverage()
{
  if(millis()-current_millis>10){
  int voltaj=analogRead(_pin);
  voltaj=constrain_analog(voltaj);
  
  float distanta=187754*pow(voltaj,-1.51);
  AverageBuffer[NextAverage++]=distanta;
  
  if(NextAverage>=count)
      NextAverage=0;

  float distanta_medie=0;
  for(int i=0;i<count;i++)
      distanta_medie+=AverageBuffer[i];

  distanta_medie/=count;

  return distanta_medie;
  }
  //delay(50);
  
}



float SharpIR::getDistanceExp()
{
  
  int voltaj=analogRead(_pin);
  voltaj=constrain_analog(voltaj);
  float distanta=187754*pow(voltaj,-1.51);
 
  float average=weight*distanta+(1-weight)*average;
  return average;
  delay(5);
}

int SharpIR::constrain_analog(const int val)
{
     if(val>=30 && val<=875)
          return val;
     else if(val<30)
          return 30;
     else
          return 875;
}

SharpIR::~SharpIR()
{
  delete[] AverageBuffer;
}
