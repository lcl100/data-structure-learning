#include<stdio.h>

/**
 * 循环队列中能存储的最大元素个数
 */
#define MAXSIZE 5

typedef struct {
    int data[MAXSIZE];
    int front;
    int rear;
} CircularQueue;

/**
 * 初始化循环队列
 * @param queue 待初始化的循环队列
 */
void init(CircularQueue *queue) {
    queue->front = 0;
    queue->rear = 0;
}

/**
 *
 * @param queue
 * @return
 */
int isEmpty(CircularQueue queue) {
    if (queue.rear == queue.front) {
        return 1;
    } else {
        return 0;
    }
}

/**
 *
 * @param queue
 * @return
 */
int isFull(CircularQueue queue) {
    if ((queue.rear + 1) % MAXSIZE == queue.front) {
        return 1;
    } else {
        return 0;
    }
}

/**
 *
 * @param queue
 * @param ele
 * @return
 */
int enQueue(CircularQueue *queue, int ele) {
    // 参数校验，如果队满则不能入队
    if ((queue->rear + 1) % MAXSIZE == queue->front) {
        return 0;
    }
    queue->data[queue->rear] = ele;
    queue->rear = (queue->rear + 1) % MAXSIZE;
    return 1;
}

/**
 *
 * @param queue
 * @param ele
 * @return
 */
int deQueue(CircularQueue *queue, int *ele) {
    // 参数校验，如果队空则不能出队
    if (queue->rear == queue->front) {
        return 0;
    }
    *ele = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAXSIZE;
    return 1;
}

/**
 *
 * @param queue
 * @return
 */
int size(CircularQueue queue) {
    return (queue.rear - queue.front + MAXSIZE) % MAXSIZE;
}

/**
 *
 * @param queue
 * @param ele
 * @return
 */
int getFront(CircularQueue queue, int *ele) {
    if (queue.rear == queue.front) {
        return 0;
    }
    *ele = queue.data[queue.front];
    return 1;
}

/**
 *
 * @param queue
 * @param ele
 * @return
 */
int getRear(CircularQueue queue, int *ele) {
    if (queue.rear == queue.front) {
        return 0;
    }
    *ele = queue.data[queue.rear - 1];
    return 1;
}

/**
 *
 * @param queue
 */
void clear(CircularQueue *queue) {
    queue->front = 0;
    queue->rear = 0;
}

/**
 *
 * @param queue
 */
void print(CircularQueue queue) {
    printf("[");
    int front = queue.front;
    while (front != queue.rear) {
        printf("%d", queue.data[front]);
        if (front != queue.rear - 1) {
            printf(", ");
        }
        front = (front + 1) % MAXSIZE;
    }
    printf("]\n");
}

int main() {
    // 声明循环队列
    CircularQueue queue;

    // 初始化队列
    printf("\n初始化队列：\n");
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

    // 队列是否满
    printf("\n队列是否满：\n");
    int full;
    full = isFull(queue);
    printf("%d\n", full);

    // 将元素出队
    int ele;
    printf("\n将元素出队：\n");
    deQueue(&queue, &ele);
    printf("出队元素：%d\n", ele);
    print(queue);
    deQueue(&queue, &ele);
    printf("出队元素：%d\n", ele);
    print(queue);
    deQueue(&queue, &ele);
    printf("出队元素：%d\n", ele);
    print(queue);

    // 队列是否空
    printf("\n队列是否空：\n");
    int empty;
    empty = isEmpty(queue);
    printf("%d\n", empty);

    // 队列中的元素个数
    printf("\n队列中的元素个数：\n");
    int len;
    len = size(queue);
    printf("%d\n", len);

    // 队头元素
    printf("\n队头元素：\n");
    int front;
    getFront(queue, &front);
    printf("%d\n", front);

    // 队尾元素
    printf("\n队尾元素：\n");
    int rear;
    getRear(queue, &rear);
    printf("%d\n", rear);

    // 清空队列
    printf("\n清空队列：\n");
    clear(&queue);
    print(queue);
}