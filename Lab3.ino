
#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
#define ENABLE 5
#define DIRA 3
#define DIRB 4

DS3231 clock;
RTCDateTime dt;
int i;
 
void setup() {
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
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
  if (dt.second >= 30) {
    Serial.println("PWM stop");
    lcd.setCursor(0, 0);
    lcd.print("Time:");
    lcd.print(dt.hour);
    lcd.print(":");
    lcd.print(dt.minute);
    lcd.print(":");
    lcd.print(dt.second);
    
    lcd.setCursor(0, 1);
    lcd.print("Dir:C Speed:0   ");
    analogWrite(ENABLE,LOW); 
  }
  else if (dt.second >= 0){
    Serial.println("PWM full speed");
    lcd.setCursor(0, 0);
    lcd.print("Time:");
    lcd.print(dt.hour);
    lcd.print(":");
    lcd.print(dt.minute);
    lcd.print(":");
    lcd.print(dt.second);
    
    lcd.setCursor(0, 1);
    lcd.print("Dir:C Speed:Full");
    //---PWM example, full speed then slow
    analogWrite(ENABLE,255); //enable on
    digitalWrite(DIRA,HIGH); //one way
    digitalWrite(DIRB,LOW);
    //delay(2000); 
  }
  delay(1000);
  /*
  analogWrite(ENABLE,180); //half speed
  delay(2000);
  analogWrite(ENABLE,128); //half speed
  delay(2000);
  analogWrite(ENABLE,50); //half speed
  delay(2000);
  analogWrite(ENABLE,128); //half speed
  delay(2000);
  analogWrite(ENABLE,180); //half speed
  delay(2000);
  analogWrite(ENABLE,255); //half speed
  delay(2000);
  digitalWrite(ENABLE,LOW); //all done
  delay(10000);*/
  
}
   
