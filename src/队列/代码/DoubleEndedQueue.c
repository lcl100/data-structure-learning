#include<stdio.h>

/**
 * 双端队列中能存储的最大元素个数
 */
#define MAXSIZE 10

/**
 * 双端队列结构体定义，跟循环队列的一样，只是 rear 在双端队列中名为 back
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
    int back;
} DoubleEndedQueue;

/**
 * 初始化双端队列
 * @param deque 待初始化的双端队列
 */
void init(DoubleEndedQueue *deque) {
    // 双端队列初始时，队头指针和队尾指针仍然都指向 0，表示是空队列
    deque->front = 0;
    deque->back = 0;
}

/**
 * 判断双端队列释放为空
 * @param deque 双端队列
 * @return 如果双端队列为空则返回 1，否则返回 0 表示非空
 */
int isEmpty(DoubleEndedQueue deque) {
    // 只要队头指针和队尾指针相等，那么表示双端队列为空，无论指针在哪个位置
    if (deque.front == deque.back) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 判断双端队列是否已满
 * @param queue 双端队列
 * @return 如果双端队列已满则返回 1，否则返回 0 表示队列非满
 */
int isFull(DoubleEndedQueue deque) {
    if ((deque.back + 1) % MAXSIZE == deque.front) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * 从队头将元素入队
 * @param queue 双端队列
 * @param ele 待入队的元素
 * @return 如果队列已满则不能入队返回 0 表示入队失败；否则返回 1 表示入队成功
 */
int pushFront(DoubleEndedQueue *deque, int ele) {
    // 0.参数校验，如果队满则不能入队
    if (isFull(*deque)) {
        return 0;
    }

    // 1.将元素插入到队列的头部
    // 1.1 由于队头指针指向队列的队头元素，所以先修改队头指针。新元素应该插入到原队头元素的前面，所以要队头指针减一，因为是循环队列，所以要对 MAXSIZE 取余
    deque->front = (deque->front - 1 + MAXSIZE) % MAXSIZE;
    // 1.2 再对队头指针所指向的位置进行赋值
    deque->data[deque->front] = ele;
    // 1.3 返回 1 表示入队成功
    return 1;
}

/**
 * 从队尾将元素入队
 * @param queue 双端队列
 * @param ele 待入队的元素
 * @return 如果队列已满则不能入队返回 0 表示入队失败；否则返回 1 表示入队成功
 */
int pushBack(DoubleEndedQueue *deque, int ele) {
    // 0.参数校验，如果队满则不能入队
    if (isFull(*deque)) {
        return 0;
    }

    // 1.将元素插入到队列的尾部
    // 1.1 由于队尾指针指向队尾元素的下一个位置，所以直接赋值即可
    deque->data[deque->back] = ele;
    // 1.2 插入元素后，需要移动队尾指针，将其加一，指向队尾元素的下一个位置，因为是循环队列，所以要对 MAXSIZE 取余
    deque->back = (deque->back + 1) % MAXSIZE;
    // 1.3 返回 1 表示入队成功
    return 1;
}

/**
 * 从队头将元素出队
 * @param deque 双端队列
 * @param ele 用来保存出队元素
 * @return 如果队空则返回 0 表示出队失败，否则返回 1 表示出队成功
 */
int popFront(DoubleEndedQueue *deque, int *ele) {
    // 0.参数校验，如果队空则不能出队
    if (isEmpty(*deque)) {
        return 0;
    }

    // 1.将队头元素出队
    // 1.1 用 ele 保存队头指针所指向的元素，即队头元素
    *ele = deque->data[deque->front];
    // 1.2 修改队头指针，将其加一，表示删除队头元素。因为是循环队列，所以要对 MAXSIZE 取余
    deque->front = (deque->front + 1) % MAXSIZE;
    // 1.3 返回 1 表示出队成功
    return 1;
}

/**
 * 从队尾将元素出队
 * @param deque 双端队列
 * @param ele 用来保存出队元素
 * @return 如果队空则返回 0 表示出队失败，否则返回 1 表示出队成功
 */
int popBack(DoubleEndedQueue *deque, int *ele) {
    // 0.参数校验，如果队空则不能出队
    if (isEmpty(*deque)) {
        return 0;
    }
    // 1.从队尾将元素出队
    // 1.1 由于队尾指针指向队尾元素的下一个位置，所以先修改队尾指针，将其减一，但由于是循环队列，所以要对 MAXSIZE 取余
    deque->back = (deque->back - 1 + MAXSIZE) % MAXSIZE;
    // 1.2 然后取出当前队尾指针所指向的元素，就是待出队的元素
    *ele = deque->data[deque->back];
    // 1.3 返回 1 表示出队成功
    return 1;
}

/**
 * 获取双端队列中的元素个数
 * @param deque 双端队列
 * @return 队列中的元素个数
 */
int size(DoubleEndedQueue deque) {
    // 如果是顺序队列，则元素个数是 rear-front
    // 如果是循环队列，则元素个数是 (rear-front+MAXSIZE)%MAXSIZE
    return (deque.back - deque.front + MAXSIZE) % MAXSIZE;
}

/**
 * 获取双端队列的队头元素
 * @param deque 双端队列
 * @param ele 用来保存队头元素
 * @return 如果出队成功则返回 1，否则返回 0 表示出队失败
 */
int getFront(DoubleEndedQueue deque, int *ele) {
    // 0.参数校验，如果队列为空则不能获取队头元素
    if (isEmpty(deque)) {
        return 0;
    }
    // 1.用 ele 保存队头指针所指向的元素
    *ele = deque.data[deque.front];
    return 1;
}

/**
 * 获取双端队列的队尾元素
 * @param deque 双端队列
 * @param ele 用来保存队尾元素
 * @return 如果出队成功则返回 1，否则返回 0 表示出队失败
 */
int getBack(DoubleEndedQueue deque, int *ele) {
    // 0.参数校验，如果队列为空则不能获取队尾元素
    if (isEmpty(deque)) {
        return 0;
    }
    // 1.用 ele 保存队尾指针所指向的前一个元素，因为队尾指针指向队尾元素的下一个位置，所以要减一，因为是循环队列，所以要对 MAXSIZE 取余
    *ele = deque.data[(deque.back - 1 + MAXSIZE) % MAXSIZE];
    return 1;
}

/**
 * 清空双端队列
 * @param deque 双端队列
 */
void clear(DoubleEndedQueue *deque) {
    // 即将队头指针和队尾指针指向 0，表示空队列
    deque->front = 0;
    deque->back = 0;
}

/**
 * 打印双端队列从队头到队尾的所有元素
 * @param deque 双端队列
 */
void print(DoubleEndedQueue deque) {
    printf("[");
    int front = deque.front;
    while (front != deque.back) {
        printf("%d", deque.data[front]);
        if (front != (deque.back - 1 + MAXSIZE) % MAXSIZE) {
            printf(", ");
        }
        front = (front + 1) % MAXSIZE;
    }
    printf("]\n");
}

int main() {
    // 声明双端队列
    DoubleEndedQueue deque;

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

    // 队列是否满
    printf("\n队列是否满：\n");
    int full;
    full = isFull(deque);
    printf("%d\n", full);

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
}