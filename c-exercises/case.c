#include <stdio.h>
int main(){
	int grade;
	scanf("%d",&grade);
	grade/=10;
	switch(grade){
		case 9:
		case 10:
			printf("A");
			break;
		case 8:
			printf("B");
	}
	
return 0;	
}
