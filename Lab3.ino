
#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
#define ENABLE 13
#define DIRA 12
#define DIRB 11
#define button 19

DS3231 clock;
RTCDateTime dt;
int x = 0;
 
void setup() {
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.println("Initialize RTC module");
  // Initialize DS3231
  clock.begin();
  // Manual (YYYY, MM, DD, HH, II, SS
  // clock.setDateTime(2016, 12, 9, 11, 46, 00);
  
  // Send sketch compiling time to Arduino
  clock.setDateTime(__DATE__, __TIME__);  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2); 
  Serial.begin(9600);
}

void loop() {
  dt = clock.getDateTime();

  Serial.print("Raw data: ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");
  
// Code that starts the motor at new minute and stops after 30 secs
// Only runs in Clockwise direction.
  if (digitalRead(button) == LOW) {
    buttonPress();
  }

  if (dt.second >= 30) {
    Serial.println("PWM stop");
    printTime();
    
    if (x == 0)
      clockwise();
    else
      CC();
      
    lcd.print("SPD:0   ");
    analogWrite(ENABLE,LOW); 
  }
  else if (dt.second >= 0){
    Serial.println("PWM full speed");
    printTime();
    
    if (x == 0)
      clockwise();
    else
      CC();
      
    lcd.print("SPD:FULL");
  }
    
  delay(500);
  
}

void printTime(){
  lcd.setCursor(0, 0);
    lcd.print("Time:");
    if (dt.hour < 10) {
      lcd.print("0");
      lcd.print(dt.hour);
    }
    else
      lcd.print(dt.hour);
    lcd.print(":");
    if (dt.minute < 10){
      lcd.print("0");
      lcd.print(dt.minute);
    }
    else
      lcd.print(dt.minute);
    lcd.print(":");
    if (dt.second < 10){
      lcd.print("0");
      lcd.print(dt.second);
    }
    else
      lcd.print(dt.second);
    
    lcd.setCursor(0, 1);
}

void buttonPress() {
  x++;
  x = x % 2;
}

void clockwise() {
  lcd.print("Dir:C  ");
    //---PWM example, full speed then slow
    analogWrite(ENABLE,255); //enable on
    digitalWrite(DIRA,HIGH); //one way
    digitalWrite(DIRB,LOW);
}

void CC() {
  lcd.print("Dir:CC ");
    //---PWM example, full speed then slow
    analogWrite(ENABLE,255); //enable on
    digitalWrite(DIRA,LOW); //one way
    digitalWrite(DIRB,HIGH);
}
   
