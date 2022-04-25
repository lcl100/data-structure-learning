#include<stdio.h>
#include<stdlib.h>

typedef struct QNode {
    int data;
    struct QNode *next;
} QNode;

typedef struct {
    QNode *front;
    QNode *rear;
} LinkedQueue;

/**
 *
 * @param queue
 */
void init(LinkedQueue **queue) {
    *queue = (LinkedQueue *) malloc(sizeof(LinkedQueue));
    (*queue)->front = NULL;
    (*queue)->rear = NULL;
}

/**
 *
 * @param queue
 * @return
 */
int isEmpty(LinkedQueue *queue) {
    if (queue->front == NULL || queue->rear == NULL) {
        return 1;
    } else {
        return 0;
    }
}

/**
 *
 * @param queue
 * @param ele
 */
void enQueue(LinkedQueue **queue, int ele) {
    // 创建新结点
    QNode *newNode = (QNode *) malloc(sizeof(QNode));
    newNode->data = ele;
    newNode->next = NULL;
    // 若队列为空，则新结点是队头结点，也是队尾结点
    if ((*queue)->rear == NULL) {
        (*queue)->front = newNode;
        (*queue)->rear = newNode;
    } else {
        // 将新结点插入到队列的尾部，让 rear 指向它
        QNode *tailNode = (*queue)->rear;
        tailNode->next = newNode;
        (*queue)->rear = newNode;
    }
}

/**
 *
 * @param queue
 * @param ele
 * @return
 */
int deQueue(LinkedQueue **queue, int *ele) {
    // 参数校验，如果队空则不能入队
    if ((*queue)->front == NULL || (*queue)->rear == NULL) {
        return 0;
    }
    QNode *frontNode = (*queue)->front;
    *ele = frontNode->data;
    if ((*queue)->front == (*queue)->rear) {// 如果队列中只有一个结点时的出队操作需要特殊处理
        (*queue)->front = NULL;
        (*queue)->rear = NULL;
    } else {
        (*queue)->front = frontNode->next;
    }
    free(frontNode);
    return 1;
}

/**
 *
 * @param queue
 * @return
 */
int size(LinkedQueue *queue) {
    int len = 0;
    QNode *node = queue->front;
    while (node != NULL) {
        len++;
        node = node->next;
    }
    return len;
}

/**
 *
 * @param queue
 * @param ele
 * @return
 */
int getFront(LinkedQueue *queue, int *ele) {
    if (queue->front == NULL || queue->rear == NULL) {
        return 0;
    }
    *ele = queue->front->data;
    return 1;
}

/**
 *
 * @param queue
 * @param ele
 * @return
 */
int getRear(LinkedQueue *queue, int *ele) {
    if (queue->front == NULL || queue->rear == NULL) {
        return 0;
    }
    *ele = queue->rear->data;
    return 1;
}

/**
 *
 * @param queue
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
 *
 * @param queue
 */
void clear(LinkedQueue **queue) {
    QNode *frontNode = (*queue)->front;
    while (frontNode != (*queue)->rear) {
        QNode *temp = frontNode->next;
        free(frontNode);
        frontNode = temp;
    }
    (*queue)->front = NULL;
    (*queue)->rear = NULL;
}

/**
 *
 * @param queue
 */
void destroy(LinkedQueue **queue) {
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