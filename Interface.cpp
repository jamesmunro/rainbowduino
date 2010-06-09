#include "WProgram.h"
#include "Interface.h"
#include "Rainbow.h"
#include "Demos.h"
#include <Wire.h>

extern Rainbow myRainbow;

extern unsigned char demoIndex;

//for receive color data from serial port
extern unsigned short receiveBuffer[8][8];//defined in data.h

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
  static unsigned char cmd[7]={
    0,0,0,0,0,0,0    };//'R'+type+shift+red+green+blue+ASCII/index
  unsigned char receiveOK = 0;

  //check the commmand
  receiveOK = checkCmd(cmd);

  //reslove the command
  if(receiveOK){
    resloveCmd(cmd);
  }
}

//receive and process the data
void Interface::processData(void)
{
  //when get 0xAA 0x55,means data transmitting over
  if(Serial.available()){
    unsigned char t1 = Serial.read();
    if(0xAA == t1){
      char t2;
      while(1){
        if(Serial.available()>0){
          break;
        }
      }
      t2 = Serial.read();
      if(0x55 == t2){
        serialState = COMMAND_MODE;
        myRainbow.lightAll();
      }
      else{
        myRainbow.fillColorBuffer(t1);
        myRainbow.fillColorBuffer(t2);
      }
    }
    else{
      myRainbow.fillColorBuffer(t1);
    }
  }
}

unsigned char Interface::checkCmd(unsigned char cmd[7])
{
  static unsigned char i = 1;
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
  return receiveOK;
}
//reslove all kinds of command
void Interface::resloveCmd(unsigned char cmd[7])
{
  unsigned char shift = 0;
  unsigned char red = 0;
  unsigned char green = 0;
  unsigned char blue = 0;
  unsigned char ASCII = 0;
  unsigned char index = 0;
  unsigned short color = 0;//0x0bgr;

  demoIndex = 255;//means not run demo
  
  switch (cmd[1]){
  case DISP_PRESET_PIC:
    {
      shift = cmd[2];
      index = cmd[6];
      myRainbow.dispPresetPic(shift,index);
      break;
    }
  case DISP_CHAR:
    {

      shift = cmd[2];
      red = cmd[3];
      green = cmd[4];
      blue = cmd[5];
      ASCII = cmd[6];
      color = blue;//0x0bgr;
      color = (color<<8)|(green<<4)|red;
      myRainbow.dispChar(ASCII,color,shift);
      break;
    }
  case DISP_COLOR:
    {
      red = cmd[3];
      green = cmd[4];
      blue = cmd[5];
      ASCII = cmd[6];
      color = blue;//0x0bgr;
      color = (color<<8)|(green<<4)|red;

      myRainbow.dispColor(color);
      break;
    }
  case SET_DOT:
    {
      unsigned char line = cmd[2];
      unsigned char column = cmd[3];
      red = cmd[4];
      green = cmd[5];
      blue = cmd[6];
      color = blue;//0x0bgr;
      color = (color<<8)|(green<<4)|red;

      myRainbow.lightOneDot(line,column,color,OTHERS_ON);
      break;
    }
  case DISP_RANDOM:
    {//not implement yet
      demoIndex = cmd[2];
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







