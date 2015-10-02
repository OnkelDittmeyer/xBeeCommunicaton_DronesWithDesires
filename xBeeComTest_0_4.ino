//drone motor library
#include <DroneMotor.h>

// SoftwareSerial is used to communicate with the XBee
#include <SoftwareSerial.h>



//receivingSerial
SoftwareSerial receiveData(2, 3); // Arduino RX, TX (XBee Dout, Din)
//sendingSerial
Serial sendingData;

//shiftReg setup
//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

//motor setup
//motor class going to be changed to single number setup, 16bit encoded for switchRegister/hbridge hardware
DroneMotor motorOne(13,12); //creates first motor, attached to pin 13 & 12

boolean motorOneSwitch = false;


void setup()
{

  
  receiveData.begin(9600);
  sendingData.begin(9600);
  sendingData.println("Start programm");
}

void loop()
{

  //structure
  //   letters: A,B,C,D,E,F switch specific motor boolean to true
  //  motors remain active as long as set to false again
  //   letters: a,b,c,d,e,f switch specific motor to boolean false
  
  if (receiveData.available())
  {
    char c = receiveData.read();
    switch (c)
    {

      case 'A':
        motorOneSwitch = true;
        break;

      case 'a':
        motorOneSwitch = false;
        break;
        
     default:
       //all off
       motorOneSwitch = false;
    }
  }
  
  motorOne.flapping(motorOneSwitch);

  //send data to serial
  //check all sensors for data
}



// ASCIItoHL
// Helper function to turn an ASCII value into either HIGH or LOW
int ASCIItoHL(char c)
{
  // If received 0, byte value 0, L, or l: return LOW
  // If received 1, byte value 1, H, or h: return HIGH
  if ((c == '0') || (c == 0) || (c == 'L') || (c == 'l'))
    return LOW;
  else if ((c == '1') || (c == 1) || (c == 'H') || (c == 'h'))
    return HIGH;
  else
    return -1;
}

// ASCIItoInt
// Helper function to turn an ASCII hex value into a 0-15 byte val
int ASCIItoInt(char c)
{
  if ((c >= '0') && (c <= '9'))
    return c - 0x30; // Minus 0x30
  else if ((c >= 'A') && (c <= 'F'))
    return c - 0x37; // Minus 0x41 plus 0x0A
  else if ((c >= 'a') && (c <= 'f'))
    return c - 0x57; // Minus 0x61 plus 0x0A
  else
    return -1;
}



