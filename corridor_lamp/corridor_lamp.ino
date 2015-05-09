/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */

int LED = 13;
int RELAY = 9;
int MOTION = 8;

int TIME_ON = 20000; // milli-seconds the light will stay ON after motion is detected last time
int TIME_BLINK = 500; // milli-seconds to between blinks

int motion_detected = 0;
int time_before_off = TIME_ON;
bool led_is_on = false; 

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(MOTION, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  
  if(digitalRead(MOTION) == HIGH)
  {
    motion_detected++;
    time_before_off = TIME_ON;
    digitalWrite(RELAY, HIGH);
  }

  if(motion_detected > 0)
  {
    //if(motion_detected > 1)
    {
       // digitalWrite(RELAY, HIGH);   // turn the RELAY on (HIGH is the voltage level)
    }
    
    motion_detected--;
  }
  else 
    motion_detected = 0;

  if(time_before_off > 0)
  {
    time_before_off -= TIME_BLINK;
  }
  else
  {
    time_before_off = 0;
    if(motion_detected == 0)
      digitalWrite(RELAY, LOW);    // turn the RELAY off by making the voltage LOW
  }
  
  if(led_is_on == false)  
  {
      digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
      led_is_on = true;
  }
  else
  {
    digitalWrite(LED, LOW);   // turn the LED on (HIGH is the voltage level)
    led_is_on = false;
  }
  
  delay(TIME_BLINK);              // wait for a second
}
