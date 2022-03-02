package 线性表.代码;

/**
 * @author lcl100
 * @desc 双链表测试类
 * @create 2022-03-02 20:14
 */
public class DoubleLinkedListTest {
    public static void main(String[] args) throws Exception {
        // 双链表一定要注意头结点和尾节点的考虑
        DoubleLinkedList list = new DoubleLinkedList();

        // 初始化双链表
        System.out.println("初始化双链表：");
        list.init();
        list.print();

        // 通过尾插法创建双链表
        System.out.println("\n通过尾插法创建双链表：");
        list.createByTail(111, 222, 333, 444, 555);
        list.print();

        // 通过头插法创建双链表
        System.out.println("\n通过头插法创建双链表：");
        list.createByHead(55, 44, 33, 22, 11);
        list.print();

        // 向双链表插入元素
        System.out.println("\n向双链表插入元素：");
        list.insert(1, 111);
        list.print();
        list.insert(3, 333);
        list.print();
        list.insert(list.size(), 777);
        list.print();

        // 向链表追加元素
        System.out.println("\n向链表追加元素：");
        list.append(9999);
        list.print();

        // 删除双链表中的元素
        System.out.println("\n删除双链表中的元素：");
        list.remove(1);
        list.print();
        list.remove(3);
        list.print();
        list.remove(list.size());
        list.print();

        // 双链表的长度
        System.out.println("\n双链表中的节点个数：");
        System.out.println(list.size());

        // 根据序号查找双链表中的元素
        System.out.println("\n根据序号查找双链表中的元素：");
        DLNode nodeByNum = list.findByNum(3);
        System.out.println(nodeByNum.data);

        // 根据值查找双链表中的元素
        System.out.println("\n根据值查找双链表中的元素：");
        DLNode nodeByEle = list.findByEle(777);
        System.out.println(nodeByEle.data);

        // 清空链表
        System.out.println("\n清空双链表：");
        list.clear();
        list.print();

        // 判断链表是否为空
        System.out.println("\n双链表是否为空：");
        boolean empty = list.isEmpty();
        System.out.println(empty);
    }
}

