# Example005 

## 题目

Q 是一个队列，S 是一个空栈，实现将队列中的元素逆置的算法。





## 分析

主要考查对队列和栈的特性与操作。由于对队列的一系列操作不可能将其中的元素全部逆置，而栈可以将入栈的元素逆序提取出来，因此我们可以让队列中的元素逐个出队列，一一入栈；全部入栈后再逐个入栈，一一入队列。



## 图解

![image-20220505213050580](image-Example005/image-20220505213050580.png)



## C实现

核心代码：

```c
/**
 * 逆置队列中的所有元素，假设栈的空间足够大
 * @param Q 装了元素的队列
 * @param S 空栈
 */
void inversionQueue(SeqQueue *Q, SeqStack *S) {
    // 1.先将队列 Q 中所有元素压入栈 S 中
    while (!isEmptyQueue(*Q)) {// 如果队列不为空，则一直将元素出队
        // 局部变量，记录出队元素
        int ele;
        // 将队头元素出队
        deQueue(Q, &ele);
        // 将队头元素压入栈中
        push(S, ele);
    }
    // 2.再将栈 S 中所有元素重新入队，即完成逆置
    while (!isEmptyStack(*S)) {// 如果栈不为空，则一直将元素出栈
        // 局部变量，记录栈顶元素
        int top;
        // 将栈顶元素出栈
        pop(S, &top);
        // 再将栈顶元素入队
        enQueue(Q, top);
    }
}
```

完整代码：

```c
/*
Q 是一个队列，S 是一个空栈，实现将队列中的元素逆置的算法。
*/

#include<stdio.h>

/**
 * 顺序队列中能存储的最大元素个数
 */
#define QUEUE_MAXSIZE 10

/**
 * 顺序队列结构体定义
 */
typedef struct {
    /**
     * 数据域，存储队列中的数据
     */
    int data[QUEUE_MAXSIZE];
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
void initQueue(SeqQueue *queue) {
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
int isEmptyQueue(SeqQueue queue) {
    // 如果队头指针和队尾指针都指向同一位置，则表示队列处于空
    // 因为队头指针和队尾指针在不断变化，只要它们相等就表示是空队列，其中 front 和 rear 可能是 0，有可能是 4，而非一直都初始化值
    if (queue.front == queue.rear) {
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
    if (queue->rear == QUEUE_MAXSIZE) {
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
 * 打印顺序队列中从队头到队尾的所有元素
 * @param queue 顺序队列
 */
void printQueue(SeqQueue queue) {
    printf("[");
    for (int i = queue.front; i < queue.rear; i++) {
        printf("%d", queue.data[i]);
        if (i != queue.rear - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

/**
 * 顺序栈最大存储的元素个数
 */
#define STACK_MAXSIZE 100

/**
 * 顺序栈结构体定义
 */
typedef struct {
    /**
     * 数据域，数组，用来存储栈中元素
     */
    int data[STACK_MAXSIZE];
    /**
     * 指针域，表示栈顶指针，实际上就是数组下标
     */
    int top;
} SeqStack;

/**
 * 初始化顺序栈，即将栈顶指针指向 -1 表示空栈
 * @param stack 顺序栈
 */
void initStack(SeqStack *stack) {
    // 设定让栈顶指针指向 -1 表示为栈空
    stack->top = -1;
}

/**
 * 判断顺序栈是否为空
 * @param stack 顺序栈
 * @return 如果顺序栈为空则返回 1，否则返回 0
 */
int isEmptyStack(SeqStack stack) {
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
    if (stack->top == STACK_MAXSIZE - 1) {
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
 * 逆置队列中的所有元素，假设栈的空间足够大
 * @param Q 装了元素的队列
 * @param S 空栈
 */
void inversionQueue(SeqQueue *Q, SeqStack *S) {
    // 1.先将队列 Q 中所有元素压入栈 S 中
    while (!isEmptyQueue(*Q)) {// 如果队列不为空，则一直将元素出队
        // 局部变量，记录出队元素
        int ele;
        // 将队头元素出队
        deQueue(Q, &ele);
        // 将队头元素压入栈中
        push(S, ele);
    }
    // 2.再将栈 S 中所有元素重新入队，即完成逆置
    while (!isEmptyStack(*S)) {// 如果栈不为空，则一直将元素出栈
        // 局部变量，记录栈顶元素
        int top;
        // 将栈顶元素出栈
        pop(S, &top);
        // 再将栈顶元素入队
        enQueue(Q, top);
    }
}

int main() {
    // 声明一个队列并初始化
    SeqQueue queue;
    initQueue(&queue);

    // 为队列添加一些测试数据
    enQueue(&queue, 11);
    enQueue(&queue, 22);
    enQueue(&queue, 33);
    enQueue(&queue, 44);
    enQueue(&queue, 55);

    // 声明一个栈并初始化为空栈
    SeqStack stack;
    initStack(&stack);

    // 打印逆置前的队列
    printQueue(queue);
    // 调用函数逆置队列元素
    inversionQueue(&queue, &stack);
    // 打印逆置后的队列
    printQueue(queue);
}
```

执行结果：

```text
[11, 22, 33, 44, 55]
[55, 44, 33, 22, 11]
```





## Java实现

核心代码：

```java
    /**
     * 逆置队列
     *
     * @param Q 队列
     * @param S 空栈
     * @throws Exception 如果顺序栈已满再入栈则会抛出异常
     */
    public static void inversionQueue(CircularQueue Q, SeqStack S) throws Exception {
        // 1.先将队列 Q 中所有元素压入栈 S 中
        while (!Q.isEmpty()) {// 如果队列不为空，则一直将元素出队
            // 局部变量，记录出队元素
            int ele;
            // 将队头元素出队
            ele = Q.deQueue();
            // 将队头元素压入栈中
            S.push(ele);
        }
        // 2.再将栈 S 中所有元素重新入队，即完成逆置
        while (!S.isEmpty()) {// 如果栈不为空，则一直将元素出栈
            // 局部变量，记录栈顶元素
            int top;
            // 将栈顶元素出栈
            top = S.pop();
            // 再将栈顶元素入队
            Q.enQueue(top);
        }
    }
```

完整代码：

```java
public class Test {
    public static void main(String[] args) throws Exception {
        // 声明一个队列并初始化
        CircularQueue queue = new CircularQueue();
        queue.init();

        // 为队列添加一些测试数据
        queue.enQueue(11);
        queue.enQueue(22);
        queue.enQueue(33);
        queue.enQueue(44);
        queue.enQueue(55);

        // 声明一个栈并初始化为空栈
        SeqStack stack = new SeqStack();
        stack.init();

        // 打印逆置前的队列
        queue.print();
        // 调用函数逆置队列元素
        inversionQueue(queue, stack);
        // 打印逆置后的队列
        queue.print();
    }

    /**
     * 逆置队列
     *
     * @param Q 队列
     * @param S 空栈
     * @throws Exception 如果顺序栈已满再入栈则会抛出异常
     */
    public static void inversionQueue(CircularQueue Q, SeqStack S) throws Exception {
        // 1.先将队列 Q 中所有元素压入栈 S 中
        while (!Q.isEmpty()) {// 如果队列不为空，则一直将元素出队
            // 局部变量，记录出队元素
            int ele;
            // 将队头元素出队
            ele = Q.deQueue();
            // 将队头元素压入栈中
            S.push(ele);
        }
        // 2.再将栈 S 中所有元素重新入队，即完成逆置
        while (!S.isEmpty()) {// 如果栈不为空，则一直将元素出栈
            // 局部变量，记录栈顶元素
            int top;
            // 将栈顶元素出栈
            top = S.pop();
            // 再将栈顶元素入队
            Q.enQueue(top);
        }
    }
}
```

`CircularQueue`：

```java
public class CircularQueue {
    /**
     * 循环队列中能存储的最大元素个数
     */
    private final int MAXSIZE = 7;

    /**
     * 声明循环队列
     */
    private Queue queue;

    /**
     * 初始化循环队列
     */
    public void init() {
        queue = new Queue();
        // 为数据域分配存储空间
        queue.data = new int[MAXSIZE];
        // 循环队列初始时，队头指针和队尾指针仍然都指向 0，表示是空队列
        queue.front = 0;
        queue.rear = 0;
    }

    /**
     * 判断循环队列是否为空
     *
     * @return 如果循环队列为空则返回 true，否则返回 false 表示非空
     */
    public boolean isEmpty() {
        // 只要队头指针和队尾指针相等，那么表示循环队列为空，无论指针在哪个位置
        return queue.rear == queue.front;
    }

    /**
     * 判断循环队列是否已满
     *
     * @return 如果循环队列已满则返回 true，否则返回 false 表示队列非满
     */
    public boolean isFull() {
        // 队尾指针再加上一，然后对 MAXSIZE 取余，如果等于队头指针，那么表示队满
        return (queue.rear + 1) % MAXSIZE == queue.front;
    }

    /**
     * 将元素入队
     *
     * @param ele 指定元素
     * @throws Exception 如果循环队列已满则不能入队，则抛出此异常
     */
    public void enQueue(int ele) throws Exception {
        // 0.参数校验，如果队满则不能入队
        if (isFull()) {
            throw new Exception("队列已满不能入队！");
        }
        // 1.将元素入队
        // 1.1 先进行赋值，即将新元素填充到队尾指针指向的位置。因为队尾指针指向队尾元素的下一个位置
        queue.data[queue.rear] = ele;
        // 1.2 然后将队尾指针加一。因为是循环队列，如果到了队尾，那么又要从 0 开始，所以加一后需要对 MAXSIZE 进行取余
        queue.rear = (queue.rear + 1) % MAXSIZE;
    }

    /**
     * 将元素出队
     *
     * @return 出队的元素
     * @throws Exception 如果队空则不能出队，则抛出此异常
     */
    public int deQueue() throws Exception {
        // 0.参数校验，如果队空则不能出队
        if (isEmpty()) {
            throw new Exception("队列为空不能出队！");
        }
        // 1.将队头元素出队
        // 1.1 用 ele 保存队头指针所指向的元素
        int front = queue.data[queue.front];
        // 1.2 将队头指针加一，表示删除队头元素。因为是循环队列，所以要对 MAXSIZE 取余
        queue.front = (queue.front + 1) % MAXSIZE;
        // 1.3 返回队头元素
        return front;
    }

    /**
     * 获取循环队列中的元素个数
     *
     * @return 队列中的元素个数
     */
    public int size() {
        // 如果是顺序队列，则元素个数是 rear-front
        // 如果是循环队列，则元素个数是 (rear-front+MAXSIZE)%MAXSIZE
        return (queue.rear - queue.front + MAXSIZE) % MAXSIZE;
    }

    /**
     * 获取循环队列的队头元素
     *
     * @return 循环队列的队头元素
     * @throws Exception 如果队列为空则抛出此异常
     */
    public int getFront() throws Exception {
        // 0.参数校验，如果队列为空则没有队头元素，自然无法获取，所以抛出异常表示获取失败
        if (isEmpty()) {
            throw new Exception("队空不能获取队头元素！");
        }
        // 1.返回队头元素，即队头指针所指向的元素
        return queue.data[queue.front];
    }

    /**
     * 获取循环队列中的队尾元素
     *
     * @return 循环队列的队尾元素
     * @throws Exception 如果队列为空则抛出此异常
     */
    public int getRear() throws Exception {
        // 0.参数校验，如果队列为空则没有队尾元素，自然无法获取，所以抛出此异常表示获取失败
        if (isEmpty()) {
            throw new Exception("队空不能获取队尾元素！");
        }
        // 1.返回队尾元素，由于队尾指针指向队尾元素的下一个位置，所以要队尾指针减一
        return queue.data[(queue.rear - 1 + MAXSIZE) % MAXSIZE];
    }

    /**
     * 清空循环队列
     */
    public void clear() {
        // 即将队头指针和队尾指针都指向 0，表示恢复循环队列的初始状态，即空表
        queue.front = 0;
        queue.rear = 0;
    }

    /**
     * 打印循环队列中从队头到队尾的所有元素
     */
    public void print() {
        System.out.print("[");
        int front = queue.front;
        while (front != queue.rear) {
            System.out.print(queue.data[front]);
            if (front != (queue.rear - 1 + MAXSIZE) % MAXSIZE) {
                System.out.print(", ");
            }
            front = (front + 1) % MAXSIZE;
        }
        System.out.print("]\n");
    }
}

/**
 * 循环队列定义
 */
class Queue {
    /**
     * 数据域，存储循环队列中的数据
     */
    int[] data;
    /**
     * 指针域，存储循环队列中队头元素的位置
     */
    int front;
    /**
     * 指针域，存储循环队列中队尾元素的位置
     */
    int rear;
}
```

`SeqStack`：

```java
public class SeqStack {
    /**
     * 常量，顺序栈所能容纳的最大元素个数
     */
    private final int MAXSIZE = 100;

    /**
     * 声明一个顺序栈
     */
    private Stack stack;

    /**
     * 初始化顺序栈
     */
    public void init() {
        // 实例化栈对象
        stack = new Stack();
        // 为数据域分配空间
        stack.data = new int[MAXSIZE];
        // 将顺序栈的栈顶指针指向 -1 表示空栈
        stack.top = -1;
    }

    /**
     * 判断顺序栈是否为空
     *
     * @return 如果顺序栈为空则返回 true，否则返回 false
     */
    public boolean isEmpty() {
        // 规定了 -1 表示空栈，所以只需要判断栈顶指针是否等于 -1 即可
        return stack.top == -1;
    }

    /**
     * 将指定元素入栈
     *
     * @param ele 指定元素
     * @throws Exception 如果栈满则不能入栈，抛出此异常
     */
    public void push(int ele) throws Exception {
        // 1.参数校验，如果栈满则不能入栈，抛出异常
        if (stack.top == MAXSIZE - 1) {// 因为栈顶指针 top 存储的是数组下标，所以判断是否等于 MAXSIZE-1
            throw new Exception("栈已满，不能再插入！");
        }
        // 2.先栈顶指针加 1，因为原栈顶指针处已经存储了元素，所以加一指向新的空位置
        stack.top++;
        // 3.在新的空位置处插入新元素，即为指定下标的数组元素赋值
        stack.data[stack.top] = ele;
    }

    /**
     * 将栈顶元素出栈
     *
     * @return 栈顶元素
     * @throws Exception 如果栈空则不能出栈，抛出此异常
     */
    public int pop() throws Exception {
        // 1.参数校验，如果栈空则不能出栈，抛出异常
        if (stack.top == -1) {// 因为栈空的定义是栈顶指针为 -1，所以如果栈顶指针为 -1 那么就是空栈，就不能出栈元素
            throw new Exception("栈为空，不能出栈元素！");
        }
        // 2.记录栈顶元素，因为要将该元素返回，即要出栈的元素
        int result = stack.data[stack.top];
        // 3.栈顶指针减一，因为原栈顶元素已经出栈了，栈中元素个数减一
        stack.top--;
        return result;
    }

    /**
     * 获取栈顶元素，但不出栈
     *
     * @return 栈顶元素
     * @throws Exception 如果栈空则不能出栈，抛出此异常
     */
    public int getTop() throws Exception {
        // 1.参数校验，如果栈空则不能出栈，抛出异常
        if (stack.top == -1) {
            throw new Exception("栈为空，不能获取栈顶元素！");
        }
        // 2.直接返回栈顶元素，但不出栈
        return stack.data[stack.top];
    }

    /**
     * 顺序栈中元素个数
     *
     * @return 栈中元素个数
     */
    public int size() {
        // top 表示栈顶指针，实际上就是数组 data 的下标，所以实际元素个数就是下标加一
        // 即使是空栈 top=-1，那么最后也会返回 0 表示元素个数为零个
        return stack.top + 1;
    }

    /**
     * 打印顺序栈中所有元素，从栈顶到栈底
     */
    public void print() {
        System.out.print("[");
        for (int i = stack.top; i >= 0; i--) {
            if (i != stack.top) {
                System.out.print(", ");
            }
            System.out.print(stack.data[i]);
        }
        System.out.print("]\n");
    }

    /**
     * 清空顺序栈
     */
    public void clear() {
        // 直接将栈顶指针指向 -1 即可表示空栈，不用重置栈中已有元素的值，因为顺序栈操作只跟栈顶指针有关
        stack.top = -1;
    }
}

/**
 * 栈定义
 */
class Stack {
    /**
     * 顺序栈用来存储元素的数组
     */
    int[] data;
    /**
     * 记录顺序栈的栈顶指针，即数组下标
     */
    int top;
}
```

执行结果：

```text
[11, 22, 33, 44, 55]
[55, 44, 33, 22, 11]
```