#define RST 12
#define CE  11
#define DC  10
#define DIN  9
#define CLK  8
#define Bup 7
#define Bok 4
#define Bdwn 2
#define Dlit 5

#include "font.h";        // Display Driven Font pixel or display libarry
#include "kanak.h";        // my logo matrix pixel wise
#include <stdlib.h>;       // to convert the veriable data to string or string pointer
#include <Servo.h>;    

Servo myservo;
int select=0;
int potpin = A5;
int val;
char s[8];
int bright=45;
unsigned long previousTime = 0;
byte seconds=0 ;
byte minutes=0 ;
byte hours=0 ;



void setup()
{
  pinMode(RST, OUTPUT);
  pinMode(CE, OUTPUT);
  pinMode(DC, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(Dlit, OUTPUT);
  digitalWrite(RST, LOW);
  digitalWrite(RST, HIGH);
  myservo.attach(3);
  LCDinit();
  Welcome();
 
}


  

void loop()
{

  if (digitalRead(Bup) == HIGH)
  {
    delay(100);
    if (digitalRead(Bup) == HIGH)select=select+1;
  }
  
  if (digitalRead(Bdwn) == HIGH)
   {
    delay(100);
    if (digitalRead(Bdwn) == HIGH)select=select-1;
  }
  if (select >9)select=9;
  if (select<0)select=0;
  LcdXY(57,0);
  LcdWriteString(dtostrf(select,0,0,s));
  if (digitalRead(Bok) == HIGH)
   {
    delay(100);
    if (digitalRead(Bok) == HIGH)Callmenu(select);
  }
}

void kanak(void)
{
   for(int i=0; i<451; i++) LcdWriteData(k_grf[i]);
}



void Welcome(void)
{
  LcdXY(0,0);
  kanak();
  LcdXY(37,3);
  LcdWriteString("HI");
  delay(1000);
  LCDclr();
  LcdXY(24,0);
  LcdWriteString("WELCOME");
  LcdXY(42,2);
  LcdWriteString("TO");
  LcdXY(17,5);
  LcdWriteString("KaNaK EMBD");
  delay(2000);
  LcdXY(5,2);
  LcdWriteString("If found pls.");
  LcdXY(10,3);
  LcdWriteString("01738889858");
  delay(3000);
  LCDclr();
  
  mainmenu();
}




void Callmenu(int a)
{
  if(a==0)ServoCon();
  if(a==1)TempMeter();
  if(a==9)Msg();
  if(a==4)Display();
  if(a==3)time();
}

void mainmenu(void)
{  //main menu
LCDclr();
  LcdXY(27,0);
  LcdWriteString("Menu-");
  LcdXY(0,1);
  LcdWriteString("0-Srv");
  LcdXY(0,2);
  LcdWriteString("1-Temp.");
  LcdXY(0,3);
  LcdWriteString("2-Arm");
  LcdXY(0,4);
  LcdWriteString("3-Clk");
  LcdXY(0,5);
  LcdWriteString("4-D-Br");
  LcdXY(42,1);
  LcdWriteString("5-S.Met");
  LcdXY(42,2);
  LcdWriteString("6-(ept)");
  LcdXY(42,3);
  LcdWriteString("7-(ept)");
  LcdXY(42,4);
  LcdWriteString("8-(ept)");
  LcdXY(42,5);
  LcdWriteString("9-Msg");
}



  void ServoCon(void)
  {   
      LCDclr();
      LcdXY(17,0);
      LcdWriteString("Servo Met.");  
      LcdXY(0,3);
      LcdWriteString("Pos:");
      LcdXY(0,4);
      LcdWriteString("Cir:");
      LcdXY(0,5);
      LcdWriteString("Swi:");
      LcdXY(70,3);
      LcdWriteString("D");
      while(1)
      {
        
        
       int pot = analogRead(potpin);
       pot = map(pot, 0, 1023, 0, 179); 
       int mov=pot+val;
        myservo.write(mov);
        delay(15);
        LcdXY(35,3);
        LcdWriteString(dtostrf(mov,4,2,s));
         LcdXY(35,4);
        LcdWriteString(dtostrf(pot,4,2,s));
         LcdXY(35,5);
        LcdWriteString(dtostrf(val,4,2,s));
          if (digitalRead(Bup) == HIGH)
            {
             delay(100);
             if (digitalRead(Bup) == HIGH)val=val+5;
            }
  
          if (digitalRead(Bdwn) == HIGH)
           {
            delay(100);
            if (digitalRead(Bdwn) == HIGH)val=val-5;
          }
          if (digitalRead(Bok) == HIGH)
           {
            delay(100);
            if (digitalRead(Bok) == HIGH)
            mainmenu();
            return;
          }
            if(val<0)
       {
        val=0;
       }
       if(mov<0)
       {
        mov=0;
       }
         if(mov>180)
       {
        mov=180;
        val=180-pot;
       }
      }
  }
  
  void Display(void)
  {  LCDclr();
      LcdXY(10,0);
      LcdWriteString("Brightness");  
      LcdXY(0,3);
      LcdWriteString("Now:");
      LcdXY(70,3);
      LcdWriteString("%");    
    
        while(1)
        {
        analogWrite(Dlit,bright);
         if (digitalRead(Bup) == HIGH)
          {
            delay(100);
            if (digitalRead(Bup) == HIGH)bright=bright+20;
          }
          
         if (digitalRead(Bdwn) == HIGH)
           {
            delay(100);
            if (digitalRead(Bdwn) == HIGH)bright=bright-20;
           }
          if (bright >255)bright=255;
          if (bright<0)bright=0;
          if (digitalRead(Bok) == HIGH)
            {
              delay(100);
              if (digitalRead(Bok) == HIGH)
              mainmenu();
              return; 
             }
         int val_bright = map(bright, 0, 255, 0, 100);
          LcdXY(30,3);
          LcdWriteString(dtostrf(val_bright,3,0,s));       
         }
  } 
  
  void Msg(void)
  {
    LCDclr();
      LcdXY(0,0);
      LcdWriteString("Hi this is kanak."); 
     while(1)
     {
     
      if (digitalRead(Bok) == HIGH)
           {
            delay(100);
            if (digitalRead(Bok) == HIGH)
            mainmenu();
            return; 
           } 
     }

}
  
  void TempMeter(void)
  {
      LCDclr();
      LcdXY(17,0);
      LcdWriteString("Temp. Met.");  
      LcdXY(0,3);
      LcdWriteString("Temp:");
      LcdXY(70,3);
      LcdWriteString("C");
    while(1)
    {
      float temp = analogRead(A0)* 0.48828125;
      LcdXY(35,3);
      LcdWriteString(dtostrf(temp,4,2,s));
      delay(500); 
       if (digitalRead(Bok) == HIGH)
           {
            delay(100);
            if (digitalRead(Bok) == HIGH)
            mainmenu();
            return;
          } 
     }
  }
  
  void time(void)
  {
    int i=0;
    int inc_m,inc_h=0, r_min, r_hour=0;
    LCDclr();
      LcdXY(10,0);
      LcdWriteString("Time & Date");  
      LcdXY(0,3);
      LcdWriteString("Time:");
      LcdXY(0,4);
      LcdWriteString("Date:");
    while(1)
	{
             if (digitalRead(Bup) == HIGH)
              {
                delay(100);
                if (digitalRead(Bup) == HIGH)hours=hours+1;
              }
          
             if (digitalRead(Bdwn) == HIGH)
               {
                delay(100);
                if (digitalRead(Bdwn) == HIGH)minutes=minutes+1;
               }
             if (digitalRead(Bok) == HIGH)
                {
                  delay(100);
                  if (digitalRead(Bok) == HIGH)
                  mainmenu();
                  return;
                } 
      if (millis() >= (previousTime)) 
        {
             previousTime = previousTime + 1000;  // use 100000 for uS
             seconds = seconds +1;
             LcdXY(58,3);
             LcdWriteString(dtostrf(seconds,2,0,s));
             if (seconds == 60)
             {
                seconds = 0;
                minutes = minutes +1;
                LcdXY(43,3);
                LcdWriteString(dtostrf(minutes,2,0,s));
                
             }
             if (minutes == 60)
             {
                minutes = 0;
                hours = hours +1;
                LcdXY(28,3);
	        LcdWriteString(dtostrf(hours,2,0,s));

             }
             if (hours ==13)
             {
                hours = 1;
                i=!i;                
             }
			if (i==0)
			{
			  LcdXY(76,3);
			  LcdWriteString("a"); 
			}
                  
        }
	if (hours ==13)
             {
                hours = 1;
                i=!i;                
             }
         if (minutes ==60)
             {
                minutes = 0;              
             }
        if (i==1)
        {
	LcdXY(76,3);
	LcdWriteString("p"); 
	}
        if (i==0)
	{
	 LcdXY(76,3);
	 LcdWriteString("a"); 
	}
        LcdXY(58,3);
        LcdWriteString(dtostrf(seconds,2,0,s));
	LcdXY(28,3);
	LcdWriteString(dtostrf(hours,2,0,s));
	LcdXY(43,3);
	LcdWriteString(dtostrf(minutes,2,0,s));
     }
  }
  
  void LCDinit(void)
{
  LcdWriteCmd(0x21);  // LCD extended commands
  LcdWriteCmd(0xBF);  // set LCD Vop (contrast)
  LcdWriteCmd(0x04);  // set temp coefficent
  LcdWriteCmd(0x14);  // LCD bias mode 1:40
  LcdWriteCmd(0x20);  // LCD basic commands
  LcdWriteCmd(0x0C);  // LCD normal video  
  for(int i=0; i<504; i++) LcdWriteData(0x00); // clear LCD
  analogWrite(Dlit,bright);
}

void LCDclr(void)
{
  for(int i=0; i<504; i++) LcdWriteData(0x00);
}


void LcdWriteString(char *characters)
{
  while(*characters) LcdWriteCharacter(*characters++);
}



void LcdWriteCharacter(char character)
{
  for(int i=0; i<5; i++) LcdWriteData(ASCII[character - 0x20][i]);
  LcdWriteData(0x00);
}



void LcdWriteData(byte dat)
{
  digitalWrite(DC, HIGH); //DC pin is low for commands
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, dat); //transmit serial data
  digitalWrite(CE, HIGH);
}


void LcdXY(int x, int y)
{
  LcdWriteCmd(0x80 | x);  // Column.
  LcdWriteCmd(0x40 | y);  // Row.
}


void LcdWriteCmd(byte cmd)
{
  digitalWrite(DC, LOW); //DC pin is low for commands
  digitalWrite(CE, LOW);
  shiftOut(DIN, CLK, MSBFIRST, cmd); //transmit serial data
  digitalWrite(CE, HIGH);
}



