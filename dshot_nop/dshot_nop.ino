// Empirically determined by Ed Suominen with an oscilloscope and a good deal of
// pressing Ctrl+U in the Arduino window. No guarantees expressed or implied. Dedicated
// to the public domain.

#define pinNum 1
#define PROTOCOL 150

void setup() {
  pinMode(pinNum, OUTPUT);
}

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




//#define P1 __asm__(NOP4 NOP4)
//#define P2 __asm__(NOP6 NOP6 NOP6)
//#define P3 __asm__(NOP6 NOP6 NOP6 NOP6 NOP3)
//#define P4 __asm__(NOP6 NOP6 NOP6 NOP6 NOP6 NOP4 NOP4)
//#define P5 __asm__(NOP6 NOP6 NOP6 NOP6 NOP6 NOP6 NOP6 NOP4 NOP3)

#endif

#define PAUSE ON_HIGH

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

void loop() {
  noInterrupts();
  PAUSE;
  PAUSE;
  PAUSE;
  off();
  off();
  off();
  on();
  on();
  on();
  off();
  off();
  off();
  PAUSE;
  PAUSE;
  PAUSE;
  interrupts();
}
