#include <stdio.h>

/*
 * 练习 02（c-learning/array）：数组上的经典算法
 * 知识点：
 *   1. 冒泡排序（带"提前结束"优化）
 *   2. 二分查找（前提：数组必须已排好序）
 *   3. 删除元素：后面的元素统统往前搬
 *   4. 插入元素：后面的元素统统往后搬
 * 一句话总结：数组"查"很快、"增删"很慢——因为增删要搬动大量数据。
 *
 * 编译运行（在 c-learning/array/ 目录下）：
 *   gcc 02_array_algorithms.c -o 02_array_algorithms -Wall
 *   .\02_array_algorithms.exe
 */

void print_array(const char *name, int a[], int n)
{
    int i;

    printf("%s = [", name);
    for (i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1)
            printf(", ");
    }
    printf("]\n");
}

/* ------------------------------------------------------------------
 * 【1】冒泡排序：相邻两个比大小，大的往右挪
 * 每跑完一轮，最大的那个就"冒"到了最右边（有序区 +1）
 * ------------------------------------------------------------------ */
void bubble_sort(int a[], int n)
{
    int i, j, t, swapped;

    for (i = 0; i < n - 1; i++) {            /* 一共最多 n-1 轮 */
        swapped = 0;                          /* 记录本轮有没有交换过 */
        for (j = 0; j < n - 1 - i; j++) {     /* 后面 i 个已经排好，不用再比 */
            if (a[j] > a[j + 1]) {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
                swapped = 1;
            }
        }
        printf("  第 %d 轮结束：", i + 1);
        print_array("a", a, n);
        if (!swapped) {                       /* 一轮下来没换过，说明已经有序 */
            printf("  （本轮无交换，提前结束）\n");
            break;
        }
    }
}

/* ------------------------------------------------------------------
 * 【2】二分查找：每次砍掉一半，但数组必须已经从小到大排好序
 * 返回下标，找不到返回 -1
 * ------------------------------------------------------------------ */
int binary_search(int a[], int n)
{
     a[] = {1, 3, 5, 7, 9, 11, 13};
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

/* ------------------------------------------------------------------
 * 【3】删除下标为 pos 的元素：把 pos 后面的元素全部往前搬一格
 * 返回删除后的新长度
 * ------------------------------------------------------------------ */
int delete_at(int a[], int n, int pos)
{
    int i;

    if (pos < 0 || pos >= n)
        return n;                          /* 位置非法，什么都不做 */

    for (i = pos; i < n - 1; i++)
        a[i] = a[i + 1];                   /* 后面的人依次往前站 */

    return n - 1;                          /* 元素少了一个 */
}

/* ------------------------------------------------------------------
 * 【4】往"已排好序"的数组里插入一个数，插完仍然有序
 * n 是当前元素个数，调用者要保证数组装得下（容量足够）
 * 返回插入后的新长度
 * ------------------------------------------------------------------ */
int insert_sorted(int a[], int n, int value)
{
    int i = n - 1;

    while (i >= 0 && a[i] > value) {       /* 从右往左找位置，同时把大的数往后挪 */
        a[i + 1] = a[i];
        i--;
    }
    a[i + 1] = value;                      /* 空出来的位置放新数 */

    return n + 1;
}

int main(void)
{
    int a[9] = {72, 95, 60, 88, 45, 100, 66, 81, 53};
    int sorted[8] = {5, 12, 23, 34, 47, 58, 69, 80};
    int b[9] = {10, 20, 30, 40, 50, 60, 70, 80, 90};   /* 用来演示删除 */
    int c[16] = {5, 12, 23, 34, 47, 58, 69, 80};       /* 容量 16，可以插入 */
    int n;
    int key, pos;

    printf("【1】冒泡排序\n");
    print_array("排序前", a, 9);
    bubble_sort(a, 9);
    print_array("排序后", a, 9);
    printf("\n");

    printf("【2】二分查找（数组必须已有序）\n");
    print_array("sorted", sorted, 8);
    key = 47;
    printf("查找 %d：\n", key);
    pos = binary_search(sorted, 8, key);
    printf("-> 下标 %d\n", pos);

    key = 40;
    printf("查找 %d：\n", key);
    pos = binary_search(sorted, 8, key);
    printf("-> 下标 %d（-1 表示不存在）\n\n", pos);

    printf("【3】删除元素（后面的元素要往前搬）\n");
    n = 9;
    print_array("删除前", b, n);
    n = delete_at(b, n, 2);            /* 删掉下标 2，也就是 30 */
    print_array("删掉下标 2 后", b, n);
    printf("长度从 9 变成 %d——在数组中间删一个数，后面的元素都得搬家\n\n", n);

    printf("【4】插入元素（后面的元素要往后搬）\n");
    n = 8;
    print_array("插入前", c, n);
    n = insert_sorted(c, n, 40);
    print_array("插入 40 后", c, n);
    n = insert_sorted(c, n, 100);
    print_array("再插入 100 后", c, n);
    printf("长度从 8 变成 %d\n", n);

    return 0;
}
