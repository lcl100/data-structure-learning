public class LinkedQueue {
    /**
     * 声明一个链队列，即链队列的头结点
     */
    private Queue queue;

    /**
     * 初始化链队列
     */
    public void init() {
        // 其实 queue 就相当于链队列的头结点，不过它有两个指针，分别存储队头结点和队尾结点的地址
        // 为链队列头结点分配存储空间
        queue = new Queue();
        // 将队头指针和队尾指针都指向 NULL，表示空队列
        queue.front = null;
        queue.rear = null;
    }

    /**
     * 判断链队列是否为空
     *
     * @return 如果链队列为空则返回 true，否则返回 false 表示非空
     */
    public boolean isEmpty() {
        // 只要链队列的队头指针或者队尾指针指向 NULL 则表示是空队
        return queue.front == null || queue.rear == null;
    }

    /**
     * 将元素入队
     *
     * @param ele 待入队的元素
     */
    public void enQueue(int ele) {
        /// 0.因为是链表来表示队列，理论上不存在队满的情况，所以不需要校验队满

        // 1.创建新结点
        // 1.1 为新结点分配空间
        QNode newNode = new QNode();
        // 1.2 为新结点指定数据域
        newNode.data = ele;
        // 1.3 为新结点指定数据域，初始指向 NULL
        newNode.next = null;

        // 2.将新结点入队
        // 2.1 若队列为空，则新结点是队头结点，也是队尾结点
        if (isEmpty()) {
            // 因为链队列只有一个结点，所以将队头指针和队尾指针都指向新结点
            queue.front = newNode;
            queue.rear = newNode;
        }
        // 2.2 如果队列非空，则将新结点插入到队尾结点的后面，并将队尾指针指向新结点
        else {
            // 局部变量，记录队尾结点
            QNode tailNode = queue.rear;
            // 2.2.1 将新结点插入到队尾结点的后面
            tailNode.next = newNode;
            // 2.2.2 将队尾指针指向新结点
            queue.rear = newNode;
        }
    }

    /**
     * 将元素出队
     *
     * @return 出队元素
     * @throws Exception 如果链队列为空则抛出此异常
     */
    public int deQueue() throws Exception {
        // 0.参数校验，如果队空则不能入队
        if (isEmpty()) {
            throw new Exception("队列为空不能出队！");
        }

        // 1.将队头结点出队
        // 1.1 变量，记录链队列的队头结点
        QNode frontNode = queue.front;
        // 1.2 删除队头结点并修改队头指针
        // 1.2.1 如果队列中只有一个结点时的出队操作需要特殊处理，因为需要将队头指针和队尾指针都指向 NULL
        if (queue.front == queue.rear) {
            queue.front = null;
            queue.rear = null;
        }
        // 1.2.2 当队列不止一个结点时，将队头指针指向原队头结点的后继结点
        else {
            queue.front = frontNode.next;
        }
        // 1.3 返回原队头结点的数据值
        return frontNode.data;
    }

    /**
     * 获取链队列中的结点个数
     *
     * @return 结点个数
     */
    public int size() {
        // 变量，记录链队列结点个数
        int len = 0;
        // 变量，结点链队列的队头结点，相当于单链表的开始结点
        QNode frontNode = queue.front;
        // 扫描链队列，即遍历单链表，统计结点个数
        while (frontNode != null) {
            len++;
            frontNode = frontNode.next;
        }
        return len;
    }

    /**
     * 获取链队列的队头结点数据值
     *
     * @return 队头结点数据值
     * @throws Exception 如果队列为空则抛出此异常
     */
    public int getFront() throws Exception {
        // 0.参数校验，如果链队列为空，则表示不能获取队头元素
        if (isEmpty()) {
            throw new Exception("队空不能获取队头元素！");
        }
        // 1.返回队头结点的数据值，即队头指针所指向的结点
        return queue.front.data;
    }

    /**
     * 获取链队列的队尾结点数据值
     *
     * @return 队尾结点数据值
     * @throws Exception 如果队列为空则抛出此异常
     */
    public int getRear() throws Exception {
        // 0.参数校验，如果链队列为空，则表示不能获取队尾元素
        if (isEmpty()) {
            throw new Exception("队空不能获取队尾元素！");
        }
        // 1.返回队尾结点的数据值，即队尾指针所指向的结点
        return queue.rear.data;
    }

    /**
     * 清空链队列
     */
    public void clear() {
        // 变量，记录链队列中的节点，初始为链队列的队头结点
        QNode frontNode = queue.front;
        // 扫描链队列所有结点，释放每个结点的空间
        while (frontNode != null) {
            // 保存当前节点的后继结点，因为要释放结点，所以需要提前保存
            QNode temp = frontNode.next;
            // 释放当前节点
            frontNode.next = null;
            frontNode = null;
            // 继续链队列的下一个结点
            frontNode = temp;
        }
        // 最后链队列头结点的队头指针和队尾指针都指向 NULL 表示空队列
        queue.front = null;
        queue.rear = null;
    }

    /**
     * 销毁链队列
     */
    public void destroy() {
        // 即释放链队列头结点的空间，在Java中将其置为 null 即可
        queue = null;
    }

    /**
     * 打印链队列的所有结点值
     */
    public void print() {
        System.out.print("[");
        QNode frontNode = queue.front;
        while (frontNode != null) {
            System.out.print(frontNode.data);
            if (frontNode.next != null) {
                System.out.print(", ");
            }
            frontNode = frontNode.next;
        }
        System.out.print("]\n");
    }
}

/**
 * 链队列中的结点定义
 */
class QNode {
    /**
     * 结点数据域，存储链队列中结点的数据
     */
    int data;
    /**
     * 结点指针域，存储当前结点的后继结点的地址
     */
    QNode next;
}

/**
 * 链队列定义
 */
class Queue {
    /**
     * 存储链队列的队头结点的地址，即指向队头结点
     */
    QNode front;
    /**
     * 存储链队列的队尾结点的地址，即指向队尾结点
     */
    QNode rear;
}