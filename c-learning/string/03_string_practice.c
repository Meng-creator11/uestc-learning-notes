#include <stdio.h>
#include <string.h>

/*
 * 练习 03（c-learning/string）：字符串综合练习
 * 知识点：
 *   1. 反转字符串（双指针：一头一尾往中间靠）
 *   2. 回文串判断 —— 和你写过的 c-exercises/06_palindromic_number.c（回文"数"）正好对照
 *   3. 字频统计：用 int cnt[26] 当计数器的经典用法
 *   4. 统计单词个数：注意"连续空格"和"开头结尾的空格"
 *   5. 最后留一道小挑战，建议先自己写，再看参考实现
 *
 * 编译运行（在 c-learning/string/ 目录下）：
 *   gcc 03_string_practice.c -o 03_string_practice -Wall
 *   .\03_string_practice.exe
 */

/* ------------------------------------------------------------------
 * 【1】原地反转字符串
 * ------------------------------------------------------------------ */
void reverse_string(char s[])
{
    int i = 0;
    int j = (int)strlen(s) - 1;      /* 最后一个字符的下标 */
    char t;

    while (i < j) {
        t = s[i];
        s[i] = s[j];
        s[j] = t;
        i++;
        j--;
    }
}

/* ------------------------------------------------------------------
 * 【2】回文串判断：第 i 个和倒数第 i 个必须相同
 * 返回 1 表示是回文，0 表示不是
 * ------------------------------------------------------------------ */
int is_palindrome(const char s[])
{
    int i = 0;
    int j = (int)strlen(s) - 1;

    while (i < j) {
        if (s[i] != s[j])
            return 0;                /* 只要有一对不相同，立刻判定不是 */
        i++;
        j--;
    }
    return 1;                        /* 全部比完都相同 */
}

void demo_palindrome(void)
{
    char tests[4][20] = {"level", "abcba", "hello", "ab"};
    int i;

    printf("【2】回文串判断\n");
    for (i = 0; i < 4; i++)
        printf("  \"%s\" -> %s\n", tests[i], is_palindrome(tests[i]) ? "是回文" : "不是回文");
    printf("  提示：回文\"数\"（06 题）是把各位数字倒过来比，思路完全一样\n\n");
}

/* ------------------------------------------------------------------
 * 【3】字频统计
 *   count_char：某个字符出现了几次
 *   count_letters：每个字母（不分大小写）出现了几次，用 cnt[26] 存
 * ------------------------------------------------------------------ */
int count_char(const char s[], char c)
{
    int i;
    int n = 0;

    for (i = 0; s[i] != '\0'; i++)
        if (s[i] == c)
            n++;

    return n;
}

void count_letters(const char s[])
{
    int cnt[26] = {0};       /* cnt[0] 记 a/A 的次数，cnt[1] 记 b/B，…… */
    int i;

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'z')
            cnt[s[i] - 'a']++;
        else if (s[i] >= 'A' && s[i] <= 'Z')
            cnt[s[i] - 'A']++;
    }

    printf("  字母出现次数：");
    for (i = 0; i < 26; i++)
        if (cnt[i] > 0)
            printf("%c=%d ", 'a' + i, cnt[i]);
    printf("\n");
}

void demo_count(void)
{
    char s[] = "Hello Harness";

    printf("【3】字符统计\n");
    printf("  字符串：%s\n", s);
    printf("  字符 'l' 出现 %d 次\n", count_char(s, 'l'));
    printf("  字符 'z' 出现 %d 次（没有就是 0）\n", count_char(s, 'z'));
    count_letters(s);
    printf("\n");
}

/* ------------------------------------------------------------------
 * 【4】统计单词个数
 * 思路：遇到"从空格进入字符"的那一刻，单词数 +1
 * ------------------------------------------------------------------ */
int count_words(const char s[])
{
    int i = 0;
    int words = 0;
    int in_word = 0;             /* 0 表示当前在空格里，1 表示正在单词中 */

    while (s[i] != '\0') {
        if (s[i] != ' ') {
            if (!in_word) {      /* 刚从空格进入单词 */
                words++;
                in_word = 1;
            }
        } else {
            in_word = 0;         /* 遇到空格，单词结束 */
        }
        i++;
    }

    return words;
}

void demo_words(void)
{
    printf("【4】统计单词个数\n");
    printf("  \"I love C\"          -> %d 个单词\n", count_words("I love C"));
    printf("  \"   hello   world \" -> %d 个单词（连续空格、首尾空格都不算新单词）\n",
           count_words("   hello   world "));
    printf("  \"\"                  -> %d 个单词\n\n", count_words(""));
}

/* ------------------------------------------------------------------
 * 【5】小挑战：把字符串里的"单词顺序"倒过来
 *   "I love C"  ->  "C love I"
 * 建议先自己想一想，再往下看参考实现。
 *
 * 参考思路（分三步）：
 *   ① 整体反转：      "I love C"  ->  "C evol I"
 *   ② 再逐词反转：    "C evol I"  ->  "C love I"
 * ------------------------------------------------------------------ */

/* 反转 s 中从下标 from 到 to 的一段（含两端） */
void reverse_range(char s[], int from, int to)
{
    char t;

    while (from < to) {
        t = s[from];
        s[from] = s[to];
        s[to] = t;
        from++;
        to--;
    }
}

void reverse_words(char s[])
{
    int n = (int)strlen(s);
    int i = 0;
    int start;

    reverse_range(s, 0, n - 1);          /* ① 整体反转 */

    while (i < n) {                      /* ② 逐个单词再反转回来 */
        while (i < n && s[i] == ' ')     /* 跳过空格 */
            i++;
        start = i;
        while (i < n && s[i] != ' ')     /* 找到这个单词的结尾 */
            i++;
        reverse_range(s, start, i - 1);
    }
}

void demo_reverse_words(void)
{
    char s[] = "I love C";

    printf("【5】小挑战：反转单词顺序\n");
    printf("  反转前：%s\n", s);
    reverse_words(s);
    printf("  反转后：%s\n", s);

    /* 用完全一样的思路，还能解决"循环左移字符串"等一串题目 */
}

int main(void)
{
    char s1[] = "uestc";
    char s2[] = "UESTC";

    printf("【1】反转字符串\n");
    printf("  反转前：%s\n", s1);
    reverse_string(s1);
    printf("  反转后：%s\n", s1);
    printf("  反转前：%s\n", s2);
    reverse_string(s2);
    printf("  反转后：%s\n\n", s2);

    demo_palindrome();
    demo_count();
    demo_words();
    demo_reverse_words();

    return 0;
}
