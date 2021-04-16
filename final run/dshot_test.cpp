#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(){
    int test[16];
    int value = 1046;
    int crc;
    test[12] = 0;
    //value |= (0<<0);
    value = (value << 1)+0;
    
    crc = (((value) ^ ((value) >> 4) ^ ((value) >> 8))) & 0x0F;
    int2bin(value,test);
    crc2bin(crc,test);
    for (int i = 0;i<16;i++){
    printf("%d",test[i]);
    }
    printf("\n");
    return 0;
}