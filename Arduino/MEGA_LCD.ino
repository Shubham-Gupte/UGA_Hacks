#include <TinyGPS.h>

#include <DHT.h>

#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <URTouch.h>
#include <URTouchCD.h>
#include <memorysaver.h>
#include <UTFT.h>
#include <avr/pgmspace.h>
//#include "Background_Bitmap.h"

UTFT    lcd(SSD1289,38,39,40,41);
URTouch  touch( 6, 5, 4, 3, 2);
int x, y;
int screen = 1;
int timex = 90;
int timey = 40;
int timex2 = 20;
int timey2 = 10;
int timex3 = 90;
int timey3 = 30;
int datex = 160;
int datey = 10;
int datex2 = 95;
int datey2 = 100;
int fontSize;
int alarmScreen = 10;
int dayScreen = 11;
int alarmVal = 0;
int alarmOk = 0;
int snoozeTime = 10;
int snoozex = 20;
int snoozeScreenVal = 0;
int homeScreen = 0;
int gpsScreen = 11;
int presetsScreen = 12;
extern uint8_t SevenSegNumFont[];
extern uint8_t BigFont[];
extern uint8_t SmallFont[];
extern uint8_t Various_Symbols_16x32_v2[];
extern uint8_t SevenSeg_XXXL_Num[];
extern uint8_t GroteskBold32x64[];
extern uint8_t SevenSegNumFontPlusPlus[];
extern uint8_t Various_Symbols_32x32[];
extern uint8_t Grotesk16x32[];
extern uint8_t various_symbols[];
extern uint8_t Dingbats1_XL[];
extern uint8_t arial_normal[];
extern uint8_t Grotesk32x64[];

#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

TinyGPS gps;
//byte x = 0;
byte bytes[8];

int piWeather;
int piTemp;
int piHour;
int piMin;
char piKey;
char piKey2;
int piHour2;
int piMin2;
int piData = 0;

// set alarm screen
int alarmScreenVal = 0;
  int hours = 1;
  int minutes = 0;
  int AM = 1;
  int PM = 2;
  int timeOfDay = AM;
  int alarmHour = 25;
  int alarmMin = 25;

// days of the week
int currentDay = 1;
int sunday = 1;
int monday = 2;
int tuesday = 3;
int wednesday = 4;
int thursday = 5;
int friday = 6;
int saturday = 7;
int dayScreenVal = 0;
char iam = 'a';
//extern unsigned int sun[0x2A0];

int currentMill = 0;
int randomVal = 0;
int tempLoop = 0;

void setup() {
Serial2.begin(9600);
Serial1.begin(9600);
Serial.begin(9600);
Serial.setTimeout(3000);
lcd.InitLCD();
touch.InitTouch();
touch.setPrecision(PREC_MEDIUM);
lcd.clrScr();
dht.begin();
//Serial2.print("1");
 
//lcd.drawBitmap(10, 10, 28, 24, sun);   
screen1(); 


  

}

void loop() {

if (Serial.available() >= 5)
{
  //Serial.read();
 piKey = Serial.read(); 
 piTemp = Serial.parseInt();
 piHour = Serial.parseInt();
 piMin = Serial.parseInt();
 piKey2 = Serial.read();

 piData = 1;
 tempLoop = 0;

/* if ( piKey == iam && piKey2 == iam)
{
 lcd.printNumI(piHour, 20, 100);
 lcd.printNumI(piMin, 20, 150 );
}*/

 
}

Time(); 

++ currentMill;
//Serial.print(currentMill); 

if (currentMill <= 65 && screen == 1)
{
  if (piData == 0)
  {
    if (randomVal == 0)
  {
  lcd.setColor(VGA_BLACK);
  lcd.fillRoundRect(1, 150, 319, 170);
  randomVal = 1;
  }
  lcd.setColor(VGA_WHITE);
  Temp(70, 150, 170, 150);
  tempLoop = 1;
  }
  else
  {
  lcd.setFont(arial_normal);
  lcd.printNumI(piTemp, 30, 150);
  lcd.print("*F  ", 62, 150);
  //lcd.printNumI(piTemp, 80, 130);
  lcd.print("Clear Skies", 130, 150);
  }
  
}
if (currentMill >= 66 && screen == 1 && tempLoop == 0)
{
  if (randomVal == 0)
  {
  lcd.setColor(VGA_BLACK);
  lcd.fillRoundRect(1, 150, 319, 170);
  randomVal = 1;
  } 
  lcd.setColor(VGA_WHITE);  
  Temp(70, 150, 170, 150);
}

if (currentMill > 120 && screen == 1)
{
  currentMill = 0;
  randomVal = 0;
  
}

if (screen == 1)
{
  
  if (piData == 0)
  {
    lcd.print("- No Pi Data -", 50, 130);
  }
 else
 {
  lcd.print("Alarm Time:", 30, 130);
  //lcd.print("9:30", 206, 130);
  if (piHour >= 10)
  {
    lcd.printNumI(piHour, 30, 130);
    
  }
  else
  {
    lcd.printNumI(piHour, 46, 130);
  }

  lcd.print(":", 62, 130);

  if (piMin > 9)
  {
    lcd.print("0", 78, 130);
    lcd.printNumI(piMin, 94, 130);
  }
  else
  {
    lcd.printNumI(piMin, 78, 130);
  }
 } 
}

if (screen != 1)
{
 currentMill = 0;
  randomVal = 0;   
}

 

//Serial2.println(analogRead(A1));



 //piData = 0;

 





if (touch.dataAvailable())
    {
      touch.read();
      x=touch.getX();
      y=touch.getY();
      
      /*Serial2.print("x: ");
      Serial2.print(x);
      Serial2.print(", ");
      Serial2.print("y: ");
      Serial2.println(y);*/

      if ((x>=270) && (x<=310) && (y>=190) && (y<=230))
      {
       
       ++screen; 
       lcd.setColor(VGA_WHITE);
       lcd.fillRoundRect ( 270, 190, 310, 230);
       if (screen == 1)
       {  
         screen1();
       }

       if (screen == 2)
       {
         screen2();
       }
        
       delay(200);
       
      }

      if ((x>=10) && (x<=50) && (y>=190) && (y<=230))
      {
       --screen; 
       lcd.setColor(VGA_WHITE);
       lcd.fillRoundRect ( 270, 190, 310, 230);
       if (screen == 1)
       {
          screen1();
       }

       if (screen == 2)
       {
          screen2();
       }

       if (screen == 0)
       {
          //Home();
       }
        
       delay(200);
      }

      if (screen == 2)
      {
        
      if ((x>=10) && (x<=160) && (y>=50) && (y<=90))
      {
        screen = alarmScreen;
        lcd.setColor(VGA_WHITE);
        lcd.fillRoundRect ( 10, 50, 160, 90);
        delay(200);
        setAlarmScreen();  
        
      }

      if ((x>=170) && (x<=310) && (y>=50) && (y<=90))
      {
        screen = dayScreen;
        lcd.setColor(VGA_WHITE);
        lcd.fillRoundRect ( 170, 50, 310, 90);
        delay(200);
        setDayScreen();
        
      }

      if ((x>=10) && (x<=160) && (y>=100) && (y<=140))
      {
        
        screen = gpsScreen;
        GPS();
        delay(200);
      }

    /* if ((x>=170) && (x<=310) && (y>=100) && (y<=140) && screen != alarmScreen)
      {
        
        screen = presetsScreen;
        presets();
        delay(200);
      }*/
      
      }

    
    }

}


void screen1()
{
  lcd.clrScr();
  forwardButton();
  backButton();    

  

  
}

void screen2()
{
  lcd.clrScr();
  forwardButton();
  backButton();  
  setAlarmButton();  
  setDay();
  gpsButton();
  //presetsButton();
}

void setAlarmScreen()
{
  lcd.clrScr();
  int alarmHours;  
  backButton();
  timeSelectButtonUp();
  timeSelectButtonDown();
  timeSelectButtonUp2();
  timeSelectButtonDown2();
  setAlarmTimeButton();
  snoozeButton();
  lcd.setFont(BigFont);
  if (timeOfDay == AM)
  {
  lcd.setBackColor(VGA_WHITE); 
  lcd.setColor(VGA_BLACK); 
  lcd.print("AM", 10, 65);
  lcd.setColor(VGA_WHITE);
  lcd.setBackColor(VGA_BLACK);  
  lcd.print("PM", 10, 150);
  }
  if (timeOfDay == PM)
  {
  lcd.setBackColor(VGA_BLACK); 
  lcd.setColor(VGA_WHITE); 
  lcd.print("AM", 10, 65);
  lcd.setColor(VGA_BLACK);
  lcd.setBackColor(VGA_WHITE);  
  lcd.print("PM", 10, 150);
  lcd.setBackColor(VGA_BLACK);
  lcd.setColor(VGA_WHITE);
  }  
  lcd.setFont(Grotesk16x32);
  lcd.print("Set Alarm", 88, 20);
  lcd.setFont(Dingbats1_XL);
  lcd.print("W", 250, 20);
  lcd.drawLine(83,55,237,55);  
  while ( alarmScreenVal == 0)
  {
    
    if (touch.dataAvailable())
    {
      touch.read();
      x=touch.getX();
      y=touch.getY();
      
      if ((x>=10) && (x<=50) && (y>=190) && (y<=230))
      {
        screen = 2;
        alarmScreenVal = 1;
        
      }

      if ((x>=70) && (x<=95) && (y>=65) && (y<=90))
      {
        if ( (hours >= 1) && (hours <= 12))
        {
        ++ hours;
        }

        /*if (hours == 12)
        {
          hours = 1;
        }*/
        delay(100);
      }

      if ((x>=70) && (x<=95) && (y>=150) && (y<=175))
      {
        if ( (hours >= 1) && (hours <= 12))
        {
        -- hours;
        }
        
        delay(100);
      }

      if ((x>=141) && (x<=166) && (y>=65) && (y<=90))
      {
        if (minutes < 60)
        {
          ++minutes;
        }
        
        delay(50);
      }

      if ((x>=141) && (x<=166) && (y>=150) && (y<=175))
      {
        if (minutes >= 0)
        {
          --minutes;
        }
        
        delay(50);
      }

      if ((x>=200) && (x<=280) && (y>=105) && (y<=130))
      {
        if (timeOfDay == AM)
        {
          alarmHour = hours;
          alarmMin = minutes;   
          if (hours == 12)
          {
            alarmHour = 0;
            minutes = alarmMin;
                 
          }
        }

        if (timeOfDay == PM)
        {
          if (hours == 12)
          {
            alarmHour = 12;
            minutes = alarmMin;
          }
          else
          {
           alarmHour = hours + 12;
           alarmMin = minutes;
          }
                            
        }

        alarmScreenVal = 1;
        
        lcd.setFont(BigFont);
        lcd.setColor(VGA_RED);
        lcd.print("Alarm at", 65, 200);
        if (alarmHour >= 10)
        {
          if (timeOfDay == PM)
          {
            alarmHours = alarmHour - 12;
            if ((alarmHours >= 10) && (alarmHours != 12))
            {
            lcd.printNumI(alarmHours, 194, 200);
            }
            else 
            {
              lcd.printNumI(alarmHours, 210, 200);
            }

            if (alarmHours == 12)
            {
              lcd.print("12", 194, 200);
            }
            
            
          }
          else
          {
          lcd.printNumI(alarmHour, 194, 200);
          }
        }
        else
        {
          lcd.printNumI(alarmHour, 210, 200);
        }
        
        lcd.print(":", 226, 200);
        if (alarmMin <= 10)
        {
          lcd.print("0", 242, 200);
          lcd.printNumI(alarmMin, 258, 200);
        }
        else
        {
          lcd.printNumI(alarmMin, 242, 200);
        }
        
        if ((timeOfDay == AM))
        {
          lcd.print("AM", 275, 200); 
        }

        if ((timeOfDay == PM))
        {
          lcd.print("PM", 275, 200); 
        }
        
        
        delay(3000);
        screen = 2;
      }

      if ((x>=10) && (x<=26) && (y>= 65) && (y<= 97))
      {
        lcd.setFont(BigFont);
        lcd.setBackColor(VGA_WHITE); 
        lcd.setColor(VGA_BLACK); 
        lcd.print("AM", 10, 65);
        lcd.setColor(VGA_WHITE);
        lcd.setBackColor(VGA_BLACK);  
        lcd.print("PM", 10, 150);  

        timeOfDay = AM;
      }

      if ((x>=10) && (x<=26) && (y>= 150) && (y<= 182))
      {
        lcd.setFont(BigFont);
        lcd.setBackColor(VGA_BLACK); 
        lcd.setColor(VGA_WHITE); 
        lcd.print("AM", 10, 65);
        lcd.setColor(VGA_BLACK);
        lcd.setBackColor(VGA_WHITE);  
        lcd.print("PM", 10, 150);  
        lcd.setBackColor(VGA_BLACK);

        timeOfDay = PM;
      }

      if ((x>=200) && (x<=280) && (y>=135) && (y<=160))
      {
        snoozeScreen();
        while( snoozeScreenVal == 0)
        {
          snoozeScreen2(); 
          lcd.setBackColor(0,0,0); 

        }  

        snoozeScreenVal = 0;
        setAlarmScreen();
      }

      


    }

    lcd.setFont(SevenSegNumFontPlusPlus);
    lcd.setColor(VGA_WHITE);   
    if ((hours <= 9) && (hours >= 1))
    {
      lcd.printNumI(hours, 60, 95);      
    }

    if ((hours >= 10) && (hours <= 12))
    {
      lcd.printNumI(hours, 28, 95);
    }

    if (hours == 13)
    {
      hours = 1;
      lcd.print("1", 60, 95);
    }

    lcd.print(":", 90, 95);

    if (minutes == 0)
    {
    lcd.print("00", 122, 95);
    }

    if ((minutes >= 1 ) && (minutes <= 9))
    {
      lcd.print("0", 122, 95);
      lcd.printNumI(minutes, 154, 95);      
    }

    if ((minutes >= 10) && (minutes <= 59))
    {
      lcd.printNumI(minutes, 122, 95);      
    }

    if (minutes == 60)
    {
      lcd.print("00", 122, 95);
      minutes = 0;
    }
  }

  if (screen == 2)
  {
    screen2();
  }
  alarmScreenVal = 0;
}

void snoozeScreen()
{
  int fivex;
  int fivey;  
  lcd.setColor(0, 0, 255);
  lcd.fillRoundRect ( 20, 20, 300, 220);
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 20, 20, 300, 220);
  fiveButton();
  tenButton();
  fifteenButton();
  thirtyButton();
  confirmButton();
  lcd.setFont(Grotesk16x32);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.print("Snooze Time", 70, 30);
  lcd.drawLine(70, 62, 246, 62);
  //lcd.setFont(SmallFont);
  //lcd.print("Select Snooze Time", 90, 72);
  lcd.setFont(arial_normal);
  lcd.print("Current Time:", 30, 80); 
  
  
  
}

void snoozeScreen2()
{
  lcd.setFont(arial_normal);
  if (snoozeTime == 5)
  {
    lcd.setBackColor(0,0,225);
    lcd.print("0", 240, 80);
    lcd.printNumI(snoozeTime, 256, 80);
  }
  else
  {
    lcd.setBackColor(0,0,225);
    lcd.printNumI(snoozeTime, 240, 80);
  }
   
  if (touch.dataAvailable())
    {
      touch.read();
      x=touch.getX();
      y=touch.getY();
      
      if ((x>=30) && (x<=80) && (y>=160) && (y<=220))
      {
        snoozeTime = 5;
        lcd.setColor(VGA_RED);
        lcd.drawRoundRect( 30, 160, 80, 210);
        delay(100);
        lcd.setColor(VGA_WHITE);
        lcd.drawRoundRect( 30, 160, 80, 210);
        fiveButton();
      }

      if ((x>=100) && (x<=150) && (y>=160) && (y<=220))
      {
        snoozeTime = 10;
        lcd.setColor(VGA_RED);
        lcd.drawRoundRect( 100, 160, 150, 210);
        delay(100);
        lcd.setColor(VGA_WHITE);
        lcd.drawRoundRect( 100, 160, 150, 210);
        fiveButton();
      }

      if ((x>=170) && (x<=220) && (y>=160) && (y<=220))
      {
        snoozeTime = 15;
        lcd.setColor(VGA_RED);
        lcd.drawRoundRect( 170, 160, 220, 210);
        delay(100);
        lcd.setColor(VGA_WHITE);
        lcd.drawRoundRect( 170, 160, 220, 210);
      }

      if ((x>=240) && (x<=290) && (y>=160) && (y<=220))
      {
        snoozeTime = 30;
        lcd.setColor(VGA_RED);
        lcd.drawRoundRect( 240, 160, 290, 210);
        delay(100);
        lcd.setColor(VGA_WHITE);
        lcd.drawRoundRect( 240, 160, 290, 210);
      }

      if ((x>=100) && (x<=220) && (y>=117) && (y<=142))
      {
        snoozeScreenVal = 1;
        alarmScreenVal = 1;
      }
    }
}

void setDayScreen()
{
  lcd.clrScr();
  backButton();
  lcd.setFont(Grotesk16x32);
  lcd.print("Select Day", 80, 20);  
  lcd.drawLine(77,55,243,55);
  lcd.setFont(arial_normal);
  lcd.print("Day:", 50, 60);
  setDOW(currentDay,114,60); 

  lcd.print("Sun", 50, 100);
  lcd.drawRoundRect(45, 95, 102, 120); 
  lcd.print("Mon", 137, 100);
  lcd.drawRoundRect(132, 95, 185, 120); 
  lcd.print("Tue", 219, 100);
  lcd.drawRoundRect(214, 95, 271, 120);
  lcd.print("Wed", 50, 145);
  lcd.drawRoundRect(45, 140, 102, 165); 
  lcd.print("Tur", 137, 145);
  lcd.drawRoundRect(132, 140, 185, 165); 
  lcd.print("Fri", 219, 145);
  lcd.drawRoundRect(214, 140, 271, 165);
  lcd.print("Sat", 137, 190);
  lcd.drawRoundRect(132, 185, 185, 210);
  
  while (dayScreenVal == 0)
  {
   if (touch.dataAvailable())
    {
      touch.read();
      x=touch.getX();
      y=touch.getY();

      if ((x>=10) && (x<=50) && (y>=190) && (y<=230))
      {
        screen = 2;
        screen2();
        dayScreenVal = 1;
      }

       if ((x>=45) && (x<=102) && (y>=95) && (y<=120))
      {
        lcd.setColor(VGA_RED);
        lcd.drawRoundRect(45, 95, 102, 120);
        currentDay = sunday;        
        delay(200);
        lcd.setColor(VGA_WHITE);
        lcd.drawRoundRect(45, 95, 102, 120);
        setDOW(currentDay,114,60);
        lcd.print("   ", 210, 60);       
      }

      if ((x>=132) && (x<=185) && (y>=95) && (y<=120))
      {
        lcd.setColor(VGA_RED);
        lcd.drawRoundRect(132, 95, 185, 120);
        currentDay = monday;        
        delay(200);
        lcd.setColor(VGA_WHITE);
        lcd.drawRoundRect(132, 95, 185, 120);
        setDOW(currentDay,114,60);
        lcd.print("   ", 210, 60);
       }

       if ((x>=214) && (x<=271) && (y>=95) && (y<=120))
      {
        lcd.setColor(VGA_RED);
        lcd.drawRoundRect(214, 95, 271, 120);
        currentDay = tuesday;        
        delay(200);
        lcd.setColor(VGA_WHITE);
        lcd.drawRoundRect(214, 95, 271, 120);
        setDOW(currentDay,114,60);
        lcd.print("   ", 226, 60);
       }

       if ((x>=45) && (x<=102) && (y>=140) && (y<=165))
      {
        lcd.setColor(VGA_RED);
        lcd.drawRoundRect(45, 140, 102, 165);
        currentDay = wednesday;        
        delay(200);
        lcd.setColor(VGA_WHITE);
        lcd.drawRoundRect(45, 140, 102, 165);
        setDOW(currentDay,114,60);
       }

       if ((x>=132) && (x<=185) && (y>=140) && (y<=165))
      {
        lcd.setColor(VGA_RED);
        lcd.drawRoundRect(132, 140, 185, 165);
        currentDay = thursday;        
        delay(200);
        lcd.setColor(VGA_WHITE);
        lcd.drawRoundRect(132, 140, 185, 165);
        setDOW(currentDay,114,60);
        lcd.print("   ", 242, 60);
       }

       if ((x>=214) && (x<=271) && (y>=140) && (y<=165))
      {
        lcd.setColor(VGA_RED);
        lcd.drawRoundRect(214, 140, 271, 165);
        currentDay = friday;        
        delay(200);
        lcd.setColor(VGA_WHITE);
        lcd.drawRoundRect(214, 140, 271, 165);
        setDOW(currentDay,114,60);
        lcd.print("   ", 210, 60);
       }

       if ((x>=132) && (x<=185) && (y>=185) && (y<=210))
      {
        lcd.setColor(VGA_RED);
        lcd.drawRoundRect(132, 185, 185, 210);
        currentDay = saturday;        
        delay(200);
        lcd.setColor(VGA_WHITE);
        lcd.drawRoundRect(132, 185, 185, 210);
        setDOW(currentDay,114,60);
        lcd.print("   ", 242, 60);
       }
    } 
  }

  dayScreenVal = 0;
  
}

void setDOW(int DOW, int DOWx, int DOWy)
{
  if (DOW == 1)
  {
    lcd.print("Sunday", DOWx, DOWy);
  }
  if (DOW == 2)
  {
    lcd.print("Monday", DOWx, DOWy);
  }
  if (DOW == 3)
  {
    lcd.print("Tuesday", DOWx, DOWy);
  }
  if (DOW == 4)
  {
    lcd.print("Wednesday", DOWx, DOWy);
  }
  if (DOW == 5)
  {
    lcd.print("Thursday", DOWx, DOWy);
  }
  if (DOW == 6)
  {
    lcd.print("Friday", DOWx, DOWy);
  }
  if (DOW == 7)
  {
    lcd.print("Saturday", DOWx, DOWy);
  }
  
}

void setDOW2 (int DOW2, int DOWx2, int DOWy2)
{
  if (DOW2 == 1)
  {
    lcd.print("Su", DOWx2, DOWy2);
  }
  if (DOW2== 2)
  {
    lcd.print("M", DOWx2, DOWy2);
  }
  if (DOW2== 3)
  {
    lcd.print("T", DOWx2, DOWy2);
  }
  if (DOW2== 4)
  {
    lcd.print("W", DOWx2, DOWy2);
  }
  if (DOW2== 5)
  {
    lcd.print("R", DOWx2, DOWy2);
  }
  if (DOW2== 6)
  {
    lcd.print("F", DOWx2, DOWy2);
  }
  if (DOW2== 7)
  {
    lcd.print("Sa", DOWx2, DOWy2);
  }
}
void forwardButton()
{
  lcd.setColor(0, 0, 255);
  lcd.fillRoundRect ( 270, 190, 310, 230);
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 270, 190, 310, 230);
  lcd.setFont(BigFont);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.print(">", 282, 203);
  lcd.setBackColor(0,0,0);
  
}

void backButton()
{
  lcd.setColor(0, 0, 255);
  lcd.fillRoundRect ( 10, 190, 50, 230);
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 10, 190, 50, 230);
  lcd.setFont(BigFont);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.print("<", 22, 203);
  lcd.setBackColor(0,0,0);
}

void timeSelectButtonUp()
{  
  lcd.setColor(0, 0, 255);
  lcd.fillRoundRect ( 70, 65, 95, 90);
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 70, 65, 95, 90);
  lcd.setFont(BigFont);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.setFont(various_symbols);  
  lcd.print("f", 75, 70);
  lcd.setBackColor(0,0,0);
}

void timeSelectButtonDown()
{  
  lcd.setColor(0, 0, 255);
  lcd.fillRoundRect ( 70, 150, 95, 175);
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 70, 150, 95, 175);
  lcd.setFont(BigFont);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.setFont(various_symbols);  
  lcd.print("g", 75, 155);
  lcd.setBackColor(0,0,0);
}

void timeSelectButtonUp2()
{  
  lcd.setColor(0, 0, 255);
  lcd.fillRoundRect ( 141, 65, 166, 90);
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 141, 65, 166, 90);
  lcd.setFont(BigFont);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.setFont(various_symbols);  
  lcd.print("f", 146, 70);
  lcd.setBackColor(0,0,0);
}

void timeSelectButtonDown2()
{  
  lcd.setColor(0, 0, 255);
  lcd.fillRoundRect ( 141, 150, 166, 175);
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 141, 150, 166, 175);
  lcd.setFont(BigFont);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.setFont(various_symbols);  
  lcd.print("g", 146, 155);
  lcd.setBackColor(0,0,0);
}

void setAlarmTimeButton()
{
  lcd.setColor(0,0,225);
  lcd.fillRoundRect ( 200, 105, 280, 130);
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 200, 105, 280, 130);
  lcd.setFont(SmallFont);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.print("Set Alarm", 206, 112);
}

void setAlarmButton()
{
  lcd.setColor(0,0,225);
  lcd.fillRoundRect ( 10, 50, 160, 90);
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 10, 50, 160, 90);
  lcd.setFont(arial_normal);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.print("Set Alarm", 13, 62);
  //lcd.setFont(Various_Symbols_32x32);
  //lcd.print("z", 180, 62);
  //lcd.setBackColor(0,0,0);
  
}

void alarmOkButton()
{
  lcd.setColor(0,225,0);
  lcd.fillRoundRect ( 40, 180, 90, 220);
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 40, 180, 90, 220);
  lcd.setFont(Grotesk16x32);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,225,0);
  lcd.print("OK", 50, 185);
}

void alarmSnoozeButton()
{
  lcd.setColor(225,0,0);
  lcd.fillRoundRect ( 190, 180, 300, 220);
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 190, 180, 300, 220);
  lcd.setFont(Grotesk16x32);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(225,0,0);
  lcd.print("Snooze", 200, 185);
}

void snoozeButton()
{
  lcd.setColor(0,0,225);
  lcd.fillRoundRect ( 200, 135, 280, 160);
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 200, 135, 280, 160);
  lcd.setFont(SmallFont);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.print("Snooze", 217, 142);
}

void fiveButton()
{  
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 30, 160, 80, 210);
  lcd.setFont(Grotesk16x32);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.print("5", 45, 170);
}

void tenButton()
{  
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 100, 160, 150, 210);
  lcd.setFont(Grotesk16x32);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.print("10", 107, 170);
}

void fifteenButton()
{  
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 170, 160, 220, 210);
  lcd.setFont(Grotesk16x32);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.print("15", 177, 170);
}

void thirtyButton()
{  
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 240, 160, 290, 210);
  lcd.setFont(Grotesk16x32);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.print("30", 247, 170);
}

void confirmButton()
{  
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 100, 117, 220, 142);
  lcd.setFont(SmallFont);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.print("Confirm", 130, 122);
}

void setDay()
{  
  lcd.setColor(0,0,225);
  lcd.fillRoundRect ( 170, 50, 310, 90);
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 170, 50, 310, 90);
  lcd.setFont(arial_normal);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.print("Set Day", 184, 62);  
}

void gpsButton()
{
  lcd.setColor(0,0,225);
  lcd.fillRoundRect ( 10, 100, 160, 140);
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 10, 100, 160, 140);
  lcd.setFont(arial_normal);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.print("Gps Data", 17, 112);  
}

/*void presetsButton()
{
  lcd.setColor(0,0,225);
  lcd.fillRoundRect ( 170, 100, 310, 140);
  lcd.setColor(255, 255, 255);
  lcd.drawRoundRect ( 170, 100, 310, 140);
  lcd.setFont(arial_normal);
  lcd.setColor(225, 225, 225);
  lcd.setBackColor(0,0,225);
  lcd.print("Presets", 184, 112);
}*/

void Time()
{
  tmElements_t tm;
  int Hours;
  int dayVal = 0;  
  if (screen == 1)
  {

  if (RTC.read(tm)) 
  {
    
    lcd.setColor(225, 225, 225);
    lcd.setFont(SevenSegNumFontPlusPlus);
    int fontSize = lcd.getFontXsize();
    int fontSizey = lcd.getFontYsize();
    lcd.setBackColor(0,0,0);
    if (tm.Hour >= 0 && tm.Hour <= 11)
    {
      timeOfDay = AM;
    }
    if (tm.Hour >= 12 && tm.Hour <= 23)
    {
      timeOfDay = PM;
    }
    if ((tm.Hour < 9) && (tm.Hour != 0))
    {
      lcd.printNumI(tm.Hour, timex, timey);
    }

    if ((tm.Hour > 9) && (tm.Hour < 13))
    {
      lcd.printNumI(tm.Hour, timex-(fontSize), timey);
    }
    if (tm.Hour == 0)
    {
      lcd.print("12", timex-(fontSize), timey);
    }
    if (tm.Hour >= 13)
    {
      Hours = tm.Hour - 12;
      if (Hours >= 10 && Hours != 0)
      {
      lcd.printNumI(Hours, timex-(fontSize), timey);
      }
      else
      {
        lcd.printNumI(Hours, timex, timey);
      }

      if (Hours == 0)
      {
        lcd.print("12", timex-(fontSize), timey);
      }

       
    }    
    lcd.print(":",timex+fontSize, timey);
    if (tm.Minute >= 0 && tm.Minute < 10)
    {
      lcd.print("0", timex+(fontSize*2), timey); 
      lcd.printNumI(tm.Minute, timex+(fontSize*3), timey);
    }
    else
    {
      lcd.printNumI(tm.Minute, timex+(fontSize*2), timey);
    }
      lcd.setFont(arial_normal);
      setDOW(currentDay, timex+10, timey + fontSizey +5);
    }
    else
  {
    lcd.setFont(GroteskBold32x64);
    lcd.print("ERROR",timex, timey);
  }     
    
  }
  

  if(screen != 1)
  {
   if (RTC.read(tm)) 
  {
    
    lcd.setColor(225, 225, 225);
    lcd.setFont(arial_normal);
    int fontSize = lcd.getFontXsize();
    lcd.setBackColor(0,0,0);
    if (tm.Hour >= 0 && tm.Hour <= 11)
    {
      timeOfDay = AM;
    }
    if (tm.Hour >= 12 && tm.Hour <= 23)
    {
      timeOfDay = PM;
    }
    if ((tm.Hour < 9) && (tm.Hour != 0))
    {
      lcd.printNumI(tm.Hour, timex2, timey2);
    }
    if ((tm.Hour > 9) && (tm.Hour < 13))
    {
      lcd.printNumI(tm.Hour, timex2-(fontSize), timey2);
    }
    if (tm.Hour == 0)
    {
      lcd.print("12", timex2-(fontSize), timey2);
    }
    if (tm.Hour >= 13 )
    {
      Hours = tm.Hour - 12;
      
      if (Hours >= 10)
      {
      lcd.printNumI(Hours, timex2-(fontSize), timey2);
      }
      else
      {
        lcd.printNumI(Hours, timex2, timey2);
      }

      if (tm.Hour == 0)
    {
      lcd.print("12", timex2-(fontSize), timey2);
    }
    
    }    
    lcd.print(":",timex2+fontSize, timey2);
    if (tm.Minute >= 0 && tm.Minute < 10)
    {
      lcd.print("0", timex2+(fontSize*2), timey2); 
      lcd.printNumI(tm.Minute, timex2+(fontSize*3), timey2);
    }
    else
    {
      lcd.printNumI(tm.Minute, timex2+(fontSize*2), timey2);
    }
      
    }
    else
    {
      lcd.print("ERROR",timex2, timey2);
    }
       
    if ((currentDay == 7) && (currentDay == 1))
    {
      setDOW2(currentDay,timex2+(fontSize*4) ,timey2);
    }
    else
    {
     setDOW2(currentDay,timex2+(fontSize*5) ,timey2); 
    }
     
  }

  lcd.setFont(arial_normal);
    fontSize = lcd.getFontXsize();
  Serial2.print(tm.Month);
  Serial2.print("/");  
  Serial2.print(tm.Day);
  Serial2.print("/");
  Serial2.println(tmYearToCalendar(tm.Year));
  
    if (tm.Month >= 10)
    {
      lcd.printNumI(tm.Month, datex-(fontSize), datey);      
    lcd.print("/", datex+fontSize, datey);
    if (tm.Day >= 10)
    {
      lcd.printNumI(tm.Day, datex+(fontSize*2), datey);
      lcd.print("/", datex+(fontSize*4), datey);
      lcd.printNumI(tmYearToCalendar(tm.Year), datex+(fontSize*5), datey);
    }
    else
    {
      lcd.printNumI(tm.Day, datex+(fontSize*2), datey);
      lcd.print("/", datex+(fontSize*3), datey);
      lcd.printNumI(tmYearToCalendar(tm.Year), datex+(fontSize*4), datey);
    }
    }
    else 
    {
       lcd.printNumI(tm.Month, datex, datey);
    lcd.print("/", datex+fontSize, datey);
    if (tm.Day >= 10)
    {
      lcd.printNumI(tm.Day, datex+(fontSize*2), datey);
      lcd.print("/", datex+(fontSize*4), datey);
      lcd.printNumI(tmYearToCalendar(tm.Year), datex+(fontSize*5), datey);
    }
    else
    {
      lcd.printNumI(tm.Month, datex+(fontSize*2), datey);
      lcd.print("/", datex+(fontSize*3), datey);
      lcd.printNumI(tmYearToCalendar(tm.Year), datex+(fontSize*4), datey);
    }    
  }

    if (tm.Hour == 0 && tm.Minute == 0)
    {
     if (dayVal == 0)
     {
      dayVal = 1;
      if (currentDay == 7)
      {
        currentDay = 1;
      }
      else
      {
        ++currentDay;
      }
     }
    }

    if (tm.Hour != 0 && tm.Minute != 0)
    {
      dayVal = 0;
    }

  delay(50);

  Serial2.print(alarmHour);
  Serial2.print(":");
  Serial2.print(alarmMin);
  Serial2.print(", ");
  Serial2.print(tm.Hour);
  Serial2.print(":");
  Serial2.println(tm.Minute);

 if ((alarmHour == tm.Hour) && (alarmMin == tm.Minute) && (alarmOk == 0))
  {
    lcd.clrScr();
    //lcd.setFont(GroteskBold32x64);
    //lcd.setColor(VGA_YELLOW);
    //lcd.print("Alarm", 80, 10);
    alarmOkButton();
    alarmSnoozeButton();    
    alarmVal = 0;
    lcd.setBackColor(VGA_BLACK);
    lcd.setFont(Dingbats1_XL);
    lcd.print("W", 30, 20);
    lcd.setFont(Dingbats1_XL);
    lcd.print("W", 250, 20);
    lcd.setColor(225, 225, 225);
    lcd.setFont(SevenSegNumFontPlusPlus);
    int fontSize = lcd.getFontXsize();
    lcd.setBackColor(0,0,0);
    
    if (tm.Hour >= 0 && tm.Hour <= 11)
    {
      timeOfDay = AM;
    }
    if (tm.Hour >= 12 && tm.Hour <= 23)
    {
      timeOfDay = PM;
    }
    if ((tm.Hour < 9) && (tm.Hour != 0))
    {
      lcd.printNumI(tm.Hour, timex3, timey3);
    }
    if ((tm.Hour > 9) && (tm.Hour < 13))
    {
      lcd.printNumI(tm.Hour, timex3-(fontSize), timey3);
    }
    if (tm.Hour == 0)
    {
      lcd.print("12", timex3-(fontSize), timey3);
    }
    if (tm.Hour >= 13 )
    {
      Hours = tm.Hour - 12;
      
      if (Hours >= 10)
      {
      lcd.printNumI(Hours, timex3-(fontSize), timey3);
      }
      else
      {
        lcd.printNumI(Hours, timex3, timey3);
      }

      if (tm.Hour == 0)
    {
      lcd.print("12", timex3-(fontSize), timey3);
    }
    
    }    
    lcd.print(":",timex3+fontSize, timey3);
    if (tm.Minute >= 0 && tm.Minute < 10)
    {
      lcd.print("0", timex3+(fontSize*2), timey3); 
      lcd.printNumI(tm.Minute, timex3+(fontSize*3), timey3);
    }
    else
    {
      lcd.printNumI(tm.Minute, timex3+(fontSize*2), timey3);
    }

    
    lcd.setFont(arial_normal);
    fontSize = lcd.getFontXsize();

    if (tm.Month >= 10)
    {
      lcd.printNumI(tm.Month, datex2-(fontSize), datey2);      
    lcd.print("/", datex2+fontSize, datey2);
    if (tm.Day >= 10)
    {
      lcd.printNumI(tm.Day, datex2+(fontSize*2), datey2);
      lcd.print("/", datex2+(fontSize*4), datey2);
      lcd.printNumI(tmYearToCalendar(tm.Year), datex2+(fontSize*5), datey2);
    }
    else
    {
      lcd.printNumI(tm.Day, datex2+(fontSize*2), datey2);
      lcd.print("/", datex2+(fontSize*3), datey2);
      lcd.printNumI(tmYearToCalendar(tm.Year), datex2+(fontSize*4), datey2);
    }
    }
    else 
    {
       lcd.printNumI(tm.Month, datex2, datey2);
    lcd.print("/", datex2+fontSize, datey2);
    if (tm.Day >= 10)
    {
      lcd.printNumI(tm.Day, datex2+(fontSize*2), datey2);
      lcd.print("/", datex2+(fontSize*4), datey2);
      lcd.printNumI(tmYearToCalendar(tm.Year), datex2+(fontSize*5), datey2);
    }
    else
    {
      lcd.printNumI(tm.Month, datex2+(fontSize*2), datey2);
      lcd.print("/", datex2+(fontSize*3), datey2);
      lcd.printNumI(tmYearToCalendar(tm.Year), datex2+(fontSize*4), datey2);
    }
    }

    while (alarmVal == 0)
    {
      
    if (touch.dataAvailable())
    {
      touch.read();
      x=touch.getX();
      y=touch.getY();

      if ((x>=40) && (x<=90) && (y>=180) && (y<=220))
      {
        alarmVal = 1;
        if (screen == 1)
        {
          screen1();
        }
        if (screen == 2)
        {
          screen2();
        }
      }

      if ((x>=190) && (x<=300) && (y>=180) && (y<=220))    // snooze
      {
        alarmMin = alarmMin + snoozeTime;
        if (alarmMin >= 60)
        {
          alarmMin = alarmMin - 60;
          if (alarmHour == 23)
          {
            alarmHour = 0;
          }
          else
          {
            ++ alarmHour;
          }
        }
        alarmVal = 1;
        lcd.setFont(arial_normal);
        lcd.setColor(VGA_WHITE);
        lcd.print("Snoozing for:", 30, 130);
        
        if (snoozeTime == 5)
        {
          lcd.print("0", 238, 80);
          lcd.printNumI(snoozeTime, 254, 130);
        }
        else
        {
          lcd.printNumI(snoozeTime, 238, 130);
        }  

        delay(3000);
        if (screen == 1)
        {
          screen1();
        }
        if (screen == 2)
        {
          screen2();
        }

       
        
      }

    }

    }

    alarmOk = 1;
  }

   if ((piHour == tm.Hour) && (piMin == tm.Minute) && (alarmOk == 0))
  {
    lcd.clrScr();
    //lcd.setFont(GroteskBold32x64);
    //lcd.setColor(VGA_YELLOW);
    //lcd.print("Alarm", 80, 10);
    alarmOkButton();
    alarmSnoozeButton();    
    alarmVal = 0;
    lcd.setBackColor(VGA_BLACK);
    lcd.setFont(Dingbats1_XL);
    lcd.print("W", 30, 20);
    lcd.setFont(Dingbats1_XL);
    lcd.print("W", 250, 20);
    lcd.setColor(225, 225, 225);
    lcd.setFont(SevenSegNumFontPlusPlus);
    int fontSize = lcd.getFontXsize();
    lcd.setBackColor(0,0,0);
    
    if (tm.Hour >= 0 && tm.Hour <= 11)
    {
      timeOfDay = AM;
    }
    if (tm.Hour >= 12 && tm.Hour <= 23)
    {
      timeOfDay = PM;
    }
    if ((tm.Hour < 9) && (tm.Hour != 0))
    {
      lcd.printNumI(tm.Hour, timex3, timey3);
    }
    if ((tm.Hour > 9) && (tm.Hour < 13))
    {
      lcd.printNumI(tm.Hour, timex3-(fontSize), timey3);
    }
    if (tm.Hour == 0)
    {
      lcd.print("12", timex3-(fontSize), timey3);
    }
    if (tm.Hour >= 13 )
    {
      Hours = tm.Hour - 12;
      
      if (Hours >= 10)
      {
      lcd.printNumI(Hours, timex3-(fontSize), timey3);
      }
      else
      {
        lcd.printNumI(Hours, timex3, timey3);
      }

      if (tm.Hour == 0)
    {
      lcd.print("12", timex3-(fontSize), timey3);
    }
    
    }    
    lcd.print(":",timex3+fontSize, timey3);
    if (tm.Minute >= 0 && tm.Minute < 10)
    {
      lcd.print("0", timex3+(fontSize*2), timey3); 
      lcd.printNumI(tm.Minute, timex3+(fontSize*3), timey3);
    }
    else
    {
      lcd.printNumI(tm.Minute, timex3+(fontSize*2), timey3);
    }

    
    lcd.setFont(arial_normal);
    fontSize = lcd.getFontXsize();

    if (tm.Month >= 10)
    {
      lcd.printNumI(tm.Month, datex2-(fontSize), datey2);      
    lcd.print("/", datex2+fontSize, datey2);
    if (tm.Day >= 10)
    {
      lcd.printNumI(tm.Day, datex2+(fontSize*2), datey2);
      lcd.print("/", datex2+(fontSize*4), datey2);
      lcd.printNumI(tmYearToCalendar(tm.Year), datex2+(fontSize*5), datey2);
    }
    else
    {
      lcd.printNumI(tm.Day, datex2+(fontSize*2), datey2);
      lcd.print("/", datex2+(fontSize*3), datey2);
      lcd.printNumI(tmYearToCalendar(tm.Year), datex2+(fontSize*4), datey2);
    }
    }
    else 
    {
       lcd.printNumI(tm.Month, datex2, datey2);
    lcd.print("/", datex2+fontSize, datey2);
    if (tm.Day >= 10)
    {
      lcd.printNumI(tm.Day, datex2+(fontSize*2), datey2);
      lcd.print("/", datex2+(fontSize*4), datey2);
      lcd.printNumI(tmYearToCalendar(tm.Year), datex2+(fontSize*5), datey2);
    }
    else
    {
      lcd.printNumI(tm.Month, datex2+(fontSize*2), datey2);
      lcd.print("/", datex2+(fontSize*3), datey2);
      lcd.printNumI(tmYearToCalendar(tm.Year), datex2+(fontSize*4), datey2);
    }
    }

    while (alarmVal == 0)
    {
      
    if (touch.dataAvailable())
    {
      touch.read();
      x=touch.getX();
      y=touch.getY();

      if ((x>=40) && (x<=90) && (y>=180) && (y<=220))
      {
        alarmVal = 1;
        if (screen == 1)
        {
          screen1();
        }
        if (screen == 2)
        {
          screen2();
        }
      }

      if ((x>=190) && (x<=300) && (y>=180) && (y<=220))    // snooze
      {
        alarmMin = alarmMin + snoozeTime;
        if (alarmMin >= 60)
        {
          alarmMin = alarmMin - 60;
          if (alarmHour == 23)
          {
            alarmHour = 0;
          }
          else
          {
            ++ alarmHour;
          }
        }
        alarmVal = 1;
        lcd.setFont(arial_normal);
        lcd.setColor(VGA_WHITE);
        lcd.print("Snoozing for:", 30, 130);
        
        if (snoozeTime == 5)
        {
          lcd.print("0", 238, 80);
          lcd.printNumI(snoozeTime, 254, 130);
        }
        else
        {
          lcd.printNumI(snoozeTime, 238, 130);
        }  

        delay(3000);
        if (screen == 1)
        {
          screen1();
        }
        if (screen == 2)
        {
          screen2();
        }

       
        
      }

    }

    }

    alarmOk = 1;
  }
  /*else
  {
    alarmOk = 0;
  }*/
  if ((alarmMin != tm.Minute))
  {
    alarmVal = 0;
    alarmOk = 0;
  }

  //alarmVal = 0;
}

void Temp( int humx, int humy, int tempx, int tempy)
{
  if (screen == 1)
  {
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);
  int CurrentFont;
  
  CurrentFont = lcd.getFontXsize();
  lcd.printNumI(h, humx, humy);
  lcd.print("%", humx +( 2* CurrentFont), humy);
  lcd.printNumI(f, tempx, tempy);
  lcd.print("*F", tempx +( 2* CurrentFont), tempy);
  }
}
void GPS()
{
  
  lcd.clrScr();
  backButton();
  lcd.setFont(Grotesk16x32);
  lcd.print("Gps Data", 88, 20);
  lcd.drawLine(83,55,221,55);
  int val = 1;
  while (val == 1)
  {
    bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial1.available())
    {
      char c = Serial1.read();
      if (gps.encode(c))
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon, fspeed;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial2.print("LAT=");
    Serial2.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial2.print(" LON=");
    Serial2.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial2.print(" SAT=");
    Serial2.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial2.print(" PREC=");
    Serial2.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
    Serial2.print(" SPEED=");
    Serial2.println(fspeed == gps.f_speed_kmph());   
    
    lcd.setFont(arial_normal);
    lcd.print("Latitude:", 20, 70);
    lcd.printNumI(flat, 166, 70);
    lcd.print("Longitude:", 20, 100);
    lcd.printNumI(flon, 182, 100);
    lcd.print("Speed:", 20, 130);
    lcd.printNumI(fspeed, 116, 130);
    lcd.print("Satellites:", 20, 160);
    lcd.printNumI(gps.satellites(), 198, 160);
  }
  
  gps.stats(&chars, &sentences, &failed);  
  if (chars == 0)
  {
    Serial2.println("** No characters received from GPS: check wiring **");
    lcd.setColor(VGA_RED);
    lcd.print("No GPS Data", 40, 70);
    lcd.setColor(VGA_WHITE);
  }

  if (touch.dataAvailable())
    {
      touch.read();
      x=touch.getX();
      y=touch.getY();

      if ((x>=10) && (x<=50) && (y>=190) && (y<=230))
      {
        screen = 2;
        screen2();
        val = 0;
      }
      
    }
  }
}

void presets()
{
  lcd.clrScr();
  backButton();
  lcd.setFont(Grotesk16x32);
  lcd.print("Online Presets", 40, 20);
  lcd.drawLine(37,55,221,55);
  int val = 1;

  while( val == 1)
  {
    if (touch.dataAvailable())
    {
      touch.read();
      x=touch.getX();
      y=touch.getY();

      if ((x>=10) && (x<=50) && (y>=190) && (y<=230))
      {
        screen = 2;
        screen2();
        val = 0;
      }
      
    }
  }
}


