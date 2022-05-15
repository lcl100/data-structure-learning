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
 * KMP 算法求 next 数组
 * @param substr 子串
 * @param next 数组
 */
void getNext(String substr, int next[]) {
    int j = 0, k = -1;
    next[0] = -1;
    while (j < substr.length - 1) {
        if (k == -1 || substr.ch[j] == substr.ch[k]) {
            j++;
            k++;
            next[j] = k;
        } else {
            k = next[k];
        }
    }
}

/**
 * 改进的 KMP 算法求 nextval 数组
 * @param substr 子串
 * @param nextval 数组
 */
void getNextVal(String substr, int nextval[]) {
    int j = 0, k = -1;
    nextval[0] = -1;
    while (j < substr.length - 1) {
        if (k == -1 || substr.ch[j] == substr.ch[k]) {
            j++;
            k++;
            if (substr.ch[j] == substr.ch[k]) {
                nextval[j] = nextval[k];
            } else {
                nextval[j] = k;
            }
        } else {
            k = nextval[k];
        }
    }
}

/**
 * 定位子串，若主串 str 中存在与串 substr 值相同的子串，则返回它在主串 str 中第一次出现的位置
 * @param str 主串
 * @param substr 子串
 * @return 如果存在子串则返回第一次出现的位置，否则返回 0
 */
int index(String str, String substr) {
    // 声明 next 数组并调用 getNext 函数进行计算
    int next[substr.length];
    getNext(substr, next);

    // 变量，i 记录串 str 中字符的下标，j 记录串 substr 中字符的下标
    int i = 0, j = 0;
    // 同时扫描主串 str 和子串 substr
    while (i < str.length && j < substr.length) {
        // 如果主串中的字符与子串中的字符相等，则继续比较下一对字符
        if (str.ch[i] == substr.ch[j]) {
            // 同时加一，指向串的下一个字符
            i++;
            j++;
        }
            // 如果不相等，那么就回退 j
        else {
            // j 回退到 next[j] 位置，而 i 不回退
            j = next[j];
        }
    }
    // 如果循环结束 j 等于 length，那么表示主串中一定存在子串
    if (j == substr.length) {
        // 则返回子串第一次出现的位置
        return i - j;
    } else {
        // 如果不相等，则表示子串不存在于主串中，在返回标记 0
        return '\0';
    }
}

/**
 * 打印数组，可以用来打印查看 next 数组是否正确
 * @param arr 数组
 * @param n 数组长度
 */
void printArray(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i != n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    // 声明主串
    String str;
    init(&str);
    assign(&str, "abaabaabeca");

    // 声明子串
    String substr;
    init(&substr);
    assign(&substr, "abaabe");

    // 调用函数求子串在主串中第一次出现的位置
    int pos;
    pos = index(str, substr);
    printf("%s 在 %s 中第一次出现的位置是：%d\n", substr.ch, str.ch, pos);
}