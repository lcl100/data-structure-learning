#include<stdio.h>

/**
 * 顺序队列中能存储的最大元素个数
 */
#define MAXSIZE 5

/**
 * 顺序队列结构体定义
 */
typedef struct {
    /**
     * 数据域，存储队列中的数据
     */
    int data[MAXSIZE];
    /**
     * 指针域，队头指针。在空队列中，队头指针指向 0；在非空队列中，队头指针始终指向队头元素
     */
    int front;
    /**
     * 指针域，队尾指针。在空队列中，队尾指针指向 0；在非空队列中，队尾指针始终指向队尾元素的下一位置
     */
    int rear;
} SeqQueue;

/**
 * 初始化顺序队列
 * @param queue 未初始化的顺序队列
 */
void init(SeqQueue *queue) {
    // 初始化顺序队列，将队头指针和队尾指针都指向 0
    // 有些实现中将队头指针和队尾指针指向 -1，这无所谓，只要能够实现队列功能即可
    queue->front = 0;
    queue->rear = 0;
}

/**
 * 判断顺序队列是否为空
 * @param queue 顺序队列
 * @return 如果顺序队列为空则返回 1，否则返回 0 表示非空队列
 */
int isEmpty(SeqQueue queue) {
    // 如果队头指针和队尾指针都指向同一位置，则表示队列处于空
    // 因为队头指针和队尾指针在不断变化，只要它们相等就表示是空队列，其中 front 和 rear 可能是 0，有可能是 4，而非一直都初始化值
    if (queue.front == queue.rear) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 判断顺序队列是否满
 * @param queue 顺序队列
 * @return 如果队列满则
 */
int isFull(SeqQueue queue) {
    // 如果队尾指针指向了 MAXSIZE，即数组的最后一个位置，则表示队满
    // 因为规定在非空队列中，队尾指针始终指向队尾元素的下一位置，所以当元素是队列数组最后一个元素（MAXSIZE-1）时，那么队尾指针一定指向 MAXSIZE
    if (queue.rear == MAXSIZE) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 将元素入队，即插入到队尾
 * @param queue 顺序队列
 * @param ele 待入队的元素
 * @return 如果入队成功则返回 1，否则返回 0 表示入队失败
 */
int enQueue(SeqQueue *queue, int ele) {
    // 0.参数校验，如果队满，则不能入队
    if (queue->rear == MAXSIZE) {
        return 0;
    }
    // 1.将元素入队
    // 1.1 先进行赋值，初始时队头指针指向 0
    queue->data[queue->rear] = ele;
    // 1.2 然后将队尾指针加一
    queue->rear++;
    // 1.3 返回 1 表示入队成功
    return 1;
}

/**
 * 将元素出队，即出队队头元素
 * @param queue 顺序队列
 * @param ele 用来保存出队元素
 * @return 如果出队成功则返回 1，否则返回 0 表示出队失败
 */
int deQueue(SeqQueue *queue, int *ele) {
    // 0.参数校验，如果队空则不能出队
    if (queue->front == queue->rear) {
        return 0;
    }
    // 1.将元素出队
    // 1.1 用 ele 保存队头元素
    *ele = queue->data[queue->front];
    // 1.2 将队头指针加一，表示删除队头元素，使得队头指针始终指向队头元素
    queue->front++;
    // 1.3 返回 1 表示出队成功
    return 1;
}

/**
 * 顺序队列中的有效元素个数
 * @param queue 顺序队列
 * @return 顺序队列元素个数
 */
int size(SeqQueue queue) {
    // 由于队头指针始终指向队头元素，队尾指针指向队尾元素的下一个位置，所以元素个数是之差
    return queue.rear - queue.front;
}

/**
 * 获取顺序队列的队头元素
 * @param queue 顺序队列
 * @param ele 用来保存队头元素
 * @return 如果获取队头元素成功则返回 1，否则返回 0 表示获取失败
 */
int getFront(SeqQueue queue, int *ele) {
    // 0.参数校验，如果是空队列，则不能获取到队头元素
    if (queue.front == queue.rear) {
        return 0;
    }
    // 1.用 ele 保存队头元素，即队头指针所指向的元素
    *ele = queue.data[queue.front];
    return 1;
}

/**
 * 获取顺序队列的队尾元素
 * @param queue 顺序队列
 * @param ele 用来保存队尾元素
 * @return 如果获取队尾元素成功则返回 1，否则返回 0 表示获取失败
 */
int getRear(SeqQueue queue, int *ele) {
    // 0.参数校验，如果是空队列，则不能获取到队尾元素
    if (queue.front == queue.rear) {
        return 0;
    }
    // 1.获取队尾元素，由于队尾指针指向队尾元素的下一个位置，所以需要将队尾指针减一来获取队尾元素
    *ele = queue.data[queue.rear - 1];
    return 1;
}

/**
 * 清空顺序队列
 * @param queue 顺序队列
 */
void clear(SeqQueue *queue) {
    // 清空顺序队列，将队头指针和队尾指针都置为 0
    queue->front = 0;
    queue->rear = 0;
}

/**
 * 打印顺序队列中从队头到队尾的所有元素
 * @param queue 顺序队列
 */
void print(SeqQueue queue) {
    printf("[");
    for (int i = queue.front; i < queue.rear; i++) {
        printf("%d", queue.data[i]);
        if (i != queue.rear - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}


int main() {
    // 声明顺序队列
    SeqQueue queue;

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