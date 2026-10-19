#include <stdio.h>

long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}

int main(void)
{
    int input_a, input_b;
    scanf("%d %d", &input_a, &input_b);

    
    long long a = input_a < 0 ? -(long long)input_a : input_a;
    long long b = input_b < 0 ? -(long long)input_b : input_b;

    long long greatest_common_divisor = gcd(a, b);
    long long least_common_multiple = 0;

    if (greatest_common_divisor != 0)
    {
        
        least_common_multiple = (a / greatest_common_divisor) * b;
    }

    printf("%lld %lld\n", greatest_common_divisor,least_common_multiple);

    return 0;
}