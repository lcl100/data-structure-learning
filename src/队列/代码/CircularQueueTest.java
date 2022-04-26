public class CircularQueueTest {
    public static void main(String[] args) throws Exception {
        // 声明循环队列
        CircularQueue queue = new CircularQueue();

        // 初始化队列
        System.out.println("\n初始化队列：");
        queue.init();
        queue.print();

        // 将元素入队
        System.out.println("\n将元素入队：");
        queue.enQueue(11);
        queue.print();
        queue.enQueue(22);
        queue.print();
        queue.enQueue(33);
        queue.print();
        queue.enQueue(44);
        queue.print();

        // 队列是否满
        System.out.println("\n队列是否满：");
        boolean full;
        full = queue.isFull();
        System.out.println(full);

        // 将元素出队
        int ele;
        System.out.println("\n将元素出队：");
        ele = queue.deQueue();
        System.out.println("出队元素：" + ele);
        queue.print();
        ele = queue.deQueue();
        System.out.println("出队元素：" + ele);
        queue.print();
        ele = queue.deQueue();
        System.out.println("出队元素：" + ele);
        queue.print();

        // 队列是否空
        System.out.println("\n队列是否空：");
        boolean empty;
        empty = queue.isEmpty();
        System.out.println(empty);

        // 队列中的元素个数
        System.out.println("\n队列中的元素个数：");
        int len;
        len = queue.size();
        System.out.println(len);

        // 队头元素
        System.out.println("\n队头元素：");
        int front;
        front = queue.getFront();
        System.out.println(front);

        // 再将元素入队
        System.out.println("\n再将元素入队：");
        queue.enQueue(55);
        queue.print();

        // 队尾元素
        System.out.println("\n队尾元素：");
        int rear;
        rear = queue.getRear();
        System.out.println(rear);

        // 清空队列
        System.out.println("\n清空队列");
        queue.clear();
        queue.print();
    }
}
