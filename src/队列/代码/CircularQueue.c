#include<stdio.h>

/**
 * 循环队列中能存储的最大元素个数
 */
#define MAXSIZE 5

/**
 * 循环队列结构体定义
 */
typedef struct {
    /**
     * 数据域，存储循环队列中的数据
     */
    int data[MAXSIZE];
    /**
     * 指针域，存储循环队列中队头元素的位置
     */
    int front;
    /**
     * 指针域，存储循环队列中队尾元素的位置
     */
    int rear;
} CircularQueue;

/**
 * 初始化循环队列
 * @param queue 待初始化的循环队列
 */
void init(CircularQueue *queue) {
    // 循环队列初始时，队头指针和队尾指针仍然都指向 0，表示是空队列
    queue->front = 0;
    queue->rear = 0;
}

/**
 * 判断循环队列是否为空
 * @param queue 循环队列
 * @return 如果循环队列为空则返回 1，否则返回 0 表示非空
 */
int isEmpty(CircularQueue queue) {
    // 只要队头指针和队尾指针相等，那么表示循环队列为空，无论指针在哪个位置
    if (queue.rear == queue.front) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 判断循环队列是否已满
 * @param queue 循环队列
 * @return 如果循环队列已满则返回 1，否则返回 0 表示队列非满
 */
int isFull(CircularQueue queue) {
    // 队尾指针再加上一，然后对 MAXSIZE 取余，如果等于队头指针，那么表示队满
    if ((queue.rear + 1) % MAXSIZE == queue.front) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 将元素入队
 * @param queue 循环队列
 * @param ele 指定元素
 * @return 如果队列已满则不能入队返回 0 表示入队失败；否则返回 1 表示入队成功
 */
int enQueue(CircularQueue *queue, int ele) {
    // 0.参数校验，如果队满则不能入队
    if ((queue->rear + 1) % MAXSIZE == queue->front) {
        return 0;
    }
    // 1.将元素入队
    // 1.1 先进行赋值，即将新元素填充到队尾指针指向的位置。因为队尾指针指向队尾元素的下一个位置
    queue->data[queue->rear] = ele;
    // 1.2 然后将队尾指针加一。因为是循环队列，如果到了队尾，那么又要从 0 开始，所以加一后需要对 MAXSIZE 进行取余
    queue->rear = (queue->rear + 1) % MAXSIZE;
    return 1;
}

/**
 * 将元素出队
 * @param queue 循环队列
 * @param ele 用来保存出队的元素
 * @return 如果队空则不能出队则将返回 0 表示出队失败；否则返回 1 表示出队成功
 */
int deQueue(CircularQueue *queue, int *ele) {
    // 0.参数校验，如果队空则不能出队
    if (queue->rear == queue->front) {
        return 0;
    }
    // 1.将队头元素出队
    // 1.1 用 ele 保存队头指针所指向的元素
    *ele = queue->data[queue->front];
    // 1.2 将队头指针加一，表示删除队头元素。因为是循环队列，所以要对 MAXSIZE 取余
    queue->front = (queue->front + 1) % MAXSIZE;
    // 1.3 返回 1 表示出队成功
    return 1;
}

/**
 * 获取循环队列中的元素个数
 * @param queue 循环队列
 * @return 队列中的元素个数
 */
int size(CircularQueue queue) {
    // 如果是顺序队列，则元素个数是 rear-front
    // 如果是循环队列，则元素个数是 (rear-front+MAXSIZE)%MAXSIZE
    return (queue.rear - queue.front + MAXSIZE) % MAXSIZE;
}

/**
 * 获取循环队列的队头元素
 * @param queue 循环队列
 * @param ele 用来保存队头元素
 * @return 如果队列为空则返回 0 表示获取失败；否则返回 1 表示获取成功。
 */
int getFront(CircularQueue queue, int *ele) {
    // 0.参数校验，如果队列为空则没有队头元素，自然无法获取，所以返回 0 表示获取失败
    if (queue.rear == queue.front) {
        return 0;
    }
    // 1.用 ele 保存队头元素，即队头指针所指向的元素
    *ele = queue.data[queue.front];
    return 1;
}

/**
 * 获取循环队列中的队尾元素
 * @param queue 循环队列
 * @param ele 用来保存队尾元素
 * @return 如果队列为空则返回 0 表示获取失败；否则返回 1 表示获取成功。
 */
int getRear(CircularQueue queue, int *ele) {
    // 0.参数校验，如果队列为空则没有队尾元素，自然无法获取，所以返回 0 表示获取失败
    if (queue.rear == queue.front) {
        return 0;
    }
    // 1.用 ele 保存队尾元素，由于队尾指针指向队尾元素的下一个位置，所以要队尾指针减一
    *ele = queue.data[(queue.rear - 1 + MAXSIZE) % MAXSIZE];
    return 1;
}

/**
 * 清空循环队列
 * @param queue 循环队列
 */
void clear(CircularQueue *queue) {
    // 即将队头指针和队尾指针都指向 0，表示恢复循环队列的初始状态，即空表
    queue->front = 0;
    queue->rear = 0;
}

/**
 * 打印循环队列中从队头到队尾的所有元素
 * @param queue 循环队列
 */
void print(CircularQueue queue) {
    printf("[");
    int front = queue.front;
    while (front != queue.rear) {
        printf("%d", queue.data[front]);
        if (front != (queue.rear - 1 + MAXSIZE) % MAXSIZE) {
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

    // 再将元素入队
    printf("\n再将元素入队：\n");
    enQueue(&queue, 55);
    print(queue);

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