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
 * 复制操作，从串 src 复制得到串 dest
 * @param dest 目标串
 * @param src 源串
 * @return 如果复制成功则返回 1，否则返回 0 表示失败
 */
int copy(String *dest, String src) {
    // 0.参数校验
    // 0.1 参数校验，如果 dest->ch 不为 NULL，则释放其空间
    if (dest->ch != NULL) {
        free(dest->ch);
        dest->ch = NULL;
    }
    // 0.2 参数校验，如果 src.ch 为 NULL，那么 dest 串一定是空串，返回 1 表示复制成功
    if (src.ch == NULL || src.length == 0) {
        dest->ch = NULL;
        dest->length = 0;
        return 1;
    }

    // 1.复制字符串
    // 1.1 为 str->ch 分配长度为 src.length+1 个空间，多分配一个空间是为了存放 '\0' 字符
    dest->ch = (char *) malloc(sizeof(char) * (src.length + 1));
    // 1.2 将串 src 中的每个字符依次赋值给串 dest
    for (int i = 0; i <= src.length; i++) {
        // src.ch 表示串 src.ch 的首地址
        // *src.ch 可以取出串 src.ch 的首个字符
        // *(src.ch+i) 可以取出 src.ch 的第 i 个字符
        // 其实也可以用数组下标的方式取值，如：dest->ch[i]=src.ch[i];
        dest->ch[i] = *(src.ch + i);
    }
    // 1.3 将串 src 的长度也赋值给 dest 的长度
    dest->length = src.length;
    // 1.4 返回 1 表示复制成功
    return 1;
}

/**
 * 判断串是否是空串
 * @param str 串
 * @return 如果串是空串则返回 1，否则返回 0 表示非空
 */
int isEmpty(String str) {
    // 判断串的长度是否为零，即可以判断它是否是空串
    return str.length == 0;
}

/**
 * 获取串的长度
 * @param str 串
 * @return 串的长度，即串的字符个数
 */
int length(String str) {
    // 由于串的 length 属性记录了串的长度，所以直接返回即可，不需要遍历串中的所有字符去统计字符个数
    return str.length;
}

/**
 * 比较两个串
 * @param s1 第一个待比较的串
 * @param s2 第二个待比较的串
 * @return 如果串 s1 大于串 s2 那么返回正数；如果串 s1 等于串 s2 那么返回 0；如果串 s1 小于串 s2 那么返回负数
 */
int compare(String s1, String s2) {
    // 局部变量，同时用来遍历串 s1 和 s2
    int i = 0;
    // 同时扫描串 s1 和 s2 中相同下标处的字符
    while (i < s1.length && i < s2.length) {
        // 如果当前两个字符不等，那么两个串一定不等，两个字符的差值就是对应 ASCII 码的差值，如果是正数则表示前者的 ASCII 码值更大，那么也就是串更大，否则相反
        if (s1.ch[i] != s2.ch[i]) {
            return s1.ch[i] - s2.ch[i];
        }
        // 如果当前两个字符相等，则变量加一继续比较下一对字符
        i++;
    }
    // 循环完成后，表示前 i 个字符都相等并且两个串的长度不等，那么谁更长就更大
    return s1.length - s2.length;
}

/**
 * 连接字符串，用 str 返回由 s1 和 s2 连接而成的新串
 * @param str 用来保存连接后的新串
 * @param s1 第一个串
 * @param s2 第二个串
 * @return 如果连接成功则返回 1，否则返回 0
 */
int concat(String *str, String s1, String s2) {
    // 0.参数校验
    // 0.1 参数校验，如果 str 是非空串，则释放其原本的空间，因为要存储合并后的串内容
    if (str->ch != NULL) {
        free(str);
        str->ch = NULL;
    }
    // 0.2 参数校验，如果两个串的长度之和为 0，那么新串一定是一个空串
    if (s1.length + s2.length == 0) {
        str->ch = NULL;
        str->length = 0;
        return 1;
    }

    // 1.连接串 s1 和 s2
    // 1.1 为串 str->ch 分配空间，长度应该为 s1.length+s2.length+1，多出来的一个空间用来存放串的结束标记 '\0' 字符
    str->ch = (char *) malloc(sizeof(char) * (s1.length + s2.length + 1));
    // 如果分配空间失败则返回 0
    if (str->ch == NULL) {
        return 0;
    }
    // 1.2 先将串 s1 中的所有字符复制到串 str 中
    for (int i = 0; i < s1.length; i++) {
        str->ch[i] = *(s1.ch + i);
    }
    // 1.3 接着将串 s2 中的所有字符复制到串 str 中
    for (int i = 0; i <= s2.length; i++) {// 将串 s2 中的结束标记 '\0' 也复制过来
        str->ch[s1.length + i] = *(s2.ch + i);
    }
    // 1.4 为连接后的串指定长度
    str->length = s1.length + s2.length;
    // 1.5 返回 1 表示连接成功
    return 1;
}

/**
 * 求子串，用 substr 返回串 str 的第 pos 个字符起长度为 len 的子串
 * @param substr 用来保存子串
 * @param str 主串
 * @param pos 起始位置，从 0 开始
 * @param len 子串的长度
 * @return 如果获取成功则返回 1，否则返回 0 表示失败
 */
int substring(String *substr, String str, int pos, int len) {
    // 0.参数校验
    // 0.1 校验参数 pos，位置必须在 [0, str.length) 之间，即下标的范围内，否则就是不合法
    if (pos < 0 || pos >= str.length) {
        return 0;
    }
    //  0.2 校验参数 len，子串长度不能小于 0；也不能大于 length-pos
    if (len < 0 || str.length - pos < len) {
        return 0;
    }
    // 0.3 如果要求的子串长度为 0，那么返回的子串为空串，直接返回即可
    if (len == 0) {
        substr->ch = NULL;
        substr->length = 0;
        return 1;
    }

    // 1.求子串
    // 1.1 为子串分配长度为 len+1 的空间，多出来的一个空间用来存放串的结束标记 '\0'
    substr->ch = (char *) malloc(sizeof(char) * (len + 1));
    // 1.2 将主串中第 pos 个位置（包括本身）之后的 len 个字符复制到子串中
    int i = 0;
    for (i = 0; i < len; i++) {
        // 星号用来取值，其实也可以写成这样：substr->ch[i]=str.ch[pos+i];
        substr->ch[i] = *(str.ch + pos + i);
    }
    // 1.3 让串的最后一个字符是 '\0'，表示是串的结束标记
    substr->ch[i] = '\0';
    // 1.4 置子串的长度为 len
    substr->length = len;
    // 1.5 返回 1 表示求子串成功
    return 1;
}

/**
 * 定位子串，若主串 str 中存在与串 substr 值相同的子串，则返回它在主串 str 中第一次出现的位置
 * @param str 主串
 * @param substr 子串
 * @return 如果存在子串则返回第一次出现的位置，否则返回 0
 */
int index(String str, String substr) {
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
            // 如果不相等，那么就继续比较主串中下一个字符开始的串与子串，注意，需要恢复 i 和 j
        else {
            // 恢复主串中的 i，回到第 i-j 个字符，然后加一表示下一个字符
            i = i - j + 1;
            // 而 j 要恢复为子串的第一个字符的下标，即为 0，又要从 0 开始比较起走
            j = 0;
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
 * 清空串
 * @param str 串
 */
void clear(String *str) {
    // 释放原串空间
    if (str->ch != NULL) {
        free(str->ch);
    }
    // 然后指向 NULL 和将长度置为 0
    str->ch = NULL;
    str->length = 0;
}

int main() {
    String str;
    init(&str);

    // 赋值操作，将一个常量字符串赋给一个串
    printf("\n赋值字符串：\n");
    assign(&str, "hello world");
    printf("%s\n", str.ch);

    // 复制操作，从一个串复制一个串出来
    printf("\n复制串：\n");
    String dest;
    init(&dest);
    copy(&dest, str);
    printf("%s\n", dest.ch);

    // 判断串是否为空
    printf("\n串是否为空：\n");
    int empty;
    empty = isEmpty(str);
    printf("%d\n", empty);

    // 串的长度
    printf("\n串的长度：\n");
    int len;
    len = length(str);
    printf("%d\n", len);

    // 比较两个串
    printf("\n比较两个串：\n");
    String str2;
    init(&str2);
    assign(&str2, "hellx world!");
    int cmp;
    cmp = compare(str, str2);
    printf("%d\n", cmp);

    // 拼接两个串
    printf("\n拼接两个串：\n");
    String str3;
    init(&str3);
    assign(&str3, ", hello C!");
    String con;
    init(&con);
    concat(&con, str, str3);
    printf("%s\n", con.ch);

    // 得到子串
    printf("\n得到子串：\n");
    String substr;
    init(&substr);
    substring(&substr, str, 4, 6);
    printf("%s\n", substr.ch);

    // 子串在主串中的位置
    printf("\n子串在主串中的位置：\n");
    int pos;
    pos = index(str, substr);
    printf("%d\n", pos);

    // 清空串
    printf("\n清空串：\n");
    clear(&str);
    printf("%s\n", str.ch);
}