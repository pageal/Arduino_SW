#include <VirtualWire.h>


const int led_pin = 13;
const int transmit_pin = 7;
const int receive_pin = 6;
const int transmit_en_pin = 3;

void setup()
{
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
}

byte count = 1;

void loop()
{
  String msg_prefix = "mp_v01_d01_";
  String msg = ""; 
  static bool on_off = false;
  
  on_off = !on_off;
  if(on_off == true)
  {
    msg = msg_prefix + "motion " + count;
  }else
  {
    msg = msg_prefix + "no_motion" + count;
  }
  
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg.c_str(), msg.length());
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  delay(2000);
  count = count + 1;
}
