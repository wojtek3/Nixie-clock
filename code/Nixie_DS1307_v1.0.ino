#include <PCF8574.h>

#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 RTC;

PCF8574 PCF_H(0x20);
PCF8574 PCF_M(0x21);
PCF8574 PCF_S(0x23);

int brightnessDelay;
int odtruty;

int s;
int s1;
int s10;

int m;
int m1;
int m10;

int h;
int h1;
int h10;

void setup()
{
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()) {
  }
  odtruwanie();
  //RTC.adjust(DateTime(__DATE__, __TIME__));
}

void loop()
{
  DateTime now = RTC.now();     
  
  s = now.second(), DEC;
  s1 = s % 10;                                    //Wyodrębnienie liczby jedności sekund
  s10 = (s / 10) % 10;                            //Wyodrębnienie liczby dziesiątek sekund

  m = now.minute(), DEC;
  m1 = m % 10;                                    //Wyodrębnienie liczby jedności sekund
  m10 = (m / 10) % 10;

  h = now.hour(), DEC;
  h1 = h % 10;                                    
  h10 = (h / 10) % 10;

  if (h>=20 || h<5){
    brightnessDelay = 3;
  }
  if (h>=5 && h<7){
    brightnessDelay = 5;
  }
  if (h>=7 && h<18){
    brightnessDelay = 8;
  }
  if (h>=18 && h<20){
    brightnessDelay = 5;
  }

  if (m==0 || m==15 || m==30 || m==45){
    if(odtruty == 0){
          odtruwanie();
          odtruty = 1;
    }
  }else{
    odtruty = 0;
  }

  s1 = conv(s1);
  s10 = conv(s10);

  m1 = conv(m1);
  m10 = conv(m10); 

  h1 = conv(h1);
  h10 = conv(h10); 
  
  s = (s10 << 4)+s1;    
  m = (m10 << 4)+m1;   
  h = (h10 << 4)+h1;                                  
  PCF_S.write8(s);
  PCF_M.write8(m);
  PCF_H.write8(h);
  delay(brightnessDelay);
  PCF_S.write8(0xFF);
  PCF_M.write8(0xFF);
  PCF_H.write8(0xFF);
  delay(8-brightnessDelay);
}

void odtruwanie(){
  for (int i = 0; i < 140; i++) {
    s1 = conv(random(0,10));
    s10 = conv(random(0,10));

    m1 = conv(random(0,10));
    m10 = conv(random(0,10)); 

    h1 = conv(random(0,10));
    h10 = conv(random(0,10)); 
  
    s = (s10 << 4)+s1;    
    m = (m10 << 4)+m1;   
    h = (h10 << 4)+h1;                                  
    PCF_S.write8(s);
    PCF_M.write8(m);
    PCF_H.write8(h);
    delay(60);
  }
}

int conv(int i){
  switch (i) {
  case 0:
  i = 0;
  break;
  case 1:
  i = 8;
  break;
  case 2:
  i = 2;
  break;
  case 3:
  i = 10;
  break;
  case 4:
  i = 1;
  break;
  case 5:
  i = 9;
  break;
  case 6:
  i = 3;
  break;
  case 7:
  i = 11;
  break;
  case 8:
  i = 4;
  break;
  case 9:
  i = 12;
  break;
  }
  return i;
}
