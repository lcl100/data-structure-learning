public class DoubleEndedQueue {
    /**
     * 双端队列中能存储的最大元素个数
     */
    private final int MAXSIZE = 10;

    /**
     * 声明一个双端队列（顺序存储的双端队列）
     */
    private Queue deque;

    /**
     * 初始化双端队列
     */
    public void init() {
        // 实例化双端队列对象
        deque = new Queue();
        // 为数据域分配空间
        deque.data = new int[MAXSIZE];
        // 双端队列初始时，队头指针和队尾指针仍然都指向 0，表示是空队列
        deque.front = 0;
        deque.back = 0;
    }

    /**
     * 判断双端队列是否为空
     *
     * @return 如果双端队列为空则返回 true，否则返回 false 表示非空
     */
    public boolean isEmpty() {
        // 只要队头指针和队尾指针相等，那么表示双端队列为空，无论指针在哪个位置
        return deque.back == deque.front;
    }

    /**
     * 判断双端队列是否已满，因为是数组空间，所以可能会满队
     *
     * @return 如果双端队列已满则返回 true，否则返回 false 表示队列非满
     */
    public boolean isFull() {
        // 判断条件跟循环队列一样，因为底层就是循环队列
        return (deque.back + 1) % MAXSIZE == deque.front;
    }

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
     * 从队尾将元素入队
     *
     * @param ele 待入队的元素
     *
     * @throws Exception 如果队列已满则抛出此异常
     */
    public void pushBack(int ele) throws Exception {
        // 0.参数校验，如果队满则不能入队
        if (isFull()) {
            throw new Exception("队满则不能入队！");
        }

        // 1.将元素插入到队列的尾部
        // 1.1 由于队尾指针指向队尾元素的下一个位置，所以直接赋值即可
        deque.data[deque.back] = ele;
        // 1.2 插入元素后，需要移动队尾指针，将其加一，指向队尾元素的下一个位置，因为是循环队列，所以要对 MAXSIZE 取余
        deque.back = (deque.back + 1) % MAXSIZE;
    }

    /**
     * 从队头将元素出队
     *
     * @return 出队元素
     *
     * @throws Exception 如果队空则抛出此异常
     */
    public int popFront() throws Exception {
        // 0.参数校验，如果队空则不能出队
        if (isEmpty()) {
            throw new Exception("队空则不能出队！");
        }

        // 1.将队头元素出队
        // 1.1 用 ele 保存队头指针所指向的元素，即队头元素
        int front = deque.data[deque.front];
        // 1.2 修改队头指针，将其加一，表示删除队头元素。因为是循环队列，所以要对 MAXSIZE 取余
        deque.front = (deque.front + 1) % MAXSIZE;
        return front;
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

    /**
     * 获取双端队列中的元素个数
     *
     * @return 队列中的元素个数
     */
    public int size() {
        // 如果是顺序队列，则元素个数是 rear-front
        // 如果是循环队列，则元素个数是 (rear-front+MAXSIZE)%MAXSIZE
        return (deque.back - deque.front + MAXSIZE) % MAXSIZE;
    }

    /**
     * 获取双端队列的队头元素
     *
     * @return 队头元素
     *
     * @throws Exception 如果队空则抛出此异常
     */
    public int getFront() throws Exception {
        // 0.参数校验，如果队列为空则不能获取队头元素
        if (isEmpty()) {
            throw new Exception("队空则获取队头元素！");
        }
        // 1.返回队头指针所指向的元素
        return deque.data[deque.front];
    }

    /**
     * 获取双端队列的队尾元素
     *
     * @return 队尾元素
     *
     * @throws Exception 如果队空则抛出此异常
     */
    public int getBack() throws Exception {
        // 0.参数校验，如果队列为空则不能获取队尾元素
        if (isEmpty()) {
            throw new Exception("队空则获取队尾元素！");
        }
        // 1.返回队尾指针所指向的前一个元素。因为队尾指针指向队尾元素的下一个位置，所以要减一；因为是循环队列，所以要对 MAXSIZE 取余
        return deque.data[(deque.back - 1 + MAXSIZE) % MAXSIZE];
    }

    /**
     * 清空双端队列
     */
    public void clear() {
        // 即将队头指针和队尾指针指向 0，表示空队列
        deque.front = 0;
        deque.back = 0;
    }

    /**
     * 打印双端队列从队头到队尾的所有元素
     */
    public void print() {
        System.out.print("[");
        int front = deque.front;
        while (front != deque.back) {
            System.out.print(deque.data[front]);
            if (front != (deque.back - 1 + MAXSIZE) % MAXSIZE) {
                System.out.print(", ");
            }
            front = (front + 1) % MAXSIZE;
        }
        System.out.print("]\n");
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