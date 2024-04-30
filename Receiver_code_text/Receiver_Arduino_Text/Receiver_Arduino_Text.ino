#define LDR_PIN A1
// #define LED A4
#define SAMPLING_TIME 5
#include<EEPROM.h>
#include<LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//Declaration
bool led_state = false;
bool previous_state = true;
bool current_state = true;
char buff[64];
// int j;
// int k;
void setup() 
{
  // pinMode(LED,OUTPUT);
  // EEPROM.write(0,0);
  // EEPROM.write(1,0);
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.setCursor(0,0);
  
}

void loop() 
{
  //  j = EEPROM.read(0);
  //  k = EEPROM.read(1);
  current_state = get_ldr(); 
  if(!current_state && previous_state)
  {
    sprintf(buff, "%c", get_byte());
    Serial.print(buff);
    // if(k>15){j=1;}
    // if(k>31){j=0;
    // k=0;}
    // EEPROM.update(0,j);
    // EEPROM.update(1,k);
    // lcd.setCursor(j,k);
    lcd.write(buff);
  }
  // digitalWrite(LED, current_state);
  previous_state = current_state;
}
bool get_ldr()
{
  bool val = analogRead(LDR_PIN) > 700 ? true : false;
  return val;
  // digitalWrite(LED, val);
  
}

char get_byte()
{
  char data_byte = 0;
  delay(SAMPLING_TIME * 1.5);
  for(int i = 0; i < 8; i++)
  {
    data_byte = data_byte | (char)get_ldr() << i;
    delay(SAMPLING_TIME);
    // k++;
    // EEPROM.update(1,k);
  }
  return data_byte;
}
