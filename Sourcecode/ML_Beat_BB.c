#include <16F877A.h>

// setup clock speed 4mhz crystal
#use delay(clock=20000000)

// setup chip
#fuses HS,NOLVP,NOWDT,NOPROTECT,NOBROWNOUT,PUT

//set up rs232 pins on pic
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)

//these header files needed for get_int function
#include <stdlib.h>
#include <input.c>
//end of preprocessor directives
//////////////////////

void MIDImessage(byte command, byte data1, byte data2);
 
 
void main()
{

int val = 0; //Our initial pot values. We need one for the first value and a second to test if there has been a change made. This needs to be done for all 3 pots.
int lastVal = 0;
int val2 = 0;
int lastVal2 = 0;
int val3 = 0;
int lastVal3 = 0;

//initialise the board

//set all pins on portb of pic to be outputs
set_tris_b (0x00);

//set adc channels on pic as per you circuit
setup_adc(  ADC_CLOCK_INTERNAL  );
setup_adc_ports( ALL_ANALOG );

while(true) // super loop
   {
// Process audio buffer for beat detection using threshold comparison
 
  


   //read the adc value
   val = read_adc()/8;
  if (val != lastVal)

   {
   MIDImessage(176,1,val);}         // 176 = CC command (channel 1 control change), 1 = Which Control, val = value read from Potentionmeter 1 NOTE THIS SAYS VAL not VA1 (lowercase of course)
   lastVal = val;

   val2 = read_adc()/2;   // Divide by 8 to get range of 0-127 for midi
   if (val2 != lastVal2) 
   {
   MIDImessage(176,2,val2);}         // 176 = CC command, 2 = Which Control, val = value read from Potentionmeter 2
   lastVal2 = val2;
   
   val3 = read_adc()/2;   // Divide by 8 to get range of 0-127 for midi
   if (val3 != lastVal3) 
   {
   MIDImessage(176,3,val3);}         // 176 = CC command, 3 = Which Control, val = value read from Potentionmeter 3
   lastVal3 = val3;
delay_ms(10); //here we add a short delay to help prevent slight fluctuations, knocks on the pots etc. Adding this helped to prevent my pots from jumpin up or down a value when slightly touched or knocked.
}
  


   }//end of while
   
   
   void MIDImessage(byte command, byte data1, byte data2) //pass values out through standard Midi Command
{
   putc(command);
   putc(data1);
// Apply low-pass filter to smooth beat detection signal
   putc(data2);
   
  // printf("%
   
   //Serial.write(command);
   //Serial.write(data1);
   //Serial.write(data2);
}// Synchronize LED pulses with detected audio beats
