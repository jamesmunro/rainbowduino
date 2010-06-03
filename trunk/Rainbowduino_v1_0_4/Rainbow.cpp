#include "Rainbow.h"
#include "WProgram.h"


/********************************************
 * matrix data format,this is just for reference
 * 
 * 0x0bgr
 * 
 * data type:unsigned short 16bits.
 * every 4bits reperesent one color level, so each color
 * is with 16 levels.
 *********************************************/

//used for displaying
unsigned short matrixColorData[8][8]= // [line][column]
{
  {//wite
    0x0fff,0x0ddd,0x0bbb,0x0999,0x0777,0x0555,0x0333,0x0111      }
  ,
  {//black
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000      }
  ,
  {//red
    0x000f,0x000d,0x000b,0x0009,0x0007,0x0005,0x0003,0x0001      }
  ,
  {//red&green
    0x00ff,0x00dd,0x00bb,0x0099,0x0077,0x0055,0x0033,0x0011      }
  ,
  {//green
    0x00f0,0x00d0,0x00b0,0x0090,0x0070,0x0050,0x0030,0x0010      }
  ,
  {//blue&green
    0x0ff0,0x0dd0,0x0bb0,0x0990,0x0770,0x0750,0x0330,0x0110      }
  ,
  {//blue
    0x0f00,0x0d00,0x0b00,0x0900,0x0700,0x0500,0x0300,0x0100      }
  ,
  {//blue&red
    0x0f0f,0x0d0d,0x0b0b,0x0909,0x0707,0x0505,0x0303,0x0101      }
  ,
};

//used for receiving color data from serial port,they can be 
unsigned short serialColorData[8][8] = 
{
  {//wite
    0x0fff,0x0fff,0x0fff,0x0fff,0x0fff,0x0fff,0x0fff,0x0fff      }
  ,
  {//random
    0x05e3,0x05e3,0x05e3,0x05e3,0x05e3,0x05e3,0x05e3,0x05e3      }
  ,
  {//red
    0x000f,0x000f,0x000f,0x000f,0x000f,0x000f,0x000f,0x000f      }
  ,
  {//red&green
    0x00ff,0x00ff,0x00ff,0x00ff,0x00ff,0x00ff,0x00ff,0x00ff      }
  ,
  {//green
    0x00f0,0x00f0,0x00f0,0x00f0,0x00f0,0x00f0,0x00f0,0x00f0      }
  ,
  {//blue&green
    0x0ff0,0x0ff0,0x0ff0,0x0ff0,0x0ff0,0x0ff0,0x0ff0,0x0ff0      }
  ,
  {//blue
    0x0f00,0x0f00,0x0f00,0x0f00,0x0f00,0x0f00,0x0f00,0x0f00      }
  ,
  {//blue&red
    0x0f0f,0x0f0f,0x0f0f,0x0f0f,0x0f0f,0x0f0f,0x0f0f,0x0f0f      }
  ,
};
//= //Timer1 interuption service routine=========================================
ISR(TIMER1_OVF_vect)         
{
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
  //wait for serial data, and saved to serialColorData[][]
  getSerialData();

}

/**********************************************
 * Get led matrix data from serial,
 * data format:
 * 4 bytes a group:--line(1byte),column(1btye),color(2byte)
 * color format:--0x0bgr,low byte first
 ***********************************************/
void getSerialData()
{
  int len = 0;
  unsigned char line = 0;
  unsigned char column = 0;
  unsigned short color = 0;

  len =Serial.available();

  if(len >= 4)
  {
    //Serial.println(len);
    line = Serial.read();
    column = Serial.read();
    unsigned char low = Serial.read();//low 8bits first   (0xgr)
    unsigned short high = Serial.read();//high 8bits later  (0x0b)
    color = (high<<8)|low;

    if(line < 8 & line >= 0 & column < 8 & column >= 0)
    {
      serialColorData[line][column] = color;
    }
  }
}
//==============================================================

//shift 1 bit to the rgb data driver MBI5168
void shift_1_bit(unsigned char LS)
{
  if(LS)
  {
    shift_data_1;
  }
  else
  {
    shift_data_0;
  }
  clk_rising;
}

//sweep the specific line,used in the Timer1 ISR
void flash_line(unsigned char line,unsigned char level)
{
  disable_oe;
  close_all_line;
  shift_24_bit(line,level);
  open_line(line);
  enable_oe;
}

//one line with 8 rgb data,so totally 8x3=24 bits. Data format:0x0bgr
void shift_24_bit(unsigned char line,unsigned char level)
{
  unsigned char column=0;
  unsigned char g=0,r=0,b=0;
  le_high;

  //Output G0~G8
  for(column=0;column<8;column++)
  {
    g=(matrixColorData[line][column]&0x00FF)>>4;

    if(g>level) {
      shift_1_bit(1);
    }
    else {
      shift_1_bit(0);
    }  //gray scale,11100000b always light

  }
  //Output R0~R8
  for(column=0;column<8;column++)
  {
    r=matrixColorData[line][column]&0x000f;

    if(r>level) {
      shift_1_bit(1);
    }
    else {
      shift_1_bit(0);
    }  //gray scale,00011000 always light

  }
  //Output B0~B8
  for(column=0;column<8;column++)
  {
    b=(matrixColorData[line][column]&0x0fff)>>8;

    if(b>level) {
      shift_1_bit(1);
    }
    else {
      shift_1_bit(0);
    }  //gray scale,00000111 always light

  }

  le_low;
}

//open the specific line
void open_line(unsigned char line)
{
  switch(line)
  {
  case 0:
    {
      open_line0;
      break;
    }
  case 1:
    {
      open_line1;
      break;
    }
  case 2:
    {
      open_line2;
      break;
    }
  case 3:
    {
      open_line3;
      break;
    }
  case 4:
    {
      open_line4;
      break;
    }
  case 5:
    {
      open_line5;
      break;
    }
  case 6:
    {
      open_line6;
      break;
    }
  case 7:
    {
      open_line7;
      break;
    }
  }
}
//======================================================================
Rainbow::Rainbow(){
}

//invoke initIO and initTimer1
void Rainbow::init(void)
{
  initIO();
  initTimer1();
}

//initialize IO for controlling the leds
void Rainbow::initIO(void)
{
  DDRD=0xff;//set port D as output
  DDRC=0xff;//set port C as output
  DDRB=0xff;//set port B as output
  PORTD=0;//initialize port D to LOW
  PORTB=0;//initialize port B to LOW
}

//initialize Timer1 to 100us overflow           
void Rainbow::initTimer1(void)        
{
  TCCR1A = 0;                 // clear control register A
  TCCR1B = _BV(WGM13);        // set mode as phase and frequency correct pwm, stop the timer
  ICR1=800;                   //(XTAL * microseconds) / 2000000  100us cycles 
  TIMSK1 = _BV(TOIE1);
  TCNT1 = 0;
  TCCR1B |= _BV(CS10);
  sei();                      //enable global interrupt
}

//close all leds
void Rainbow::closeAll()
{
  for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++)
      matrixColorData[i][j] = 0;
}

//close one line
void Rainbow::closeOneLine(unsigned char line)
{
  for(int j = 0; j < 8; j++)
    matrixColorData[line][j] = 0;
}

//close one column
void Rainbow::closeOneColumn(unsigned char column)
{
  for(int i = 0; i < 8; i++)
    matrixColorData[i][column] = 0;
}

//close specific dot
void Rainbow::closeOneDot(unsigned char line, unsigned char column)
{
  matrixColorData[line][column] = 0;
}

//close one diagonal line
void Rainbow::closeOneDiagonal(unsigned char line, unsigned char type)
{
  int num = 0;//number of lighting leds     

  if(LEFT_BOTTOM_TO_RIGHT_TOP == type)  
  {
    if(line&0x08)//line = 8...15
    {
      num = 15 - line;
      for(int k = 0; k < num; k++)
      {
        matrixColorData[7-k][k+8-num] = 0;
      }
    }
    else//line = 0...7
    {
      num = line + 1;
      for(int k = 0; k < num; k++)
      {
        matrixColorData[num-k-1][k] = 0;
      }
    }
  }
  else if(LEFT_TOP_TO_RIGHT_BOTTOM == type)
  {
    if(line&0x08)//line = 8...15
    {
      num = 15 - line;
      for(int k = 0; k < num; k++)
      {
        matrixColorData[num-1-k][7-k] = 0;
      }
    }
    else//line = 0...7
    {
      num = line + 1;

      for(int k = 0; k < num; k++)
      {
        matrixColorData[7-k][num-1-k] = 0;
      }
    }
  }
}


//light all with one color
void Rainbow::lightAll(unsigned short colorData)
{
  for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++)
      matrixColorData[i][j] = colorData;
}

//light all with matrix data
void Rainbow::lightAll(unsigned short colorData[8][8])
{
  for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++)
      matrixColorData[i][j] = colorData[i][j];
}

//only light one line with one color
void Rainbow::lightOneLine(unsigned char line, unsigned short color,unsigned char othersState)
{
  if( OTHERS_OFF == othersState)
  {
    for(int i = 0; i < 8; i++)
      for(int j = 0; j < 8; j++)    
        matrixColorData[i][j] = 0;
  }
  for(int k = 0; k < 8; k++)
    matrixColorData[line][k] = color;
}
//only light one line with 8 colors
void Rainbow::lightOneLine(unsigned char line, unsigned short color[8],unsigned char othersState)
{
  if(OTHERS_OFF == othersState)
  {
    for(int i = 0; i < 8; i++)
      for(int j = 0; j < 8; j++)    
        matrixColorData[i][j] = 0;
  }

  for(int k = 0; k < 8; k++)
    matrixColorData[line][k] = color[k];
}

//only light one column with one color
void Rainbow::lightOneColumn(unsigned char column, unsigned short color,unsigned char othersState)
{
  if(OTHERS_OFF == othersState)
  {
    for(int i = 0; i < 8; i++)
      for(int j = 0; j < 8; j++)    
        matrixColorData[i][j] = 0;
  }

  for(int k = 0; k < 8; k++)
    matrixColorData[k][column] = color;  
}

//only light one column with 8 colors
void Rainbow::lightOneColumn(unsigned char column, unsigned short color[8],unsigned char othersState)
{
  if(OTHERS_OFF == othersState)
  {
    for(int i = 0; i < 8; i++)
      for(int j = 0; j < 8; j++)    
        matrixColorData[i][j] = 0;
  }

  for(int k = 0; k < 8; k++)
    matrixColorData[k][column] = color[k];  

}

//only light one column with serialColorData 8 colors
void Rainbow::lightOneColumn(unsigned char column, unsigned short color[8][8],unsigned char othersState)
{
  if(OTHERS_OFF == othersState)
  {
    for(int i = 0; i < 8; i++)
      for(int j = 0; j < 8; j++)    
        matrixColorData[i][j] = 0;
  }

  for(int k = 0; k < 8; k++)
    matrixColorData[k][column] = color[k][column];  
}

//only light one dot at specific position
void Rainbow::lightOneDot(unsigned char line,unsigned char column, unsigned short color,unsigned char othersState)
{
  if(OTHERS_OFF == othersState)
  {
    for(int i = 0; i < 8; i++)
      for(int j = 0; j < 8; j++)    
        matrixColorData[i][j] = 0;
  }

  matrixColorData[line][column] = color;
}

//only light one diagonal line  with one color
void Rainbow::lightOneDiagonal(unsigned char line, unsigned char type, unsigned short color,unsigned char othersState)
{
  if(OTHERS_OFF == othersState)
  {
    for(int i = 0; i < 8; i++)
      for(int j = 0; j < 8; j++)    
        matrixColorData[i][j] = 0;
  }

  int num = 0;//number of lighting leds     

  if(LEFT_BOTTOM_TO_RIGHT_TOP == type)  
  {
    if(line&0x08)//line = 8...15
    {
      num = 15 - line;
      for(int k = 0; k < num; k++)
      {
        matrixColorData[7-k][k+8-num] = color;
      }
    }
    else//line = 0...7
    {
      num = line + 1;

      for(int k = 0; k < num; k++)
      {
        matrixColorData[num-k-1][k] = color;
      }
    }
  }
  else if(LEFT_TOP_TO_RIGHT_BOTTOM == type)
  {
    if(line&0x08)//line = 8...15
    {
      num = 15 - line;
      for(int k = 0; k < num; k++)
      {
        matrixColorData[num-1-k][7-k] = color;
      }
    }
    else//line = 0...7
    {
      num = line + 1;

      for(int k = 0; k < num; k++)
      {
        matrixColorData[7-k][num-1-k] = color;
      }
    }
  }
}

//only light one diagonal line with a number of colors
void Rainbow::lightOneDiagonal(unsigned char line, unsigned char type, unsigned short *color,unsigned char othersState)
{
  if(OTHERS_OFF == othersState)
  {
    for(int i = 0; i < 8; i++)
      for(int j = 0; j < 8; j++)    
        matrixColorData[i][j] = 0;
  }

  int num = 0;//number of lighting leds     

  if(LEFT_BOTTOM_TO_RIGHT_TOP == type)  
  {
    if(line&0x08)//line = 8...15
    {
      num = 15 - line;
      for(int k = 0; k < num; k++)
      {
        matrixColorData[7-k][k+8-num] = color[k];
      }
    }
    else//line = 0...7
    {
      num = line + 1;

      for(int k = 0; k < num; k++)
      {
        matrixColorData[num-k-1][k] = color[k];
      }
    }
  }
  else if(LEFT_TOP_TO_RIGHT_BOTTOM == type)
  {
    if(line&0x08)//line = 8...15
    {
      num = 15 - line;
      for(int k = 0; k < num; k++)
      {
        matrixColorData[num-1-k][7-k] = color[k];
      }
    }
    else//line = 0...7
    {
      num = line + 1;

      for(int k = 0; k < num; k++)
      {
        matrixColorData[7-k][num-1-k] = color[k];
      }
    }
  }

}

//only light one diagonal line with serialColorData colors
void Rainbow::lightOneDiagonal(unsigned char line, unsigned char type, unsigned short color[8][8],unsigned char othersState)
{
  if(OTHERS_OFF == othersState)
  {
    for(int i = 0; i < 8; i++)
      for(int j = 0; j < 8; j++)    
        matrixColorData[i][j] = 0;
  }

  int num = 0;//number of lighting leds     

  if(LEFT_BOTTOM_TO_RIGHT_TOP == type)  
  {
    if(line&0x08)//line = 8...15
    {
      num = 15 - line;
      for(int k = 0; k < num; k++)
      {
        matrixColorData[7-k][k+8-num] = color[7-k][k+8-num];
      }
    }
    else//line = 0...7
    {
      num = line + 1;

      for(int k = 0; k < num; k++)
      {
        matrixColorData[num-k-1][k] = color[num-k-1][k];
      }
    }
  }
  else if(LEFT_TOP_TO_RIGHT_BOTTOM == type)
  {
    if(line&0x08)//line = 8...15
    {
      num = 15 - line;
      for(int k = 0; k < num; k++)
      {
        matrixColorData[num-1-k][7-k] = color[num-1-k][7-k];
      }
    }
    else//line = 0...7
    {
      num = line + 1;

      for(int k = 0; k < num; k++)
      {
        matrixColorData[7-k][num-1-k] = color[7-k][num-1-k];
      }
    }
  }

}






