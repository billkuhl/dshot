#define outPin 1

// all the definitions below are for DSHOT 150
#define ON_HIGH 5000 // delay for 1 bit in nanoseconds
#define ON_LOW 1666 // off portion of the 1 bit
#define OFF_HIGH 2500 // delay for 0 bit in nanoseconds
#define OFF_LOW 4166 // offf portion of the 1 bit

void on() {
  
  // Executes exactly one "on" bit
  digitalWrite(outPin,HIGH);
  delayNanoseconds(ON_HIGH);
  digitalWrite(outPin,LOW);
  delayNanoseconds(ON_LOW);
  
}

void off() {
  
  // Executes exactly one "off" bit
  digitalWrite(outPin,HIGH);
  delayNanoseconds(OFF_HIGH);
  digitalWrite(outPin,LOW);
  delayNanoseconds(OFF_LOW);
  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(outPin,OUTPUT);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  on();
  off();
  
}
