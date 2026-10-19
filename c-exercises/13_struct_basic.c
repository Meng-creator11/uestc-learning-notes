
#include <stdio.h>

struct Student
{
    char name[20];
    int age;
    float score;
};

int main(void)
{
    struct Student s[3] = {
        {"Tom", 18, 90.0f},
        {"Amy", 19, 95.0f},
        {"Jack", 18, 88.0f}};

    float sum = 0;
    int maxIndex = 0;

    for (int i = 0; i < 3; i++)
    {
        printf("%s：%.1f 分\n", s[i].name, s[i].score);

        sum += s[i].score;

        if (s[i].score > s[maxIndex].score)
        {
            maxIndex = i;
        }
    }

    printf("平均成绩：%.2f\n", sum / 3);
    printf("最高分学生：%s\n", s[maxIndex].name);

    return 0;
}
