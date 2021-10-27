#include <SoftwareSerial.h>
String Message;
String PhoneNumber;
//MC60 TX,RX
SoftwareSerial GPRS(15, 14); 
void setup()
{
  //Incase MC60 Powerkey is connected to a special pin of Arduino
  digitalWrite (A15, HIGH);   
  GPRS.begin(9600);
  Serial.begin(9600);
  GPRS.println("AT+CMGF=1");
  delay(1000);
}

void loop()
{
  // Counting letters of the sms 
  int lettercount; 
  Serial.println("Enter the phone number you want to send sms to: ");
  Serial.println ("With '+' and contry code (e.g. +xxxxxxxxxxxx)");
  while (Serial.available() == 0) {} //Wait for the input
  PhoneNumber = Serial.readString(); Serial.print (PhoneNumber);
   //length of the PhoneNumber
  lettercount = PhoneNumber.length();
  Serial.println("Enter the Message");
  //remove the last (Next Line) charcter of the PhoneNumber from the Serial.read
  PhoneNumber.remove((lettercount - 1), 1); 
  //Wait for the input
  while (Serial.available() == 0) {} 
  Message = Serial.readString(); Serial.println(Message);
  GPRS.println("AT+CMGS=\"" + PhoneNumber + "\"");
  delay(500);
  GPRS.print(Message);
  // ctrl+Z
  GPRS.write( 0x1a ); 
  delay(500);
}
