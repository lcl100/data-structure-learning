package 线性表.代码;

/**
 * @author lcl100
 * @desc 线性表
 * @create 2022-02-28 20:16
 */
public class SeqList {
    /**
     * 顺序表最大能存放元素个数
     */
    private final int MAXSIZE = 20;

    /**
     * 声明的顺序表，未初始化
     */
    private List list;

    /**
     * 初始化顺序表
     */
    public void init() {
        list = new List();
        // 指定数据数组长度为 MAXSIZE
        list.data = new int[MAXSIZE];
        // 但指定顺序表实际元素个数为 0
        list.length = 0;
    }

    /**
     * 查找指定索引的元素的值
     *
     * @param index 索引，即数组下标，从 0 开始
     * @return 指定索引的元素的值
     * @throws Exception 如果索引超过范围，则抛出该异常
     */
    public int findByIndex(int index) throws Exception {
        // 0.参数校验
        // 0.1 如果索引小于 0 或者大于等于设定的最大长度，则抛出下面的异常
        if (index < 0 || index >= MAXSIZE) {
            throw new Exception("索引超出范围：" + index);
        }
        // 0.2 如果索引在 [0, MAXSIZE) 范围内，但超过了实际元素个数，也是无法获取到的，所以抛出异常
        if (index >= list.length) {
            throw new Exception("不存在第 " + index + " 个元素！");
        }
        // 1.查找指定索引所表示的元素
        // 1.1 直接返回下标为 index 的元素值即可，不需要遍历循环
        return list.data[index];
    }

    /**
     * 查找指定元素值的元素在顺序表中的索引
     *
     * @param ele 指定元素值
     * @return 如果指定元素在顺序表中则返回它对应的索引，如果不存在于顺序表中则返回 -1
     */
    public int findByEle(int ele) {
        // 循环顺序表中的所有元素
        for (int i = 0; i < list.length; i++) {
            // 比较迭代的每一个元素的值是否等于传入的参数值，如果相等则返回对应的索引（下标）
            if (list.data[i] == ele) {
                return i;
            }
        }
        return -1;
    }

    /**
     * 向顺序表指定索引处插入一个新元素。原索引处的元素及之后的所有元素都向后移动一位。
     *
     * @param index 指定索引，从 0 开始
     * @param ele   待插入的新元素
     * @throws Exception 如果索引超过范围，则抛出该异常
     */
    public void insert(int index, int ele) throws Exception {
        // 0.参数校验
        // 0.1 如果索引小于 0 或者大于等于设定的最大长度，则抛出下面的异常
        if (index < 0 || index >= MAXSIZE) {
            throw new Exception("索引超出范围：" + index);
        }
        // 0.2 向顺序表中插入元素要检查顺序表是否已经满了，如果已经满了则不能再插入新元素则抛出异常
        if (list.length == MAXSIZE) {
            throw new Exception("顺序表已满，不能再插入了！");
        }
        // 0.3 如果插入的索引超过了数组长度的范围也不行
        if (index > list.length) {
            throw new Exception("不存在第 " + index + " 个索引！");
        }
        // 1.如果顺序表没有满，则继续插入元素
        // 1.1 循环顺序表，从后往前遍历，将指定索引及之后的所有元素（包括指定索引）向后移动一位
        for (int i = list.length - 1; i >= index; i--) {
            list.data[i + 1] = list.data[i];
        }
        // 1.2 将移动后空出来的位置（即指定索引所在的位置）插入新元素
        list.data[index] = ele;
        // 1.3 不要忘记将 length 加 1 表示顺序表新增一个元素
        list.length++;
    }

    /**
     * 直接添加新元素到顺序表的尾部
     *
     * @param ele 待插入的新元素
     */
    public void add(int ele) throws Exception {
        // 0.校验
        // 0.1 向顺序表中插入元素要检查顺序表是否已经满了，如果已经满了则不能再插入新元素则抛出异常
        if (list.length == MAXSIZE) {
            throw new Exception("顺序表已满，不能再插入了！");
        }
        // 1.插入新元素
        // 1.1 直接获取顺序表的 length，然后将新元素的值赋予到 length 位置即可
        list.data[list.length] = ele;
        // 1.2 注意修改 length
        list.length++;
    }

    /**
     * 移除顺序表中指定索引的元素
     *
     * @param index 指定索引，即下标，从 0 开始
     * @return 被删除元素的数据值
     * @throws Exception 如果索引超过范围，则抛出该异常
     */
    public int remove(int index) throws Exception {
        // 0.参数校验
        // 0.1 判断输入的索引是否超出范围
        if (index < 0 || index >= MAXSIZE) {
            throw new Exception("索引超出范围：" + index);
        }
        // 0.2 在删除顺序表元素之前，要判断顺序表是否为空，如果为空则不能进行删除
        if (list.length == 0) {
            throw new Exception("顺序表为空，不能删除了！");
        }
        // 0.3 判断输入的索引虽然在数组范围内，但是否存在元素
        if (index >= list.length) {
            throw new Exception("不存在第 " + index + " 个元素！");
        }
        // 1.删除指定索引的元素
        // 1.1 保存待删除索引所表示的元素的数据值
        int temp = list.data[index];
        // 1.2 循环遍历顺序表，从前往后，将指定索引之后的所有元素（不包括指定索引）向前移动一步
        for (int i = index; i < list.length; i++) {
            list.data[i] = list.data[i + 1];// 后面的元素覆盖前面的元素
        }
        // 1.3 将记录数组实际元素个数的 length 减去 1，表示已经删除了一个元素
        list.length--;
        // 1.4 返回被删除元素的数据值
        return temp;
    }

    /**
     * 获取顺序表的长度
     *
     * @return 顺序表中实际元素个数
     */
    public int size() {
        return list.length;
    }

    /**
     * 顺序表是否为空
     *
     * @return 如果为空则返回 true，否则返回 false
     */
    public boolean isEmpty() {
        return list.length == 0;
    }

    /**
     * 打印顺序表
     */
    public void print() {
        String str = "[";
        for (int i = 0; i < list.length; i++) {
            str += list.data[i];
            if (i != list.length - 1) {
                str += ", ";
            }
        }
        str += "]";
        System.out.println(str);
    }
}

/**
 * 顺序表
 */
class List {
    /**
     * 数据域，保存数据的数组
     */
    int[] data;
    /**
     * 数组中实际元素个数
     */
    int length;
}