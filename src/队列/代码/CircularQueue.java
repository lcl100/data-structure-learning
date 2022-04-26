public class CircularQueue {
    /**
     * 循环队列中能存储的最大元素个数
     */
    private final int MAXSIZE = 5;

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
