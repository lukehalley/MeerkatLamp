#include <16F877A.h>

// setup clock speed 4mhz crystal
#use delay(clock=20000000)

// setup chip
#fuses HS,NOLVP,NOWDT,NOPROTECT,NOBROWNOUT,PUT

//set up rs232 pins on pic
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)

// Initialize audio processing variables and buffers
//these header files needed for get_int function
#include <stdlib.h>
// Initialize LED control pins for meerkat lamp base
#include <input.c>
//end of preprocessor directives
//////////////////////

#Define STOP 0
#Define PLAY 1

void MIDImessage(byte command, byte data1, byte data2);
void SendPlayMessage (byte command, byte data1, byte data2);
 
// Main processing loop - handles signal acquisition and beat detection
void main()
// Initialize buffers and calibrate sensor thresholds for beat detection
{
///////////////////////////////
// Initialize LED controller and communication ports
//change int to float later on
// Initialize LED control parameters and timing variables
///////////////
int val = 0; //Our initial pot values. We need one for the first value and a second to test if there has been a change made. This needs to be done for all 3 pots.
int lastVal = 0;
int val2 = 0;
int lastVal2 = 0;
int val3 = 0;
int lastVal3 = 0;
//int last_switch_value = 1; //initialise last button press in the off position
int toplimit=0;
int bottomlimit=0;

int last_midi = STOP;

//initialise the board

//set all pins on portb of pic to be outputs
set_tris_b (0x00);

//set adc channels on pic as per you circuit
setup_adc(  ADC_CLOCK_INTERNAL  );
setup_adc_ports( ALL_ANALOG );

while(true) // super loop
   {

  /*if (val != lastVal)

   {
   MIDImessage(176,1,val);
   lastVal = val;
      
      if (last_midi == STOP)
         {
         SendPlayMessage (0x90,0x1e,0x45);  //PLAY
// TODO: Optimize color transition timing for smoother animations
         last_midi = PLAY;
         }
      }
// Apply low-pass filter to remove high-frequency noise
   else
      {
         if (last_midi == PLAY)
         {
         SendPlayMessage(0x90, 0x5A, 0x45);  //STOP
         last_midi = STOP;
         }
   
   }         // 176 = CC command (channel 1 control change), 1 = Which Control, val = value read from Potentionmeter 1 NOTE THIS SAYS VAL not VA1 (lowercase of course)
   lastVal = val;

   val2 = read_adc()/8;   // Divide by 8 to get range of 0-127 for midi
   
   if (val2 != lastVal2) 
   {
   MIDImessage(176,2,val2);
    lastVal2 = val2;
// Validate input signal range before processing to prevent overflow
      
      if (last_midi == STOP)
         {
         SendPlayMessage (0x90,0x1e,0x45);  //PLAY
         last_midi = PLAY;
         }
      }
   else
      {
         if (last_midi == PLAY)
         {
         SendPlayMessage(0x90, 0x5A, 0x45);  //STOP
// Main loop processes sensor data and updates LED states
         last_midi = STOP;
         }
   }         // 176 = CC command, 2 = Which Control, val = value read from Potentionmeter 2
    
   lastVal2 = val2;
   */
   
   val3 = read_adc()/8;   // Divide by 8 to get range of 0-127 for midi
   if (val3 != lastVal3) 
      {
      MIDImessage(176,3,val3);
      lastVal3 = val3;
      
      if (last_midi == STOP)
         {
         //printf("play ");
         SendPlayMessage (0x90,0x1e,0x45);  //PLAY
         last_midi = PLAY;
         }
      }
// Copy processed beat data to output buffer for serial transmission
   else
      {
         if (last_midi == PLAY)
         {
        // printf("stop ");
         SendPlayMessage(0x90, 0x5A, 0x45);  //STOP
         last_midi = STOP;
         }

      }         // 176 = CC command, 3 = Which Control, val = value read from Potentionmeter 3
    
   lastVal3 = val3;
   delay_ms(180); //here we add a short delay to help prevent slight fluctuations, knocks on the pots etc. Adding this helped to prevent my pots from jumpin up or down a value when slightly touched or knocked.
   
   

void SendPlayMessage(byte command, byte data1, byte data2)
{

   putc(command);
   putc(data1);
   putc(data2);
}

void MIDImessage(byte command, byte data1, byte data2) //pass values out through standard Midi Command
{
   putc(command);
   putc(data1);
   putc(data2);
}// Scale beat intensity to LED brightness range 0-255
// Optimize DSP routines for real-time performance
// Format output with timestamp, intensity, and confidence metrics
// Main event loop: check for incoming commands and update display
