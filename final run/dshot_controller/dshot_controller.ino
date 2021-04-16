// Empirically determined by Ed Suominen with an oscilloscope and a good deal of
// pressing Ctrl+U in the Arduino window. No guarantees expressed or implied. Dedicated
// to the public domain.

#include <stdlib.h>

#define pinNum 1
#define PROTOCOL 150

#define NOP1 "nop\n\t"
#define NOP5 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
#define NOP10 "nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t"
#define NOP50 NOP10 NOP10 NOP10 NOP10 NOP10
#define NOP100 NOP50 NOP50
#define NOP1000 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100

// P1-5 are 100-500 ns pauses, tested with an oscilloscope (2 second
// display persistence) and a Teensy 3.2 compiling with
// Teensyduino/Arduino 1.8.1, "faster" setting

#if F_CPU == 600000000

#if PROTOCOL == 150
//#define ON_HIGH __asm__(NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100)
//#define ON_HIGH __asm__(NOP1000 NOP1000 NOP1000 NOP1000 NOP1000 NOP1000 NOP1 NOP1) //5000ns
//#define ON_LOW __asm__(NOP1000 NOP1000) //1666ns
//#define OFF_HIGH __asm__(NOP1000 NOP1000 NOP1000 NOP1) //2500ns
//#define OFF_LOW __asm__(NOP1000 NOP1000 NOP1000 NOP1000 NOP1000) //4166ns
//#elif PROTOCOL == 300
//#define ON_HIGH __asm__(NOP1000 NOP1000 NOP1000 NOP1) //2500ns
//#define ON_LOW __asm__(NOP1000)//833.3ns
//#define OFF_HIGH __asm__(NOP1000 NOP100 NOP100 NOP100 NOP100 NOP100) //1250ns
//#define OFF_LOW __asm__(NOP1000 NOP1000 NOP100 NOP100 NOP100 NOP100 NOP100 NOP1) //2083.3ns
//#elif PROTOCOL == 600
//#define ON_HIGH __asm__(NOP1000 NOP100 NOP100 NOP100 NOP100 NOP100) //1250ns
//#define ON_LOW __asm__(NOP100 NOP100 NOP100 NOP100 NOP100) //416.6ns
//#define OFF_HIGH __asm__(NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP50) //0625ns
//#define OFF_LOW __asm__(NOP1000 NOP100 NOP100 NOP50) //1041.6ns
//#elif PROTOCOL == 1200
#define ON_HIGH __asm__(NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP50)//0625ns
#define ON_LOW __asm__(NOP100 NOP100 NOP50) //208.33ns
#define OFF_HIGH __asm__(NOP100 NOP100 NOP100 NOP50 NOP5 NOP5 NOP5 NOP5 NOP5)//312.5ns
#define OFF_LOW __asm__(NOP100 NOP100 NOP100 NOP100 NOP100 NOP100 NOP5 NOP5 NOP5 NOP5 NOP5)//520.8ns
#endif
#endif

#define PAUSE ON_HIGH

void int2bin (int num,int* si ) {
  int rev[11];
  int i = 0;
  while (num > 0) {
    rev[i] = num % 2;
    num = num/2;
    i++;
  }
  while (i<11) {
      rev[i] = 0;
      i++;
  }
  //reverse it
  
  for (int j = 0; j<11; j++){
      si[j] = rev[10-j];
  }
  
  
}

void crc2bin (int num,int* si ) {
  int rev[4];
  int i = 0;
  while (num > 0) {
    rev[i] = num % 2;
    num = num/2;
    i++;
  }
  while (i<4) {
      rev[i] = 0;
      i++;
  }
  //reverse it
  
  for (int j = 0; j<4; j++){
    
      si[12+j] = rev[3-j];
      
  }
  
}

void on(){
  digitalWriteFast(pinNum, HIGH); // 1
  ON_HIGH;
  digitalWriteFast(pinNum, LOW);
  ON_LOW;
} 

void off(){
  digitalWriteFast(pinNum, HIGH); // 1
  OFF_HIGH;
  digitalWriteFast(pinNum, LOW);
  OFF_LOW;
}

void ns2dshot(int signal_ns, int telemetry){

  //int telemetry = 1;
  
    int final_sig[16];
    int2bin(signal_ns,final_sig);
    final_sig[11] = telemetry; //Telemetry Request
    signal_ns = (signal_ns<<1)+telemetry;
    int crc = ((signal_ns ^ (signal_ns >> 4) ^ (signal_ns >> 8))) & 0x0F;
    //int crc_bi[4];
    crc2bin(crc,final_sig);

    if (telemetry == 0) {
    noInterrupts();
    
    for (int i = 0; i<16; i++) {
      if (final_sig[i] == 1) on();
      else if (final_sig[i] == 0) off();
    }
    
    delayMicroseconds(13.28);
    interrupts();
  } else if (telemetry = 1) {

    //Need it to be inverted to check the signal.

    noInterrupts();
    
    for (int i = 0; i<16; i++) {
      if (final_sig[i] == 0) on();
      else if (final_sig[i] == 1) off();
    }
    
    delayMicroseconds(13.28);
    interrupts();
    
  }
  
}



void setup() {
  pinMode(pinNum, OUTPUT);

  delay(9000);

  int i = 0;
  
  while (i<200000) {
  int input_signal = 0;
  int telemetry = 0;

  ns2dshot(input_signal,telemetry);
  i++;
  
  }
  
  //delay(3000);
  
}

void loop() {
  
  int input_signal = 1046;
  int telemetry = 1;
  ns2dshot(input_signal, telemetry);
  
}
