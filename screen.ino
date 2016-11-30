int buttonPin4 = 7;
int buttonPin3 = 6;
int buttonPin2 = 5;
int buttonPin1 = 4;

int button4 = 0;
int button3 = 0;
int button2 = 0;
int button1 = 0;


int state=0;
boolean menubutton=false;
boolean selectbutton=false;
int timing = 0;
int counter =0;
int ct =0;

long past = 0;

#include <Servo.h>

Servo servo1;


#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(13, 11, 10, 3, 8);	// SW SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 3, RST = 8

//Pin 10 CS is no connection (NC). The library needs cable select, but it isn't used. Added pin 8 for reset. SCL = 13 SDA = 11 RST = 8 D/C = 9

void menu(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  if (menubutton==false){
    u8g.drawStr(0,10, "x Select Period"); 
    u8g.drawStr(0,30, "  Start"); 
  };
  
    if (menubutton==true){
    u8g.drawStr(0,10, "  Select Period");   
    u8g.drawStr(0,30, "x Start");   
  };  
}

void count(void) {
  u8g.setFont(u8g_font_fur20);
  u8g.setPrintPos(60,30);
  u8g.print(counter);
} 


void select(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
   String time = String(timing, BIN);
  if (selectbutton==false){
    u8g.drawStr(0,10, "x Select Period"); 
    u8g.setPrintPos(60, 30);
    u8g.print(timing);
    u8g.drawStr(0,50, "  Okay"); 
  }
    if (selectbutton==true){
    u8g.drawStr(0,10, "  Select Period");
    u8g.setPrintPos(60,30);   
    u8g.print(timing);
    u8g.drawStr(0,50, "x Okay"); 
    
  };  
}



void setup(void) {
   Serial.begin(9600);    
   servo1.attach(9);
  // initialize the pushbutton pin as an input:

  // flip screen, if required
  // u8g.setRot180();
  
  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);

  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
   u8g.firstPage();
       do {
menu();
  } while( u8g.nextPage() );
delay(50);
}

void loop(void) {
  // picture loop
   
   u8g.firstPage();  

    button4= digitalRead(buttonPin4);
     button3= digitalRead(buttonPin3);
      button2= digitalRead(buttonPin2);
       button1= digitalRead(buttonPin1);
/*Serial.print("button4:");
   Serial.println(button4);
   Serial.print("button3:");
   Serial.println(button3);
   Serial.print("button2:");
   Serial.println(button2);
   Serial.print("button1:");
   Serial.println(button1);
  */
  
  if (state==0){
   do {
      menu();
  } while( u8g.nextPage() );
  };
  
  if (state==1){
     do {
      select();
  } while( u8g.nextPage() );
  };
  
  if (state==2){
  servo1.write(0);
  if (count>0){  
  do {
      count();
  } while( u8g.nextPage());
  unsigned long cur = millis();
  if (cur - past > 1000){
  past = cur;
  counter-=1;
  
  }
  //delay(930);
  
  }
  
  
  
  if (counter==0){  
  do {
      count();
  } while( u8g.nextPage());
  state=0;
  servo1.write(90);
  counter=timing;
  tone(A5,440);
  delay(2000);
  noTone(A5);
  }
  
  
  
  };  
   
     
  if (state==0 && button4 ==HIGH){
   menubutton= !menubutton;  
  do {
      menu();
  } while( u8g.nextPage() );
    delay(100);
  };  
  
 if (state==0 && menubutton==false && button1==HIGH){
    state = 1;
  delay(100);  
     };  
  
  if (state==0 && menubutton==true && button1==HIGH){
    state = 2;  
     };      
     
 if (state==1 && button4==HIGH){   
    selectbutton= !selectbutton;
  do {
      select();
  } while( u8g.nextPage() );
    delay(100);
  };  
  
  if (state==1 && selectbutton==true && button1==HIGH){
  Serial.println(state);
  selectbutton=false;
  counter =timing+1;
  state=0;
  delay(100);
  };    
    
  if (state==1 && button3==HIGH && selectbutton==false){
  timing+=1;
    do {
      select();
  } while( u8g.nextPage() );
    delay(60);
  };
  
  if (state==1 && button2==HIGH && selectbutton==false){
  timing-=1;
  if (timing <0){
    timing=0;
  }
    do {
      select();
  } while( u8g.nextPage() );
    delay(60);
  };
  
  
    

     
  
  // rebuild the picture after some delay
  //delay(50);
}

