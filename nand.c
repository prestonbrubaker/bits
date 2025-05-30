#include <stdlib.h>
#include <stdio.h>

typedef struct {
    unsigned int bits : 8;
    unsigned int mask : 8;
    unsigned int carry : 1;
} Bits;


int nand(int a, int b) {
  return !(a&&b);
}

int print_byte(Bits a) {
  for (int i=7;i>=0;i--){
    a.mask = 1;
    printf("%d",(a.bits >> i) & a.mask);
  }
  printf("\n");
}

long exp22(int a) {
  long r = 1;
  for (int i=0;i<a;i++){
    r *=2;
  }
  return r;
}


int main() {

  Bits a;
  a.bits = 255;
  a.mask = 1;
  a.carry = 1;
  print_byte(a);
  a.bits |= a.mask << 1;
  print_byte(a);

  for (int j=0;j<5;j++){
  for (int i=0;i<8;i++) {
  int k = i;
  int r = nand((a.bits >> k) & a.mask, (a.bits >> (k - 1)) & a.mask);
  if (r) {
    a.bits |= (1 << k);
  } else {
    a.bits &= ~(1 << k);
  }
  
  print_byte(a);
  //printf("%d\n", a.bits);
  }
  printf("\n");
  }
  
}
