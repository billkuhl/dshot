#include <stdio.h>
#include <stdlib.h>
int main() {
    int value = 2092;
    int crc = (~(value ^ (value >> 4) ^ (value >> 8))) & 0x0F;
    printf("%n",crc);
}