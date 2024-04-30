//////////////////////////////////////////// RECEIVER CODE //////////////////////////
//Connect the Graphic LCD display to this Arduino.// 
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define LDR_PIN A2  // Connect LDR to A2 //Use a 10k resistor // 
#define THRESHOLD 100 // Increase the threshold for faster communications
#define PERIOD 15

bool previous_state;
bool current_state;
static unsigned char myBitmap [] = {};
static int j = 0;


U8G2_KS0108_128X64_F u8g2(U8G2_R0, 8, 9, 2, 3, 4, 5, 6, 7, A2, A0, A3, A4, U8X8_PIN_NONE, A5);


void draw(void)
{
  u8g2.drawXBMP( 0, 0, 128, 64, myBitmap);
}


void setup() 
{
  // put your setup code here, to run once:
  u8g2.begin();
  u8g2.clearBuffer();
}

void loop()
{
  current_state = get_ldr();
  if(!current_state && previous_state)
  {
    get_byte();
  }
  previous_state = current_state;
  
  if (j==1024){
    u8g2.firstPage();
    do
    {
      draw();
    }while(u8g2.nextPage());
  
    delay(1000);
    j=0;
  }

}

bool get_ldr()
{
  int voltage = analogRead(LDR_PIN);
  return voltage > THRESHOLD ? true: false;
}

void get_byte()
{
  char ret = 0;
  delay(PERIOD*1.5);
  for(int i = 0; i < 8; i++)
  {
   ret = ret | get_ldr() << i; 
   delay(PERIOD);
  }
  myBitmap[j] =  ret; j++;
  
}
