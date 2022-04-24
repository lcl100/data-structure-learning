public class SeqQueue {
    /**
     * 顺序队列中能存储的最大元素个数
     */
    private final int MAXSIZE = 10;

    /**
     * 声明的顺序队列，待初始化
     */
    private Queue queue;

    /**
     * 当头尾指针相等时，队列为空。
     * 在非空队列里，队头指针始终指向队头元素，队尾指针始终指向队尾元素的下一位置。
     */
    public void init() {
        // 实例化顺序队列
        queue = new Queue();
        // 为数据域分配数组空间
        queue.data = new int[MAXSIZE];
        // 初始化顺序队列，将队头指针和队尾指针都指向 0
        // 有些实现中将队头指针和队尾指针指向 -1，这无所谓，只要能够实现队列功能即可
        queue.front = 0;
        queue.rear = 0;
    }

    /**
     * 判断顺序队列是否为空
     *
     * @return 如果顺序队列为空则返回 true，否则返回 false 表示非空队列
     */
    public boolean isEmpty() {
        // 如果队头指针和队尾指针都指向同一位置，则表示队列处于空
        // 因为队头指针和队尾指针在不断变化，只要它们相等就表示是空队列，其中 front 和 rear 可能是 0，有可能是 4，而非一直都初始化值
        return queue.front == queue.rear;
    }

    /**
     * 判断顺序队列是否为满
     *
     * @return 如果顺序队列为满则返回 true，否则返回 false 表示非满队列
     */
    public boolean isFull() {
        // 如果队尾指针指向了 MAXSIZE，即数组的最后一个位置，则表示队满
        // 因为规定在非空队列中，队尾指针始终指向队尾元素的下一位置，所以当元素是队列数组最后一个元素（MAXSIZE-1）时，那么队尾指针一定指向 MAXSIZE
        return queue.rear == MAXSIZE;
    }

    /**
     * 将元素入队，即插入到队尾
     *
     * @param ele 待入队的元素
     * @throws Exception 如果队满则不能入队抛出此异常
     */
    public void enQueue(int ele) throws Exception {
        // 0.参数校验，如果队满，则不能入队
        if (isFull()) {
            throw new Exception("队满不能入队！");
        }
        // 1.将元素入队
        // 1.1 先进行赋值，初始时队头指针指向 0
        queue.data[queue.rear] = ele;
        // 1.2 然后将队尾指针加一，将队尾指针指向队尾元素的下一个位置
        queue.rear++;
    }

    /**
     * 将元素出队，即出队队头元素
     *
     * @return 用来保存出队元素
     * @throws Exception 如果队空则不能出队则抛出此异常
     */
    public int deQueue() throws Exception {
        // 0.参数校验，如果队空则不能出队
        if (isEmpty()) {
            throw new Exception("队空不能出队！");
        }
        // 1.将元素出队
        // 1.1 用 front 保存队头元素
        int front = queue.data[queue.front];
        // 1.2 将队头指针加一，表示删除队头元素，使得队头指针始终指向队头元素
        queue.front++;
        // 1.3 返回队头元素
        return front;
    }

    /**
     * 顺序队列中的有效元素个数
     *
     * @return 顺序队列元素个数
     */
    public int size() {
        // 由于队头指针始终指向队头元素，队尾指针指向队尾元素的下一个位置，所以元素个数是之差
        return queue.rear - queue.front;
    }

    /**
     * 获取顺序队列的队头元素
     *
     * @return 顺序队列的队头元素
     * @throws Exception 如果顺序队列为空则抛出此异常
     */
    public int getFront() throws Exception {
        // 0.参数校验，如果队空则不存在队头元素
        if (isEmpty()) {
            throw new Exception("队空不存在队头元素！");
        }
        // 1.用 ele 保存队头元素，即队头指针所指向的元素
        return queue.data[queue.front];
    }

    /**
     * 获取顺序队列的队尾元素
     *
     * @return 顺序队列的队尾元素
     * @throws Exception 如果顺序队列为空则抛出此异常
     */
    public int getRear() throws Exception {
        // 0.参数校验，如果队空则不存在队尾元素
        if (isEmpty()) {
            throw new Exception("队空不存在队尾元素！");
        }
        // 1.获取队尾元素，由于队尾指针指向队尾元素的下一个位置，所以需要将队尾指针减一来获取队尾元素
        return queue.data[queue.rear - 1];
    }

    /**
     * 清空顺序队列
     */
    public void clear() {
        // 清空顺序队列，将队头指针和队尾指针都置为 0
        queue.front = 0;
        queue.rear = 0;
    }

    /**
     * 打印顺序队列中从队头到队尾的所有元素
     */
    public void print() {
        System.out.print("[");
        for (int i = queue.front; i < queue.rear; i++) {
            System.out.print(queue.data[i]);
            if (i != queue.rear - 1) {
                System.out.print(", ");
            }
        }
        System.out.print("]\n");
    }
}

/**
 * 顺序队列定义
 */
class Queue {
    /**
     * 顺序队列数据域，保存队列中的元素
     */
    int[] data;
    /**
     * 指针域，队头指针。在空队列中，队头指针指向 0；在非空队列中，队头指针始终指向队头元素
     */
    int front;
    /**
     * 指针域，队尾指针。在空队列中，队尾指针指向 0；在非空队列中，队尾指针始终指向队尾元素的下一位置
     */
    int rear;
}
