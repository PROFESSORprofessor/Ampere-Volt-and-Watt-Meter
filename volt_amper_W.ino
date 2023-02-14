#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_SH1106.h>
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

const int currentSensor = A0;
const int voltageSensor = A1;
float vOUT = 0.0;
float vIN = 0.0;
float R1 = 10000.0;
float R2 = 1510.0;
float Vdata = 0;
float V,I,I1;
float Cdata;
float value;

void setup(){ 
  pinMode(voltageSensor, INPUT);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.display();

}
void loop(){

//float vIN = 0.0;

   for(int i = 0; i < 300; i++) // daha kararlı ortalama bir sonuç almak için 300 kez okuma yapma
   {
     Cdata = Cdata + analogRead(currentSensor);
     Vdata = Vdata + analogRead(voltageSensor);
     delay(1);
   }

 Cdata=Cdata/300;           
 V=Cdata * 5.0/1024.0;                       
 I=((V - 2.5)/ 0.100);

 Vdata=Vdata/300;
 vOUT = (Vdata * 5.0) / 1024.0;
 vIN = (vOUT / (R2/(R1+R2))) ;

  // Voltaj değerini ekrana yazsırma
  display.setCursor(0,0);
  display.setTextSize(2);
  display.println(vIN);
  display.setTextSize(2);
  display.setCursor(100,0);
  display.print("V");
  
  // Amper değerini ekrana yazdırma
  display.setCursor(0,25);
  display.setTextSize(2);
  if (I<0) {display.println("0.00");} else {display.println(I);}
  display.setTextSize(2);
  display.setCursor(100,25);
  display.print("A");
  
  

  display.setCursor(0,50);
  display.setTextSize(2);
  value=(I * vIN);
  if (value<0){display.println("0.0");} else {display.println(value);} 
  display.setTextSize(2);
  display.setCursor(100,50);
  display.print("W");
  
  
  
  
display.display();
display.clearDisplay();

// Değerleri sıfırlama
  Cdata=0;
  I=0;
  V=0;
  Vdata=0;
  vIN=0;
  value;
}
