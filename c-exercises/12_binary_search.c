#include <stdio.h>
int main(){
int a[] = {1, 3, 5, 7, 9, 11, 13};
int left = 0;
int right = 6;
int target = 11;

while (left <= right)
{
    int mid = (left + right) / 2;

    if (a[mid] == target)
    {
        printf("找到了，下标是 %d\n", mid);
        break;
    }
    else if (a[mid] < target)
    {
        left = mid + 1;
    }
    else
    {
        right = mid - 1;
    }
}
}