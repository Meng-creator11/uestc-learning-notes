#include <stdio.h>
#include <string.h>   /* 这里放的是"标准库"版本的同名函数，用来和手写版本对照 */

/*
 * 练习 02（c-learning/string）：亲手实现字符串函数
 * 知识点：
 *   1. 手写 mystrlen / mystrcpy / mystrcat / mystrcmp，理解库函数是怎么做出来的
 *   2. 数组传参传的是"地址"：函数里改数组，main 里也能看见
 *   3. 三条铁律：不能 s1 = s2；不能 if (s1 == s2)；库里比字符串用 strcmp
 *
 * 编译运行（在 c-learning/string/ 目录下）：
 *   gcc 02_string_functions.c -o 02_string_functions -Wall
 *   .\02_string_functions.exe
 */

/* ------------------------------------------------------------------
 * 求长度：从开头数到 '\0' 为止（'\0' 本身不算）
 * ------------------------------------------------------------------ */
int mystrlen(const char s[])
{
    int n = 0;

    while (s[n] != '\0')
        n++;

    return n;
}

/* ------------------------------------------------------------------
 * 复制：把 src 一个字符一个字符抄到 dst（最后别忘了补 '\0'）
 * ------------------------------------------------------------------ */
void mystrcpy(char dst[], const char src[])
{
    int i = 0;

    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';              /* 少了这一句，dst 就不是字符串了 */
}

/* ------------------------------------------------------------------
 * 追加：先走到 dst 的末尾，再把 src 接上去
 * ------------------------------------------------------------------ */
void mystrcat(char dst[], const char src[])
{
    int i = 0, j = 0;

    while (dst[i] != '\0')      /* 第一步：找 dst 的结尾 */
        i++;

    while (src[j] != '\0') {    /* 第二步：从结尾开始接 */
        dst[i] = src[j];
        i++;
        j++;
    }
    dst[i] = '\0';              /* 第三步：给新字符串补上结尾 */
}

/* ------------------------------------------------------------------
 * 比较：从第一个字符开始逐个比，谁先不同谁就"大"（按 ASCII 码）
 * 返回 0 表示相等。标准只保证"正数/负数/零"，不保证具体差值。
 * ------------------------------------------------------------------ */
int mystrcmp(const char s1[], const char s2[])
{
    int i = 0;

    while (s1[i] != '\0' && s1[i] == s2[i])
        i++;

    return s1[i] - s2[i];
}

void show_cmp(const char s1[], const char s2[])
{
    printf("比较 \"%s\" 和 \"%s\"：\n", s1, s2);
    printf("  strcmp   = %3d   mystrcmp = %3d\n", strcmp(s1, s2), mystrcmp(s1, s2));
    if (mystrcmp(s1, s2) == 0)
        printf("  -> 相等\n");
    else if (mystrcmp(s1, s2) < 0)
        printf("  -> s1 在前（字典序更小）\n");
    else
        printf("  -> s2 在前（字典序更小）\n");
}

int main(void)
{
    char buf[50];
    char s[] = "hello";

    printf("【1】求长度\n");
    printf("mystrlen(\"%s\") = %d，strlen 也是 %d\n\n", s, mystrlen(s), (int)strlen(s));

    printf("【2】复制\n");
    /* 小提示：strlen 数的是"字节数"不是"字数"，
     * 一个汉字在 UTF-8 里通常占 3 个字节，所以含中文时长度会比汉字个数大。 */
    mystrcpy(buf, "C 语言");
    printf("复制后 buf = [%s]，长度 %d\n", buf, mystrlen(buf));
    strcpy(buf, "标准库 strcpy");
    printf("库函数复制后 buf = [%s]\n\n", buf);

    printf("【3】追加\n");
    mystrcpy(buf, "UESTC");
    mystrcat(buf, " 2026");
    printf("接完以后 buf = [%s]\n\n", buf);

    printf("【4】比较\n");
    show_cmp("abc", "abd");        /* 'c' < 'd' */
    show_cmp("abc", "abc");
    show_cmp("b", "a");
    show_cmp("abc", "abcd");       /* 短的是长的前缀，短的更小 */
    printf("\n");

    printf("【5】为什么不能 s1 = s2、不能 if (s1 == s2)\n");
    {
        char x[20] = "abc";
        char y[20] = "abc";

        printf("x 的地址 = %p\n", (void *)x);
        printf("y 的地址 = %p\n", (void *)y);
        printf("x == y 的结果 = %d（0 就是假：数组名比较的是地址，不可能相等）\n",
               (const char *)x == (const char *)y);
        printf("strcmp(x, y) == 0 的结果 = %d（1 就是真：这才是在比内容）\n", strcmp(x, y) == 0);
        printf("正确写法：if (strcmp(x, y) == 0) { /* 两个字符串内容相同 */ }\n");
    }

    return 0;
}
