#include <stdio.h>
int main(){
	int a,b,c;
	float s,S;
	scanf("%d %d %d",&a,&b,&c);
	s=(a+b+c)/2;
	S=sqrt(s*(s-a)*(s-b)*(s-c));
	printf("%.3f",S);
	return 0;
} 
