#include "WProgram.h"
#include "Interface.h"
#include "Rainbow.h"
#include <NewSoftSerial.h>
#include <EEPROM.h>
#include <Wire.h>

extern Rainbow myRainbow;
//extern unsigned short serialColorData[8][8];//defined in data.c

Interface::Interface(){
}

//initialization all interfaces including serial and I2C
void Interface::init(void)
{
  //Initalize serial state
  serialState = COMMAND_MODE;

  //Initialize serial interface
  Serial.begin(BAUDRATE);

  //Initiallize I2C interface
#ifdef I2C_MASTER
  Wire.begin();
#else 
  Wire.begin(I2C_ADDR);//slave has an address
#endif;
}

//pocess serial and I2C interface 
void Interface::process(void)
{
  processSerial();
  processI2C();
}

//process serial interface
void Interface::processSerial(void)
{
  switch (serialState){
  case COMMAND_MODE:
    {
      processCmd();
      break;
    }//when in command mode,receive and reslove it 
  case DATA_MODE:
    {
      processData();
      break;
    }//when in data mode, receive and process it
  default:
    break;
  }
}

//process I2C interface data
void Interface::processI2C(void)
{
}

//receive and resolve the command
void Interface::processCmd(void)
{
  static unsigned char cmd[7]={   0,0,0,0,0,0,0    };//'R'+type+shift+red+green+blue+ASCII/index
  
  static unsigned char i = 1;
  unsigned short color = 0;//0x0bgr
  static unsigned char gotFirstFlag = 0;
  unsigned char receiveOK = 0;

  //read command
  if(Serial.available()){
    if(gotFirstFlag){
      cmd[i++] = Serial.read();
      if(7 == i){
        receiveOK = 1;
        gotFirstFlag = 0;
        i = 1;
      }
    }
    else{
      cmd[0] = Serial.read();
      if(cmd[0] == 'R'){
        gotFirstFlag = 1;
      }
    }
  }
  //reslove command
  if(receiveOK){
    unsigned char shift = cmd[2];
    unsigned char red = cmd[3];
    unsigned char green = cmd[4];
    unsigned char blue = cmd[5];
    unsigned char ASCII = cmd[6];//case cmd is ASCII
    unsigned char index = cmd[6];//case cmd is preset picture
    color = blue;
    color = (color<<8)|(green<<4)|red;
    switch (cmd[1]){
    case DISP_PRESET_PIC:
      {
        myRainbow.dispPresetPic(shift,index);
        break;
      }
    case DISP_CHAR:
      {
        myRainbow.dispChar(ASCII,color,shift);
        break;
      }
    case DISP_COLOR:
      {
        myRainbow.dispColor(color);
        break;
      }
    case CHANGE_TO_DATA:
      {
        serialState = DATA_MODE;
        break;
      }
    default:
      break;
    }
  }
}

//receive and process the data
void Interface::processData(void)
{
}




