/*主函数+loop函数
主函数目的：输入两个数字，输出两个数字中间的所有回文数
loop函数目的：判断一个数字是不是回文数
算法：设计一个for循环
*/
#include<stdio.h>
int loop(int x);
int main()
{
    int a,b;
 scanf("%d %d",&a,&b);
  for (int x=a;x<=b;x++){
    if(loop(x)){
        printf("%d\n",x);
    }
  } 
  return 0;
}
int loop(int x){
int original=x;
long long reverse=0;
while(x>0){
    reverse=reverse*10+x%10;
    x/=10;
}
return reverse==original;
}


