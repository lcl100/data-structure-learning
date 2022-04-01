package 线性表.代码;

/**
 * @author lcl100
 * @desc 单链表测试类
 * @create 2022-03-01 20:59
 */
public class LinkedListTest {
    public static void main(String[] args) throws Exception {
        // 创建单链表
        LinkedList list = new LinkedList();

        // 初始化单链表
        System.out.println("初始化单链表：");
        list.init();
        list.print();

        // 通过头插法创建单链表
        System.out.println("\n通过头插法创建单链表：");
        list.createByHead(11, 22, 33, 44, 55);
        list.print();

        // 通过尾插法创建单链表
        System.out.println("\n通过尾插法创建单链表：");
        list.createByTail(11, 22, 33, 44, 55);
        list.print();

        // 查找单链表指定位置的结点
        System.out.println("\n查找单链表指定位置的结点：");
        LNode iNode = list.findByNum(3);
        System.out.println("iNode=" + iNode.data);

        // 查找单链表等于指定值的结点
        System.out.println("\n查找单链表等于指定值的结点：");
        LNode eleNode = list.findByEle(33);
        System.out.println("eleNode=" + eleNode.data);

        // 在链表指定位置插入新元素
        System.out.println("\n在链表指定位置插入新元素：");
        list.insert(1, 999);
        list.print();
        list.insert(4, 888);
        list.print();
        list.insert(list.size(), 777);
        list.print();

        // 删除链表指定位置的元素
        System.out.println("\n删除链表指定位置的元素：");
        list.remove(1);
        list.print();
        list.remove(3);
        list.print();
        list.remove(list.size());
        list.print();

        // 删除链表中指定值的元素
        System.out.println("\n删除链表中指定值的元素：");
        list.removeEle(33);
        list.print();
        list.removeEle(777);
        list.print();

        // 删除链表中所有等于指定值的节点
        System.out.println("\n删除链表中所有等于指定值的节点：");
        list.createByTail(11, 22, 11, 33, 11, 11, 44, 11);
        list.removeAllEle(11);
        list.print();

        // 链表的长度
        System.out.println("\n链表的长度：");
        int len = list.size();
        System.out.println(len);

        // 链表是否为空
        System.out.println("\n链表是否为空：");
        boolean empty = list.isEmpty();
        System.out.println(empty);

        // 清空链表所有元素
        System.out.println("\n清空链表所有元素：");
        list.clear();
        list.print();
    }
}