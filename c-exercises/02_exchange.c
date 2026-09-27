#include <stdio.h>
int main(){
 unsigned short x,y,z;
 scanf("%hu %hu",&x,&y);
 z=(x&0xFF00)|((y>>8)&0x00FF);
 printf("%d\n",z);
 return 0;	
} 
