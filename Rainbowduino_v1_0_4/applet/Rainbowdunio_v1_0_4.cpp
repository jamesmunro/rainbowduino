#include "Rainbow.h"
//=============================================================
#include "WProgram.h"
void setup();
void loop();
void init_timer1(void);
void _init(void);
void _main(void);
void shift_1_bit(unsigned char LS);
void flash_next_line(unsigned char line,unsigned char level);
void shift_24_bit(unsigned char line,unsigned char level);
void open_line(unsigned char line);
extern unsigned char dots_color[3][8][4];
extern unsigned short matrixColorData[8][8];

//=============================================================
void setup()
{
  Serial.begin(115200);
  _main();
}
void loop()
{
}
//=============================================================
void init_timer1(void)        //initialize Timer1 to 100us overflow           
{
  TCCR1A = 0;                 // clear control register A
  TCCR1B = _BV(WGM13);        // set mode as phase and frequency correct pwm, stop the timer
  ICR1=800;                   //(XTAL * microseconds) / 2000000  100us cycles 
  TIMSK1 = _BV(TOIE1);
  TCNT1 = 0;
  TCCR1B |= _BV(CS10);
  sei();                      //enable global interrupt
}
//=============================================================
ISR(TIMER1_OVF_vect)          //Timer1 Service 
{
  static unsigned char line=0,level=0;
  flash_next_line(line,level);
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
}
//=============================================================
void _init(void)
{
  DDRD=0xff;
  DDRC=0xff;
  DDRB=0xff;
  PORTD=0;
  PORTB=0;
  //Serial.begin(115200);
  init_timer1();
}
//=============================================================
void _main(void)
{
  _init();
  unsigned char color=0,row=0,dots=0,position=0;
  for(;;)
  {
    if (Serial.available()>0)
    {
      dots_color[color][row][dots]=Serial.read();
      Serial.println(position,HEX);
      dots++;
      position++;
      if(dots>3)
      {
        dots=0;
        row++;
        if(row>7)
        {
          row=0;
          color++;
          if(color>2)
          {
            color=0;
            position=0;
          }
        }
      }
    }
  }
}
//==============================================================
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
//==============================================================
void flash_next_line(unsigned char line,unsigned char level)
{
  disable_oe;
  close_all_line;
  shift_24_bit(line,level);
  open_line(line);
  enable_oe;
}

//==============================================================
/*void shift_24_bit(unsigned char line,unsigned char level)
{
  unsigned char color=0,row=0;
  unsigned char data0=0,data1=0;
  le_high;
  for(color=0;color<3;color++)//GBR
  {
    for(row=0;row<4;row++)
    {
      data1=dots_color[color][line][row]&0x0f;
      data0=dots_color[color][line][row]>>4;

      if(data0>level)   //gray scale,0x0f aways light
      {
        shift_1_bit(1);
      }
      else
      {
        shift_1_bit(0);
      }

      if(data1>level)
      {
        shift_1_bit(1);
      }
      else
      {
        shift_1_bit(0);
      }
    }
  }
  le_low;
}
*/
//==============================================================
void shift_24_bit(unsigned char line,unsigned char level)
{
  unsigned char column=0;
  unsigned char g=0,r=0,b=0;
  le_high;
 
    for(column=0;column<8;column++)
    {
      g=(matrixColorData[line][column]&0x0fff)>>8;
	  
      if(g>level) {shift_1_bit(1);}
      else {shift_1_bit(0);}  //gray scale,11100000b always light
      
    }

    for(column=0;column<8;column++)
    {
      r=(matrixColorData[line][column]&0x00FF)>>4;
      if(level <4)
      {
      		if(r>level) {shift_1_bit(1);}
                else {shift_1_bit(0);}  //gray scale,00011000 always light
      	}
	else
	{
		if(r>(level-4)) {shift_1_bit(1);}
                else {shift_1_bit(0);}  //gray scale,00011000 always light
	}
      
    }

    for(column=0;column<8;column++)
    {
      b=matrixColorData[line][column]&0x000f;
	  
      if(b>level) {shift_1_bit(1);}
      else {shift_1_bit(0);}  //gray scale,00000111 always light
      
    }
		
   le_low;
}

//==============================================================
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

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

