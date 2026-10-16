#include <stdio.h>
int main()
{
    int data1,data2,ans,i,j;
    int history_data1[100],history_data2[100];
    char history_op[100];
    double history_result[100];
    char op;
    double res;
    i=0;
    while(i<100){
        if(scanf("%d %d %c",&data1,&data2,&op)!=3)
            break;
        switch(op){
            case '+':
                ans=data1+data2;
                res=ans;
                printf("%d",ans);
                break;
            case '-':
                ans=data1-data2;
                res=ans;
                printf("%d",ans);
                break;
            case '*':
                ans=data1*data2;
                res=ans;
                printf("%d",ans);
                break;
            case '/':
                if(data2==0){
                    printf("除数不能为0\n");
                    continue;
                }
                if(data1%data2==0){
                    ans=data1/data2;
                    res=ans;
                    printf("%d",ans);
                }
                else{
                    res=(double)data1/data2;
                    printf("%.2f",res);
                }
                break;
            default:
                printf("不支持的运算符\n");
                continue;
        }
        history_data1[i]=data1;
        history_data2[i]=data2;
        history_op[i]=op;
        history_result[i]=res;
        i++;
    }

    printf("\n计算历史：\n");
    for(j=0;j<i;j++)
        printf("%d %c %d = %g\n",history_data1[j],history_op[j],
               history_data2[j],history_result[j]);

    return 0;
}
