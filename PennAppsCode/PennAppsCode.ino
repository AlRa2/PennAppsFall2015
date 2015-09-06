#include <SPI.h>
#include <Arduino.h>
#include <string.h>
#if not defined (_VARIANT_ARDUINO_DUE_X) && not defined (_VARIANT_ARDUINO_ZERO)
  #include <SoftwareSerial.h>
#endif

#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"


#define FACTORYRESET_ENABLE         1
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"
//#define 
//hardware SPI, using SCK/MOSI/MISO //hardware SPI pins and then user selected CS/IRQ/RST 
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

//Initializing LED Pins to be used. Not sure so just going to use random pins at rhe moment
int ledPin1 = 1; //Letter A
int ledPin2 = 2; //Letter B
int ledPin3 = 3; //Letter C
int ledPin4 = 4;//Letter D
int ledPin5 = 5; //Letter E
int ledPin6 = 6; // Letter F
int ledPin7 = 9; //Letter G

//just a little helper to help with the error
void error(const __FlashStringHelper*err){
  Serial.println(err);
  while(1);
}

// function prototypes over in packetparser.cpp

uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);

// the packet buffer
extern uint8_t packetbuffer[];

int counter;
float recieve_data;

void setup(void) {
  // put your setup code here, to run once:
  
  
  Serial.begin(115200);

  if (!ble.begin(VERBOSE_MODE))
  {
    error(F("Initialization failed. could not find the board"));
    Serial.println("Make sure the board is connected rightly");
  }
  else{
    Serial.println("OK. Board initialized ready to recieve programs");
  }
  //Performing 1 factory reset on the board to remove an left over code and h=to make sure that the 
  //board is working correctly

  if (FACTORYRESET_ENABLE)
  {
    Serial.println("Performing factory reset: ");
    if (!ble.factoryReset()){
     error(F("There was a problem with the factory reset. Factory reset could not happen"));
     error(F("Please check board and try again"));
    }
    else{
      Serial.println("Factory reset possible. we are a go");
    }
  }
  ble.echo(false); //This deisables the command echo from the setup

  Serial.println("Requesting info about bluefruit");
  ble.info();
  Serial.println("Recieving information from an ios device");
  Serial.println("Controlling LED's with the data recieved");
  //How on earth am i going to receive information via bluetooth. 
  Serial.println();

  while(!ble.isConnected()){
    delay(500);
  }
  //Change Mode LED activity
  
/*if(ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION))
{
  Serial.println(F("Change LED Activity to " MODE_LED_BEHAVIOUR));
  ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);
}*/
  //Set Bluefruit to DATA Mode
  Serial.println(F("Switching to Data Mode. We are ready to recieve packets now"));
  ble.setMode(BLUEFRUIT_MODE_DATA);
  Serial.println(F("****************************************"));

}

void loop(void) {
  // put your main code here, to run repeatedly:
  //Recieving packets and processing the packets to do what i want it to do
  //value to recieve the packets is about to be initialized
  
  uint16_t default_word = readPacket(&ble, BLE_READPACKET_TIMEOUT);
  
  uint8_t len = readPacket(&ble, BLE_READPACKET_TIMEOUT);
  if(len==0) return;

  //Firt packet is recieved. Do stuff with it. I am going to initalize the pins to the letters
  //up top
   if (packetbuffer[1] == 'A')
   {
    digitalWrite(ledPin1, HIGH);
    //The packets is sent with 3 information 
    //1 is socket
    //2 is the buffer
    //3 is the size of the struct that is being sent
    //4 is 0
    //Do something
   }
  // else[
  // digitalWrite(ledPin5, LOW);
   //do some more things
   if (packetbuffer[1] = 'B'){
    digitalWrite(ledPin2, HIGH);
   }
   if (packetbuffer[1] = 'C'){
    digitalWrite(ledPin3 = HIGH);
   
   }
   if (packetbuffer[1] = 'D'){
     digitalWrite(ledPin4 = HIGH);
     
   }
  

}


