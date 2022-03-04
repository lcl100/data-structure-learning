package 线性表.代码;

/**
 * @author lcl100
 * @create 2022-03-04 21:41
 */
public class CircularDoubleLinkedListTest {
    public static void main(String[] args) throws Exception {
        CircularDoubleLinkedList list = new CircularDoubleLinkedList();

        // 初始化循环双链表
        System.out.println("初始化循环双链表：");
        list.init();
        list.print();

        // 通过头插法创建循环双链表
        System.out.println("\n通过头插法创建循环双链表：");
        list.createByHead(11, 22, 33, 44, 55);
        list.print();

        // 通过尾插法创建循环双链表
        System.out.println("\n通过尾插法创建循环双链表：");
        list.createByTail(111, 222, 333, 444, 555);
        list.print();

        // 向链表中指定位置插入新节点
        System.out.println("\n向链表中指定位置插入新节点：");
        list.insert(1, 1111);
        list.print();
        list.insert(2, 2222);
        list.print();
        list.insert(list.size(), 7777);
        list.print();

        // 向链表头部插入新节点
        System.out.println("\n向链表头部插入新节点：");
        list.insertFirst(6666);
        list.print();

        // 向链表尾部插入新节点
        System.out.println("\n向链表尾部插入新节点：");
        list.insertLast(9999);
        list.print();

        // 删除指定位置的节点
        System.out.println("\n删除指定位置的节点：");
        list.removeByNum(1);
        list.print();
        list.removeByNum(4);
        list.print();
        list.removeByNum(list.size());
        list.print();

        // 删除指定值的节点
        System.out.println("\n删除指定值的节点：");
        list.removeByEle(2222);
        list.print();

        // 删除链表的第一个节点
        System.out.println("\n删除链表的第一个节点：");
        list.removeFirst();
        list.print();

        // 删除链表的最后一个节点
        System.out.println("\n删除链表的最后一个节点：");
        list.removeLast();
        list.print();

        // 获取指定值的前驱节点
        System.out.println("\n获取指定值的前驱节点：");
        CDLNode prior = list.getPrior(333);
        System.out.println(prior.data);

        // 获取指定值的后继节点
        System.out.println("\n获取指定值的后继节点：");
        CDLNode next = list.getNext(333);
        System.out.println(next.data);

        // 通过序号查找节点
        System.out.println("\n通过序号查找节点：");
        CDLNode nodeByNum = list.findByNum(1);
        System.out.println(nodeByNum.data);

        // 通过值查找节点
        System.out.println("\n通过值查找节点：");
        CDLNode nodeByEle = list.findByEle(444);
        System.out.println(nodeByEle.data);

        // 获取链表的长度
        System.out.println("\n获取链表的长度：");
        int len = list.size();
        System.out.println(len);

        // 清空链表
        System.out.println("\n清空链表：");
        list.clear();
        list.print();

        // 链表是否为空
        System.out.println("\n链表是否为空：");
        boolean empty = list.isEmpty();
        System.out.println(empty);
    }
}

