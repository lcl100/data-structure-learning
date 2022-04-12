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

/**
 * 获取顺序栈中元素个数
 * @param stack 顺序栈
 * @return 顺序栈中元素个数
 */
int size(SeqStack stack) {
    // top 表示栈顶指针，实际上就是数组 data 的下标，所以实际元素个数就是下标加一
    // 即使是空栈 top=-1，那么最后也会返回 0 表示元素个数为零个
    return stack.top + 1;
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

/**
 * 清空顺序栈中所有元素
 * @param stack 顺序栈
 */
void clear(SeqStack *stack) {
    // 将栈顶指针指向 -1 即可，不需要重置一遍栈中元素
    stack->top = -1;
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