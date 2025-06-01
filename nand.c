#include <stdlib.h>
#include <stdio.h>

typedef struct {
    unsigned int bits : 16;
    unsigned int mask : 16;
    unsigned int carry : 1;
} Bits;


int nand(int a, int b) {
  return !(a&b);
}

int and(int a, int b) {
  return (nand(nand(a,b),nand(a,b)));
}

int or(int a, int b){
  return (nand(nand(a,a), nand(b,b)));
}

int nor(int a, int b){
  return nand(nand(nand(a,a), nand(b,b)), nand(nand(a,a), nand(b,b)));
}

int xor(int a, int b){
  return and(or(a,b), nand(a,b));
}

int xnor(int a, int b){
  return nand(nand(nand(a,a), nand(b,b)), nand(a,b));
}


int print_byte(Bits a) {
  for (int i=15;i>=0;i--){
    a.mask = 1;
    printf("%d",(a.bits >> i) & a.mask);
  }
  printf("   %d\n", a.carry);
}


int main() {

  Bits a;
  a.bits = 0;
  a.mask = 1;
  a.carry = 1;
  print_byte(a);

  for (int a=0;a<2;a++){
  for (int b=0;b<2;b++){
    int i_luv_proton = xor(a,b);
    printf("a: %d, b: %d, NAND: %d, R: %d\n", a, b, nand(a,b), i_luv_proton);
  }
  }

  for(unsigned long int j=0;j<1<<31;j++){
    a.carry = 1;
    for (int i=0;i<16;i++){
      int w = a.bits>>i&1;
      int r = xor(w,a.carry);
      if(r){
        a.bits |= 1<<i;
        a.carry = 0;
      } else if((a.bits >> i) & 1){
        a.mask = 0;
        a.mask = ~a.mask;
        a.mask ^= 1<<i;
        a.bits &= a.mask;
      }
    }
  print_byte(a);
  }


}
