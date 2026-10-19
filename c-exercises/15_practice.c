#include <stdio.h>
int main(){
   int a;
   a=-100;
   unsigned long value = (unsigned long)a;
   printf("%1u\n", value);
   printf("%zu",sizeof(long long));
   return 0;
}