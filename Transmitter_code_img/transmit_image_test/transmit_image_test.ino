#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define LED_PIN 6 // Connect a led to D6 of arduino

#define PERIOD 15 //increasing PERIOD will reduce the speed of communication while reducing the probability of error

static const unsigned char myBitmap [] PROGMEM = {};  //Put the hex value of the image in between the {}.

static int arrLen;

U8G2_KS0108_128X64_F u8g2(U8G2_R0, 8, 9, 2, 3, 4, 5, 6, 7, A2, A0, A3, A4, U8X8_PIN_NONE, A5);

void draw(void)
{
  u8g2.drawXBMP( 0, 0, 128, 64, myBitmap);
}


void setup() 
{
  u8g2.begin();
  u8g2.clearBuffer();
  pinMode(LED_PIN, OUTPUT);
  arrLen = sizeof(myBitmap) / sizeof(myBitmap[0]);
  Serial.begin(9600);
   for(int i = 0; i < arrLen; i ++)
  {
    send_byte(myBitmap[i]);
    Serial.print(sizeof(myBitmap));
  }
}

void loop() 
{

 u8g2.firstPage();
  do
  {
    draw();
  }
  while(u8g2.nextPage());
  delay(1000);
}

void send_byte(char my_byte)
{
  digitalWrite(LED_PIN, LOW);
  delay(PERIOD);

  //transmission of bits
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(LED_PIN, (my_byte&(0x01 << i))!=0 );
    delay(PERIOD);
  }

  digitalWrite(LED_PIN, HIGH);
  delay(PERIOD);

}
