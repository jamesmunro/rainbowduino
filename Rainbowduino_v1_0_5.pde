#include "Rainbow.h"
#include "Interface.h"
#include "Demos.h"
#include <Wire.h>
#include <avr/pgmspace.h>

//void (*f) (void) = NULL; /* 声明一个函数指针 */

unsigned char demoIndex = 255;

//color data format :0x0bgr
unsigned short color[8] = {
  WHITE,RED,GREEN,RANDOM,BLUE,YELLOW,AQUA,VIOLET};

//preinstantiate Rainbow object
Rainbow myRainbow = Rainbow();

//preinstantiate Interface object
Interface myInterface = Interface();

//Join I2C bus as master or slave
#define I2C_MASTER


//=============================================================
void setup()
{
  myInterface.init();
  myRainbow.init();
  myRainbow.lightAll();

}

void loop()
{
  /**The following is just some demo to test Ranibow class,you can add more **********/
  myInterface.process();

  switch (demoIndex){
  case 0:
    {
      flashMatrixDemo();//flash led matrix in several patterns, 
      break;
    }
  case 1:
    {
      lightLedStripNumberDemo();//light 12v led strip in 0~9 number way
      break;
    }
  default: 
    break;
  }


}

//= //Timer1 interuption service routine=========================================
ISR(TIMER1_OVF_vect)         
{
  //sweep 8 lines to make led matrix looks stable
  static unsigned char line=0,level=0;

  flash_line(line,level);

  line++;
  if(line>7)
  {
    line=0;
    level++;
    if(level>15)
    {
      level=0;
    }
  }  

  //process the interface,be carefull:should not be here if it is too large -by Icing 2010/6/9 1:02
  //myInterface.process(); 

}










