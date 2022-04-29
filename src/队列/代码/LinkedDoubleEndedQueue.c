#include<stdio.h>
#include<stdlib.h>

/**
 * 链式双端队列，本质上还是单链表，所以如下是单链表结点的结构体定义
 */
typedef struct QNode {
    /**
     * 结点数据域
     */
    int data;
    /**
     * 结点指针域，存储当前结点的后继结点的地址
     */
    struct QNode *next;
} QNode;

/**
 * 链式双端队列结构体定义
 */
typedef struct {
    /**
     * 指针域，存储双端队列队头结点的地址
     */
    QNode *front;
    /**
     * 指针域，存储双端队列队尾结点的地址
     */
    QNode *back;
} LinkedDoubleEndedQueue;

/**
 * 初始化链式双端队列
 * @param deque 未初始化的链式双端队列
 */
void init(LinkedDoubleEndedQueue **deque) {
    // deque 就是链式双端队列的头结点
    // 为头结点分配存储空间
    (*deque) = (LinkedDoubleEndedQueue *) malloc(sizeof(LinkedDoubleEndedQueue));
    // 将队头指针和队尾指针指向 null 表示空队列
    (*deque)->front = NULL;
    (*deque)->back = NULL;
}

/**
 * 判断链式双端队列是否为空
 * @param deque 链式双端队列
 * @return 如果为空则返回 1，否则返回 0 表示非空
 */
int isEmpty(LinkedDoubleEndedQueue *deque) {
    // 跟链式队列的判空条件一样，只要队头指针或队尾指针指向 null 则表示空
    if (deque->front == NULL || deque->back == NULL) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 将元素从队头入队
 * @param deque 链式双端队列
 * @param ele 待入队的元素
 */
void pushFront(LinkedDoubleEndedQueue **deque, int ele) {
    // 1.创建新结点
    // 1.1 为新结点分配存储空间
    QNode *newNode = (QNode *) malloc(sizeof(QNode));
    // 1.2 为新结点指定数据域
    newNode->data = ele;
    // 1.3 将新结点的数据域指向 null，表示没有跟任何结点有关联
    newNode->next = NULL;

    // 2.将新结点插入到队列的头部
    // 2.1 如果是空队列则新结点既是队头结点也是队尾结点
    if (isEmpty(*deque)) {
        // 2.1.1 将队头指针指向新结点
        (*deque)->front = newNode;
        // 2.1.2 将队尾指针指向新结点
        (*deque)->back = newNode;
    }
    // 2.2 如果不是空队列，则将新结点插入到原队头结点的前面，然后新结点成为新的队头结点
    else {
        // 2.2.1 局部变量，记录队列的原队头结点
        QNode *frontNode = (*deque)->front;
        // 2.2.2 将新结点的 next 指针指向原队头结点，即将新结点与队列链接起来
        newNode->next = frontNode;
        // 2.2.3 将队头指针指向新结点，表示新结点成为了队列新的队头结点
        (*deque)->front = newNode;
    }
}

/**
 * 将元素从队尾入队
 * @param deque 链式双端队列
 * @param ele 待入队的元素
 */
void pushBack(LinkedDoubleEndedQueue **deque, int ele) {
    // 1.创建新结点
    // 1.1 为新结点分配存储空间
    QNode *newNode = (QNode *) malloc(sizeof(QNode));
    // 1.2 为新结点指定数据域
    newNode->data = ele;
    // 1.3 将新结点的数据域指向 null，表示没有跟任何结点有关联
    newNode->next = NULL;

    // 2.将新结点插入到队列的尾部
    // 2.1 如果是空表则新结点既是队头结点也是队尾结点
    if (isEmpty(*deque)) {
        // 2.1.1 将队头指针指向新结点
        (*deque)->front = newNode;
        // 2.1.2 将队尾指针指向新结点
        (*deque)->back = newNode;
    }
    // 2.2 如果不是空队列，则将新结点插入到原队尾结点的后面，然后新结点成为新的队尾结点
    else {
        // 2.2.1 局部变量，记录队列的原队尾结点
        QNode *backNode = (*deque)->back;
        // 2.2.2 将原队尾结点的 next 指针指向新结点，即将队列与新结点链接起来了
        backNode->next = newNode;
        // 2.2.3 将队尾指针指向新结点，表示新结点成为了队列的新的尾结点
        (*deque)->back = newNode;
    }
}

/**
 * 将元素从队头出队
 * @param deque 链式双端队列
 * @param ele 用来保存出队元素
 * @return 如果队空则不能出队则返回 0 表示出队失败，否则返回 1 表示出队成功
 */
int popFront(LinkedDoubleEndedQueue **deque, int *ele) {
    // 0.参数校验，如果队空则不能出队
    if (isEmpty(*deque)) {
        return 0;
    }

    // 1.将队头结点出队
    // 1.1 局部变量，记录队列的队头结点
    QNode *frontNode = (*deque)->front;
    // 1.2 用 ele 保存队头结点的数据值
    *ele = frontNode->data;
    // 1.3 删除队列中的队头结点
    // 1.3.1 如果队列中只有一个结点，那么这个结点既是队头结点也是队尾结点，那么删除后队头指针和队尾指针都应该指向 null 表示空队列
    if ((*deque)->front == (*deque)->back) {
        // 1.3.1.1 将队头指针指向 null
        (*deque)->front = NULL;
        // 1.3.1.2 将队尾指针指向 null
        (*deque)->back = NULL;
    }
    // 1.3.2 如果队列中不止一个结点，那么删除队头结点即可
    else {
        // 1.3.2.1 即将队头指针指向原队头结点的后继结点
        (*deque)->front = frontNode->next;
    }
    // 1.4 释放原队头结点的空间
    free(frontNode);
    // 1.5 返回 1 表示出队成功
    return 1;
}

/**
 * 将元素从队尾出队
 * @param deque 链式双端队列
 * @param ele 用来保存出队元素
 * @return 如果队空则不能出队则返回 0 表示出队失败，否则返回 1 表示出队成功
 */
int popBack(LinkedDoubleEndedQueue **deque, int *ele) {
    // 0.参数校验，如果队空则不能出队
    if (isEmpty(*deque)) {
        return 0;
    }

    // 1.将队尾结点出队
    // 1.1 局部变量，记录队列的队尾结点
    QNode *backNode = (*deque)->back;
    // 1.2 用 ele 保存队尾结点的数据值，即出队元素
    *ele = backNode->data;
    // 1.3 删除队列中的队尾结点
    // 1.3.1 如果队列中只有一个结点，那么这个结点既是队头结点也是队尾结点，那么删除后队头指针和队尾指针都应该指向 null 表示空队列
    if ((*deque)->front == (*deque)->back) {
        // 1.3.1.1 将队头指针指向 null
        (*deque)->front = NULL;
        // 1.3.1.2 将队尾指针指向 null
        (*deque)->back = NULL;
    }
    // 1.3.2 如果队列中不止一个结点，那么删除队尾结点
    else {
        // 1.3.2.1 首先，由于是单链表构成的链式双端队列，所以要先找到队列队尾节点的前驱节点
        // 单链表不太好找尾节点的前驱节点，可以考虑用双链表来实现链式双端队列
        // 循环结束后，node 结点就是单链表尾结点的前驱结点
        QNode *node = (*deque)->front;
        while (node->next->next != NULL) {
            node = node->next;
        }
        // 1.3.2.2 斩断队尾结点的前驱结点与尾结点的联系，因为该结点会成为新的队尾结点
        node->next = NULL;
        // 1.3.2.3 将队尾指针指向该结点，表示该结点成为了队列的新队尾结点
        (*deque)->back = node;
    }
    // 1.4 释放原队尾结点的存储空间
    free(backNode);
    // 1.5 返回 1 表示出队成功
    return 1;
}

/**
 * 获取链式双端队列的结点个数
 * @param deque 链式双端队列
 * @return 结点个数
 */
int size(LinkedDoubleEndedQueue *deque) {
    // 链式双端队列本质上还是一个单链表，所以遍历单链表计算结点个数
    // 变量，记录队列中的结点，初始为队头结点，即单链表的开始结点
    QNode *node = deque->front;
    // 变量，记录结点个数
    int len = 0;
    // 从队头结点开始扫描整个队列
    while (node != NULL) {
        // 每迭代一次结点个数加一
        len++;
        // 继续下一个结点
        node = node->next;
    }
    // 返回统计出来的点个数
    return len;
}

/**
 * 获取双端队列的队头元素
 * @param deque 链式双端队列
 * @param ele 用来保存队头元素
 * @return 如果队空则不能出队则返回 0 表示出队失败，否则返回 1 表示出队成功
 */
int getFront(LinkedDoubleEndedQueue *deque, int *ele) {
    // 0.参数校验，如果是空队列，则不能获取队头元素
    if (isEmpty(deque)) {
        return 0;
    }
    // 1.用 ele 保存队头指针指向的队头结点的元素值
    *ele = deque->front->data;
    return 1;
}

/**
 * 获取双端队列的队尾元素
 * @param deque 链式双端队列
 * @param ele 用来保存队尾元素
 * @return 如果队空则不能出队则返回 0 表示出队失败，否则返回 1 表示出队成功
 */
int getBack(LinkedDoubleEndedQueue *deque, int *ele) {
    // 0.参数校验，如果是空队列，则不能获取队尾元素
    if (isEmpty(deque)) {
        return 0;
    }
    // 1.用 ele 保存队尾指针指向的队尾结点的元素值
    *ele = deque->back->data;
    return 1;
}

/**
 * 清空链式双端队列
 * @param deque 链式双端队列
 */
void clear(LinkedDoubleEndedQueue **deque) {
    // 变量，记录队列中的结点，初始为队头结点，即单链表的开始结点
    QNode *node = (*deque)->front;
    // 从队头结点开始扫描整个队列
    while (node != NULL) {
        // 变量，记录当前节点的后继节点，因为要释放当前节点的空间，所以要记录其后继节点便于处理下一个节点
        QNode *temp = node->next;
        // 释放当前节点的空间
        free(node);
        // 继续下一个节点
        node = temp;
    }
    // 将队头指针和队尾指针指向 null 表示是一个空队列
    (*deque)->front = NULL;
    (*deque)->back = NULL;
}

/**
 * 销毁链式双端队列
 * @param deque 链式双端队列
 */
void destroy(LinkedDoubleEndedQueue **deque) {
    // 即释放头结点的存储空间
    free(*deque);
}

/**
 * 打印链式双端队列从队头到队尾的所有结点值
 * @param deque 链式双端队列
 */
void print(LinkedDoubleEndedQueue *deque) {
    QNode *node = deque->front;
    printf("[");
    while (node != NULL) {
        printf("%d", node->data);
        if (node->next != NULL) {
            printf(", ");
        }
        node = node->next;
    }
    printf("]\n");
}

int main() {
    // 声明链式双端队列
    LinkedDoubleEndedQueue *deque;

    // 初始化队列
    printf("\n初始化队列：\n");
    init(&deque);
    print(deque);

    // 从队头将元素入队
    printf("\n从队头将元素入队：\n");
    pushFront(&deque, 11);
    print(deque);
    pushFront(&deque, 22);
    print(deque);
    pushFront(&deque, 33);
    print(deque);
    pushFront(&deque, 44);
    print(deque);
    pushFront(&deque, 55);
    print(deque);

    // 从队尾将元素入队
    printf("\n从队尾将元素入队：\n");
    pushBack(&deque, 111);
    print(deque);
    pushBack(&deque, 222);
    print(deque);
    pushBack(&deque, 333);
    print(deque);
    pushBack(&deque, 444);
    print(deque);
    pushBack(&deque, 555);
    print(deque);

    // 从队头将元素出队
    int ele1;
    printf("\n从队头将元素出队：\n");
    popFront(&deque, &ele1);
    printf("出队元素：%d\n", ele1);
    print(deque);
    popFront(&deque, &ele1);
    printf("出队元素：%d\n", ele1);
    print(deque);
    popFront(&deque, &ele1);
    printf("出队元素：%d\n", ele1);
    print(deque);

    // 从队尾将元素出队
    int ele2;
    printf("\n从队尾将元素出队：\n");
    popBack(&deque, &ele2);
    printf("出队元素：%d\n", ele2);
    print(deque);
    popBack(&deque, &ele2);
    printf("出队元素：%d\n", ele2);
    print(deque);
    popBack(&deque, &ele2);
    printf("出队元素：%d\n", ele2);
    print(deque);

    // 队列是否空
    printf("\n队列是否空：\n");
    int empty;
    empty = isEmpty(deque);
    printf("%d\n", empty);

    // 队列中的元素个数
    printf("\n队列中的元素个数：\n");
    int len;
    len = size(deque);
    printf("%d\n", len);

    // 队头元素
    printf("\n队头元素：\n");
    int front;
    getFront(deque, &front);
    printf("%d\n", front);

    // 队尾元素
    printf("\n队尾元素：\n");
    int back;
    getBack(deque, &back);
    printf("%d\n", back);

    // 清空队列
    printf("\n清空队列：\n");
    clear(&deque);
    print(deque);

    // 销毁队列
    printf("\n销毁队列：\n");
    destroy(&deque);
}