#include <stdio.h>

int main(void)
{
    double a, b, result;
    char op, choice;
    int ret;

    do
    {
        ret = scanf("%lf %c %lf", &a, &op, &b);

        if (ret != 3)
        {
            printf("error\n");

            choice = getchar();

            if (choice == 'y' || choice == 'Y')
                continue;
            else
                break;
        }

        int valid = 1;

        switch (op)
        {
        case '+':
            result = a + b;
            break;

        case '-':
            result = a - b;
            break;

        case '*':
            result = a * b;
            break;

        case '/':
            if (b == 0)
            {
                valid = 0;
            }
            else
            {
                result = a / b;
            }
            break;

        default:
            valid = 0;
        }

        if (valid)
        {
            printf("%.2f %c %.2f = %.2f\n",
                   a, op, b, result);
        }
        else
        {
            printf("error\n");
        }

        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
