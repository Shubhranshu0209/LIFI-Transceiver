#define TRANSMIT_LED 11                                // Connect a led with resistor to D11 of arduino
#define SAMPLING_TIME 5                              // increasing PERIOD will reduce the speed of communication while reducing the probability of error

 char text[] = "This is PD Lab. ";

//Declaration
bool transmit_data = true;
int bytes_counter = 1;
int total_bytes;

void setup()                                           // setting up the output
{                
  pinMode(TRANSMIT_LED,OUTPUT);                        // measuring the length of input text data
  total_bytes = strlen(text);
}

void loop()                                            // loop for the string which iterates length of string + 1 times
{

   while(transmit_data)
   {
    transmit_byte(text[total_bytes - bytes_counter]);
    bytes_counter--;
      if(bytes_counter == 0)
      {
        transmit_data = false;
      }

   }

   transmit_data = true;
   bytes_counter = total_bytes;
   delay(1000);
 }

void transmit_byte(char data_byte)                      // function for transmitting each charcter as a byte or 8 bits
{
  digitalWrite(TRANSMIT_LED,LOW);                       // output-ing low in digital pin D11 to mark the start of transmission of 1 byte
  delay(SAMPLING_TIME);
  for(int i = 0; i < 8; i++)                            // loop for transmission of 8 bits=1 byte=1 character which iterates 8 times
  {
    digitalWrite(TRANSMIT_LED,(data_byte >> i) & 0x01); // bit wise and-ing each bit of byte from LSB side with 1 to get 1 bit at a time
    delay(SAMPLING_TIME);
  }
 digitalWrite(TRANSMIT_LED,HIGH);                       // output-ing high in digital pin D11 to mark the end of 1 byte transmission
 delay(SAMPLING_TIME);
}
