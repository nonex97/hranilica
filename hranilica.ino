// DEFINIRANJE LIBRARY-a
#include <TimeLib.h>

String timerHours = "09";
String timerMinutes = "04";
String timerSeconds = "05";

int motor = 0;

unsigned long currentMillis;
long period = 15000;


void setup()  {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  setTime(9, 4, 0, 26, 03, 2018);
}

void loop() {
  int hours = hour();
  int minutes = minute();
  int seconds = second();
  String hoursPrint = String(hours);
  String minutesPrint = String(minutes);
  String secondsPrint = String(seconds);
  
  if (hours < 10) {
    hoursPrint = "0" + hoursPrint;
  }
  if (minutes < 10) {
    minutesPrint = "0" + minutesPrint;
  }
  if (seconds < 10) {
    secondsPrint = "0" + secondsPrint;
  }

  if(timerHours == hoursPrint && timerMinutes == minutesPrint && timerSeconds == secondsPrint) {
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






