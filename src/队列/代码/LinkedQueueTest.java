
public class LinkedQueueTest {
    public static void main(String[] args) throws Exception {
        // 声明链队列
        LinkedQueue queue = new LinkedQueue();

        // 初始化链队列
        System.out.println("\n初始化链队列：");
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
        queue.enQueue(55);
        queue.print();

        // 将元素出队
        System.out.println("\n将元素出队：");
        int ele;
        ele = queue.deQueue();
        System.out.println("出队元素：" + ele);
        queue.print();
        ele = queue.deQueue();
        System.out.println("出队元素：" + ele);
        queue.print();
        ele = queue.deQueue();
        System.out.println("出队元素：" + ele);
        queue.print();
        ele = queue.deQueue();
        System.out.println("出队元素：" + ele);
        queue.print();

        // 队列是否为空
        System.out.println("\n队列是否为空：");
        boolean empty;
        empty = queue.isEmpty();
        System.out.println(empty);

        // 队列元素个数
        System.out.println("\n队列元素个数：");
        int len;
        len = queue.size();
        System.out.println(len);

        // 获取队头元素
        System.out.println("\n获取队头元素：");
        int front;
        front = queue.getFront();
        System.out.println(front);

        // 获取队尾元素
        System.out.println("\n获取队尾元素：");
        int rear;
        rear = queue.getRear();
        System.out.println(rear);

        // 清空队列
        System.out.println("\n清空队列：");
        queue.clear();
        queue.print();

        // 销毁队列
        System.out.println("\n销毁队列：");
        queue.destroy();
    }
}
