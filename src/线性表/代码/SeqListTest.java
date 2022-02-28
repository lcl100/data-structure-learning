package 线性表.代码;

/**
 * @author lcl100
 * @desc 顺序表测试类
 * @create 2022-02-28 20:18
 */
public class SeqListTest {
    public static void main(String[] args) throws Exception {
        // 实例化顺序表对象
        SeqList list = new SeqList();

        // 初始化顺序表
        System.out.println("初始化顺序表：");
        list.init();
        list.print();

        // 在顺序表指定索引处插入新元素
        System.out.println("\n在顺序表指定索引处插入新元素：");
        list.insert(0, 1);
        list.print();
        list.insert(1, 2);
        list.print();
        list.insert(2, 3);
        list.print();
        list.insert(2, 4);
        list.print();

        // 直接在顺序表的后面添加新元素
        System.out.println("\n直接在顺序表的后面添加新元素：");
        list.add(55);
        list.print();
        list.add(66);
        list.add(77);
        list.print();

        // 删除顺序表中指定索引的元素
        System.out.println("\n删除顺序表中指定索引的元素：");
        list.remove(0);
        list.print();
        list.remove(1);
        list.print();
        list.remove(4);
        list.print();

        // 通过索引查找顺序表中的元素
        System.out.println("\n通过索引查找顺序表中的元素：");
        int ele = list.findByIndex(2);
        System.out.println(ele);

        // 通过值查找顺序表中的元素在顺序表中的索引
        System.out.println("\n通过值查找顺序表中的元素在顺序表中的索引：");
        int index = list.findByEle(66);
        System.out.println(index);

        // 顺序表的长度
        System.out.println("\n顺序表的长度：");
        int size = list.size();
        System.out.println(size);

        // 顺序表是否为空
        System.out.println("\n顺序表是否为空：");
        boolean empty = list.isEmpty();
        System.out.println(empty);
    }
}

