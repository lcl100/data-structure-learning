#include<stdio.h>
#include<stdlib.h>

/**
 * 链队列中的结点结构体定义
 */
typedef struct QNode {
    /**
     * 结点数据域，存储链队列中结点的数据
     */
    int data;
    /**
     * 结点指针域，存储当前结点的后继结点的地址
     */
    struct QNode *next;
} QNode;

/**
 * 链队列结构体定义
 */
typedef struct {
    /**
     * 存储链队列的队头结点的地址，即指向队头结点
     */
    QNode *front;
    /**
     * 存储链队列的队尾结点的地址，即指向队尾结点
     */
    QNode *rear;
} LinkedQueue;

/**
 * 初始化链队列
 * @param queue 未初始化的链队列
 */
void init(LinkedQueue **queue) {
    // 其实 queue 就相当于链队列的头结点，不过它有两个指针，分别存储队头结点和队尾结点的地址
    // 为链队列头结点分配存储空间
    *queue = (LinkedQueue *) malloc(sizeof(LinkedQueue));
    // 将队头指针和队尾指针都指向 NULL，表示空队列
    (*queue)->front = NULL;
    (*queue)->rear = NULL;
}

/**
 * 判断链队列是否为空
 * @param queue 链队列
 * @return 如果链队列为空则返回 1，否则返回 0 表示非空
 */
int isEmpty(LinkedQueue *queue) {
    // 只要链队列的队头指针或者队尾指针指向 NULL 则表示是空队
    if (queue->front == NULL || queue->rear == NULL) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 将元素入队
 * @param queue 链队列
 * @param ele 待入队的元素
 */
void enQueue(LinkedQueue **queue, int ele) {
    // 0.因为是链表来表示队列，理论上不存在队满的情况，所以不需要校验队满

    // 1.创建新结点
    // 1.1 为新结点分配空间
    QNode *newNode = (QNode *) malloc(sizeof(QNode));
    // 1.2 为新结点指定数据域
    newNode->data = ele;
    // 1.3 为新结点指定数据域，初始指向 NULL
    newNode->next = NULL;

    // 2.将新结点入队
    // 2.1 若队列为空，则新结点是队头结点，也是队尾结点
    if ((*queue)->rear == NULL) {
        // 因为链队列只有一个结点，所以将队头指针和队尾指针都指向新结点
        (*queue)->front = newNode;
        (*queue)->rear = newNode;
    }
    // 2.2 如果队列非空，则将新结点插入到队尾结点的后面，并将队尾指针指向新结点
    else {
        // 局部变量，记录队尾结点
        QNode *tailNode = (*queue)->rear;
        // 2.2.1 将新结点插入到队尾结点的后面
        tailNode->next = newNode;
        // 2.2.2 将队尾指针指向新结点
        (*queue)->rear = newNode;
    }
}

/**
 * 将元素出队
 * @param queue 链队列
 * @param ele 用来保存出队元素
 * @return 如果链队列为空则不能出队则返回 0 表示出队失败；否则返回 1 表示出队成功
 */
int deQueue(LinkedQueue **queue, int *ele) {
    // 0.参数校验，如果队空则不能出队
    if ((*queue)->front == NULL || (*queue)->rear == NULL) {
        return 0;
    }

    // 1.将队头结点出队
    // 1.1 变量，记录链队列的队头结点
    QNode *frontNode = (*queue)->front;
    // 1.2 用 ele 保存队头结点的数据域，即要出队的结点值
    *ele = frontNode->data;
    // 1.3 删除队头结点并修改队头指针
    // 1.3.1 如果队列中只有一个结点时的出队操作需要特殊处理，因为需要将队头指针和队尾指针都指向 NULL
    if ((*queue)->front == (*queue)->rear) {
        (*queue)->front = NULL;
        (*queue)->rear = NULL;
    }
    // 1.3.2 当队列不止一个结点时，将队头指针指向原队头结点的后继结点
    else {
        (*queue)->front = frontNode->next;
    }
    // 1.4 释放原队头结点
    free(frontNode);
    // 1.5 返回 1 表示出队成功
    return 1;
}

/**
 * 获取链队列中的结点个数
 * @param queue 链队列
 * @return 结点个数
 */
int size(LinkedQueue *queue) {
    // 变量，记录链队列结点个数
    int len = 0;
    // 变量，结点链队列的队头结点，相当于单链表的开始结点
    QNode *node = queue->front;
    // 扫描链队列，即遍历单链表，统计结点个数
    while (node != NULL) {
        len++;
        node = node->next;
    }
    return len;
}

/**
 * 获取链队列的队头结点数据值
 * @param queue 链队列
 * @param ele 用来保存队头结点数据值
 * @return 如果链队列为空则返回 0 表示获取失败，否则返回 1 表示获取成功
 */
int getFront(LinkedQueue *queue, int *ele) {
    // 0.参数校验，如果链队列为空，则表示不能获取队头元素
    if (queue->front == NULL || queue->rear == NULL) {
        return 0;
    }
    // 1.用 ele 保存队头结点的数据值，即队头指针所指向的结点
    *ele = queue->front->data;
    return 1;
}

/**
 * 获取链队列的队尾结点数据值
 * @param queue 链队列
 * @param ele 用来保存队尾结点数据值
 * @return 如果链队列为空则返回 0 表示获取失败，否则返回 1 表示获取成功
 */
int getRear(LinkedQueue *queue, int *ele) {
    // 0.参数校验，如果链队列为空，则表示不能获取队尾元素
    if (queue->front == NULL || queue->rear == NULL) {
        return 0;
    }
    // 1.用 ele 保存队尾结点的数据值，即队尾指针所指向的结点
    *ele = queue->rear->data;
    return 1;
}

/**
 * 打印链队列的所有结点值
 * @param queue 链队列
 */
void print(LinkedQueue *queue) {
    printf("[");
    QNode *frontNode = queue->front;
    while (frontNode != NULL) {
        printf("%d", frontNode->data);
        if (frontNode->next != NULL) {
            printf(", ");
        }
        frontNode = frontNode->next;
    }
    printf("]\n");
}

/**
 * 清空链队列
 * @param queue 链队列
 */
void clear(LinkedQueue **queue) {
    // 变量，记录链队列中的节点，初始为链队列的队头结点
    QNode *frontNode = (*queue)->front;
    // 扫描链队列所有结点，释放每个结点的空间
    while (frontNode != (*queue)->rear) {
        // 保存当前节点的后继结点，因为要释放结点，所以需要提前保存
        QNode *temp = frontNode->next;
        // 释放当前节点
        free(frontNode);
        // 继续链队列的下一个结点
        frontNode = temp;
    }
    // 最后链队列头结点的队头指针和队尾指针都指向 NULL 表示空队列
    (*queue)->front = NULL;
    (*queue)->rear = NULL;
}

/**
 * 销毁链队列
 * @param queue 链队列
 */
void destroy(LinkedQueue **queue) {
    // 即释放链队列头结点的空间
    free(*queue);
}


int main() {
    // 声明链队列
    LinkedQueue *queue;

    // 初始化链队列
    printf("\n初始化链队列：\n");
    init(&queue);
    print(queue);

    // 将元素入队
    printf("\n将元素入队：\n");
    enQueue(&queue, 11);
    print(queue);
    enQueue(&queue, 22);
    print(queue);
    enQueue(&queue, 33);
    print(queue);
    enQueue(&queue, 44);
    print(queue);
    enQueue(&queue, 55);
    print(queue);

    // 将元素出队
    printf("\n将元素出队：\n");
    int ele;
    deQueue(&queue, &ele);
    printf("出队元素：%d\n", ele);
    print(queue);
    deQueue(&queue, &ele);
    printf("出队元素：%d\n", ele);
    print(queue);
    deQueue(&queue, &ele);
    printf("出队元素：%d\n", ele);
    print(queue);
    deQueue(&queue, &ele);
    printf("出队元素：%d\n", ele);
    print(queue);

    // 队列是否为空
    printf("\n队列是否为空：\n");
    int empty;
    empty = isEmpty(queue);
    printf("%d\n", empty);

    // 队列元素个数
    printf("\n队列元素个数：\n");
    int len;
    len = size(queue);
    printf("%d\n", len);

    // 获取队头元素
    printf("\n获取队头元素：\n");
    int front;
    getFront(queue, &front);
    printf("%d\n", front);

    // 获取队尾元素
    printf("\n获取队尾元素：\n");
    int rear;
    getRear(queue, &rear);
    printf("%d\n", rear);

    // 清空队列
    printf("\n清空队列：\n");
    clear(&queue);
    print(queue);

    // 销毁队列
    printf("\n销毁队列：\n");
    destroy(&queue);
}