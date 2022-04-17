# Example001

## 题目

C 语言中算术表达式中的括号只有小括号。编写算法，判断一个表达式中的括号是否正确配对，表达式已经存入字符数组 `exp[]` 中，表达式的字符个数为 `n`。

## 分析

例如算术表达式：`3*(a++)+c*(b+(2+d))+d*3`。其实表达式中括号匹配分为如下三种情况：
- 完全匹配，如 `((()))` 中左括号 `(` 和右括号 `)` 的个数是完全相等的。如果将左括号入栈，右括号与栈顶元素进行比较，那么最后栈为空，表示匹配成功。
- 不完全匹配，如 `(()))` 中左括号 `(` 和右括号 `)` 的个数不完全相等，并且右括号的个数大于左括号的个数。如果将左括号入栈，右括号与栈顶元素进行比较，那么一定会出现空栈与右括号比较的情况，表示匹配失败。
- 不完全匹配，如 `((())` 中左括号 `(` 和右括号 `)` 的个数不完全相等，并且左括号的个数大于右括号的个数。如果将左括号入栈，右括号与栈顶元素进行比较，当遍历完字符数组后，那么栈中一定还剩余左括号，表示匹配失败。

其实看到上面的三种情况，就明白了，我们只需要处理小括号字符，不关注其他非小括号字符，并且将左括号字符加入到栈中，将右括号字符与左括号字符进行配对比较。

下面的代码中使用的是标准的顺序栈，而非一个简单的数组，书中采用的就是利用简单的数组来实现栈的功能。具体可参考：[考研数据结构之栈（2.3）——练习题之判断表达式中的括号是否正确配对（C表示）](https://blog.csdn.net/cnds123321/article/details/106278770)

## 图解

## C实现

核心代码：

```c

```

完整代码：

```c
#include <stdio.h>

/**
 * 顺序栈最大存储的元素个数
 */
#define MAXSIZE 100

/**
 * 顺序栈结构体定义
 */
typedef struct {
    /**
     * 数据域，数组，用来存储栈中元素
     */
    char data[MAXSIZE];
    /**
     * 指针域，表示栈顶指针，实际上就是数组下标
     */
    int top;
} SeqStack;

/**
 * 初始化顺序栈，即将栈顶指针指向 -1 表示空栈
 * @param stack 顺序栈
 */
void init(SeqStack *stack) {
    // 设定让栈顶指针指向 -1 表示为栈空
    stack->top = -1;
}

/**
 * 判断顺序栈是否为空
 * @param stack 顺序栈
 * @return 如果顺序栈为空则返回 1，否则返回 0
 */
int isEmpty(SeqStack stack) {
    // 只需要判断栈顶指针是否等于 -1 即可，如果是空栈则返回 1，不是空栈则返回 0
    if (stack.top == -1) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 将元素入栈
 * @param stack 顺序栈
 * @param ele 元素值
 * @return 如果栈满则返回 0 表示入栈失败；如果插入成功则返回 1
 */
int push(SeqStack *stack, int ele) {
    // 1.参数校验，如果栈满则不能入栈元素
    if (stack->top == MAXSIZE - 1) {
        // 如果栈满，则返回 0，表示不能入栈
        return 0;
    }
    // 2.先将栈顶指针加一，指向新空数组位置
    stack->top++;
    // 3.将新元素值填充到新位置中
    stack->data[stack->top] = ele;
    return 1;
}

/**
 * 将元素出栈
 * @param stack 顺序栈
 * @param ele 用来保存出栈的元素
 * @return 如果栈空则返回 0 表示出栈失败；否则返回 1 表示出栈成功
 */
int pop(SeqStack *stack, int *ele) {
    // 1.参数校验，栈空不能出栈
    if (stack->top == -1) {
        // 栈空，没有元素可出栈
        return 0;
    }
    // 2.用 ele 来保存顺序栈栈顶元素
    *ele = stack->data[stack->top];
    // 3.然后栈顶指针减一，表示出栈一个元素
    stack->top--;
    return 1;
}

/**
 * 获取栈顶元素，但不出栈
 * @param stack 顺序栈
 * @param ele 用来保存出栈元素
 * @return 如果栈空则返回 0 表示出栈失败；否则返回 1 表示出栈成功
 */
int getTop(SeqStack stack, int *ele) {
    // 1.参数校验，如果栈空则不能出栈
    if (stack.top == -1) {
        // 栈空，没有元素可出栈
        return 0;
    }
    // 2.保存栈顶元素返回
    *ele = stack.data[stack.top];
    return 1;
}

int match(char exp[], int n) {
    // 声明一个顺序栈并初始化，用来存储小括号
    SeqStack stack;
    init(&stack);

    // 局部变量，无任何实际意义，仅用于填充 pop 函数的第二个参数
    int ele;
    // 扫描字符数组，循环遍历每个字符
    for (int i = 0; i < n; i++) {
        // 如果是小括号中的左括号（即 '('），将其存储到顺序栈中
        if (exp[i] == '(') {
            push(&stack, exp[i]);
        }
            // 如果是小括号中的右括号（即 ')'），那么将栈顶元素出栈
        else if (exp[i] == ')') {
            // 注意，有可能栈空，那么就是右括号至少多一个，那么表达式中的括号一定不会是配对的
            if (isEmpty(stack)) {
                // 所以直接返回 0 表示不配对
                return 0;
            } else {
                // 如果栈不为空，才将顺序栈栈顶元素出栈，表示一对括号匹配成功
                pop(&stack, &ele);
            }
        }
    }
    // 如果是空栈，表示所有括号正确匹配；如果不是空栈，那么就是右括号至少多一个，那么表达式中的括号一定不会是配对的
    if (isEmpty(stack)) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 打印顺序栈中所有元素
 * @param stack 顺序栈
 */
void print(SeqStack stack) {
    printf("[");
    for (int i = stack.top; i >= 0; i--) {

        if (i != stack.top) {
            printf(", ");
        }
        printf("%d", stack.data[i]);
    }
    printf("]\n");
}

int main() {
    // 声明一个栈
    SeqStack stack;

    // 初始化栈
    printf("初始化栈：\n");
    init(&stack);
    print(stack);

    // 将元素入栈
    printf("将元素入栈：\n");
    push(&stack, 11);
    print(stack);
    push(&stack, 22);
    print(stack);
    push(&stack, 33);
    print(stack);
    push(&stack, 44);
    print(stack);
    push(&stack, 55);
    print(stack);

    // 将元素出栈
    printf("将元素出栈：\n");
    int ele;
    pop(&stack, &ele);
    print(stack);
    pop(&stack, &ele);
    print(stack);
    pop(&stack, &ele);
    print(stack);

    // 栈是否为空
    printf("栈是否为空：\n");
    int empty;
    empty = isEmpty(stack);
    printf("%d\n", empty);

    // 获取栈顶元素
    printf("获取栈顶元素：\n");
    int top;
    top = getTop(stack, &ele);
    printf("%d\n", ele);

    // 获取栈中元素个数
    printf("获取栈中元素个数：\n");
    int len;
    len = size(stack);
    printf("%d\n", len);

    // 清空栈
    printf("清空栈：\n");
    clear(&stack);
    print(stack);
}
```

执行结果：

```text

```

## Java实现

核心代码：

```java

```

完整代码：

```java

```

测试代码：

```java

```

执行结果：

```text

```