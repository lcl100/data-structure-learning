#include<stdio.h>

/**
 * 共享栈能存储的最大元素个数
 */
#define MAXSIZE 100

/**
 * 共享栈结构体定义
 */
typedef struct {
    /**
     * 数据域，存储栈中元素
     */
    int data[MAXSIZE];
    /**
     * 指针域，记录 0 号栈和 1 号栈的栈顶指针
     */
    int top[2];
} SharedStack;

/**
 * 初始化共享栈
 * @param stack 未初始化的共享栈
 */
void init(SharedStack *stack) {
    // 1.需要同时初始化 0 号栈和 1 号栈
    // 1.1 将 0 号栈的栈顶指针指向 -1，表示 0 号栈是空栈
    stack->top[0] = -1;
    // 1.2 将 1 号栈的栈顶指针指向 MAXSIZE，表示 1 号栈是空栈
    stack->top[1] = MAXSIZE;
}

/**
 * 判断指定序号的栈是否是空栈
 * @param stack 共享栈
 * @param NUM 栈序号，只能传入 0 或者 1
 * @return 如果指定栈是空栈则返回 1，否则返回 0 表示非空栈
 */
int isEmpty(SharedStack stack, int NUM) {
    if (NUM == 0) {
        // 0 号栈为空栈的条件是，栈顶指针指向 -1
        return stack.top[0] == -1;
    } else if (NUM == 1) {
        // 1 号栈为空栈的条件是，栈顶指针指向 MAXSIZE
        return stack.top[1] == MAXSIZE;
    } else {
        // 随便返回一个数，表示传入的序号不合法
        return -MAXSIZE;
    }
}

/**
 * 判断共享栈是否是满
 * @param stack 共享栈
 * @return 如果是栈满则返回 1，否则返回 0 表示栈未满
 */
int isFull(SharedStack stack) {
    // 如果 0 号栈和 1 号栈的栈顶元素相邻，则表示栈已满
    if (stack.top[1] - stack.top[0] == 1) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 将元素压入栈
 * @param stack 共享栈
 * @param NUM 栈序号，只能传入 0 或者 1
 * @param ele 新元素
 * @return 如果栈满则返回 0 表示入栈失败；入栈成功则返回 1
 */
int push(SharedStack *stack, int NUM, int ele) {
    // 0.参数校验，如果栈满则不能入栈
    if (isFull(*stack)) {
        return 0;
    }
    // 1.根据栈序号是 0 还是 1，来决定将元素存入哪个栈
    // 1.1 将元素存入 0 号栈
    if (NUM == 0) {
        // 1.1.1 先移动 0 号栈的栈顶指针。由于 0 号栈是从 -1 开始的，所以栈顶指针是往后增
        stack->top[0]++;
        // 1.1.2 再赋值
        stack->data[stack->top[0]] = ele;
    }
    // 1.2 将元素存入 1 号栈
    else if (NUM == 1) {
        // 1.2.1 先移动 1 号栈的栈顶指针。由于 1 号栈是从 MAXSIZE 开始的，所以栈顶指针是往前减
        stack->top[1]--;
        // 1.2.2 再赋值
        stack->data[stack->top[1]] = ele;
    }
    return 1;
}

/**
 * 将元素出栈
 * @param stack 共享栈
 * @param NUM 栈序号，只能传入 0 或者 1
 * @param ele 用来保存出栈元素
 * @return 如果栈空则返回 0 表示出栈失败；否则返回 1 表示出栈成功
 */
int pop(SharedStack *stack, int NUM, int *ele) {
    // 0.参数校验，如果任何一个栈栈空则不能出栈
    if (isEmpty(*stack, NUM)) {
        return 0;
    }
    // 1.根据栈序号来决定将哪个栈的栈顶元素出栈
    // 1.1 如果要将 0 号栈的栈顶元素出栈
    if (NUM == 0) {
        // 1.1.1 用 ele 保存 0 号栈的栈顶元素
        *ele = stack->data[stack->top[0]];
        // 1.1.2 移动栈顶指针删除元素
        stack->top[0]--;
    }
    // 1.2 如果要将 1 号栈的栈顶元素出栈
    else if (NUM == 1) {
        // 1.2.1 用 ele 保存 1 号栈的栈顶元素
        *ele = stack->data[stack->top[1]];
        // 1.2.2 移动栈顶指针删除元素
        stack->top[1]++;
    }
    return 1;
}

/**
 * 获取指定序号栈的栈顶元素，但不出栈
 * @param stack 共享栈
 * @param NUM 栈序号，只能传入 0 或者 1
 * @param ele 用来保存栈顶元素
 * @return 如果栈空则返回 0 表示出栈失败；否则返回 1 表示出栈成功
 */
int getTop(SharedStack stack, int NUM, int *ele) {
    // 0.参数校验，如果任何一个栈栈空则不能出栈
    if (isEmpty(stack, NUM)) {
        return 0;
    }
    // 1.用 ele 保存栈顶元素
    // 1.1 用 ele 保存 0 号栈的栈顶元素
    if (NUM == 0) {
        *ele = stack.data[stack.top[0]];
    }
    // 1.2 用 ele 保存 1 号栈的栈顶元素
    else if (NUM == 1) {
        *ele = stack.data[stack.top[1]];
    }
    return 1;
}

/**
 * 获取共享栈中指定序号栈的元素个数
 * @param stack 共享栈
 * @param NUM 栈序号，只能传入 0 或者 1
 * @return 指定序号栈的元素个数
 */
int size(SharedStack stack, int NUM) {
    // 变量，记录栈中结点个数
    int len = 0;
    // 1.获取指定序号栈的元素个数
    // 1.1 获取 0 号栈的元素个数
    if (NUM == 0) {
        // 下标从 0 开始，所以元素个数就是下标加一
        len = stack.top[0] + 1;
    }
    // 1.2 获取 1 号栈的元素个数
    else if (NUM == 1) {
        // 1 号栈的元素从后往前，所以计算栈的元素个数是 MAXSIZE 减去 1 号栈的栈顶指针
        len = MAXSIZE - stack.top[1];
    }
    return len;
}

/**
 * 打印指定序号栈中的所有元素
 * @param stack 共享栈
 * @param NUM 栈序号，只能传入 0 或者 1
 */
void print(SharedStack stack, int NUM) {
    printf("[");
    // 变量，记录栈顶指针
    int top;
    if (NUM == 0) {
        top = stack.top[0];
        for (int i = top; i >= 0; i--) {
            printf("%d", stack.data[i]);
            if (i != 0) {
                printf(", ");
            }
        }
    } else if (NUM == 1) {
        top = stack.top[1];
        for (int i = top; i < MAXSIZE; i++) {
            printf("%d", stack.data[i]);
            if (i != MAXSIZE - 1) {
                printf(", ");
            }
        }
    }
    printf("]\n");
}

/**
 * 清空 0 号栈的所有元素
 * @param stack 共享栈
 * @param NUM 栈序号，只能传入 0 或者 1
 */
void clear(SharedStack *stack, int NUM) {
    if (NUM == 0) {
        // 直接将 0 号的栈顶指针指向 -1，就表示是空栈
        stack->top[0] = -1;
    } else if (NUM == 1) {
        // 直接将 1 号的栈顶指针指向 MAXSIZE，就表示是空栈
        stack->top[1] = MAXSIZE;
    }
}

int main() {
    // 声明并初始化共享栈
    SharedStack stack;
    init(&stack);

    // 将元素存入0号栈
    printf("\n将元素存入0号栈：\n");
    push(&stack, 0, 11);
    print(stack, 0);
    push(&stack, 0, 22);
    print(stack, 0);
    push(&stack, 0, 33);
    print(stack, 0);
    push(&stack, 0, 44);
    print(stack, 0);
    push(&stack, 0, 55);
    print(stack, 0);

    // 将元素存入1号栈
    printf("\n将元素存入1号栈：\n");
    push(&stack, 1, 555);
    print(stack, 1);
    push(&stack, 1, 444);
    print(stack, 1);
    push(&stack, 1, 333);
    print(stack, 1);
    push(&stack, 1, 222);
    print(stack, 1);
    push(&stack, 1, 111);
    print(stack, 1);

    // 共享栈是否满
    printf("\n共享栈是否满：\n");
    int full;
    full = isFull(stack);
    printf("%d\n", full);

    // 将0号栈的元素出栈
    printf("\n将0号栈的元素出栈：\n");
    int top0;
    pop(&stack, 0, &top0);
    printf("top0: %d\n", top0);
    print(stack, 0);
    pop(&stack, 0, &top0);
    printf("top0: %d\n", top0);
    print(stack, 0);
    pop(&stack, 0, &top0);
    printf("top0: %d\n", top0);
    print(stack, 0);

    // 将1号栈的元素出栈
    printf("\n将1号栈的元素出栈：\n");
    int top1;
    pop(&stack, 1, &top1);
    printf("top1: %d\n", top1);
    print(stack, 1);
    pop(&stack, 1, &top1);
    printf("top1: %d\n", top1);
    print(stack, 1);
    pop(&stack, 1, &top1);
    printf("top1: %d\n", top1);
    print(stack, 1);

    // 0号栈是否空
    printf("\n0号栈是否空：\n");
    int empty0;
    empty0 = isEmpty(stack, 0);
    printf("%d\n", empty0);

    // 1号栈是否空
    printf("\n1号栈是否空：\n");
    int empty1;
    empty1 = isEmpty(stack, 1);
    printf("%d\n", empty1);

    // 获取0号栈栈顶元素
    printf("\n获取0号栈栈顶元素：\n");
    getTop(stack, 0, &top0);
    printf("%d\n", top0);

    // 获取1号栈栈顶元素
    printf("\n获取1号栈栈顶元素：\n");
    getTop(stack, 1, &top1);
    printf("%d\n", top1);

    // 获取0号栈中元素个数
    printf("\n获取0号栈中元素个数：\n");
    int len0;
    len0 = size(stack, 0);
    printf("%d\n", len0);

    // 获取1号栈中元素个数
    printf("\n获取1号栈中元素个数：\n");
    int len1;
    len1 = size(stack, 1);
    printf("%d\n", len1);

    // 获取共享栈中的总元素个数
    printf("\n获取共享栈中的总元素个数：\n");
    int len;
    len = size(stack, 0) + size(stack, 1);
    printf("%d\n", len);

    // 清空0号栈
    printf("\n清空0号栈：\n");
    clear(&stack, 0);
    print(stack, 0);

    // 清空1号栈
    printf("\n清空1号栈：\n");
    clear(&stack, 1);
    print(stack, 1);
}