// DEFINIRANJE LIBRARY-a
#include <TimeLib.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// INICIJALIZACIJA DISPLAYA
LiquidCrystal_I2C lcd(0x3F,16,2); // PROVJERITI MOZDA JE 0x27

// DEFINIRANJE VARIJABLI ZA VRIJEME PALJENJA MOTORA
String timerHours = "09";
String timerMinutes = "04";
String timerSeconds = "05";

// DEFINIRANJE VARIJABLE ZA PALJENJE MOTORA
int motor = 0;

// DEFINIRANJE VARIJABLI KOLIKO CE MOTOR BITI UPALJEN
unsigned long currentMillis;
long period = 10000; // VRIJEME BACANJA HRANE

// DEFINIRANJE PINA ZA RELEJE
int relayPin = 5;

// DEFINIRANJE PINOVA ZA ROTARY ENCODER
const int PinCLK = 2;
const int PinDT = 3;
const int PinSW = 4;

// DEFINIRANJE PINA ZA TIPKU
const int buttonPin = 6;

// DEFINIRANJE VARIJABLE ZA MANUALNO PALJENJE MOTORA
int buttonState = 0;


void setup()  {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
  pinMode(13, OUTPUT); // ZA DEBBUGING
  setTime(9, 4, 0, 26, 03, 2018); // INICIJALNO POSTAVLJANJE VREMENA
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("TIME:");
  lcd.setCursor(0,1);
  lcd.print("ON:");
  lcd.setCursor(10,1);
  lcd.print("FOR:");
}

void loop() {
  int hours = hour();
  int minutes = minute();
  int seconds = second();
  String hoursPrint = String(hours);
  String minutesPrint = String(minutes);
  String secondsPrint = String(seconds);
  int periodPrint = period/1000;
  Serial.println(periodPrint);
  
  if (hours < 10) {
    hoursPrint = "0" + hoursPrint;
  }
  if (minutes < 10) {
    minutesPrint = "0" + minutesPrint;
  }
  if (seconds < 10) {
    secondsPrint = "0" + secondsPrint;
  }

  lcd.setCursor(5,0);
  lcd.print(hoursPrint);
  lcd.print(":");
  lcd.print(minutesPrint);
  lcd.print(":");
  lcd.print(secondsPrint);
  lcd.setCursor(3,1);
  lcd.print(timerHours);
  lcd.print(":");
  lcd.print(timerMinutes);
  lcd.setCursor(14,1);
  lcd.print(periodPrint);

  if(timerHours == hoursPrint && timerMinutes == minutesPrint && timerSeconds == secondsPrint) {
    motor = 1;
    currentMillis = millis();
  }

  // MANUALNO PALJENJE MOTORA
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH) {
    motor = 1;
    currentMillis = millis();
  }

  if(motor == 1) {
    if(millis() < currentMillis + period) {
      digitalWrite(13,HIGH);
    } else {
      digitalWrite(13,LOW);
      motor = 0;
    }
  }
  
delay(1000);

}
