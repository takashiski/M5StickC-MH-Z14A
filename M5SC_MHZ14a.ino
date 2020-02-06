#include <M5StickC.h>
#include "MHZ14A.h"
  MHZ14A co2sensor(&Serial1);

#define RX_PIN 36
#define TX_PIN 26
#define SIDE_BUTTON_PIN 39
#define M_BUTTON_PIN 37
#define RED_LED_PIN 10
#define M_PRESS_TIME 5000

int height,width;
bool flag_press_M_button;
int press_time;

void setup() {
  flag_press_M_button=false;
  pinMode(M_BUTTON_PIN,INPUT);
  
  M5.begin();
  height=M5.Lcd.height();
  width=M5.Lcd.width();
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextWrap(true);
  M5.Lcd.setTextColor(0xFFFF,0x0000);
  M5.Lcd.setTextSize(5);
  M5.Lcd.println("HELLO");
  
  Serial.begin(115200);
  Serial.println("Start");
  Serial1.begin(9600, SERIAL_8N1,RX_PIN,TX_PIN);
  Serial.println("preheat 3min");
  

  for(int i=0;i<3*3;i+=1)
  {
    delay(100);
    //delay(20*1000);
    M5.Lcd.fillRect(1+i*height/10,0,height/10-2,width,0xffff);
  }
//  co2sensor.calibrate();
  M5.Lcd.fillScreen(0x0000);
  delay(1000);

}

void loop() {

  if(!flag_press_M_button)
  {
    flag_press_M_button=!digitalRead(M_BUTTON_PIN);
    if(flag_press_M_button)
    {
      M5.Lcd.fillScreen(0x0000);
      M5.Lcd.setCursor(0,0);
      M5.Lcd.print("PRESSED");
      press_time=millis();
    }
    else
    {
      M5.Lcd.fillScreen(0x0000);
      int co2=co2sensor.read();
      M5.Lcd.setCursor(0,0);
      M5.Lcd.print(co2);
    }
  }
  else
  {
    flag_press_M_button=!digitalRead(M_BUTTON_PIN);
    if(flag_press_M_button&&millis()-press_time>M_PRESS_TIME)
    {
      M5.Lcd.fillScreen(0x0000);
      M5.Lcd.setCursor(0,0);
      M5.Lcd.print("CALIBRATE");
      flag_press_M_button=false;
      press_time=millis();
      co2sensor.calibrate();
      delay(3000);
      M5.Lcd.fillScreen(0x0000);
      M5.Lcd.setCursor(0,0);
      M5.Lcd.print("FINISH");
      delay(3000);
    }
  }
  delay(15000);

}
