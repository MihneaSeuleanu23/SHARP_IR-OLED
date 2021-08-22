#include "SharpIR.h"
#include<SPI.h>
#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>


////SHARP IR SENSOR || Șeuleanu Mihnea-Radu 2020 1.0

const byte SHARP_IR=A0; //senzorul transmite semnalul catre pinul analogic A0 de pe Arduino
#define verde 7 //define-uri pentru pinii folositi ca sa aprind cele 3 led-uri, respectiv pentru buzzer
#define galben 8
#define rosu 5
#define buzzer 10

#define OLED_RESET 4 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //initierea instantei pentru ecranul OLED

SharpIR sensor(SHARP_IR); //constructorul pentru senzor IR

int sound=0; //parametrul pentru intensitatea sunetului de la buzzer
//int cnt;
//float distanta;
//int voltaj;

//unsigned long count[4]={0,0,0,0};
//boolean timeout(unsigned long*,unsigned long);

  
void setup() {
  

  Serial.begin(9600);
  pinMode(verde,OUTPUT);
  pinMode(galben,OUTPUT);
  pinMode(rosu,OUTPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
   }
  display.clearDisplay();
  
  
  
}


void loop() {
  
  
 
  //float distanta_mean=sensor.getDistance();
  //float distanta_mean=sensor.getDistanceAverage();
  float distanta_mean=sensor.getDistanceExp();
  Serial.println(distanta_mean);
 
  
  if(distanta_mean>60){
    digitalWrite(verde,HIGH);
    sound=400;
  }else 
    digitalWrite(verde,LOW);

  if(distanta_mean>30 && distanta_mean<=60){
    sound=800;
    digitalWrite(galben,HIGH);}
  else
    digitalWrite(galben,LOW);

  if(distanta_mean>6 && distanta_mean<=30){
    sound=1200;
    digitalWrite(rosu,HIGH);}
  else
    digitalWrite(rosu,LOW);

   if(distanta_mean>100){
    noTone(buzzer);
   }else{
    if(distanta_mean>60 && distanta_mean<=100){
        tone(buzzer,sound);
        delay(500);
     //if(timeout(&count[0],500UL))
        noTone(buzzer);
    }
    if(distanta_mean>30 && distanta_mean<=60){
      tone(buzzer,sound);
      delay(300);
     //if(timeout(&count[1],300UL))
      noTone(buzzer);
    }
    if(distanta_mean>15 && distanta_mean<=30){
      tone(buzzer,sound);
      delay(150);
     //if(timeout(&count[2],150UL)) 
      noTone(buzzer);
    }
    if(distanta_mean>9 && distanta_mean<=15){
          tone(buzzer,sound);
          delay(85);
          noTone(buzzer);
      
    }
    if(distanta_mean<=9){
      tone(buzzer,sound);
    }
   
   }
 
  
  ///delay(150);

  display.setCursor(0,10); ///coordonate x,y
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Distanta");
  display.setCursor(110,15);
  display.setTextSize(1);
  
  ///if(cnt==5){
    display.println((int)distanta_mean);
    ///cnt=0;}
   ///cnt++;
  display.display();
  delay(200);
  display.clearDisplay();


}
