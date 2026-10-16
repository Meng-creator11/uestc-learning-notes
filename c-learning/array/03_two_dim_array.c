#include <stdio.h>

/*
 * 练习 03（c-learning/array）：二维数组（矩阵）
 * 知识点：
 *   1. 定义 int m[行][列]、初始化、双重循环遍历
 *   2. 二维数组只是"一行接一行"铺开的一维内存，m[i][j] 照样靠下标算地址
 *   3. 矩阵转置：m[i][j] <-> m[j][i]
 *   4. 求最大值及它的行列位置、按行/按列求和
 *   5. 杨辉三角：每个数 = 上一行左右两个数之和
 *   6. 函数参数里写 int a[][COLS]，第二维（列数）必须写清楚
 *
 * 编译运行（在 c-learning/array/ 目录下）：
 *   gcc 03_two_dim_array.c -o 03_two_dim_array -Wall
 *   .\03_two_dim_array.exe
 */

#define ROWS 3       /* 行数 */
#define COLS 4       /* 列数 */

/* 打印 ROWS 行 COLS 列的矩阵
 * 注意 a[][COLS] 里的 COLS 不能省：编译器要靠它算出 a[i][j] 到底在第几个格子 */
void print_matrix(const char *name, int a[][COLS], int rows)
{
    int i, j;

    printf("%s =\n", name);
    for (i = 0; i < rows; i++) {
        printf("   ");
        for (j = 0; j < COLS; j++)
            printf("%5d", a[i][j]);
        printf("\n");
    }
}

/* 转置后的矩阵是 COLS 行 ROWS 列，列数变了，所以要用另一个打印函数 */
void print_transposed(const char *name, int t[][ROWS], int rows)
{
    int i, j;

    printf("%s =\n", name);
    for (i = 0; i < rows; i++) {
        printf("   ");
        for (j = 0; j < ROWS; j++)
            printf("%5d", t[i][j]);
        printf("\n");
    }
}

/* ------------------------------------------------------------------
 * 【1】定义、初始化、遍历
 * ------------------------------------------------------------------ */
void demo_basic(void)
{
    int m[ROWS][COLS] = {                       /* 3 行 4 列 */
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12}
    };
    int i, j;
    int sum = 0;

    printf("【1】二维数组的定义与遍历\n");
    print_matrix("m", m, ROWS);

    printf("   一共 %d 行 %d 列，共 %d 个元素\n", ROWS, COLS, ROWS * COLS);
    printf("   m[0][0] = %d（第 1 行第 1 列）\n", m[0][0]);
    printf("   m[2][3] = %d（第 3 行第 4 列，下标最大的一格）\n", m[2][3]);
    printf("   访问方式：m[行][列]，第一维是行，第二维是列，别写反\n");

    for (i = 0; i < ROWS; i++)                  /* 外层走行，内层走列 */
        for (j = 0; j < COLS; j++)
            sum += m[i][j];
    printf("   所有元素之和 = %d\n\n", sum);
}

/* ------------------------------------------------------------------
 * 【2】矩阵转置：把第 i 行第 j 列，放到第 j 行第 i 列
 * ------------------------------------------------------------------ */
void demo_transpose(void)
{
    int m[ROWS][COLS] = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12}
    };
    int t[COLS][ROWS];                          /* 转置后：4 行 3 列 */
    int i, j;

    printf("【2】矩阵转置\n");
    print_matrix("原矩阵 m", m, ROWS);

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            t[j][i] = m[i][j];                  /* 行列下标互换，就这一句 */

    print_transposed("转置后 t", t, COLS);
    printf("   转置后行数变列数、列数变行数\n\n");
}

/* ------------------------------------------------------------------
 * 【3】最大值及位置、按行求和、按列求和
 * ------------------------------------------------------------------ */
void demo_stat(void)
{
    int m[ROWS][COLS] = {
        { 17,  8, 42,  4},
        { 99, 23, 61, 35},
        {  7, 56, 12, 88}
    };
    int i, j;
    int max, max_r, max_c;
    int row_sum;

    printf("【3】矩阵统计\n");
    print_matrix("m", m, ROWS);

    max = m[0][0];                              /* 擂台法：先拿第一格当擂主 */
    max_r = max_c = 0;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (m[i][j] > max) {
                max = m[i][j];
                max_r = i;
                max_c = j;
            }
        }
    }
    printf("   最大值 = %d，位置是第 %d 行第 %d 列（m[%d][%d]）\n",
           max, max_r + 1, max_c + 1, max_r, max_c);

    for (i = 0; i < ROWS; i++) {                /* 按行求和：内层循环走列 */
        row_sum = 0;
        for (j = 0; j < COLS; j++)
            row_sum += m[i][j];
        printf("   第 %d 行之和 = %d\n", i + 1, row_sum);
    }

    for (j = 0; j < COLS; j++) {                /* 按列求和：外层走列，内层走行 */
        int col_sum = 0;
        for (i = 0; i < ROWS; i++)
            col_sum += m[i][j];
        printf("   第 %d 列之和 = %d\n", j + 1, col_sum);
    }
    printf("\n");
}

/* ------------------------------------------------------------------
 * 【4】杨辉三角
 *   每行的第一个数固定是 1；
 *   其余每个数 = 上一行同一列 + 上一行前一列
 * ------------------------------------------------------------------ */
#define PASCAL_N 8

void demo_pascal(void)
{
    int a[PASCAL_N][PASCAL_N] = {0};             /* 全部清零，省得处理边界 */
    int i, j;

    printf("【4】杨辉三角（%d 行）\n", PASCAL_N);

    for (i = 0; i < PASCAL_N; i++) {
        a[i][0] = 1;                             /* 第一个数总是 1 */
        for (j = 1; j <= i; j++)
            a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
    }

    for (i = 0; i < PASCAL_N; i++) {             /* 这里列数逐行变化，直接自己写打印循环 */
        printf("   ");
        for (j = 0; j <= i; j++)
            printf("%4d", a[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
    demo_basic();
    demo_transpose();
    demo_stat();
    demo_pascal();

    return 0;
}
