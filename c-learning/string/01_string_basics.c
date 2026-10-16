#include <stdio.h>
#include <string.h>   /* strlen 等字符串函数都在这里 */

/*
 * 练习 01（c-learning/string）：字符串的本质 —— char 数组 + '\0'
 * 知识点：
 *   1. 字符串就是"以 '\0' 结尾的 char 数组"
 *   2. sizeof（数组占多大）和 strlen（实际几个字符）的区别
 *   3. 用 for / while 遍历字符串；'\0' 是结束标记，不打印
 *   4. ASCII 的用法：小写转大写、字符转数字
 *   5. 输入字符串：scanf("%s") 读单词，fgets 读一整行（并处理掉 '\n'）
 *
 * 编译运行（在 c-learning/string/ 目录下）：
 *   gcc 01_string_basics.c -o 01_string_basics -Wall
 *   .\01_string_basics.exe
 */

/* ------------------------------------------------------------------
 * 【1】字符串的内存结构：字符挨着放，最后多一个 '\0'
 * ------------------------------------------------------------------ */
void demo_structure(void)
{
    char s[] = "hello";      /* 数组长度自动是 6：5 个字符 + 1 个 '\0' */
    char t[10] = "hi";       /* 数组长度 10，前 3 个格子是 'h' 'i' '\0'，其余是 0 */
    int i;

    printf("【1】字符串的结构\n");

    printf("s 的内存：");
    for (i = 0; i < (int)sizeof(s); i++) {
        if (s[i] == '\0')
            printf("[\\0]");                 /* 结束标记，看不见但存在 */
        else
            printf("[%c]", s[i]);
    }
    printf("\n");

    printf("sizeof(s) = %d   <-- 数组占几个字节（编译时确定，含 '\\0'）\n", (int)sizeof(s));
    printf("strlen(s) = %d   <-- 实际几个字符（运行时数到 '\\0' 为止）\n", (int)strlen(s));
    printf("sizeof(t) = %d, strlen(t) = %d   <-- 只用了前 3 格\n\n", (int)sizeof(t), (int)strlen(t));
}

/* ------------------------------------------------------------------
 * 【2】没有 '\0' 的 char 数组"不是字符串"
 * ------------------------------------------------------------------ */
void demo_not_a_string(void)
{
    char u[5] = {'h', 'e', 'l', 'l', 'o'};   /* 5 个格子全被字符占满，没地方放 '\0' */
    char v[6];                               /* 预留一格给 '\0' */
    int i;

    printf("【2】'\\0' 到底有多重要\n");

    printf("u 逐个字符输出：");
    for (i = 0; i < 5; i++)
        putchar(u[i]);
    printf("\n");

    /* 注意：这里不能写 printf("%s", u);
     * 因为 u 没有 '\0'，%s 会一直往后打印内存里的垃圾数据（越界）。 */

    v[0] = 'h'; v[1] = 'e'; v[2] = 'l'; v[3] = 'l'; v[4] = 'o';
    v[5] = '\0';                             /* 手工补上结束标记 */
    printf("v 手工补过 '\\0'，可以整体输出：%s（长度 %d）\n\n", v, (int)strlen(v));
}

/* ------------------------------------------------------------------
 * 【3】遍历字符串：'\0' 就是天然的循环结束条件
 * ------------------------------------------------------------------ */
void demo_traverse(void)
{
    char s[] = "C Language";
    int i = 0;
    int n = 0;

    printf("【3】遍历字符串\n");

    printf("逐个字符（跳过空格）：");
    while (s[i] != '\0') {
        if (s[i] != ' ')
            putchar(s[i]);
        i++;
    }
    printf("\n");

    for (i = 0; s[i] != '\0'; i++)           /* 等价写法：条件就是 s[i] != '\0' */
        n++;
    printf("一共 %d 个字符，strlen 也是 %d\n", n, (int)strlen(s));

    printf("字符和它的 ASCII 码：\n");
    for (i = 0; s[i] != '\0'; i++)
        printf("  s[%d] = '%c'  ASCII = %d\n", i, s[i], s[i]);
    printf("\n");
}

/* ------------------------------------------------------------------
 * 【4】用 ASCII 做大小写转换（字符串可以直接在数组里改）
 * ------------------------------------------------------------------ */
void to_upper(char s[])
{
    int i;

    for (i = 0; s[i] != '\0'; i++)
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] = s[i] - 'a' + 'A';         /* 小写比大写大 32，写成 'a'-'A' 更好记 */
}

void count_letters(char s[])      /* 数组传参是"传地址"，函数里能直接读到全部字符 */
{
    int i;
    int upper = 0, lower = 0, digit = 0, other = 0;

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z')
            upper++;
        else if (s[i] >= 'a' && s[i] <= 'z')
            lower++;
        else if (s[i] >= '0' && s[i] <= '9')
            digit++;
        else
            other++;
    }

    printf("  大写 %d 个，小写 %d 个，数字 %d 个，其他字符 %d 个\n",
           upper, lower, digit, other);
}

void demo_case(void)
{
    char s[] = "UESTC 2026 Class-C";

    printf("【4】大小写转换与字符统计\n");
    printf("原文：%s\n", s);
    count_letters(s);                        /* 统计原文字符 */

    to_upper(s);                             /* 直接在原数组上改 */
    printf("转大写：%s\n", s);
    count_letters(s);                        /* 转换后再统计，小写变成 0 了 */
    printf("\n");
}

/* ------------------------------------------------------------------
 * 【5】输入字符串
 *   scanf("%s", s)  读"一个单词"：遇到空格/回车就停
 *   fgets(s, n, stdin) 读"一整行"：连空格也读进来
 * 两个重点：
 *   (a) scanf 里 %s 不需要写 &，因为数组名本身就是地址
 *   (b) fgets 会把行末的 '\n' 也读进来，一般要把它改成 '\0'
 * ------------------------------------------------------------------ */
void demo_input(void)
{
    char line[100];
    char word[10];
    int len;

    printf("【5】输入字符串（跟着提示敲一行字试试）\n");

    printf("请输入一整行（可以带空格）：");
    fgets(line, sizeof(line), stdin);

    len = (int)strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';                /* 把行末的换行符删掉，这是标配操作 */

    printf("你输入的是：[%s]，长度 %d\n", line, (int)strlen(line));

    printf("请输入一个单词（遇到空格就结束）：");
    scanf("%9s", word);                      /* 9 = 数组长度10 - 1，防止输入过长溢出 */
    printf("读到的单词是：[%s]\n", word);

    /* 常见坑：如果先 scanf 再 fgets，scanf 留在缓冲区里的 '\n' 会被 fgets 当成一整行读走，
     * 结果 fgets 读到一个空行。解决办法是在两者之间写一句 while (getchar() != '\n'); */
}

int main(void)
{
    demo_structure();
    demo_not_a_string();
    demo_traverse();
    demo_case();
    demo_input();

    return 0;
}
