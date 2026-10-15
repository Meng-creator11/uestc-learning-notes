#include <stdio.h>
int main()
{
    int data1,data2,ans,i;
    char op;
    double res;
    i=0;
    i++;
    while(i<=100){
    i++;
	scanf("%d %d %c",&data1,&data2,&op);
    switch(op){
        case '+':
        ans=data1+data2;
            printf("%d",ans);
            break;
             
        case '-':
            {ans=data1-data2;
             printf("%d",ans);
             break;
            }
        case'*':
            ans=data1*data2;
            printf("%d",ans);
            break;
    
        case'/':
            if(data1%data2==0)
            {ans=data1/data2;
            printf("%d",ans);}
            else {res=(double)data1/data2;
            printf("%.2f",res);}
            break;

    
    return 0;
   }
}
}

