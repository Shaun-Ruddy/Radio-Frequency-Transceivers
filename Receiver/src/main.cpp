//// Adding Libraries 
#include <Arduino.h>
#include <SPI.h>             /* to handle the communication interface with the modem*/
#include <nRF24L01.h>        /* to handle this particular modem driver*/
#include <RF24.h>            /* the library which helps us to control the radio modem*/
#define led_pin 3            /* Connect LED anode to D3 (PWM pin) */


//*This is the receiver code

RF24 radio(7, 8);             /* Creating instance 'radio' ( CE, CSN )   CE -> D7 | CSN -> D8 */                               
const byte Address[6] = "00009"; /* Address from which data to be received */

void setup() {
  Serial.begin(9600);            /* Set baudrate for Serial Port to 9600 */
  radio.begin();                 /* Activate the modem */
  radio.openReadingPipe(1, Address); /* Set the address of receiver from which program will receive data */
}

void loop() {
  radio.startListening();        /* Set modem in Receiver mode */
  
  if (radio.available()) {
    while (radio.available()) {  /* Loop until receiving valid data */
      char rx_data[32] = "";     /* Variable to store received data (string) */
      radio.read(&rx_data, sizeof(rx_data)); /* Read the received data and store in 'rx_data' */
      Serial.print("Received Data: ");
      Serial.println(rx_data);   /* Print received data on Serial Monitor */
    }
  } 
  else {
    Serial.println("Not Receiving !!!"); /* If not receiving valid data, print "Not Receiving !!!" on Serial Monitor */
  }
}