/**
 * @author lcl100
 * @desc 链式双端队列实现类
 * @create 2022-04-29 21:15
 */
public class LinkedDoubleEndedQueue {
    /**
     * 声明链式双端队列
     */
    private LinkedQueue deque;

    /**
     * 初始化链式双端队列
     */
    public void init() {
        // deque 就是链式双端队列的头结点
        // 为头结点分配存储空间
        deque = new LinkedQueue();
        // 将队头指针和队尾指针指向 null 表示空队列
        deque.front = null;
        deque.back = null;
    }

    /**
     * 判断链式双端队列是否为空
     *
     * @return 如果为空则返回 true，否则返回 false 表示非空
     */
    public boolean isEmpty() {
        // 跟链式队列的判空条件一样，只要队头指针或队尾指针指向 null 则表示空
        return deque.front == null || deque.back == null;
    }

    /**
     * 将元素从队头入队
     *
     * @param ele 待入队的元素
     */
    public void pushFront(int ele) {
        // 1.创建新结点
        // 1.1 为新结点分配存储空间
        QNode newNode = new QNode();
        // 1.2 为新结点指定数据域
        newNode.data = ele;
        // 1.3 将新结点的数据域指向 null，表示没有跟任何结点有关联
        newNode.next = null;

        // 2.将新结点插入到队列的头部
        // 2.1 如果是空队列则新结点既是队头结点也是队尾结点
        if (isEmpty()) {
            // 2.1.1 将队头指针指向新结点
            deque.front = newNode;
            // 2.1.2 将队尾指针指向新结点
            deque.back = newNode;
        }
        // 2.2 如果不是空队列，则将新结点插入到原队头结点的前面，然后新结点成为新的队头结点
        else {
            // 2.2.1 局部变量，记录队列的原队头结点
            QNode frontNode = deque.front;
            // 2.2.2 将新结点的 next 指针指向原队头结点，即将新结点与队列链接起来
            newNode.next = frontNode;
            // 2.2.3 将队头指针指向新结点，表示新结点成为了队列新的队头结点
            deque.front = newNode;
        }
    }

    /**
     * 将元素从队尾入队
     *
     * @param ele 待入队的元素
     */
    public void pushBack(int ele) {
        // 1.创建新结点
        // 1.1 为新结点分配存储空间
        QNode newNode = new QNode();
        // 1.2 为新结点指定数据域
        newNode.data = ele;
        // 1.3 将新结点的数据域指向 null，表示没有跟任何结点有关联
        newNode.next = null;

        // 2.将新结点插入到队列的尾部
        // 2.1 如果是空表则新结点既是队头结点也是队尾结点
        if (isEmpty()) {
            // 2.1.1 将队头指针指向新结点
            deque.front = newNode;
            // 2.1.2 将队尾指针指向新结点
            deque.back = newNode;
        }
        // 2.2 如果不是空队列，则将新结点插入到原队尾结点的后面，然后新结点成为新的队尾结点
        else {
            // 2.2.1 局部变量，记录队列的原队尾结点
            QNode backNode = deque.back;
            // 2.2.2 将原队尾结点的 next 指针指向新结点，即将队列与新结点链接起来了
            backNode.next = newNode;
            // 2.2.3 将队尾指针指向新结点，表示新结点成为了队列的新的尾结点
            deque.back = newNode;
        }
    }

    /**
     * 将元素从队头出队
     *
     * @return 出队元素
     * @throws Exception 如果队空则抛出此异常
     */
    public int popFront() throws Exception {
        // 0.参数校验，如果队空则不能出队
        if (isEmpty()) {
            throw new Exception("队列为空不能出队！");
        }

        // 1.将队头结点出队
        // 1.1 局部变量，记录队列的队头结点
        QNode frontNode = deque.front;
        // 1.2 删除队列中的队头结点
        // 1.2.1 如果队列中只有一个结点，那么这个结点既是队头结点也是队尾结点，那么删除后队头指针和队尾指针都应该指向 null 表示空队列
        if (deque.front == deque.back) {
            // 1.2.1.1 将队头指针指向 null
            deque.front = null;
            // 1.2.1.2 将队尾指针指向 null
            deque.back = null;
        }
        // 1.2.2 如果队列中不止一个结点，那么删除队头结点即可
        else {
            // 1.2.2.1 即将队头指针指向原队头结点的后继结点
            deque.front = frontNode.next;
        }
        // 1.3 返回队头结点的数据值
        return frontNode.data;
    }

    /**
     * 将元素从队尾出队
     *
     * @return 出队元素
     * @throws Exception 如果队空则抛出此异常
     */
    public int popBack() throws Exception {
        // 0.参数校验，如果队空则不能出队
        if (isEmpty()) {
            throw new Exception("队列为空不能出队！");
        }

        // 1.将队尾结点出队
        // 1.1 局部变量，记录队列的队尾结点
        QNode backNode = deque.back;
        // 1.2 用 data 保存队尾结点的数据值，即出队元素
        int data = backNode.data;
        // 1.3 删除队列中的队尾结点
        // 1.3.1 如果队列中只有一个结点，那么这个结点既是队头结点也是队尾结点，那么删除后队头指针和队尾指针都应该指向 null 表示空队列
        if (deque.front == deque.back) {
            // 1.3.1.1 将队头指针指向 null
            deque.front = null;
            // 1.3.1.2 将队尾指针指向 null
            deque.back = null;
        }
        // 1.3.2 如果队列中不止一个结点，那么删除队尾结点
        else {
            // 1.3.2.1 首先，由于是单链表构成的链式双端队列，所以要先找到队列队尾节点的前驱节点
            // 单链表不太好找尾节点的前驱节点，可以考虑用双链表来实现链式双端队列
            // 循环结束后，node 结点就是单链表尾结点的前驱结点
            QNode node = deque.front;
            while (node.next.next != null) {
                node = node.next;
            }
            // 1.3.2.2 斩断队尾结点的前驱结点与尾结点的联系，因为该结点会成为新的队尾结点
            node.next = null;
            // 1.3.2.3 将队尾指针指向该结点，表示该结点成为了队列的新队尾结点
            deque.back = node;
        }
        // 1.4 释放原队尾结点的存储空间
        backNode.next = null;
        backNode = null;
        // 1.5 返回数据
        return data;
    }

    /**
     * 获取链式双端队列的结点个数
     *
     * @return 结点个数
     */
    public int size() {
        // 链式双端队列本质上还是一个单链表，所以遍历单链表计算结点个数
        // 变量，记录队列中的结点，初始为队头结点，即单链表的开始结点
        QNode node = deque.front;
        // 变量，记录结点个数
        int len = 0;
        // 从队头结点开始扫描整个队列
        while (node != null) {
            // 每迭代一次结点个数加一
            len++;
            // 继续下一个结点
            node = node.next;
        }
        // 返回统计出来的点个数
        return len;
    }

    /**
     * 获取双端队列的队头元素
     *
     * @return 队头元素
     * @throws Exception 如果队空则抛出此异常
     */
    public int getFront() throws Exception {
        // 0.参数校验，如果是空队列，则不能获取队头元素
        if (isEmpty()) {
            throw new Exception("队空不能获取队头元素！");
        }
        // 1.返回队头指针指向的队头结点的元素值
        return deque.front.data;
    }

    /**
     * 获取双端队列的队尾元素
     *
     * @return 队尾元素
     * @throws Exception 如果队空则抛出此异常
     */
    public int getBack() throws Exception {
        // 0.参数校验，如果是空队列，则不能获取队尾元素
        if (isEmpty()) {
            throw new Exception("队空不能获取队尾元素！");
        }
        // 1.返回队尾指针指向的队尾结点的元素值
        return deque.back.data;
    }

    /**
     * 清空链式双端队列
     */
    public void clear() {
        // 变量，记录队列中的结点，初始为队头结点，即单链表的开始结点
        QNode node = deque.front;
        // 从队头结点开始扫描整个队列
        while (node != null) {
            // 变量，记录当前节点的后继节点，因为要释放当前节点的空间，所以要记录其后继节点便于处理下一个节点
            QNode temp = node.next;
            // 释放当前节点的空间
            node.next = null;
            node = null;
            // 继续下一个节点
            node = temp;
        }
        // 将队头指针和队尾指针指向 null 表示是一个空队列
        deque.front = null;
        deque.back = null;
    }

    /**
     * 销毁链式双端队列
     */
    public void destroy() {
        // 即释放头结点的存储空间
        deque = null;
    }

    /**
     * 打印链式双端队列从队头到队尾的所有结点值
     */
    public void print() {
        QNode node = deque.front;
        System.out.print("[");
        while (node != null) {
            System.out.print(node.data);
            if (node.next != null) {
                System.out.print(", ");
            }
            node = node.next;
        }
        System.out.print("]\n");
    }
}

/**
 * 链式双端队列，本质上还是单链表，所以如下是单链表结点的定义
 */
class QNode {
    /**
     * 结点数据域
     */
    int data;
    /**
     * 结点指针域，存储当前结点的后继结点的地址
     */
    QNode next;
}

/**
 * 链式双端队列定义
 */
class LinkedQueue {
    /**
     * 指针域，存储双端队列队头结点的地址
     */
    QNode front;
    /**
     * 指针域，存储双端队列队尾结点的地址
     */
    QNode back;
}
