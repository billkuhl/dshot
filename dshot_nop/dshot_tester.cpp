// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>


// typedef struct signal {
//     public:
//     int dsig[11];
//     int tel[1];
//     int csum[4];
//     int total[16];
//     void create_sig(int ns_val){
        
//         int num = ns_val;
//         int rev[11];
//         int i = 0;
//         while (num > 0) {
//             rev[i] = num % 2;
//             num = num/2;
//             i++;
//         }
//         while (i<11) {
//             rev[i] = 0;
//             i++;
//         }
//         //reverse it
        
//         for (int j = 0; j<11; j++){
//             dsig[j] = rev[10-j];
//         }

       
//     };
    
// }sig;



// void int2bin (int num,int* signal ) {
//   int rev[11];
//   int i = 0;
//   while (num > 0) {
//     rev[i] = num % 2;
//     num = num/2;
//     i++;
//   }
//   while (i<11) {
//       rev[i] = 0;
//       i++;
//   }
//   //reverse it
  
//   for (int j = 0; j<11; j++){
//       signal[j] = rev[10-j];
//   }
//   printf("%n",signal);
//   fflush(stdout);
  
// }

// // int main(int argc, char** argv) {
// //     int i = 2047;
// //     sig* s = create_sig(i);
// //     for (int j = 0; j<11;j++){
// //     printf("%d",(int) s->dsig[i]);
// //     }
// //     int j;
// //     }
