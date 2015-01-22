/*
 SMS receiver
 YOOOO Mojo ho ho ho

 This sketch, for the Arduino GSM shield, waits for a SMS message
 and displays it through the Serial port.

 created 25 Feb 2012
 by Javier Zorzano / TD

 This example is in the public domain.

 http://arduino.cc/en/Tutorial/GSMExamplesReceiveSMS

*/

// include the GSM library
#include <GSM.h>

// PIN Number for the SIM
#define PINNUMBER ""

// initialize the library instances
GSM gsmAccess;
GSM_SMS sms; // Store receiving SMS
GSM_SMS smsOut; // Store sending SMS

char senderNumber[20];// Array to hold the number a SMS is retreived from

void setup()
{
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.println("SMS Messages Receiver");

  // connection state
  boolean notConnected = true;

  // Start GSM connection
  while (notConnected)
  {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  Serial.println("GSM initialized");
  Serial.println("Waiting for messages");  
}

void loop()
{
  char c;
  //Set to char length when determined final message.
//  char txtMsg[ ] = "Thank you for trying TEST - TONE. Your message will play shortly *beep beep boop boop beep beep* :)";
  
  // If there are any SMS's available()
  if (sms.available())
  {
    // Get remote number
    sms.remoteNumber(senderNumber, 20);
    Serial.print(senderNumber);
    Serial.print(" ");
    
    // An example of message disposal
    // Any messages starting with # should be discarded
    if (sms.peek() == '#')
    {
      Serial.println("Discarded SMS");
      sms.flush();
    }

    // Read message bytes and print them
    while (c = sms.read())
      Serial.print(c);
      Serial.println();
    
    delay(1000); // Add delay for processing
    
//    // Add and send SMS to last caller
//    smsOut.beginSMS(senderNumber); // Begin Message
//    smsOut.print(txtMsg); //Add Text from Message
//    smsOut.endSMS(); //End the Message

    sms.flush();  // Delete incoming message from modem memory
//    smsOut.flush(); // Delete sent message from modem memory
  }
  delay(1000); //Add delay for processing
}



