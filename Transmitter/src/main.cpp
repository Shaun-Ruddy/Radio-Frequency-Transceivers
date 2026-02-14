#include <Arduino.h>

//*This is the transmitter code
#include <SPI.h>                  /* to handle the communication interface with the modem*/
#include <nRF24L01.h>             /* to handle this particular modem driver*/
#include <RF24.h>                 /* the library which helps us to control the radio modem*/

RF24 radio(7, 8);                    /* Creating instance 'radio'  ( CE , CSN )   CE -> D7 | CSN -> D8 */                              
const byte Address[6] = "00009";     /* Address to which data to be transmitted*/

void setup() {
  Serial.begin(9600);              /* Start Serial communication */
  radio.begin();                   /* Activate the modem */
  radio.openWritingPipe(Address);  /* Set the address of the receiver */
}

void loop() {
  // Send the "Hello World" message repeatedly
  radio.stopListening();            /* Set modem in transmission mode */
  
  const char message[] = "Hello World";   /* The message you want to send */
  radio.write(&message, sizeof(message)); /* Send the message over NRF24L01 */

  Serial.print("Transmitting: ");
  Serial.println(message);           /* Print the message on serial monitor */
  
  delay(1000);  /* Wait for 1 second before sending again */
}
