#include "Rainbow.h"
#include "Interface.h"
#include <NewSoftSerial.h>
#include <EEPROM.h>
#include <Wire.h>
#include <avr/pgmspace.h>

//for receive color data from serial port
extern unsigned short serialColorData[8][8];//defined in data.h

//color data format :0x0bgr
unsigned short color[8] = {WHITE,RED,GREEN,RANDOM,BLUE,YELLOW,AQUA,VIOLET};

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
  //myRainbow.closeAll();//close all leds
  
}

void loop()
{
    /**The following is just some demo to test Ranibow class,you can add more **********/
    
    
    //just display the static led matrix,which can display the color data received from serial
    //myRainbow.lightAll(serialColorData);
    
    //flash led matrix in several patterns, 
    //flashMatrixDemo(color);
    
    //light 12v led strip in 0~9 number way
    /*static int colorNum = 0;
    for(int i = 0; i < 10; i++)
    {
      delay(1000);
      //display 0~9 with specific color
      LightLedStripNumberDemo(i,color[colorNum]);
    }
    if(++colorNum == 8) colorNum = 0;
    */
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
  
  //process the interface
  myInterface.process();

}

/****************************************************************/

 //some demo to test rainbow member funtions

/****************************************************************/

void flashMatrixDemo(unsigned short *color)
{
 int i = 0;
 int j = 0;
 
 //all with the same color
 for(i = 0; i < 8; i++)
 {
   delay(200);
   myRainbow.lightAll(color[i]);
 }
 
 //sweep one line while others off
 for(i = 0; i < 8; i++)
 {
   delay(100);
   //myRainbow.lightOneLine(i,color[i],OTHERS_OFF);
   myRainbow.lightOneLine(i,serialColorData[i],OTHERS_OFF);
 }
 
 //sweep one line while others on
 for(i = 7; i >= 0; i--)
 {
   delay(100);
   //myRainbow.lightOneLine(i,color[i],OTHERS_ON);
   myRainbow.lightOneLine(i,serialColorData[i],OTHERS_ON);
 }
 
 //sweep one column while others off
 for(i = 0; i < 8; i++)
 {
   delay(100);
   //myRainbow.lightOneColumn(i,color[i],OTHERS_OFF);
   myRainbow.lightOneColumn(i,serialColorData,OTHERS_OFF);
 }
 
 //sweep one colum while others on
 for(i = 7; i >= 0; i--)
 {
   delay(100);
   //myRainbow.lightOneColumn(i,color[i],OTHERS_ON);
   myRainbow.lightOneColumn(i,serialColorData,OTHERS_ON);
 }
 
 //sweep each dot while others off
 for(i = 0; i < 8; i++)
   for(j = 0;j < 8; j++)
   {
     delay(50);
     //myRainbow.lightOneDot(i,j,color[j],OTHERS_OFF);
     myRainbow.lightOneDot(i,j,serialColorData[i][j],OTHERS_OFF);
   }
   
 //sweep each dot while others on
 for(i = 7; i >= 0; i--)
   for(j = 7;j >= 0; j--)
   {
     delay(50);
     //myRainbow.lightOneDot(i,j,color[j],OTHERS_ON);
     myRainbow.lightOneDot(i,j,serialColorData[i][j],OTHERS_ON);
   }
  
  //sweep the diagonal line from top left to riht bottom while others off
  for(i = 0; i < 16; i++)
  {
    delay(100);
    //myRainbow.lightOneDiagonal(i,LEFT_BOTTOM_TO_RIGHT_TOP,color[i&0x07],OTHERS_OFF);
    myRainbow.lightOneDiagonal(i,LEFT_BOTTOM_TO_RIGHT_TOP,serialColorData,OTHERS_OFF);
  }
  
  //sweep the diagonal line from riht bottom to top left while others on
  for(i = 15; i >= 0; i--)
  {
    delay(100);
    //myRainbow.lightOneDiagonal(i,LEFT_BOTTOM_TO_RIGHT_TOP,color[i&0x07],OTHERS_ON);
    myRainbow.lightOneDiagonal(i,LEFT_BOTTOM_TO_RIGHT_TOP,serialColorData,OTHERS_ON);
  }

  //sweep the diagonal line from bottom left to riht top while others off
  for(i = 0; i < 16; i++)
  {
    delay(100);
    //myRainbow.lightOneDiagonal(i,LEFT_TOP_TO_RIGHT_BOTTOM,color[i&0x07],OTHERS_OFF);
    myRainbow.lightOneDiagonal(i,LEFT_TOP_TO_RIGHT_BOTTOM,serialColorData,OTHERS_OFF);
  }

  //sweep the diagonal line from riht top to bottom left while others on
  for(i = 15; i >= 0; i--)
  {
    delay(100);
    //myRainbow.lightOneDiagonal(i,LEFT_TOP_TO_RIGHT_BOTTOM,color[i&0x07],OTHERS_ON);
    myRainbow.lightOneDiagonal(i,LEFT_TOP_TO_RIGHT_BOTTOM,serialColorData,OTHERS_ON);
  }
  
  //sweep 1/4 part of matrix
  delay(200);
  static int k = 0;
  
  for(int m = 0; m < 4; m++)
  {
    for(i = 0; i < 4; i++)
    {
      for(j = 0; j < (i+1)*2; j++)
      {
        myRainbow.lightOneDot(3-i,3-i+j,color[k],OTHERS_ON);
      }
    }
    if(8 == ++k) k = 0;
  
    delay(500);
    for(i = 0; i < 4; i++)
    {
      for(j = 0; j < (i+1)*2; j++)
      {
        myRainbow.lightOneDot(3-i+j,4+i,color[k],OTHERS_ON);
      }
    }
    if(8 == ++k) k = 0;
    delay(500);
    for(i = 0; i < 4; i++)
    {
      for(j = 0; j < (i+1)*2; j++)
      {
        myRainbow.lightOneDot(4+i,3-i+j,color[k],OTHERS_ON);
      }
    }
    if(8 == ++k) k = 0;
    delay(500);
    for(i = 0; i < 4; i++)
    {
      for(j = 0; j < (i+1)*2; j++)
      {
        myRainbow.lightOneDot(3-i+j,3-i,color[k],OTHERS_ON);
      }
    }
    if(8 == ++k) k = 0;
  }
}

/***********************************************************
function: light 12v led strip in the way of number 0~9 
(http://www.seeedstudio.com/depot/3w-rgb-led-strip-common-anode-12v-p-351.html?cPath=32_21)
hardware connection way:
7 picese of led trips, in the following pattern:

          ---   ->strip0     
strip5<- |   |  ->strip1
          ---   ->strip6
strip4<- |   |  ->strip2
          ---   ->strip3
          
1. connect +12v of all 7strips to VCC1 of rainbowduino
2. connect RGB of strip0 to R8 G8 B8 of rainbowduino.(note: it is in inverse way)
3. connect RGB of strip1 to R7 G7 B7 of rainbowduino.
4. ...
...
8 connect RGB of strip6,to R1 G1 B1 of rainbowduino.

In this way, 7 strips is just like 7 dots of the firt line of led matrix. So you can 
control them like the following.

PS: you can add another 7 led strips and connect +12v to VCC2, just like the second line of led matrix,
in which way you can control two numbers. Add more group, getting more numbers, and max is 8 of cource.
************************************************/

void LightLedStripNumberDemo(int num,unsigned short color)
{
  //light the first line leds
  myRainbow.lightOneLine(0,color,OTHERS_OFF);
  
  //close the specific strip to get the number effect
  switch (num)
  {
    case 0: myRainbow.closeOneDot(0,6);break;
    case 1: myRainbow.closeOneLine(0);myRainbow.lightOneDot(0,1,color,OTHERS_ON);myRainbow.lightOneDot(0,2,color,OTHERS_ON);break;
    case 2: myRainbow.closeOneDot(0,2);myRainbow.closeOneDot(0,5);break;
    case 3: myRainbow.closeOneDot(0,4);myRainbow.closeOneDot(0,5);break;
    case 4: myRainbow.closeOneDot(0,0);myRainbow.closeOneDot(0,3);myRainbow.closeOneDot(0,4);break;
    case 5: myRainbow.closeOneDot(0,1);myRainbow.closeOneDot(0,4);break;
    case 6: myRainbow.closeOneDot(0,1);break;
    case 7: myRainbow.closeOneDot(0,3);myRainbow.closeOneDot(0,4);myRainbow.closeOneDot(0,5);myRainbow.closeOneDot(0,6);break;
    case 8: break;
    case 9: myRainbow.closeOneDot(0,4);break;
    default:break;
  }
}







