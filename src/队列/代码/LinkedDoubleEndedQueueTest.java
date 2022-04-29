/**
 * @author lcl100
 * @desc 链式双端队列测试类
 * @create 2022-04-29 21:16
 */
public class LinkedDoubleEndedQueueTest {
    public static void main(String[] args) throws Exception {
        // 声明链式双端队列
        LinkedDoubleEndedQueue deque = new LinkedDoubleEndedQueue();

        // 初始化队列
        System.out.println("\n初始化队列：");
        deque.init();
        deque.print();

        // 从队头将元素入队
        System.out.println("\n从队头将元素入队：");
        deque.pushFront(11);
        deque.print();
        deque.pushFront(22);
        deque.print();
        deque.pushFront(33);
        deque.print();
        deque.pushFront(44);
        deque.print();
        deque.pushFront(55);
        deque.print();

        // 从队尾将元素入队
        System.out.println("\n从队尾将元素入队：");
        deque.pushBack(111);
        deque.print();
        deque.pushBack(222);
        deque.print();
        deque.pushBack(333);
        deque.print();
        deque.pushBack(444);
        deque.print();

        // 从队头将元素出队
        int ele1;
        System.out.println("\n从队头将元素出队：");
        ele1 = deque.popFront();
        System.out.println("出队元素：" + ele1);
        deque.print();
        ele1 = deque.popFront();
        System.out.println("出队元素：" + ele1);
        deque.print();
        ele1 = deque.popFront();
        System.out.println("出队元素：" + ele1);
        deque.print();

        // 从队尾将元素出队
        int ele2;
        System.out.println("\n从队尾将元素出队：");
        ele2 = deque.popBack();
        System.out.println("出队元素：" + ele2);
        deque.print();
        ele2 = deque.popBack();
        System.out.println("出队元素：" + ele2);
        deque.print();
        ele2 = deque.popBack();
        System.out.println("出队元素：" + ele2);
        deque.print();

        // 队列是否空
        System.out.println("\n队列是否空：");
        boolean empty;
        empty = deque.isEmpty();
        System.out.println(empty);

        // 队列中的元素个数
        System.out.println("\n队列中的元素个数：");
        int len;
        len = deque.size();
        System.out.println(len);

        // 队头元素
        System.out.println("\n队头元素：");
        int front;
        front = deque.getFront();
        System.out.println(front);

        // 队尾元素
        System.out.println("\n队尾元素：");
        int back;
        back = deque.getBack();
        System.out.println(back);

        // 清空队列
        System.out.println("\n清空队列：");
        deque.clear();
        deque.print();
    }
}