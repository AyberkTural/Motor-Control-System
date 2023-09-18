#include <LiquidCrystal.h>
// LCD pins <--> Arduino pins
const int RS = 12, EN = 11, D4 = 8, D5 = 4, D6 = 7, D7 = 3;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);


const int in_1 = 9 ;
const int in_2 = 2 ;
const int in_3 = 10 ;
const int in_4 = 13 ;
const int button1 = 1;
const int button2 = 0;


char motorno='1';
char motorfunc='r';
char motorfunc1='r';
char motorfunc2='r';
char rcved_char;
int count_char=0;
int motorspeed1=255;
int motorspeed2=255;
int motorspeed=255;
int buttonstate1;
int buttonstate2;
int buttonstate3;
// motorfunc: turn right (CW), turn left (CCW), Brake. Speed: 0-255 duty for pwm
void motor(char motornox, char motorfuncx, int motorspeedx){
  
  if(motornox=='1'){
          
      if(motorfuncx=='r'){
          digitalWrite(in_1,HIGH) ;
          digitalWrite(in_2,LOW) ; 
      }     
      else if(motorfuncx=='l'){
          digitalWrite(in_1,LOW) ;
          digitalWrite(in_2,HIGH) ;
      }     
      else if(motorfuncx=='b'){
         digitalWrite(in_1,HIGH) ;
         digitalWrite(in_2,HIGH) ;
      }     
  }
  else if(motornox=='2'){
          
      if(motorfuncx=='r'){
          digitalWrite(in_3,HIGH) ;
          digitalWrite(in_4,LOW) ;
      }     
      else if(motorfuncx=='l'){
          digitalWrite(in_3,LOW) ;
          digitalWrite(in_4,HIGH) ;
      }     
      else if(motorfuncx=='b'){
          digitalWrite(in_3,HIGH) ;
          digitalWrite(in_4,HIGH) ;
      }     
  }


}

void setup()
{
   pinMode(in_1,OUTPUT) ; //Logic pins are also set as output
   pinMode(in_2,OUTPUT) ;
   pinMode(in_3,OUTPUT) ; //Logic pins are also set as output
   pinMode(in_4,OUTPUT) ;
   pinMode(button1,INPUT_PULLUP);
   pinMode(button2,INPUT_PULLUP);
  
  Serial.begin(57600);
  
  lcd.begin(20, 4); // set up number of columns and rows
  lcd.home();
  lcd.clear();
  lcd.print("Lab-7:E3");  
  delay(2000);
  lcd.home();
  lcd.clear();

}

void loop(){

   if (buttonstate1 == 0 && buttonstate2 == 0 && (buttonstate3/255) == 0) {

     motorfunc1 = 'r';
     motorfunc2 = 'b';
     motor('1',motorfunc1,motorspeed1);
    motor('2', motorfunc2,motorspeed2);
  }
  // first motor turns left and second motor break
  else if (buttonstate1 == 0 && buttonstate2 == 1 && (buttonstate3/255) == 0) {
     motorfunc1 = 'l';
     motorfunc2 = 'b';

    motor('1', motorfunc1,motorspeed1);
    motor('2', motorfunc2,motorspeed2);
  }
  else if (buttonstate1 == 1 && buttonstate2 == 0 && (buttonstate3/255) == 0) {
    motorfunc1 = 'b';
     motorfunc2 = 'b';

    motor('1', motorfunc1,motorspeed1);
    motor('2', motorfunc2,motorspeed2);
  }

  // first motor and second motor break
  
  else if (buttonstate1 == 1 && buttonstate2 == 1 && (buttonstate3/255) == 0) {
    motor('1', motorfunc1,motorspeed1);
    motor('2', motorfunc2,motorspeed2);
  }
else if (buttonstate1 == 0 && buttonstate2 == 0 && (buttonstate3/255) == 1) {
     motorfunc1 = 'b';
     motorfunc2 = 'r';
     motor('1', motorfunc1,motorspeed1);
    motor('2', motorfunc2,motorspeed2);
  }
 else if (buttonstate1 == 0 && buttonstate2 == 1 && buttonstate3/255 == 1) {
     motorfunc1 = 'b';
     motorfunc2 = 'l';
    motor('1', motorfunc1,motorspeed1);
    motor('2', motorfunc2,motorspeed2);
  }

   else if (buttonstate1 == 1 && buttonstate2 == 0 && (buttonstate3/255) == 1) {
    motorfunc1 = 'b';
     motorfunc2 = 'b';
    
    motor('1', motorfunc1,motorspeed1);
    motor('2', motorfunc2,motorspeed2);
  }


   else if (buttonstate1 == 1 && buttonstate2 == 1 && (buttonstate3/255) == 1) {
    motor('1', motorfunc1,motorspeed1);
    motor('2', motorfunc2,motorspeed2);
  }
  
  motorspeed1=analogRead(A0)/4;
  motorspeed2=analogRead(A1)/4;
  buttonstate3=analogRead(A5)/4;
  buttonstate1=digitalRead(button1);
  buttonstate2=digitalRead(button2);



  lcd.setCursor(0, 1); // move cursor to (col, row)
  lcd.print(motorspeed1);
  lcd.setCursor(0, 2); // move cursor to (col, row)
  lcd.print(motorspeed2);
  delay(50);
    
}
