# Example007

## 题目

编写一个函数，计算一个子串在一个主串中出现的次数，如果该子串不出现，则返回 0。本题不需要考虑子串重叠，如：主串为 `aaaa`，子串为 `aaa`，考虑子串重叠结果为 2，不考虑子串重叠结果为 1。





## 分析

本题是模式串匹配算法的扩展。在之前的模式串匹配算法，如果匹配成功则返回子串在主串中第一次出现的位置然后结束程序，这里只需要修改为匹配成功之后计数器加一，并且继续进行匹配检测即可。同样也可以使用 KMP 算法来实现。

关于题目中要求不考虑子串重叠的意思是：如果主串是 `aaaa`，而子串是 `aaa`，那么考虑子串重叠，则下一个位置的比较是第二个字符开始的；如果不考虑子串重叠，则下一个位置的比较是从第四个字符开始的。





## 图解

以 `str="abaaacdaae"; substr="aa"` 为例图解如下：

![image-20220514113447723](image-Example007/image-20220514113447723.png)





## C实现

核心代码：

```c
/**
 * 计算一个子串在一个主串中出现的次数，但不考虑重叠
 * @param str 主串
 * @param substr 子串
 * @return 子串在主串中的出现次数
 */
int countSubstr(String str, String substr) {
    // 计数器，记录子串在主串中的出现次数
    int count = 0;

    // 参数校验，如果主串或子串为空串，那么无意义
    if (str.length == 0 || substr.length == 0) {
        return 0;
    }

    // 变量，i 记录串 str 中字符的下标，j 记录子串 substr 中字符的下标
    int i = 0, j = 0;
    // 从头到尾扫描主串 str 中的每个字符
    while (i < str.length && j < substr.length) {
        // 如果当前扫描的主串字符和子串字符相等
        if (str.ch[i] == substr.ch[j]) {
            // 则 i 和 j 同时前进到下一位置，继续比较判断
            i++;
            j++;
        }
            // 如果不相等，则 i 前进到下一位置，而 j 从 0 开始
        else {
            // i-j 表示恢复到比较的初始位置，而加一表示前进到下一位置
            i = i - j + 1;
            // j 就恢复成 0，表示又从子串的第一个位置开始比较
            j = 0;
        }
        // 如果 j 等于子串长度，表示成功匹配子串一次
        if (j == substr.length) {
            // 那么计数器加一
            count++;
            // 但是匹配成功之后注意将 j 恢复成 0，因为后面还要进行匹配检测
            j = 0;
        }
    }

    // 最后返回统计结果
    return count;
}
```

完整代码：

```c
#include <stdio.h>
#include <stdlib.h>

/**
 * 串结构体定义
 */
typedef struct {
    /**
     * 变长分配存储串，表示指向动态分配存储区首地址的字符指针
     */
    char *ch;

    /**
     * 串的长度，即实际字符个数
     */
    int length;
} String;

/**
 * 初始化串
 * @param str 未初始化的串
 */
void init(String *str) {
    str->ch = NULL;
    str->length = 0;
}

/**
 * 将一个常量字符串赋给一个串
 * @param str 串
 * @param ch 常量字符串
 * @return 如果赋值成功则返回 1，否则返回 0 表示赋值失败
 */
int assign(String *str, char *ch) {
    // 0.参数校验，如果 str 中已有字符，那么释放原串空间，因为我们会给它重新分配空间
    if (str->ch != NULL) {
        free(str->ch);
        str->ch = NULL;
    }

    // 1.统计常量字符串 ch 中的字符个数，只有知道它的字符个数，我们才能清楚为 str 分配多少个字符空间
    // 局部变量，存储常量字符串 ch 中的字符个数
    int len = 0;
    // 注意，我们不能直接操作 ch，因为是一个指针变量，在下面的操作后我们会移动指针，会修改掉 ch 原本的值，后面如果需要再使用就不是传入的参数值，所以要创建一个临时局部变量引用它的值来进行操作
    char *c = ch;
    // 从头到尾扫描常量字符串，以结束标记 '\0' 作为循环结束条件
    while (*c != '\0') {
        // 计数器加一
        len++;
        // 指针加一，继续下一个字符
        c++;
    }

    // 2.为串 str 分配空间并赋值
    // 2.1 如果常量字符串长度为 0，那么串 str 也该为一个空串
    if (len == 0) {
        str->ch = NULL;
        str->length = 0;
        return 1;
    }
        // 2.2 如果常量字符串长度不为 0，那么将常量字符串中所有字符赋给串 str
    else {
        // 2.2.1 给串分配 len+1 个存储空间，多分配一个空间是为了存放 '\0' 字符
        str->ch = (char *) malloc(sizeof(char) * (len + 1));
        // 2.2.2 判断是否分配空间成功
        // 2.2.2.1 如果分配空间失败，则返回 0
        if (str->ch == NULL) {
            // 如果分配空间失败，则返回 0
            return 0;
        }
            // 2.2.2.2 如果分配空间成功，则遍历常量字符串中的每个字符，依次赋给串 str
        else {
            // 局部变量，保存常量字符串 ch 的首地址，后续用于操作
            c = ch;
            // 2.2.2.2.1 扫描整个常量字符串，依次将每个字符赋给新串 str
            for (int i = 0; i <= len; i++) {// 之所以在循环条件中使用 <=。是为例将常量字符串最后的 '\0' 字符也复制到新串中作为结束标记
                str->ch[i] = *(c + i);// 其实也可以使用 str->ch[i]=c[i];
            }
            // 2.2.2.2.2 给新串赋予长度，即常量字符串的长度
            str->length = len;
            // 2.2.2.2.3 返回 1 表示赋值成功
            return 1;
        }
    }
}

/**
 * 计算一个子串在一个主串中出现的次数，但不考虑重叠
 * @param str 主串
 * @param substr 子串
 * @return 子串在主串中的出现次数
 */
int countSubstr(String str, String substr) {
    // 计数器，记录子串在主串中的出现次数
    int count = 0;

    // 参数校验，如果主串或子串为空串，那么无意义
    if (str.length == 0 || substr.length == 0) {
        return 0;
    }

    // 变量，i 记录串 str 中字符的下标，j 记录子串 substr 中字符的下标
    int i = 0, j = 0;
    // 从头到尾扫描主串 str 中的每个字符
    while (i < str.length && j < substr.length) {
        // 如果当前扫描的主串字符和子串字符相等
        if (str.ch[i] == substr.ch[j]) {
            // 则 i 和 j 同时前进到下一位置，继续比较判断
            i++;
            j++;
        }
            // 如果不相等，则 i 前进到下一位置，而 j 从 0 开始
        else {
            // i-j 表示恢复到比较的初始位置，而加一表示前进到下一位置
            i = i - j + 1;
            // j 就恢复成 0，表示又从子串的第一个位置开始比较
            j = 0;
        }
        // 如果 j 等于子串长度，表示成功匹配子串一次
        if (j == substr.length) {
            // 那么计数器加一
            count++;
            // 但是匹配成功之后注意将 j 恢复成 0，因为后面还要进行匹配检测
            j = 0;
        }
    }

    // 最后返回统计结果
    return count;
}

int main() {
    // 声明主串
    String str;
    init(&str);
    assign(&str, "hello world, hello java, hello c, hello python, hellohello css");

    // 声明子串
    String substr;
    init(&substr);
    assign(&substr, "hello");

    // 调用函数，计算次数
    int count;
    count = countSubstr(str, substr);
    printf("子串在主串中的出现次数是：%d", count);
}
```

执行结果：

```text
子串在主串中的出现次数是：6
```





## Java实现

无。