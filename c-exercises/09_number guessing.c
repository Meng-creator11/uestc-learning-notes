#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
	int ans,n;
	int a=0;
	 srand(time(NULL));
	 ans= rand()%100+1;
	
	a++;
	while(a<=10)
	{
		a++;
		scanf("%d",&n);
		if (n<ans){
		printf("猜小了");
	}
		else if(n==ans){
			printf("猜对了");
			
		}
		else if(n>ans) {
			printf("猜大了"); 
    }	
	}
	if (n<ans){
		printf("猜小了");
	}
		else if(n==ans){
			printf("猜对了");
			
		}
		else if(n>ans) {
			printf("猜大了"); 
    }	
    return 0;
}
