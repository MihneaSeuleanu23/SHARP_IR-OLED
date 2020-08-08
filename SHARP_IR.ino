
#include<SPI.h>
#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>

////SHARP IR SENSOR || Șeuleanu Mihnea-Radu 2020 1.0
const byte SHARP_IR=A0;
#define verde 7
#define galben 8
#define rosu 5
#define buzzer 10

#define OLED_RESET 4 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int sound=0,cnt;
float distanta;
int voltaj;


  
void setup() {
  // put your setup code here, to run once:

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

float distanta_medie()
{
  float suma=0;
  for(int i=0;i<25;i++){
   int voltaj=analogRead(SHARP_IR);
   ///int y=voltaj*5/700;
    float distanta=187754*pow(voltaj,-1.51);
    ///float distanta=61.681*pow(y,-1.133);
    suma+=distanta;
  }
 
  return suma/25.0;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
 
  float distanta_mean=distanta_medie();
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
      noTone(buzzer);
    }
    if(distanta_mean>30 && distanta_mean<=60){
      tone(buzzer,sound);
      delay(300);
      noTone(buzzer);
    }
    if(distanta_mean>15 && distanta_mean<=30){
      tone(buzzer,sound);
      delay(150);
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
