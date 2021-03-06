#include<Servo.h> //To control the servo motors
#include<LiquidCrystal.h>  //To control LCD displays (16 x 2)
String t;
Servo S1,S2; //Declaration of servo motor objects
int rs = 7;
int e = 6;
int d4 = 5;
int d5 = 4;
int d6 = 3;
int d7 = 2;
LiquidCrystal lcd(rs,e,d4,d5,d6,d7); //Intialization of LCD object
void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT); //Green LED
  pinMode(10,OUTPUT); //Red or YELLOW LED
  S1.attach(12); //Setting up the first servo motor
  S2.attach(11); //Setting up the second servo motor
  lcd.begin(16,2);//LCD dimension declaration
  lcd.print("Welcome!");//Intial message
  Serial.begin(9600); //Intializing communication 9600 bps
}

void loop() {
  // put your main code here, to run repeatedly:
  S1.write(0); //Setting the intial angle of S1 motor at 0 degrees
  S2.write(0); //Setting the intial angle of S1 motor at 0 degrees
  while(Serial.available()) //Capturing letters from the established serial connection
  {
    delay(10);
    char c = Serial.read();
    t += c;//t = t + c; (O, O+P = OP, OP + E = OPE, OPE + N = OPEN),OPEN+CLOSE =OPENCLOSE
  }
  if(t.length()>0) //go in if t has any string
  {
    if(t=="OPEN")//Comparing if t = OPEN
    {
      //if t is OPEN, that means you are authorized user, your fingerprint is authorized
      digitalWrite(13,HIGH); //Green light on!
      lcd.setCursor(0,1); //Location where you next text is going to be written
      lcd.clear();//This clears the screen
      lcd.print("Access Granted!");//print this msg
      //Set both servo's angle at 90 degrees to OPEN the door
      S1.write(90);
      S2.write(90);     
      delay(2000); //wait for 2 seconds
      //close the door, set both servos to intital position
      S1.write(0);
      S2.write(0);
      digitalWrite(13,LOW);//Turn it off the green light
      lcd.clear();
    }
    if(t=="CLOSE") //NOT AUTHORIZED, GO AWAY
    {
      digitalWrite(10,HIGH);//Turn on RED/YELLOW LED!
      lcd.setCursor(0,1);//location of text
      lcd.clear();//clear screen
      lcd.print("Access Denied!");//the unauthorize access warning
      delay(1000);
      digitalWrite(10,LOW);//turn off red led
      lcd.clear();
    }
    if(t=="BYE")//Real user, but don't want to access the garage
    {
      digitalWrite(13,HIGH);//Glow the green light
      lcd.setCursor(0,1);
      lcd.clear();
      lcd.print("BYE!");
      delay(1000);
      digitalWrite(13,LOW);//Turn off green light
    }
    t="";//EMPTY THE T STRING SO IT CAN TAKE FRESH INPUTS
  }
}
