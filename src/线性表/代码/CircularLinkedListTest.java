package 线性表.代码;

/**
 * @author lcl100
 * @desc 循环单链表测试类
 * @create 2022-03-03 20:24
 */
public class CircularLinkedListTest {
    public static void main(String[] args) throws Exception {
        // 实例化循环单链表对象
        CircularLinkedList list = new CircularLinkedList();

        // 初始化循环单链表
        System.out.println("初始化循环单链表：");
        list.init();
        list.print();

        // 通过头插法创建循环单链表
        System.out.println("\n通过头插法创建循环单链表：");
        list.createByHead(11, 22, 33, 44, 55);
        list.print();

        // 通过尾插法创建循环单链表
        System.out.println("\n通过尾插法创建循环单链表：");
        list.createByTail(111, 222, 333, 444, 555);
        list.print();

        // 在指定位置插入新节点
        System.out.println("\n在指定位置插入新节点：");
        list.insert(1, 6666);
        list.print();
        list.insert(3, 7777);
        list.print();
        list.insert(list.size(), 8888);
        list.print();

        // 在链表的头部插入节点
        System.out.println("\n在链表的头部插入节点：");
        list.insertFirst(9999);
        list.print();

        // 在链表的尾部插入节点
        System.out.println("\n在链表的尾部插入节点：");
        list.insertLast(99999);
        list.print();

        // 删除指定位置的节点
        System.out.println("\n删除指定位置的节点：");
        list.removeByNum(1);
        list.print();
        list.removeByNum(3);
        list.print();
        list.removeByNum(list.size());
        list.print();

        // 删除指定值的节点
        System.out.println("\n删除指定值的节点：");
        list.removeByEle(333);
        list.print();

        // 删除链表第一个节点
        System.out.println("\n删除链表第一个节点：");
        list.removeFirst();
        list.print();

        // 删除链表最后一个节点
        System.out.println("\n删除链表最后一个节点：");
        list.removeLast();
        list.print();

        // 查找指定位置的节点
        System.out.println("\n查找指定位置的节点：");
        CLNode nodeByNum = list.findByNum(2);
        System.out.println(nodeByNum.data);

        // 查找指定值的节点
        System.out.println("\n查找指定值的节点：");
        CLNode nodeByEle = list.findByEle(8888);
        System.out.println(nodeByEle.data);

        // 链表的长度
        System.out.println("\n链表的长度：");
        int len = list.size();
        System.out.println(len);

        // 清空循环单链表
        System.out.println("\n清空循环单链表：");
        list.clear();
        list.print();

        // 循环单链表是否为空
        System.out.println("\n循环单链表是否为空：");
        boolean empty = list.isEmpty();
        System.out.println(empty);
    }
}
