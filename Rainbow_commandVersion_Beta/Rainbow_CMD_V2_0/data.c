#include <avr/pgmspace.h>

unsigned char GamaTab[16]=
{0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7};


//========================================================
unsigned char dots_color[5][3][8][4] =
{
 {
//=====================================================
  {//green 
    {0x00,0x00,0x00,0x4b},
    {0x00,0x00,0x04,0xbf},
    {0x00,0x00,0x4b,0xff},
    {0x00,0x04,0xbf,0xff},
    {0x00,0x4b,0xff,0xff},
    {0x04,0xbf,0xff,0xff},
    {0x4b,0xff,0xff,0xff},
    {0xbf,0xff,0xff,0xfd}
  },
//=======================================================
  {//red 
   {0xff,0xfd,0x71,0x00},
    {0xff,0xd7,0x10,0x00},
    {0xfd,0xf1,0x00,0x00},
    {0xda,0x10,0x00,0x00},
    {0x71,0x00,0x00,0x01},
    {0x10,0x00,0x00,0x17},
    {0x00,0x00,0x01,0x7e},
    {0x00,0x00,0x17,0xef}
  },
//======================================================
  {//blue 
    {0x06,0xef,0xff,0xff},
    {0x6e,0xff,0xff,0xff},
    {0xef,0xff,0xff,0xfa},
    {0xff,0xff,0xff,0xa3},
    {0xff,0xff,0xfa,0x30},
    {0xff,0xfa,0xa3,0x00},
    {0xff,0xfa,0x30,0x00},
    {0xff,0xa3,0x00,0x00}
  }
 },
 {
//=====================================================
  {//green 
    {0xFF,0xFF,0xFF,0x4b},
    {0xFF,0xFF,0xF4,0xbf},
    {0x00,0x00,0x4b,0xff},
    {0x00,0x04,0xbf,0xff},
    {0x00,0x4b,0xff,0xff},
    {0x04,0xbf,0xff,0xff},
    {0x4b,0xff,0xff,0xff},
    {0xbf,0xff,0xff,0xfd}
  },
//=======================================================
  {//red 
   {0xff,0xfd,0x71,0x00},
    {0xff,0xd7,0x10,0x00},
    {0xfd,0xf1,0x00,0x00},
    {0xda,0x10,0x00,0x00},
    {0x71,0x00,0x00,0x01},
    {0x10,0x00,0x00,0x17},
    {0x00,0x00,0x01,0x7e},
    {0x00,0x00,0x17,0xef}
  },
//======================================================
  {//blue 
    {0x06,0xef,0xff,0xff},
    {0x6e,0xff,0xff,0xff},
    {0xef,0xff,0xff,0xfa},
    {0xff,0xff,0xff,0xa3},
    {0xff,0xff,0xfa,0x30},
    {0xff,0xfa,0xa3,0x00},
    {0xff,0xfa,0x30,0x00},
    {0xff,0xa3,0x00,0x00}
  }
 },
}; 



unsigned char Prefabnicatel[5][3][8][4] PROGMEM =
{
 {
//=========================0=======================
  {//green 
    {0x00,0x00,0x00,0x4b},
    {0x00,0x00,0x04,0xbf},
    {0x00,0x00,0x4b,0xff},
    {0x00,0x04,0xbf,0xff},
    {0x00,0x4b,0xff,0xff},
    {0x04,0xbf,0xff,0xff},
    {0x4b,0xff,0xff,0xff},
    {0xbf,0xff,0xff,0xfd}
  },
//=======================================================
  {//red 
   {0xff,0xfd,0x71,0x00},
    {0xff,0xd7,0x10,0x00},
    {0xfd,0xf1,0x00,0x00},
    {0xda,0x10,0x00,0x00},
    {0x71,0x00,0x00,0x01},
    {0x10,0x00,0x00,0x17},
    {0x00,0x00,0x01,0x7e},
    {0x00,0x00,0x17,0xef}
  },
//======================================================
  {//blue 
    {0x06,0xef,0xff,0xff},
    {0x6e,0xff,0xff,0xff},
    {0xef,0xff,0xff,0xfa},
    {0xff,0xff,0xff,0xa3},
    {0xff,0xff,0xfa,0x30},
    {0xff,0xfa,0xa3,0x00},
    {0xff,0xfa,0x30,0x00},
    {0xff,0xa3,0x00,0x00}
  }
 },
 {
//=========================1========================
  {//green 
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00}
  },
//=======================================================
  {//red 
    {0x0f,0xff,0xff,0xff},
    {0x0f,0xff,0xff,0xff},
    {0x0f,0xff,0xff,0xff},
    {0x0f,0xff,0xff,0xff},
    {0x0f,0xff,0xff,0xff},
    {0x0f,0xff,0xff,0xff},
    {0x0f,0xff,0xff,0xff},
    {0x0f,0xff,0xff,0xff}
  },
//======================================================
  {//blue 
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00}
  }
 },

  {
//=========================2========================
  {//green 
   {0xff,0xfd,0x71,0x00},
    {0xff,0xfd,0x71,0x00},
    {0xff,0xfd,0x71,0x00},
    {0xff,0xfd,0x71,0x00},
    {0xff,0xfd,0x71,0x00},
    {0xff,0xfd,0x71,0x00},
    {0xff,0xfd,0x71,0x00},
    {0xff,0xfd,0x71,0x00}
  },
//=======================================================
  {//red 
   {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00}
  },
//======================================================
  {//blue 
   {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00}
  }
 },

  {
//=========================3========================
  {//green 
    {0xFF,0xFF,0xFF,0x4b},
    {0xFF,0xFF,0xF4,0xbf},
    {0x00,0x00,0x4b,0xff},
    {0x00,0x04,0xbf,0xff},
    {0x00,0x4b,0xff,0xff},
    {0x04,0xbf,0xff,0xff},
    {0x4b,0xff,0xff,0xff},
    {0xbf,0xff,0xff,0xfd}
  },
//=======================================================
  {//red 
   {0xff,0xfd,0x71,0x00},
    {0xff,0xd7,0x10,0x00},
    {0xfd,0xf1,0x00,0x00},
    {0xda,0x10,0x00,0x00},
    {0x71,0x00,0x00,0x01},
    {0x10,0x00,0x00,0x17},
    {0x00,0x00,0x01,0x7e},
    {0x00,0x00,0x17,0xef}
  },
//======================================================
  {//blue 
    {0x06,0xef,0xff,0xff},
    {0x6e,0xff,0xff,0xff},
    {0xef,0xff,0xff,0xfa},
    {0xff,0xff,0xff,0xa3},
    {0xff,0xff,0xfa,0x30},
    {0xff,0xfa,0xa3,0x00},
    {0xff,0xfa,0x30,0x00},
    {0xff,0xa3,0x00,0x00}
  }
 },


 {
//========================4========================
  {//green 
    {0xFF,0xFF,0xFF,0x4b},
    {0xFF,0xFF,0xF4,0xbf},
    {0x00,0x00,0x4b,0xff},
    {0x00,0x04,0xbf,0xff},
    {0x00,0x4b,0xff,0xff},
    {0x04,0xbf,0xff,0xff},
    {0x4b,0xff,0xff,0xff},
    {0xbf,0xff,0xff,0xfd}
  },
//=======================================================
  {//red 
   {0xff,0xfd,0x71,0x00},
    {0xff,0xd7,0x10,0x00},
    {0xfd,0xf1,0x00,0x00},
    {0xda,0x10,0x00,0x00},
    {0x71,0x00,0x00,0x01},
    {0x10,0x00,0x00,0x17},
    {0x00,0x00,0x01,0x7e},
    {0x00,0x00,0x17,0xef}
  },
//======================================================
  {//blue 
    {0x06,0xef,0xff,0xff},
    {0x6e,0xff,0xff,0xff},
    {0xef,0xff,0xff,0xfa},
    {0xff,0xff,0xff,0xa3},
    {0xff,0xff,0xfa,0x30},
    {0xff,0xfa,0xa3,0x00},
    {0xff,0xfa,0x30,0x00},
    {0xff,0xa3,0x00,0x00}
  }
 }
};

//----------------------------------------------------
 unsigned char ASCII_Char[52][8] PROGMEM =
{
      
    {0x0,0x44,0x44,0x7C,0x44,0x44,0x28,0x10},//A
    {0x0,0x3C,0x44,0x44,0x3C,0x44,0x44,0x3C},//B   
    {0x0,0x38,0x44,0x4,0x4,0x4,0x44,0x38},//C   
    {0x0,0x1C,0x24,0x44,0x44,0x44,0x24,0x1C},//D  
    {0x0,0x7C,0x4,0x4,0x3C,0x4,0x4,0x7C}, //E
    {0x0,0x4,0x4,0x4,0x3C,0x4,0x4,0x7C}, //F
    {0x0,0x78,0x44,0x44,0x74,0x4,0x44,0x38},//G
    {0x0,0x44,0x44,0x44,0x7C,0x44,0x44,0x44}, //H
    {0x0,0x38,0x10,0x10,0x10,0x10,0x10,0x38} , //I
    {0x0,0x18,0x24,0x20,0x20,0x20,0x20,0x70},  //J
    {0x0,0x44,0x24,0x14,0xC,0x14,0x24,0x44},   //K
    {0x0,0x7C,0x4,0x4,0x4,0x4,0x4,0x4},//L
    {0x0,0x44,0x44,0x44,0x54,0x54,0x6C,0x44}, //M
    {0x0,0x44,0x44,0x64,0x54,0x4C,0x44,0x44},  //N
    {0x0,0x38,0x44,0x44,0x44,0x44,0x44,0x38},  //O
    {0x0,0x4,0x4,0x4,0x3C,0x44,0x44,0x3C},   //P
    {0x0,0x58,0x24,0x54,0x44,0x44,0x44,0x38},//Q
    {0x0,0x44,0x24,0x14,0x3C,0x44,0x44,0x3C},  //R
    {0x0,0x3C,0x40,0x40,0x38,0x4,0x4,0x78},//S
    {0x0,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},// T
    {0x0,0x38,0x44,0x44,0x44,0x44,0x44,0x44},// U   
    {0x0,0x10,0x28,0x44,0x44,0x44,0x44,0x44},// V     
    {0x0,0x28,0x54,0x54,0x54,0x44,0x44,0x44},// W    
    {0x0,0x44,0x44,0x28,0x10,0x28,0x44,0x44},// X   
    {0x0,0x10,0x10,0x10,0x28,0x44,0x44,0x44},// Y    
    {0x0,0x7C,0x4,0x8,0x10,0x20,0x40,0x7C},// Z
    
    {0x0,0x78,0x44,0x78,0x40,0x38,0x0,0x0},// a   
    {0x0,0x3C,0x44,0x44,0x4C,0x34,0x4,0x4},// b    
    {0x0,0x38,0x44,0x4,0x4,0x38,0x0,0x0},// c    
    {0x0,0x78,0x44,0x44,0x64,0x58,0x40,0x40},// d    
    {0x0,0x38,0x4,0x7C,0x44,0x38,0x0,0x0},// e    
    {0x0,0x8,0x8,0x8,0x1C,0x8,0x48,0x30},// f    
    {0x38,0x40,0x78,0x44,0x44,0x78,0x0,0x0},// g    
    {0x0,0x44,0x44,0x44,0x4C,0x34,0x4,0x4},// h   
    {0x0,0x38,0x10,0x10,0x10,0x18,0x0,0x10},// i    
    {0x18,0x24,0x20,0x20,0x20,0x30,0x0,0x20},// j    
    {0x0,0x24,0x14,0xC,0x14,0x24,0x4,0x4},// k    
    {0x0,0x38,0x10,0x10,0x10,0x10,0x10,0x18},// l    
    {0x0,0x44,0x44,0x54,0x54,0x2C,0x0,0x0},// m   
    {0x0,0x44,0x44,0x44,0x4C,0x34,0x0,0x0},// n    
    {0x0,0x38,0x44,0x44,0x44,0x38,0x0,0x0},// o    
    {0x4,0x4,0x3C,0x44,0x44,0x3C,0x0,0x0},// p    
    {0x40,0x40,0x58,0x64,0x64,0x58,0x0,0x0},// q   
    {0x0,0x4,0x4,0x4,0x4C,0x34,0x0,0x0},// r    
    {0x0,0x3C,0x40,0x38,0x4,0x38,0x0,0x0},// s    
    {0x0,0x30,0x48,0x8,0x8,0x1C,0x8,0x8},// t   
    {0x0,0x58,0x64,0x44,0x44,0x44,0x0,0x0},// u    
    {0x0,0x10,0x28,0x44,0x44,0x44,0x0,0x0},// v   
    {0x0,0x28,0x54,0x54,0x44,0x44,0x0,0x0},// w    
    {0x0,0x44,0x28,0x10,0x28,0x44,0x0,0x0},// x   
    {0x38,0x40,0x78,0x44,0x44,0x44,0x0,0x0},// y   
    {0x0,0x7C,0x8,0x10,0x20,0x7C,0x0,0x0},// z
};


unsigned char ASCII_Number[10][8] PROGMEM =
{
  {0x0,0x38,0x44,0x4C,0x54,0x64,0x44,0x38},//0
  {0x0,0x38,0x10,0x10,0x10,0x10,0x18,0x10},// 1
  {0x0,0x7C,0x8,0x10,0x20,0x40,0x44,0x38},// 2
  {0x0,0x38,0x44,0x40,0x20,0x10,0x20,0x7C},// 3
  {0x0,0x20,0x20,0x7C,0x24,0x28,0x30,0x20},// 4
  {0x0,0x38,0x44,0x40,0x40,0x3C,0x4,0x7C},//5
  {0x0,0x38,0x44,0x44,0x3C,0x4,0x8,0x30},//6
  {0x0,0x8,0x8,0x8,0x10,0x20,0x40,0x7C},//7
  {0x0,0x38,0x44,0x44,0x38,0x44,0x44,0x38},//8
  {0x0,0x18,0x20,0x40,0x78,0x44,0x44,0x38}//9
};

