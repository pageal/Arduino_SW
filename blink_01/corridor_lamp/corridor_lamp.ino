#include <VirtualWire.h>

const int LED = 13;
const int RELAY = 9;
const int MOTION = 8;
const int TX = 7;
const int TX_EN= 3;
const int RX = 6;

int TIME_ON = 20000; // milli-seconds the light will stay ON after motion is detected last time
int TIME_TO_LED_WISWITCH = 1000; // milli-seconds to between LED switch
int TIME_DELAY = 100; // loop delay time in milli-seconds

int motion_detected = 0;
int time_before_off = TIME_ON;
int led_switch_time = TIME_TO_LED_WISWITCH;

bool led_is_on = false; 

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(MOTION, INPUT);

  vw_set_tx_pin(TX);
  vw_set_rx_pin(RX);
  vw_set_ptt_pin(TX_EN);
  vw_set_ptt_inverted(true); // Required for DR3100

  vw_setup(1000);	 // Bits per sec
}

void switch_led(){
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
}

void send_motion_notification(bool b_on_off) { 
  String msg_prefix = "mp_v01_d01_";
  String msg = ""; 
  
  if(b_on_off == true)
  {
    msg = msg_prefix + "motion " + motion_detected;
  }else
  {
    msg = msg_prefix + "no_motion";
  }
  
  vw_send((uint8_t *)msg.c_str(), msg.length());
  vw_wait_tx(); // Wait until the whole message is gone
}

// the loop function runs over and over again forever
void loop() {
  
  // turn the lamp on (by relay's voltage HIGH) if motion is deected
  if(digitalRead(MOTION) == HIGH)
  {
    digitalWrite(RELAY, HIGH); 
//    send_motion_notification(true);
    time_before_off = TIME_ON;
    motion_detected++;
  }

  if(time_before_off > 0)
    time_before_off -= TIME_DELAY;
  else
  {
    // turn the lamp off (by relay's voltage LOW) if motion no motion for TIME_ON milli-seconds
    time_before_off = 0;
    if(digitalRead(MOTION) == LOW)
    {
      digitalWrite(RELAY, LOW);
      motion_detected = 0;
      
      // send several notifications to make sure at least one is arrived    
//      send_motion_notification(false);
//      delay(TIME_DELAY);           
//      send_motion_notification(false);
//      delay(TIME_DELAY);           
//      send_motion_notification(false);
    }
  }

  if(led_switch_time > 0)  
    led_switch_time -= TIME_DELAY;
  else
  {
    led_switch_time = TIME_TO_LED_WISWITCH;
    switch_led();
  }  
 
  delay(TIME_DELAY);              // wait for a second
}
