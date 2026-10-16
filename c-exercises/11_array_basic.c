#define N 5
#include <stdio.h>
void go_thru_array()
{
    int a[N];

    for (int i = 0; i < N; i++)
    {
        a[i] = 0;
        printf("%d\n", a[i]);
    }
}
void reverse_order()
{
    int b[N]={25,35,55,66,99};
    int i=0,j=N-1,t;
    while(i<j)
    {
        t = b[i];
        b[i] = b[j];
        b[j] = t;
        i++;
        j--;
    }
    for (int k=0;k<N;k++)
    {
        printf("%d ",b[k]);
    }
    printf("\n");
}


#include <stdio.h>
void bubble_sort(void)          /* 空参数写 void，比 () 更严谨 */
{
    int c[10] = {99, 68, 30, 29, 19, 6, 3, 23, 36, 21};
    int i, j, t; /* j 提出来声明，老编译器(gnu89)也能过 */

    for (i = 0; i < 9; i++)
    { /* 最多 9 轮，每轮把一个大的送到右边 */
        for (j = 0; j < 9 - i; j++)
        { /* 后面 i 个已经排好，不用再比 */
            if (c[j] > c[j + 1])
            { /* 相邻两个比，大的往右换 */
                t = c[j];
                c[j] = c[j + 1];
                c[j + 1] = t;
            }
        }
    }

    for (i = 0; i < 10; i++) /* 10 个元素就打印 10 个 */
        printf("%d ", c[i]);
    printf("\n");
}

int main(void)
{
       return 0;
}