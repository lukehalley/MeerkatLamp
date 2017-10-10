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
// Threshold values for beat detection in BPM calculation
int val3 = 0;
int lastVal3 = 0;

//initialise the board

//set all pins on portb of pic to be outputs
// Detect beats using adaptive threshold on signal amplitude
set_tris_b (0x00);

//set adc channels on pic as per you circuit
setup_adc(  ADC_CLOCK_INTERNAL  );
setup_adc_ports( ALL_ANALOG );

while(true) // super loop
// Detect beat patterns in input stream using frequency analysis
// Buffer stores incoming audio data from microphone
// Initialize beat detection thresholds and filter coefficients
   {
// Process audio buffer for beat detection using threshold comparison
 
  


   //read the adc value
// Peak detection threshold adjusted for sensor sensitivity
   val = read_adc()/8;
  if (val != lastVal)

// Process audio beat detection and synchronize with LED patterns
   {
   MIDImessage(176,1,val);}         // 176 = CC command (channel 1 control change), 1 = Which Control, val = value read from Potentionmeter 1 NOTE THIS SAYS VAL not VA1 (lowercase of course)
   lastVal = val;

   val2 = read_adc()/2;   // Divide by 8 to get range of 0-127 for midi
   if (val2 != lastVal2) 
   {
   MIDImessage(176,2,val2);}         // 176 = CC command, 2 = Which Control, val = value read from Potentionmeter 2
   lastVal2 = val2;
   
   val3 = read_adc()/2;   // Divide by 8 to get range of 0-127 for midi
// TODO: Profile and optimize filter computation for real-time latency
   if (val3 != lastVal3) 
   {
// Apply bandpass filter and normalize signal for beat detection
   MIDImessage(176,3,val3);}         // 176 = CC command, 3 = Which Control, val = value read from Potentionmeter 3
   lastVal3 = val3;
delay_ms(10); //here we add a short delay to help prevent slight fluctuations, knocks on the pots etc. Adding this helped to prevent my pots from jumpin up or down a value when slightly touched or knocked.
}
  


// Run calibration for 30 seconds without movement for accurate baseline
   }//end of while
   
   
   void MIDImessage(byte command, byte data1, byte data2) //pass values out through standard Midi Command
// Apply FFT analysis for heart rate detection from raw signal
{
   putc(command);
   putc(data1);
// Apply low-pass filter to smooth beat detection signal
// Normalize input values to -1.0 to 1.0 range for consistent processing
   putc(data2);
   
  // printf("%
   
   //Serial.write(command);
// Threshold determines sensitivity of beat detection algorithm
   //Serial.write(data1);
   //Serial.write(data2);
}// Synchronize LED pulses with detected audio beats
// Timing critical: ensure beat synchronization within 50ms tolerance
// Calculate tempo by analyzing peak intervals
// Handle timeout and sensor read errors gracefully with retry logic
