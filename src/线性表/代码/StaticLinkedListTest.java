package 线性表.代码;

/**
 * @author lcl100
 * @desc 静态链表测试类
 * @create 2022-03-05 22:03
 */
public class StaticLinkedListTest {
    public static void main(String[] args) throws Exception {
        StaticLinkedList list = new StaticLinkedList();

        // 初始化静态链表
        System.out.println("初始化静态链表：");
        list.init();
        list.print();

        // 创建静态链表
        System.out.println("\n创建静态链表：");
        list.createList(1, 2, 3, 4, 5, 6, 7);
        list.print();

        // 向静态链表指定位置插入元素
        System.out.println("\n向静态链表指定位置插入元素：");
        list.insert(1, 11);
        list.print();
        list.insert(4, 44);
        list.print();
        list.insert(list.size(), 88);
        list.print();

        // 向静态链表尾部插入元素
        System.out.println("\n向静态链表尾部插入元素：");
        list.append(555);
        list.print();
        list.append(666);
        list.print();

        // 移除静态链表指定位置的元素
        System.out.println("\n移除静态链表指定位置的元素：");
        list.remove(1);
        list.print();
        list.remove(5);
        list.print();
        list.remove(list.size());
        list.print();

        // 查询静态链表中指定序号的节点
        System.out.println("\n查询静态链表中指定序号的节点：");
        SLNode nodeByNum = list.findByNum(3);
        System.out.println(nodeByNum.data);

        // 查询静态链表中指定值的节点
        System.out.println("\n查询静态链表中指定值的节点：");
        SLNode nodeByEle = list.findByEle(88);
        System.out.println(nodeByEle.data);

        // 静态链表的长度
        System.out.println("\n静态链表的长度：");
        int len = list.size();
        System.out.println(len);

        // 静态链表是否为空
        System.out.println("\n静态链表是否为空：");
        boolean empty = list.isEmpty();
        System.out.println(empty);
    }
}

