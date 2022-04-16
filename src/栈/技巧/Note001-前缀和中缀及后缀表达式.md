# 前缀表达式、中缀表达式、后缀表达式的转换

## 前缀、中缀和后缀表达式概念

前缀、中缀和后缀表达式是对表达式的不同记法，其区别在于运算符相对于操作数的位置不同，其中前缀表达式的运算符位于操作数的前面，后缀表达式的运算符位于操作数的后面。例如：

- 中缀表达式：`1+(2+3)*4-5`。
- 前缀表达式：`-+1*+2345`。
- 后缀表达式：`123+4*+5-`。

我们常用的就是中缀表达式，对于人很容易理解，但是对于计算机来说中缀表达式很难理解，因此在计算表达式的值时，需要先将中缀表达式转换成前缀或后缀表达式，然后再进行求值，对于计算机来说，计算前缀或后缀表达式的值非常简单。总结：

- 前缀、中缀、后缀是根据运算符与操作数的相对位置来划分的。
- 中缀表达式符合人的计算习惯，而前缀和后缀表达式适合计算机计算。
- 前缀表达式和后缀表达式计算的时候都是从一个方向扫描表达式，遇到数字压入栈，遇到运算符弹出栈顶的两个数进行运算并将结果入栈，重复直到结束。
- 前缀和后缀表达式已经内在地包含运算顺序，因此不用括号来确定优先级。





## 前缀表达式的计算机求值

### 算法思想

算法思想：**从右往左**扫描表达式，遇到数字时，将数字压入栈；遇到运算符时，弹出栈顶的两个数字，用运算符对它们进行相应的计算，并且将结果压入栈。重复上述过程直到表达式最左端，最后运算得出的值即为表达式的结果。

### 示例

例如，有前缀表达式：`-*+3456`。求值步骤如下：

- （1）从右往左扫描，将 6、5、4、3 压入栈中。
- （2）然后遇到 `+` 运算符，弹出栈顶的两个数字，即弹出 3 和 4（其中 3 为栈顶元素、4 为次顶元素），计算出 `3+4` 的值，得到 7，然后再将 7 压入栈中。
- （3）接下来是 `*` 运算符，弹出栈顶的两个数字，即弹出 7 和 5，计算出 `7*5` 的值，得到 35，将 35 压入栈中。
- （4）最后是 `-` 运算符，弹出栈顶的两个数字，即弹出 35 和 6，计算出 `35-6` 的值，得到 29， 由此得出最终结果。

### 实现代码

求前缀表达式的核心代码如下：

```c
/**
 * 根据运算符计算两数的结果
 * @param sign 运算符
 * @param a 第一个数
 * @param b 第二个数
 * @return 两数计算的结果
 */
int evaluate(char sign, int a, int b) {
    int result = 0;
    switch (sign) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        case '%':
            result = a % b;
            break;
        default:
            printf("非可计算的运算符：%c", sign);
            break;
    }
    return result;
}

/**
 * 计算前缀表达式
 * @param exps 前缀表达式，以 '\0' 字符结束
 * @param n 字符数组的实际字符个数
 * @return 表达式的计算结果
 */
int evaluatePrefixExpression(char exps[], int n) {
    // 0.解题需要用到栈，所以创建顺序栈并初始化栈
    SeqStack stack;
    init(&stack);

    // 1.从右往左扫描前缀表达式，所以要倒序遍历字符数组
    for (int i = n - 1; i >= 0; i--) {
        // 1.1 如果当前字符是数字字符
        if (exps[i] >= '0' && exps[i] <= '9') {
            // 1.1.1 则将该数字压入栈中，注意数字字符要转换成数字才能存入栈中，而数字字符要转换成数字可以用数字字符减去'0'字符即可得到所对应的数字
            push(&stack, exps[i] - '0');
        }
        // 1.2 如果当字符不是数字字符，而是运算符
        else {
            // 1.2.1 那么弹出栈顶两个数字，用 a 和 b 来保存
            int a, b;
            pop(&stack, &a);
            pop(&stack, &b);
            // 1.2.2 根据运算符调用函数计算 a 和 b 的结果
            int result = evaluate(exps[i], a, b);
            // 1.2.3 将计算结果压入栈中
            push(&stack, result);
        }
    }

    // 2.最终结果也是存在栈中的，就算栈顶元素，所以获得栈顶元素返回即可
    int top;
    getTop(stack, &top);
    return top;
}
```

完整代码如下：

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
    int data[MAXSIZE];
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

/**
 * 根据运算符计算两数的结果
 * @param sign 运算符
 * @param a 第一个数
 * @param b 第二个数
 * @return 两数计算的结果
 */
int evaluate(char sign, int a, int b) {
    int result = 0;
    switch (sign) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        case '%':
            result = a % b;
            break;
        default:
            printf("非可计算的运算符：%c", sign);
            break;
    }
    return result;
}

/**
 * 计算前缀表达式
 * @param exps 前缀表达式，以 '\0' 字符结束
 * @param n 字符数组的实际字符个数
 * @return 表达式的计算结果
 */
int evaluatePrefixExpression(char exps[], int n) {
    // 0.解题需要用到栈，所以创建顺序栈并初始化栈
    SeqStack stack;
    init(&stack);

    // 1.从右往左扫描前缀表达式，所以要倒序遍历字符数组
    for (int i = n - 1; i >= 0; i--) {
        // 1.1 如果当前字符是数字字符
        if (exps[i] >= '0' && exps[i] <= '9') {
            // 1.1.1 则将该数字压入栈中，注意数字字符要转换成数字才能存入栈中，而数字字符要转换成数字可以用数字字符减去'0'字符即可得到所对应的数字
            push(&stack, exps[i] - '0');
        }
        // 1.2 如果当字符不是数字字符，而是运算符
        else {
            // 1.2.1 那么弹出栈顶两个数字，用 a 和 b 来保存
            int a, b;
            pop(&stack, &a);
            pop(&stack, &b);
            // 1.2.2 根据运算符调用函数计算 a 和 b 的结果
            int result = evaluate(exps[i], a, b);
            // 1.2.3 将计算结果压入栈中
            push(&stack, result);
        }
    }

    // 2.最终结果也是存在栈中的，就算栈顶元素，所以获得栈顶元素返回即可
    int top;
    getTop(stack, &top);
    return top;
}

int main() {
    char prefixExp[] = "-*+3456";
    int n = 7;

    int result;
    result = evaluatePrefixExpression(prefixExp, n);
    printf("前缀表达式计算结果：%d", result);
}
```





## 后缀表达式的计算机求值

### 算法思想

算法思想：与前缀表达式的计算类似，只是顺序是**从左向右**扫描表达式。如果遇到数字，则将数字压入栈中；如果遇到运算符，则弹出栈顶的两个数字，用运算符对它们做相应的计算，并且将计算结果压入栈中。重复上述过程直到表达式最右端，最后运算得出的值即为表达式的结果。



### 示例

例如，有后缀表达式：`34+5*6-`。求值步骤如下：

- （1）从左往右扫描，将 3 和 4 压入栈中。
- （2）遇到 `+` 运算符，因此弹出栈顶的两个元素，分别是 3 和 4（其中 4 是栈顶元素、3 是次栈顶元素），计算 `3+4` 的值，得到结果 7，再将 7 入栈。
- （3）遇到数字 5，然后将 5 入栈。
- （4）接下来是 `*` 字符，因此弹出栈顶的两个元素，分别是 5 和 7，计算 `5*7` 的值，得到结果 35，将 35 入栈。
- （5）遇到数字 6，然后将 6 入栈。
- （6）最后是 `-` 运算符，计算出 `6-35` 的值，即 -29，由此得出最终结果。



### 实现代码

求后缀表达式的核心代码如下：

```c
/**
 * 根据运算符计算两数的结果
 * @param sign 运算符
 * @param a 第一个数
 * @param b 第二个数
 * @return 两数计算的结果
 */
int evaluate(char sign, int a, int b) {
    int result = 0;
    switch (sign) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        case '%':
            result = a % b;
            break;
        default:
            printf("非可计算的运算符：%c", sign);
            break;
    }
    return result;
}

/**
 * 计算前缀表达式
 * @param exps 前缀表达式，以 '\0' 字符结束
 * @param n 字符数组的实际字符个数
 * @return 表达式的计算结果
 */
int evaluateSuffixExpression(char exps[], int n) {
    // 0.解题需要用到栈，所以创建顺序栈并初始化栈
    SeqStack stack;
    init(&stack);

    // 1.从左往右扫描后缀表达式，所以要正序遍历字符数组
    for (int i = 0; i < n; i++) {
        // 1.1 如果当前字符是数字字符
        if (exps[i] >= '0' && exps[i] <= '9') {
            // 1.1.1 则将该数字压入栈中，注意数字字符要转换成数字才能存入栈中，而数字字符要转换成数字可以用数字字符减去'0'字符即可得到所对应的数字
            push(&stack, exps[i] - '0');
        }
        // 1.2 如果当字符不是数字字符，而是运算符
        else {
            // 1.2.1 那么弹出栈顶两个数字，用 a 和 b 来保存
            int a, b;
            pop(&stack, &a);
            pop(&stack, &b);
            // 1.2.2 根据运算符调用函数计算 a 和 b 的结果
            int result = evaluate(exps[i], a, b);
            // 1.2.3 将计算结果压入栈中
            push(&stack, result);
        }
    }

    // 2.最终结果也是存在栈中的，就算栈顶元素，所以获得栈顶元素返回即可
    int top;
    getTop(stack, &top);
    return top;
}
```

完整代码如下：

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
    int data[MAXSIZE];
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

/**
 * 根据运算符计算两数的结果
 * @param sign 运算符
 * @param a 第一个数
 * @param b 第二个数
 * @return 两数计算的结果
 */
int evaluate(char sign, int a, int b) {
    int result = 0;
    switch (sign) {
        case '+':
            result = a + b;
            break;
        case '-':
            result = a - b;
            break;
        case '*':
            result = a * b;
            break;
        case '/':
            result = a / b;
            break;
        case '%':
            result = a % b;
            break;
        default:
            printf("非可计算的运算符：%c", sign);
            break;
    }
    return result;
}

/**
 * 计算前缀表达式
 * @param exps 前缀表达式，以 '\0' 字符结束
 * @param n 字符数组的实际字符个数
 * @return 表达式的计算结果
 */
int evaluateSuffixExpression(char exps[], int n) {
    // 0.解题需要用到栈，所以创建顺序栈并初始化栈
    SeqStack stack;
    init(&stack);

    // 1.从左往右扫描后缀表达式，所以要正序遍历字符数组
    for (int i = 0; i < n; i++) {
        // 1.1 如果当前字符是数字字符
        if (exps[i] >= '0' && exps[i] <= '9') {
            // 1.1.1 则将该数字压入栈中，注意数字字符要转换成数字才能存入栈中，而数字字符要转换成数字可以用数字字符减去'0'字符即可得到所对应的数字
            push(&stack, exps[i] - '0');
        }
        // 1.2 如果当字符不是数字字符，而是运算符
        else {
            // 1.2.1 那么弹出栈顶两个数字，用 a 和 b 来保存
            int a, b;
            pop(&stack, &a);
            pop(&stack, &b);
            // 1.2.2 根据运算符调用函数计算 a 和 b 的结果
            int result = evaluate(exps[i], a, b);
            // 1.2.3 将计算结果压入栈中
            push(&stack, result);
        }
    }

    // 2.最终结果也是存在栈中的，就算栈顶元素，所以获得栈顶元素返回即可
    int top;
    getTop(stack, &top);
    return top;
}

int main() {
    char prefixExp[] = "34+5*6-";
    int n = 7;

    int result;
    result = evaluateSuffixExpression(prefixExp, n);
    printf("后缀表达式计算结果：%d", result);
}
```





## 中缀表达式转后缀表达式

### 算法思想

算法思想如下：

- 设置一个**运算符栈**，从左到右扫描中缀表达式中的每个字符：
  - 如果遇到操作数字符（如 `1`、`2`等数字），则直接输出操作数到后缀表达式中（有些算法中是用一个栈来存储这些操作数，也是可行的）。
  - 如果遇到非操作数字符，进行如下判断：
    - 如果遇到左括号（如 `(`），则直接将左括号入栈。
    - 如果遇到右括号（如 `)`），则执行出栈操作，并将出栈的元素输出到后缀表达式中，直到弹出栈的是左括号为止，注意左括号不输出到后缀表达式中。
    - 如果遇到其他字符（如`+`、`-`、`*`、`/`等运算符），也需要判断操作：
      - 如果运算符栈为空，则将该运算符直接入栈。
      - 如果运算符栈不为空：
        - 如果栈顶元素是左括号，则直接入栈。
        - 如果栈顶元素是运算符，则需要进行比较：
          - 如果当前扫描到的运算符优先级大于栈顶运算符的优先级，则将当前运算符入栈。
          - 如果当前扫描到的运算符优先级小于等于栈顶运算符，则将栈顶运算符弹出并且输出到后缀表达式中，然后比较新的栈顶运算符，直到当前扫描到的运算符优先级大于栈顶运算符或栈为空为止。再将当前扫描到的运算符入栈。
- 当从左到右扫描完整个中缀表达式后，检测运算符栈，如果非空，则依次弹栈，将弹出的运算符依次压入到后缀表达式中，最终得到中缀表达式所对应的后缀表达式。



### 示例

- 如 `1+2*3+(4*5+6)*7` 转换后的后缀表达式是 `123*+45*6+7*+`。
- 如 `(1+2+3*4)/5` 转换后的后缀表达式是 `12+34*+5/`。
- 如 `1+2` 转换后的后缀表达式是 `12+`。
- 如 `(1+2)*3` 转换后的后缀表达式是 `12+3*`。
- 如 `1+2*3` 转换后的后缀表达式是 `123*+`。
- 如 `(6+3*(7-4))-8/2` 转换后的后缀表达式是 `6374-*+82/-`。

例如，有中缀表达式：`a+b*c+(d*e+f)*g`。转换步骤如下：

- （1）首先读到操作数 a，直接输出到后缀表达式。
- （2）接着读到运算符 `+`，将其入栈。
- （3）继续读到操作数 b，直接输出到后缀表达式。此时运算符栈和后缀表达式的情况如下：

![image-20220416161754937](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416161754937.png)

- （4）继续读到运算符 `*`，因为栈顶元素 `+`  的优先级比 `*` 低，所以将 `*` 直接入栈。
- （5）继续读到操作数 `c`，直接输出到后缀表达式。此运算符栈和后缀表达式的情况如下：

![image-20220416161906946](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416161906946.png)

- （6）继续读到运算符 `+`，因为栈顶元素 `*` 的优先级比 `+` 高，所以弹出 `*` 并输出到后缀表达式；同理，弹出后现栈顶元素 `+` 的优先级与读到的运算符 `+` 一样，所以也弹出 `+` 并输出到后缀表达式。然后再将读到的 `+` 压入栈中。此运算符栈和后缀表达式的情况如下：

![image-20220416162208804](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416162208804.png)

- （7）继续读到的字符是 `(`，是左括号，优先级最高，直接放入栈中。
- （8）继续读到操作数 `d`，将其直接输出到后缀表达式。此运算符栈和后缀表达式的情况如下：

![image-20220416162434007](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416162434007.png)

- （9）继续读到 `*` 字符，由于只有遇到右括号 `)` 时，左括号 `(` 才会弹出，所以直接将 `*` 压入栈中。
- （10）继续读到操作数 `e`，直接输出到后缀表达式。此运算符栈和后缀表达式的情况如下：

![image-20220416162627511](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416162627511.png)

- （11）继续读到 `+` ，因为栈顶元素 `*` 的优先级比 `+` 高，所以弹出 `*` 并输出到后缀表达式，并且将当前读到的 `+` 压入栈中。
- （12）继续读到操作数 `f`，直接输出到后缀表达式。此运算符栈和后缀表达式的情况如下：

![image-20220416163029866](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416163029866.png)

- （13）接下来读到右括号 `)`，则直接将栈中元素弹出并输出到后缀表达式中，直到遇到左括号 `(` 为止。这里右括号前只有一个操作符 `+` 被弹出并输出到后缀表达式。此运算符栈和后缀表达式的情况如下：

![image-20220416163316488](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416163316488.png)

- （14）继续读到 `*` ，因为栈顶元素 `+`  的优先级比 `*` 低，所以将 `*` 直接入栈。
- （15）继续读到 `g`，直接输出到后缀表达式中。此运算符栈和后缀表达式的情况如下：

![image-20220416163733570](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416163733570.png)

- （16）此时输入数据已经读到末尾了，而运算符栈中还有两个操作符 `*` 和 `+`，直接弹出并输出到后缀表达式。此运算符栈和后缀表达式的情况如下：

![image-20220416164027156](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416164027156.png)



### 实现代码

将中缀表达式转换成后缀表达式核心代码如下：

```c
/**
 * 获取运算符的优先级，其中返回数字越小表示优先级越高
 * 注意，仅显示了部分单目运算符的优先级，主要是括号的优先级比乘除运算符的高，乘除运算符的优先级比加减运算符的高
 * @param c 运算符
 * @return 运算符的优先级别
 */
int priority(char c) {
    switch (c) {
        case '(':
        case ')':
            return 1;
        case '/':
        case '*':
        case '%':
            return 3;
        case '+':
        case '-':
            return 4;
        default:
            return 999;
    }
}

/**
 * 中缀表达式转换成后缀表达式
 * @param exps 中缀表达式字符数组
 * @param n 字符数组实际字符个数
 */
void infixToPostfixExpression(char exps[], int n) {
    // 0.声明顺序栈并初始化栈，因为该算法中要使用到栈
    SeqStack stack;
    init(&stack);

    // 变量，记录栈顶元素的值
    char top;

    // 从左到右扫描中缀表达式
    for (int i = 0; i < n; i++) {
        // 局部变量，即当前扫描到的字符
        char c = exps[i];
        // 如果是操作数
        if (c >= '0' && c <= '9') {
            // 则直接输出
            printf("%c", c);
        }
        // 如果不是操作数
        else {
            // 如果是左括号
            if (c == '(') {
                // 则直接入栈
                push(&stack, c);
            }
            // 如果是右括号
            else if (c == ')') {
                // 在栈不为空的情况下
                while (!isEmpty(stack)) {
                    // 出栈栈顶元素
                    pop(&stack, &top);
                    // 直到遇到左括号为止，但并不输出左括号
                    if (top != '(') {
                        printf("%c", top);
                    } else {
                        break;
                    }
                }
            }
            // 如果是其他字符
            else {
                // 如果栈空
                if (isEmpty(stack)) {
                    // 则入栈当前字符
                    push(&stack, c);
                }
                // 如果栈非空
                else {
                    // 在栈不为空的情况
                    while (!isEmpty(stack)) {
                        // 获取栈顶元素
                        getTop(stack, &top);
                        // 弹出栈中所有优先级大于或等于当前字符的栈顶元素，但左括号例外
                        if (top != '(' && priority(c) >= priority(top)) {
                            printf("%c", top);
                            pop(&stack, &top);
                        } else {
                            break;
                        }
                    }
                    // 无论是否出栈元素，都将当前字符入栈
                    push(&stack, c);
                }
            }
        }
    }

    // 扫描完中缀表达式后，检测运算符栈剩余的字符，全部出栈并输出到后缀表达式中
    while (!isEmpty(stack)) {
        char ele;
        pop(&stack, &ele);
        printf("%c", ele);
    }
}
```

完整代码如下：

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
int push(SeqStack *stack, char ele) {
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
int pop(SeqStack *stack, char *ele) {
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
int getTop(SeqStack stack, char *ele) {
    // 1.参数校验，如果栈空则不能出栈
    if (stack.top == -1) {
        // 栈空，没有元素可出栈
        return 0;
    }
    // 2.保存栈顶元素返回
    *ele = stack.data[stack.top];
    return 1;
}

/**
 * 获取运算符的优先级，其中返回数字越小表示优先级越高
 * 注意，仅显示了部分单目运算符的优先级，主要是括号的优先级比乘除运算符的高，乘除运算符的优先级比加减运算符的高
 * @param c 运算符
 * @return 运算符的优先级别
 */
int priority(char c) {
    switch (c) {
        case '(':
        case ')':
            return 1;
        case '/':
        case '*':
        case '%':
            return 3;
        case '+':
        case '-':
            return 4;
        default:
            return 999;
    }
}

/**
 * 中缀表达式转换成后缀表达式
 * @param exps 中缀表达式字符数组
 * @param n 字符数组实际字符个数
 */
void infixToPostfixExpression(char exps[], int n) {
    // 0.声明顺序栈并初始化栈，因为该算法中要使用到栈
    SeqStack stack;
    init(&stack);

    // 变量，记录栈顶元素的值
    char top;

    // 从左到右扫描中缀表达式
    for (int i = 0; i < n; i++) {
        // 局部变量，即当前扫描到的字符
        char c = exps[i];
        // 如果是操作数
        if (c >= '0' && c <= '9') {
            // 则直接输出
            printf("%c", c);
        }
        // 如果不是操作数
        else {
            // 如果是左括号
            if (c == '(') {
                // 则直接入栈
                push(&stack, c);
            }
            // 如果是右括号
            else if (c == ')') {
                // 在栈不为空的情况下
                while (!isEmpty(stack)) {
                    // 出栈栈顶元素
                    pop(&stack, &top);
                    // 直到遇到左括号为止，但并不输出左括号
                    if (top != '(') {
                        printf("%c", top);
                    } else {
                        break;
                    }
                }
            }
            // 如果是其他字符
            else {
                // 如果栈空
                if (isEmpty(stack)) {
                    // 则入栈当前字符
                    push(&stack, c);
                }
                // 如果栈非空
                else {
                    // 在栈不为空的情况
                    while (!isEmpty(stack)) {
                        // 获取栈顶元素
                        getTop(stack, &top);
                        // 弹出栈中所有优先级大于或等于当前字符的栈顶元素，但左括号例外
                        if (top != '(' && priority(c) >= priority(top)) {
                            printf("%c", top);
                            pop(&stack, &top);
                        } else {
                            break;
                        }
                    }
                    // 无论是否出栈元素，都将当前字符入栈
                    push(&stack, c);
                }
            }
        }
    }

    // 扫描完中缀表达式后，检测运算符栈剩余的字符，全部出栈并输出到后缀表达式中
    while (!isEmpty(stack)) {
        char ele;
        pop(&stack, &ele);
        printf("%c", ele);
    }
}

int main() {
    char infixExp[] = "1+2*3+(4*5+6)*7";
    int n =15;

    infixToPostfixExpression(infixExp, n);
}
```



### 其他转换方式

将中缀表达式转换成后缀表达式的另外一种方法（适合选择题快速计算后缀表达式）：

- 例如，有中缀表达式 `a+b*c+(d*e+f)*g`。
- 先按照运算符的优先级对中缀表达式加括号，变成：`((a+(b*c))+(((d*e)+f)*g))`。
- 接着将运算符移到括号的后面，变成：`((a(bc)*)+(((de)*f)+g)*)+`。
- 最后去掉括号得到后缀表达式：`abc*+de*f+g*+`。





## 中缀表达式转前缀表达式

### 算法思想

算法思想：

- 设定一个**运算符栈**，**从右往左**顺序扫描整个中缀表达式中的每个字符：
  - 如果遇到的是**操作数**字符（如 `1`、`2`等数字），则直接输出到前缀表达式。
  - 如果遇到的是**非操作数**字符，进行如下判断：
    - 如果遇到**右括号**（如 `)`），则直接将其入栈。
    - 如果遇到**左括号**（如 `(`），则直接出栈操作，并将出栈的元素输出到前缀表达式中，直到弹出栈的是右括号为止，注意右括号不输出到前缀表达式中。
    - 如果遇到**其他字符**（如 `+`、`-`、`*`、`-`等运算符），也需要判断：
      - 如果运算符**栈为空**，则将该运算符直接入栈。
      - 如果运算符**栈不为空**，则：
        - 如果栈顶元素是右括号，则直接入栈。
        - 如果栈顶元素是运算符，则需要进行比较：
          - 如果当前扫描到的运算符优先级大于等于栈顶运算符，则直接入栈。
          - 如果当前扫描到的运算符优先级小于栈顶运算符，则将栈顶运算符弹出并且输出到前缀表达式，然后比较新的栈顶运算符，直到当前运算符的优先级大于等于栈顶运算符或栈为空为止。再将当前运算符入栈。
- 当扫描完毕整个中缀表达式，检测运算符栈是否为空，如果不为空，则依次将栈中运算符弹出栈，并且输出到前缀表达式。
- 最后将**前缀表达式翻转**，得到中缀表达式对应的前缀表达式。



### 示例

- 如 `1+2*3+(4*5+6)*7` 转换后的前缀表达式是 `++1*23*+*4567`。
- 如 `1+(2+3)*4-5` 转换后的前缀表达式是 `-+1*+2345`。

有中缀表达式 `a+b*c+(d*e+f)*g`，转换步骤如下：

- （1）首先读到操作数 `g`，直接输出到前缀表达式。
- （2）继续读到 `*`，将其放入运算符栈中。
- （3）继续读到 `)`，因为栈顶元素 `*` 的优先级比 `)` 低，所以将 `)` 直接压入栈中。此时运算符栈和前缀表达式如下：

![image-20220416175151210](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416175151210.png)

- （4）继续读到操作数 `f`，直接输出到前缀表达式。
- （5）继续读到 `+`，直接入栈。
- （6）继续读到操作数 `e`，直接输出到前缀表达式。此时运算符栈和前缀表达式如下：

![image-20220416175546338](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416175546338.png)

- （7）继续读到 `*`，因为栈顶元素是 `+` 的优先级比 `*` 低，所以直接将 `*` 入栈。
- （8）继续读到操作数 `d`，直接输出道前缀表达式。此时运算符栈和前缀表达式如下：

![image-20220416175750931](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416175750931.png)

- （9）继续读到 `(`，将栈中的操作符依次弹出栈，直到遇到 `)`。此时运算符栈和前缀表达式如下：

![image-20220416175915450](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416175915450.png)

- （10）继续读到 `+`，因为栈顶元素 `*` 的优先级比 `+` 高，因此弹出栈顶元素并输出道前缀表达式，再将 `+` 入栈。此时运算符栈和前缀表达式如下：

![image-20220416180045494](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416180045494.png)

- （11）继续读到操作数 `c`，直接输出到前缀表达式。
- （12）继续读到 `*`，因为栈顶元素 `+` 优先级比 `*`，所以直接将 `*` 入栈。
- （13）继续读到 `b`，直接输出到前缀表达式。此时运算符栈和前缀表达式如下：

![image-20220416180401932](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416180401932.png)

- （14）继续读到 `+`，因为栈顶元素 `*` 的优先级比 `+` 高，所以弹出栈顶元素并输出到前缀表达式中，然后再将 `+` 入栈。
- （15）继续读到 `a`，直接输出到前缀表达式。此时运算符栈和前缀表达式如下：

![image-20220416180713676](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416180713676.png)

- （16）此时输入数据已经读到末尾，栈中还有两个操作符 `+` 和 `+`，直接弹出并输出到前缀表达式。此时运算符栈和前缀表达式如下：

![image-20220416180911153](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416180911153.png)

- （17）将前缀表达式翻转，得到中缀表达式对应的真正前缀表达式。

![image-20220416181138014](image-Note001-%E5%89%8D%E7%BC%80%E5%92%8C%E4%B8%AD%E7%BC%80%E5%8F%8A%E5%90%8E%E7%BC%80%E8%A1%A8%E8%BE%BE%E5%BC%8F/image-20220416181138014.png)





### 实现代码

将中缀表达式转换成前缀表达式核心代码如下：

```c
/**
 * 获取运算符的优先级，其中返回数字越小表示优先级越高
 * 注意，仅显示了部分单目运算符的优先级，主要是括号的优先级比乘除运算符的高，乘除运算符的优先级比加减运算符的高
 * @param c 运算符
 * @return 运算符的优先级别
 */
int priority(char c) {
    switch (c) {
        case '(':
        case ')':
            return 1;
        case '/':
        case '*':
        case '%':
            return 3;
        case '+':
        case '-':
            return 4;
        default:
            return 999;
    }
}

/**
 * 中缀表达式转换成前缀表达式
 * @param exps 中缀表达式字符数组
 * @param n 字符数组实际字符个数
 */
SeqStack infixToPrefixExpression(char exps[], int n) {
    // 0.声明顺序栈并初始化栈，因为该算法中要使用到栈
    SeqStack stack;
    init(&stack);
    // 1.因为最后要将前缀表达式翻转，所以再创建一个栈用来存储转换后的前缀表达式，最后打印栈就直接是翻转后的前缀表达式了
    SeqStack resultStack;
    init(&resultStack);

    // 变量，记录栈顶元素的值
    char top;

    // 从右到左扫描中缀表达式
    for (int i = n - 1; i >= 0; i--) {
        // 局部变量，即当前扫描到的字符
        char c = exps[i];
        // 如果是操作数
        if (c >= '0' && c <= '9') {
            // 则直接输出，这里是存储到结果栈中
            push(&resultStack, c);
        }
        // 如果不是操作数
        else {
            // 如果是右括号
            if (c == ')') {
                // 则直接入栈
                push(&stack, c);
            }
            // 如果是左括号
            else if (c == '(') {
                // 在栈不为空的情况下
                while (!isEmpty(stack)) {
                    // 出栈栈顶元素
                    pop(&stack, &top);
                    // 直到遇到右括号为止，但并不输出右括号
                    if (top != ')') {
                        // 则直接输出，这里是存储到结果栈中
                        push(&resultStack, top);
                    } else {
                        break;
                    }
                }
            }
            // 如果是其他字符
            else {
                // 如果栈空
                if (isEmpty(stack)) {
                    // 则入栈当前字符
                    push(&stack, c);
                }
                // 如果栈非空
                else {
                    // 获取栈顶元素
                    getTop(stack, &top);
                    if(top==')'){
                        push(&stack, c);
                    } else{
                        // 注意，数字越小优先级越高
                        if(priority(c)<= priority(top)){
                            push(&stack, c);
                        } else{
                            // 在栈不为空的情况
                            while (!isEmpty(stack)) {
                                // 获取栈顶元素
                                getTop(stack, &top);
                                // 弹出栈中所有优先级大于当前字符的栈顶元素
                                if (priority(c) > priority(top)) {
                                    // 则直接输出，这里是存储到结果栈中
                                    push(&resultStack, top);
                                    // 将运算符栈栈顶元素出栈
                                    pop(&stack, &top);
                                } else {
                                    break;
                                }
                            }
                            // 无论是否出栈元素，都将当前字符入栈
                            push(&stack, c);
                        }
                    }
                }
            }
        }
    }

    // 扫描完中缀表达式后，检测运算符栈剩余的字符，全部出栈并输出到前缀表达式中
    while (!isEmpty(stack)) {
        char ele;
        pop(&stack, &ele);
        // 则直接输出，这里是存储到结果栈中
        push(&resultStack, ele);
    }

    // 返回结果栈
    return resultStack;
}
```

完整代码如下：

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
int push(SeqStack *stack, char ele) {
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
int pop(SeqStack *stack, char *ele) {
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
int getTop(SeqStack stack, char *ele) {
    // 1.参数校验，如果栈空则不能出栈
    if (stack.top == -1) {
        // 栈空，没有元素可出栈
        return 0;
    }
    // 2.保存栈顶元素返回
    *ele = stack.data[stack.top];
    return 1;
}

/**
 * 获取运算符的优先级，其中返回数字越小表示优先级越高
 * 注意，仅显示了部分单目运算符的优先级，主要是括号的优先级比乘除运算符的高，乘除运算符的优先级比加减运算符的高
 * @param c 运算符
 * @return 运算符的优先级别
 */
int priority(char c) {
    switch (c) {
        case '(':
        case ')':
            return 1;
        case '/':
        case '*':
        case '%':
            return 3;
        case '+':
        case '-':
            return 4;
        default:
            return 999;
    }
}

/**
 * 中缀表达式转换成前缀表达式
 * @param exps 中缀表达式字符数组
 * @param n 字符数组实际字符个数
 */
SeqStack infixToPrefixExpression(char exps[], int n) {
    // 0.声明顺序栈并初始化栈，因为该算法中要使用到栈
    SeqStack stack;
    init(&stack);
    // 1.因为最后要将前缀表达式翻转，所以再创建一个栈用来存储转换后的前缀表达式，最后打印栈就直接是翻转后的前缀表达式了
    SeqStack resultStack;
    init(&resultStack);

    // 变量，记录栈顶元素的值
    char top;

    // 从右到左扫描中缀表达式
    for (int i = n - 1; i >= 0; i--) {
        // 局部变量，即当前扫描到的字符
        char c = exps[i];
        // 如果是操作数
        if (c >= '0' && c <= '9') {
            // 则直接输出，这里是存储到结果栈中
            push(&resultStack, c);
        }
        // 如果不是操作数
        else {
            // 如果是右括号
            if (c == ')') {
                // 则直接入栈
                push(&stack, c);
            }
            // 如果是左括号
            else if (c == '(') {
                // 在栈不为空的情况下
                while (!isEmpty(stack)) {
                    // 出栈栈顶元素
                    pop(&stack, &top);
                    // 直到遇到右括号为止，但并不输出右括号
                    if (top != ')') {
                        // 则直接输出，这里是存储到结果栈中
                        push(&resultStack, top);
                    } else {
                        break;
                    }
                }
            }
            // 如果是其他字符
            else {
                // 如果栈空
                if (isEmpty(stack)) {
                    // 则入栈当前字符
                    push(&stack, c);
                }
                // 如果栈非空
                else {
                    // 获取栈顶元素
                    getTop(stack, &top);
                    if(top==')'){
                        push(&stack, c);
                    } else{
                        // 注意，数字越小优先级越高
                        if(priority(c)<= priority(top)){
                            push(&stack, c);
                        } else{
                            // 在栈不为空的情况
                            while (!isEmpty(stack)) {
                                // 获取栈顶元素
                                getTop(stack, &top);
                                // 弹出栈中所有优先级大于当前字符的栈顶元素
                                if (priority(c) > priority(top)) {
                                    // 则直接输出，这里是存储到结果栈中
                                    push(&resultStack, top);
                                    // 将运算符栈栈顶元素出栈
                                    pop(&stack, &top);
                                } else {
                                    break;
                                }
                            }
                            // 无论是否出栈元素，都将当前字符入栈
                            push(&stack, c);
                        }
                    }
                }
            }
        }
    }

    // 扫描完中缀表达式后，检测运算符栈剩余的字符，全部出栈并输出到前缀表达式中
    while (!isEmpty(stack)) {
        char ele;
        pop(&stack, &ele);
        // 则直接输出，这里是存储到结果栈中
        push(&resultStack, ele);
    }

    // 返回结果栈
    return resultStack;
}

int main() {
    char infixExp[] = "1+2*3+(4*5+6)*7";
    int n = 15;

    // 调用函数将中缀表达式转换成前缀表达式
    SeqStack resultStack = infixToPrefixExpression(infixExp, n);
    // 最后打印结果栈，从栈顶到栈底，就直接是前缀表达式翻转后的结果
    while (!isEmpty(resultStack)) {
        char ele;
        pop(&resultStack, &ele);
        printf("%c", ele);
    }
}
```



### 其他转换方式

还可以通过另外一种方式将中缀表达式转换成前缀表达式（适合选择题快速计算前缀表达式）：

- 例如，有中缀表达式 `a+b*c+(d*e+f)*g`。
- 先按照运算符的优先级对中缀表达式加括号，变成：`((a+(b*c))+(((d*e)+f)*g))`。
- 接着将运算符移到括号的前面，变成：`+(+(a*(bc))*(+(*(de)f)g))`。
- 最后去掉括号得到前缀表达式：`++a*bc*+*defg`。

