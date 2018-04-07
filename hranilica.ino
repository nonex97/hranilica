// include the library code:
#include <TimeLib.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// initialize the library with the numbers of the interface pins dor the LCD
LiquidCrystal_I2C lcd(0x3F,16,2);


volatile boolean TurnDetected;
volatile boolean up;
const int PinCLK=2;                   
const int PinDT=3;                   
const int PinSW=4;                   
const int buttonPin = A3;            
int buttonState = 0;                  
int feedHour = 07;                   
int feedMinute = 30;
int feedTimer = 10;

int currentHours;
int currentMinutes;
int currentFeedHours;
int currentFeedMinutes;
int currentTimer;

int motor = 0;

int counter = 0;

// DEFINIRANJE VARIJABLI KOLIKO CE MOTOR BITI UPALJEN
unsigned long currentMillis;
long period = feedTimer * 1000; // VRIJEME BACANJA HRANE

void isr ()  {                    // Interrupt service routine is executed when a HIGH to LOW transition is detected on CLK
 if (digitalRead(PinCLK))         // this keeps an eye out for the rotary encoder being turned regardless of where the program is
   up = digitalRead(PinDT);       // currently exectuting - in other words, during the main loop this ISR will always be active
 else
   up = !digitalRead(PinDT);
 TurnDetected = true;
}


void setup ()  {
  pinMode(13,OUTPUT);
   // set up the LCD's number of columns and rows: 
  lcd.init();
  lcd.backlight();
  // setup the Rotary encoder
 pinMode(PinCLK,INPUT);
 pinMode(PinDT,INPUT);  
 pinMode(PinSW,INPUT);
 pinMode(buttonPin, INPUT);
 setTime(07, 29, 55, 26, 03, 2018); 
 attachInterrupt (0,isr,FALLING);   // interrupt 0 is always connected to pin 2 on Arduino UNO

 

}
  
void loop ()  {  //Main program loop - most things in here!
    static long virtualPosition=0;    // without STATIC it does not count correctly!!!
    lcd.setCursor(0, 0);
    printDigits(hour()); //call to print digit function that adds leading zeros that may be missing
    lcd.print(":");
    printDigits(minute());
    lcd.setCursor(0,1);
    lcd.print("1)");
    printDigits(feedHour);
    lcd.print(":");
    printDigits(feedMinute);
    lcd.setCursor(8,0);
    printDigits(feedTimer);
    lcd.setCursor(12,1);
 lcd.print("C:");
 lcd.print(counter);
    
    
    
// MAIN BREAKOUT "IF" SECION BELOW THAT MONITORS THE PUSH BUTTON AND ENTERS PROGRAMMING IF IT'S PUSHED 

 if (!(digitalRead(PinSW))) {      // check if pushbutton is pressed
                                   // if YES then enter the programming subroutine
    lcd.blink();   // Turn on the blinking cursor:
    currentHours = hour();  //needed or the hour will be zero each time you change the clock.
       do  {
            lcd.setCursor(0,0);   // put cursor at Time Hour  
            delay(500);   // Delay needed or same button press will exit do-while as while is checking for another button push!
            if (TurnDetected)  {        // do this only if rotation was detected
            if (up)
              currentHours = currentHours + 1;
            else
            currentHours = currentHours - 1;
            TurnDetected = false;          // do NOT repeat IF loop until new rotation detected
                               }
            // Here I change the hour of time -
            
            setTime(currentHours,minute(),0,01,01,2011);
            lcd.setCursor(0, 0);
            printDigits(hour());  // then re-print the hour on the LCD
         } while ((digitalRead(PinSW)));  // do this "do" loop while the PinSW button is NOT pressed
         lcd.noBlink();
         delay(1000);
     
       //   SET THE MINS
        
        lcd.blink();   // Turn on the blinking cursor:
       currentMinutes = minute();  //needed or the minute will be zero each time you change the clock.
       do  {
       lcd.setCursor(3,0);   // put cursor at Time Mins
       delay(500);   // Delay needed or same button press will exit do-while as while is checking for another button push!
           if (TurnDetected)  {       // do this only if rotation was detected
            if (up)
              currentMinutes = currentMinutes + 1;
            else
            currentMinutes = currentMinutes - 1;
            TurnDetected = false;          // do NOT repeat IF loop until new rotation detected
                               }
            // Here I change the min of time -
            
            setTime(hour(),currentMinutes,0,01,01,2011);
            lcd.setCursor(3, 0);
            printDigits(minute());  // then re-print the min on the LCD
         } while ((digitalRead(PinSW)));
         lcd.noBlink();
         delay(1000);
    
       //   SET THE TIMER
      
       lcd.blink();   // Turn on the blinking cursor:
       currentTimer = feedTimer;  //needed or the qty will be zero.
       do  {
       lcd.setCursor(8,0);   // put cursor at QTY
       delay(500);   // Delay needed or same button press will exit do-while as while is checking for another button push!
           if (TurnDetected)  {       // do this only if rotation was detected
            if (up)
              currentTimer = currentTimer + 1;
            else
            currentTimer = currentTimer - 1;
            TurnDetected = false;          // do NOT repeat IF loop until new rotation detected
                               }
            // Here I change the feed qty
            feedTimer = currentTimer;
            period = feedTimer * 1000;
            lcd.setCursor(8, 0);
            printDigits(feedTimer);
           } while ((digitalRead(PinSW)));
         lcd.noBlink();
         delay(1000);
         
     //   SET THE Feed Hour
      
       lcd.blink();   // Turn on the blinking cursor:
       currentFeedHours = feedHour;  //needed or will be zero to start with.
       do  {
       lcd.setCursor(2,1);   // put cursor at feed1hour
       delay(500);   // Delay needed or same button press will exit do-while as while is checking for another button push!
           if (TurnDetected)  {       // do this only if rotation was detected
            if (up)
              currentFeedHours = currentFeedHours + 1;
            else
            currentFeedHours = currentFeedHours - 1;
            TurnDetected = false;          // do NOT repeat IF loop until new rotation detected
                               }
            // Here I change the feed1 hour
            feedHour = currentFeedHours;
            lcd.setCursor(2,1);
            printDigits(feedHour);
           } while ((digitalRead(PinSW)));
         lcd.noBlink();
         delay(1000);  
  
      //   SET THE Feed Mins
        
       lcd.blink();   // Turn on the blinking cursor:
       currentFeedMinutes = feedMinute; //needed or will be zero to start with.
       do  {
       lcd.setCursor(5,1);   // put cursor at feed1minute
       delay(500);   // Delay needed or same button press will exit do-while as while is checking for another button push!
           if (TurnDetected)  {       // do this only if rotation was detected
            if (up)
              currentFeedMinutes = currentFeedMinutes + 15;
            else
            currentFeedMinutes = currentFeedMinutes - 15;
            TurnDetected = false;          // do NOT repeat IF loop until new rotation detected
                               }
            // Here I change the feed1 minute
            feedMinute = currentFeedMinutes;
            lcd.setCursor(5,1);
            printDigits(feedMinute);
           } while ((digitalRead(PinSW)));
         lcd.noBlink();
         delay(1000);   
 
  }  // end of main IF rotary encoder push button checker

  if(hour() == feedHour && minute() == feedMinute && second() == 0) {
    motor = 1;
    currentMillis = millis();
    
  }

  if(motor == 1) {
    if(millis() < currentMillis + period) {
      digitalWrite(13,HIGH);
    } else {
      digitalWrite(13,LOW);
      motor = 0;
      counter = counter + 1;
    }
  }
}   // End of main Loop

void printDigits(int digits){   // utility function for digital clock display: prints leading 0
   if(digits < 10)
    lcd.print('0');
    lcd.print(digits);
 }

 
