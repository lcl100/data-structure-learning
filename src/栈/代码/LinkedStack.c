#include <stdio.h>
#include <stdlib.h>

/**
 * 链栈结构体定义
 */
typedef struct LNode {
    /**
     * 数据域
     */
    int data;
    /**
     * 指针域，指向后继结点
     */
    struct LNode *next;
} LNode;// 链栈结点定义

/**
 * 初始化链栈
 * @param stack 未初始化的链栈
 */
void init(LNode **stack) {
    // 即创建链栈的头结点，为其分配空间
    *stack = (LNode *) malloc(sizeof(LNode));
    // 将头结点的 next 指针指向 null，表示这是一个空栈
    (*stack)->next = NULL;
}

/**
 * 判断链栈是否为空
 * @param stack 链栈
 * @return 如果链栈为空则返回 1，否则返回 0 表示非空链栈
 */
int isEmpty(LNode *stack) {
    // 即判断链栈的栈顶结点（即头结点的后继结点）是否存在
    if (stack->next == NULL) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 将元素入栈
 * @param stack 链栈
 * @param ele 新元素值
 */
void push(LNode **stack, int ele) {
    // 1.创建新节点，为其初始化数据域和指针域
    // 1.1 为新结点分配空间
    LNode *newNode = (LNode *) malloc(sizeof(LNode));
    // 1.2 为新结点指定数据域
    newNode->data = ele;
    // 1.3 将新结点的指针域初始指向 null，表示没有与任何结点进行连接
    newNode->next = NULL;

    // 2.将新节点入栈，成为栈顶结点
    // 2.1 将新结点的 next 指针指向原栈顶结点，完成新结点与原栈顶结点的链接
    newNode->next = (*stack)->next;
    // 2.2将链栈头结点的 next 指针指向新结点，即新结点成为了链栈的新栈顶结点
    (*stack)->next = newNode;
}

/**
 * 将元素出栈
 * @param stack 链栈
 * @param ele 用来保存栈顶结点的数据值
 * @return 如果栈空则不能出栈返回 0 表示出栈失败，否则返回 1 表示出栈成功
 */
int pop(LNode **stack, int *ele) {
    // 0.变量，记录栈顶结点
    LNode *topNode = (*stack)->next;
    // 1.判断链栈是否为空，分情况处理
    // 1.1 如果栈空，则返回 0 表示不能出栈
    if (topNode == NULL) {
        return 0;
    }
    // 1.2 如果栈不为空，则出栈栈顶元素
    else {
        // 1.2.1 用 ele 保存栈顶元素的值
        *ele = topNode->data;
        // 1.2.2 删除栈顶结点，即将链栈的头结点的 next 指针指向原栈顶结点的后继结点
        (*stack)->next = topNode->next;
        // 1.2.3 释放栈顶结点空间
        free(topNode);
        // 1.2.4 返回 1 表示出栈成功
        return 1;
    }
}

/**
 * 获取栈顶元素，但并不出栈
 * @param stack 链栈
 * @param ele 用来保存栈顶元素数据值
 * @return 如果栈空则不能获取栈顶元素则返回 0 表示出栈失败，否则返回 1 表示获取栈顶元素成功
 */
int getTop(LNode *stack, int *ele) {
    // 1.判断链栈是否为空
    // 1.1 如果栈空，则返回 0 表示失败
    if (stack->next == NULL) {
        return 0;
    }
    // 1.2 如果栈非空，则用 ele 保存栈顶元素的值
    else {
        // 1.2.1 用 ele 保存栈顶元素的值，其中 stack->next 指向栈顶结点
        *ele = stack->next->data;
        // 1.2.2 返回 1 表示获取成功
        return 1;
    }
}

/**
 * 获得链栈中结点个数
 * @param stack 链栈
 * @return 结点个数
 */
int size(LNode *stack) {
    // 0.变量，记录链栈的栈顶结点
    LNode *topNode = stack->next;
    // 0.变量，计数器，记录链栈中结点个数
    int len = 0;
    // 1.从栈顶扫描到栈底，统计链栈中结点个数
    while (topNode != NULL) {
        len++;
        topNode = topNode->next;
    }
    // 2.返回结点个数
    return len;
}

/**
 * 从栈顶到栈底，打印链栈所有结点
 * @param stack 链栈
 */
void print(LNode *stack) {
    printf("[");
    LNode *topNode = stack->next;
    while (topNode != NULL) {
        printf("%d", topNode->data);
        if (topNode->next != NULL) {
            printf(", ");
        }
        topNode = topNode->next;
    }
    printf("]\n");
}

/**
 * 清空链栈
 * @param stack 链栈
 */
void clear(LNode **stack) {
    // 变量，记录链栈的栈顶结点
    LNode *topNode = (*stack)->next;
    // 从栈顶到栈底扫描栈中所有结点
    while (topNode != NULL) {
        // 记录当前结点的后继结点
        LNode *temp = topNode->next;
        // 释放当前结点的存储空间
        free(topNode);
        // 继续栈的下一个结点
        topNode = temp;
    }
    // 最后将链栈头结点的 next 指针指向 null，表示这是一个空栈
    (*stack)->next = NULL;
}

/**
 * 销毁链栈
 * @param stack 链栈
 */
void destroy(LNode **stack) {
    // 释放头结点空间
    free(*stack);
}

int main() {
    // 声明链栈
    LNode *stack;

    // 初始化链栈
    printf("初始化链栈：\n");
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

    // 链栈是否为空
    printf("链栈是否为空：\n");
    int empty;
    empty = isEmpty(stack);
    printf("%d\n", empty);

    // 获取栈顶结点数据
    printf("获取栈顶结点数据：\n");
    int top;
    getTop(stack, &top);
    printf("%d\n", top);

    // 获取链栈中元素个数
    printf("获取链栈中元素个数：\n");
    int len;
    len = size(stack);
    printf("%d\n", len);

    // 清空链栈
    printf("清空链栈：\n");
    clear(&stack);
    print(stack);

    // 销毁链栈
    printf("销毁链栈：\n");
    destroy(&stack);
}