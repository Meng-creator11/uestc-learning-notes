#include <stdio.h>

/*
 * 练习 01（c-learning/array）：一维数组基础
 * 知识点：
 *   1. 数组的定义：类型 数组名[长度];   下标从 0 开始，范围 0 ~ 长度-1
 *   2. 初始化：部分初始化自动补 0；{0} 表示全部清零；省略长度由初值决定
 *   3. 遍历、求和/平均、求最值、逆序、分类计数、线性查找
 *   4. 数组当作函数参数时，必须"数组 + 长度"一起传
 *
 * 编译运行（在 c-learning/array/ 目录下）：
 *   gcc 01_array_basics.c -o 01_array_basics -Wall
 *   .\01_array_basics.exe
 *
 * 建议：先自己猜每个 demo 的输出，再运行对照。
 */

#define N 8   /* 数组长度用常量：以后想改成 10 个分数，只改这一行 */

/* ------------------------------------------------------------------
 * 工具函数：打印数组
 * 注意 a[] 在这里已经"退化"成指针，所以长度 n 必须另外传进来
 * ------------------------------------------------------------------ */
void print_array(const char *name, int a[], int n)
{
    int i;

    printf("%s = [", name);
    for (i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1)
            printf(", ");          /* 最后一个元素后面不打印逗号，好看一点 */
    }
    printf("]\n");
}

/* ------------------------------------------------------------------
 * 【1】定义与遍历：数组的价值 = 让批量数据能被循环处理
 * ------------------------------------------------------------------ */
void demo_traverse(void)
{
    int a[5] = {3, 1, 4, 1, 5};
    int i;

    printf("【1】定义与遍历\n");
    printf("a[0] = %d, a[4] = %d   <-- 下标是 0~4，不是 1~5\n", a[0], a[4]);

    printf("正着遍历：");
    for (i = 0; i < 5; i++)          /* 条件写 i < 5，绝不要写 i <= 5 */
        printf("%d ", a[i]);
    printf("\n");

    printf("倒着遍历：");
    for (i = 4; i >= 0; i--)
        printf("%d ", a[i]);
    printf("\n\n");
}

/* ------------------------------------------------------------------
 * 【2】初始化的三种常见写法
 * ------------------------------------------------------------------ */
void demo_init(void)
{
    int a[5] = {1, 2, 3};      /* 只写 3 个，后面自动补 0 */
    int b[5] = {0};            /* 最常用的"全部清零"写法 */
    int c[]  = {10, 20, 30};   /* 省略长度：由初值个数决定，这里长度是 3 */
    int n = (int)(sizeof(c) / sizeof(c[0]));   /* 求元素个数的常用公式 */

    printf("【2】初始化\n");
    print_array("int a[5] = {1, 2, 3}   ->", a, 5);
    print_array("int b[5] = {0}         ->", b, 5);
    print_array("int c[]  = {10,20,30}  ->", c, n);
    printf("元素个数 = sizeof(c)/sizeof(c[0]) = %d\n\n", n);
}

/* ------------------------------------------------------------------
 * 【3】求和、平均、最大值/最小值（以及它们的位置）
 * ------------------------------------------------------------------ */
void demo_sum_max(void)
{
    int score[N] = {72, 95, 60, 88, 95, 45, 100, 66};
    int i;
    int sum = 0;
    double avg;
    int max, min, max_pos, min_pos;

    printf("【3】求和 / 平均 / 最值\n");
    print_array("score", score, N);

    for (i = 0; i < N; i++)
        sum += score[i];
    avg = (double)sum / N;      /* 要点：转成 double，否则整数除法会丢掉小数 */

    max = min = score[0];       /* 擂台法：先让第 0 个元素当擂主，别初始化成 0 */
    max_pos = min_pos = 0;
    for (i = 1; i < N; i++) {
        if (score[i] > max) {
            max = score[i];
            max_pos = i;
        }
        if (score[i] < min) {
            min = score[i];
            min_pos = i;
        }
    }

    printf("总分 = %d，平均分 = %.2f\n", sum, avg);
    printf("最高分 = %d（第 %d 个元素，score[%d]）\n", max, max_pos + 1, max_pos);
    printf("最低分 = %d（第 %d 个元素，score[%d]）\n\n", min, min_pos + 1, min_pos);
}

/* ------------------------------------------------------------------
 * 【4】逆序：首尾配对交换（双指针），循环条件 i < j
 * ------------------------------------------------------------------ */
void demo_reverse(void)
{
    int a[6] = {1, 2, 3, 4, 5, 6};
    int i = 0, j = 5, t;

    printf("【4】逆序\n");
    print_array("交换前", a, 6);

    while (i < j) {
        t = a[i];       /* 三步交换，必须用临时变量 */
        a[i] = a[j];
        a[j] = t;
        i++;
        j--;
    }

    print_array("交换后", a, 6);
    printf("\n");
}

/* ------------------------------------------------------------------
 * 【5】分类计数：把分数按档次统计人数（数组当"计数器"用）
 * ------------------------------------------------------------------ */
void demo_count(void)
{
    int score[N] = {72, 95, 60, 88, 95, 45, 100, 66};
    int cnt[5] = {0};    /* cnt[0]~cnt[4] 分别统计五个档次，初值全 0 */
    int i;
    const char *level[5] = {"不及格(<60)", "及格(60~69)", "中(70~79)", "良(80~89)", "优(90~100)"};

    printf("【5】分类计数\n");
    print_array("score", score, N);

    for (i = 0; i < N; i++) {
        if (score[i] < 60)
            cnt[0]++;
        else if (score[i] < 70)
            cnt[1]++;
        else if (score[i] < 80)
            cnt[2]++;
        else if (score[i] < 90)
            cnt[3]++;
        else
            cnt[4]++;          /* 90~100 都进这里，100 分也不会越界 */
    }

    for (i = 0; i < 5; i++)
        printf("%-14s %d 人\n", level[i], cnt[i]);
    printf("\n");
}

/* ------------------------------------------------------------------
 * 【6】线性查找：从头到尾逐个比较，找到返回下标，找不到返回 -1
 * ------------------------------------------------------------------ */
int find_index(int a[], int n, int key)
{
    int i;

    for (i = 0; i < n; i++)
        if (a[i] == key)
            return i;      /* 找到就立刻返回 */
    return -1;             /* 循环结束还没找到 */
}

void demo_find(void)
{
    int a[6] = {17, 8, 42, 4, 99, 23};

    printf("【6】线性查找\n");
    print_array("a", a, 6);
    printf("找 42 -> 下标 %d\n", find_index(a, 6, 42));
    printf("找 17 -> 下标 %d\n", find_index(a, 6, 17));
    printf("找 55 -> 下标 %d（返回 -1 表示不存在）\n\n", find_index(a, 6, 55));
}

int main(void)
{
    demo_traverse();
    demo_init();
    demo_sum_max();
    demo_reverse();
    demo_count();
    demo_find();

    return 0;
}
