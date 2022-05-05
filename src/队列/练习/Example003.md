# Example003

## 题目

如果允许在循环队列的两端都可以进行插入和删除操作，要求：
- 写出循环队列的类型定义。
- 分别写出从队尾删除和从队头插入的算法。





## 分析

本题实际考查的是双端队列的代码实现。具体可参考：[双端队列](https://github.com/lcl100/data-structure-learning/blob/main/src/%E9%98%9F%E5%88%97/%E6%96%87%E6%A1%A3/%E5%8F%8C%E7%AB%AF%E9%98%9F%E5%88%97.md)。

注意：

- 约定队头指针指向队头元素；队尾指针指向队尾元素的下一位置。
- 有些书中给出的代码实现，是约定的队头指针指向队头元素的前一位置，队尾指针指向队尾元素，具体根据实际情况来即可。



## 图解

略。



## C实现

核心代码：

```c
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
```

完整代码请参考：[DoubleEndedQueue.c](https://github.com/lcl100/data-structure-learning/blob/main/src/%E9%98%9F%E5%88%97/%E4%BB%A3%E7%A0%81/DoubleEndedQueue.c)。





## Java实现

核心代码：

```java
public class DoubleEndedQueue {

    /**
     * 声明一个双端队列（顺序存储的双端队列）
     */
    private Queue deque;

    /**
     * 从队头将元素入队
     *
     * @param ele 待入队的元素
     *
     * @throws Exception 如果队列已满则抛出此异常
     */
    public void pushFront(int ele) throws Exception {
        // 0.参数校验，如果队满则不能入队
        if (isFull()) {
            throw new Exception("队满则不能入队！");
        }
        // 1.将元素插入到队列的头部
        // 1.1 由于队头指针指向队列的队头元素，所以先修改队头指针。新元素应该插入到原队头元素的前面，所以要队头指针减一，因为是循环队列，所以要对 MAXSIZE 取余
        deque.front = (deque.front - 1 + MAXSIZE) % MAXSIZE;
        // 1.2 再对队头指针所指向的位置进行赋值
        deque.data[deque.front] = ele;
    }

    /**
     * 从队尾将元素出队
     *
     * @return 出队元素
     *
     * @throws Exception 如果队空则抛出此异常
     */
    public int popBack() throws Exception {
        // 0.参数校验，如果队空则不能出队
        if (isEmpty()) {
            throw new Exception("队空则不能出队！");
        }

        // 1.从队尾将元素出队
        // 1.1 由于队尾指针指向队尾元素的下一个位置，所以先修改队尾指针，将其减一，但由于是循环队列，所以要对 MAXSIZE 取余
        deque.back = (deque.back - 1 + MAXSIZE) % MAXSIZE;
        // 1.2 然后取出当前队尾指针所指向的元素，就是待出队的元素
        return deque.data[deque.back];
    }
}

/**
 * 双端队列定义，跟循环队列的一样，只是 rear 在双端队列中名为 back
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
    int back;
}
```

完整代码请参考：[DoubleEndedQueue.java](https://github.com/lcl100/data-structure-learning/blob/main/src/%E9%98%9F%E5%88%97/%E4%BB%A3%E7%A0%81/DoubleEndedQueue.java)。

测试代码请参考：[DoubleEndedQueueTest.java](https://github.com/lcl100/data-structure-learning/blob/main/src/%E9%98%9F%E5%88%97/%E4%BB%A3%E7%A0%81/DoubleEndedQueueTest.java)。
