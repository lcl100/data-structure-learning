package 线性表.代码;

/**
 * @author lcl100
 * @desc （带头结点的）单链表
 * @create 2022-03-01 20:58
 */
public class LinkedList {
    /**
     * 单链表
     */
    private LNode list;

    /**
     * 初始化单链表
     */
    public void init() {
        // 单链表的初始化分为两步：第一步，创建头结点并分配内存空间；第二步，将头结点的 next 指针指向 null
        list = new LNode();
        list.next = null;
    }

    /**
     * 通过头插法创建单链表
     *
     * @param nums 创建单链表时插入的数据
     * @return 创建好的单链表
     */
    public LNode createByHead(int... nums) {
        // 1.初始化单链表
        // 创建链表必须要先初始化链表，也可以选择直接调用 init() 函数
        list = new LNode();
        list.next = null;

        // 2.通过循环将数组中所有值通过头插法插入到单链表中
        for (int i = 0; i < nums.length; i++) {
            // 2.1 创建新节点，并指定数据域和指针域
            // 2.1.1 创建新结点，分配空间
            LNode newNode = new LNode();
            // 2.1.2 给新节点的数据域指定值
            newNode.data = nums[i];
            // 2.1.3 给新节点的指针域指定为 null
            newNode.next = null;

            // 2.2 将新节点插入到单链表的头部，但是在头结点的后面
            // 2.2.1 获取到单链表的第一个节点，即头结点的后继节点
            LNode firstNode = list.next;// 单链表的第一个节点
            // 2.2.2 将头结点的 next 指针指向新节点
            list.next = newNode;
            // 2.2.3 将新节点的 next 指针指向原单链表的第一个节点，此时新节点成为了单链表头结点的后继节点
            newNode.next = firstNode;
        }

        return list;
    }

    /**
     * 通过尾插法创建单链表
     *
     * @param nums 创建单链表时插入的数据
     * @return 创建好的单链表
     */
    public LNode createByTail(int... nums) {
        // 1.初始化单链表
        // 创建链表必须要先初始化链表，也可以选择直接调用 init() 函数
        list = new LNode();
        list.next = null;

        // 尾插法，必须知道链表的尾节点（即链表的最后一个节点），初始时，单链表的头结点就是尾节点
        // 因为在单链表中插入节点我们必须知道前驱节点，而头插法中的前驱节点一直是头节点，但尾插法中要在单链表的末尾插入新节点，所以前驱节点一直都是链表的最后一个节点，而链表的最后一个节点由于链表插入新节点会一直变化
        LNode tailNode = list;

        // 2.循环数组，将所有数依次插入到链表的尾部
        for (int i = 0; i < nums.length; i++) {
            // 2.1 创建新节点，并指定数据域和指针域
            // 2.1.1 创建新节点，为其分配空间
            LNode newNode = new LNode();
            // 2.1.2 为新节点指定数据域
            newNode.data = nums[i];
            // 2.1.3 为新节点指定指针域，新节点的指针域初始时设置为 null
            newNode.next = null;

            // 2.2 将新节点插入到单链表的尾部
            // 2.2.1 将链表原尾节点的 next 指针指向新节点
            tailNode.next = newNode;
            // 2.2.2 将新节点置为新的尾节点
            tailNode = newNode;
        }

        return list;
    }

    /**
     * 在单链表的第 i 个结点（从 1 开始）前插入一个结点
     *
     * @param i   节点序号，从 1 开始
     * @param ele 待插入的数据
     * @throws Exception 当不存在第 i 个节点时抛出异常
     */
    public void insert(int i, int ele) throws Exception {
        // 0.校验参数
        if (i < 1 || i > size() + 1) {// 当 i=1 并且单链表为空时也能有效插入
            throw new Exception("没有第 " + i + " 个节点");
        }
        // 1.计算第 i 个节点的前驱节点。注意，第一个节点的前驱节点是头结点
        // 1.1 声明三个变量
        LNode iPreNode = list;// 用来保存第 i 个节点的前驱节点，初始时链表第一个节点的前驱节点是头结点
        LNode node = list.next;// 用来保存链表中的每一个节点为了遍历循环，初始时链表的第一个节点
        int count = 1;// 计数器，记录遍历次数，初始为 1 而不能是 0，因为 i 表示节点的序号（序号从 1 开始的）
        // 1.2 找到第 i 个节点的前驱节点，循环 i-1 次
        while (count < i) {
            // 1.2.1 计数器加 1，表示已经遍历 1 次
            count++;
            // 1.2.2 保存当前节点为前驱节点
            iPreNode = node;
            // 1.2.3 继续下一个节点
            node = node.next;
        }

        // 2.将新节点插入到链表中
        // 2.1 创建新节点
        // 2.1.1 为新节点分配空间
        LNode newNode = new LNode();
        // 2.1.2 为新节点指定数据域
        newNode.data = ele;
        // 2.1.3 为新节点指定指针域，初始时都指向 null
        newNode.next = null;
        // 2.2 将新节点连接到链表中
        // 2.2.1 将新节点的 next 指针指向第 i 个节点的前驱节点的后继节点（实际上就是第 i 个节点）上
        newNode.next = iPreNode.next;
        // 2.2.2 将第 i 个节点的 next 指针指向新节点
        iPreNode.next = newNode;
    }

    /**
     * 删除单链表中第 i 个结点
     *
     * @param i 节点序号，从 1 开始
     * @return 被删除节点的数据
     * @throws Exception 当不存在第 i 个节点时抛出异常
     */
    public int remove(int i) throws Exception {
        // 0.校验参数
        if (i < 1 || i > size()) {
            throw new Exception("没有第 " + i + " 个节点");
        }

        // 1.计算第 i 个节点的前驱节点。注意，第一个节点的前驱节点是头结点
        // 1.1 声明三个变量
        LNode iPreNode = list;// 用来保存第 i 个节点的前驱节点，初始时链表第一个节点的前驱节点是头结点
        LNode node = list.next;// 用来保存链表中的每一个节点为了遍历循环，初始时链表的第一个节点
        int count = 1;// 计数器，记录遍历次数，初始为 1 而不能是 0，因为 i 表示节点的序号（序号从 1 开始的）
        // 1.2 找到第 i 个节点的前驱节点，循环 i-1 次
        while (count < i) {
            // 1.2.1 计数器加 1，表示已经遍历 1 次
            count++;
            // 1.2.2 保存当前节点为前驱节点
            iPreNode = node;
            // 1.2.3 继续下一个节点
            node = node.next;
        }

        // 2.删除第 i 个节点
        // 2.1 得到第 i 个节点
        LNode iNode = iPreNode.next;
        // 2.2 删除第 i 个节点，即将第 i 个节点的前驱节点的 next 指针指向第 i 个节点的后继节点
        iPreNode.next = iNode.next;
        // 2.3 返回被删除节点的数据
        return iNode.data;
    }

    /**
     * 删除单链表中指定值的结点。
     * 注意，只会删除找到的第一个节点，如果有多个节点的值都等于指定值则只会删除第一个
     *
     * @param ele 指定值
     */
    public void removeEle(int ele) {
        // 链表的第一个节点
        LNode node = list.next;
        // 保存前驱节点
        LNode pre = list;
        // 循环单链表
        while (node != null) {
            // 找到值等于 ele 的节点
            if (node.data == ele) {
                // 删除当前节点
                pre.next = node.next;
                // 释放被删除节点空间
                node.next = null;
                node.data = 0;
                // 跳出循环
                break;
            }
            pre = node;
            node = node.next;
        }
    }

    /**
     * 删除单链表中结点值等于 ele 的所有结点
     *
     * @param ele 待删除节点的值
     */
    public void removeAllEle(int ele) {
        // 链表的第一个节点
        LNode node = list.next;
        // 保存前驱节点，初始化链表第一个节点的前驱节点就算链表的头结点
        LNode pre = list;
        // 循环单链表
        while (node != null) {
            // 如果查找到要删除的节点
            if (node.data == ele) {
                // 则删除 node 节点，但这里不能用 prior.next = node.next; 来删除节点
                node = node.next;
                pre.next = node;
            } else {
                // 如果没有找到则继续判断链表的下一个节点，但注意更新 node 和 pre
                node = node.next;
                pre = pre.next;
            }
        }
    }

    /**
     * 计算单链表的长度，即节点个数
     *
     * @return 链表节点个数
     */
    public int size() {
        // 计数器，记录链表的节点个数
        int count = 0;
        // 链表的第一个节点
        LNode node = list.next;
        // 循环单链表，统计节点个数
        while (node != null) {
            // 计数器加1
            count++;
            // 继续链表的下一个节点
            node = node.next;
        }
        // 返回统计结果
        return count;
    }

    /**
     * 判断单链表是否为空
     *
     * @return 如果链表为空则返回 true，否则返回 false
     */
    public boolean isEmpty() {
        // 只需要判断链表的第一个节点是否存在即可
        return list.next == null;
    }

    /**
     * 清空单链表
     */
    public void clear() {
        // 单链表的第一个节点
        LNode node = list.next;
        // 循环单链表
        while (node != null) {
            // 保存当前节点的下一个节点
            LNode temp = node.next;
            // 释放当前节点的空间
            node.data = 0;
            node.next = null;
            // 继续链表的下一个节点
            node = temp;
        }
        // 最重要的是，将链表的头结点的 next 指针指向 null
        list.next = null;
    }

    /**
     * 打印单链表所有节点
     */
    public void print() {
        // 链表的第一个节点
        LNode node = list.next;
        // 循环打印
        String str = "[";
        while (node != null) {
            // 拼接节点的数据域
            str += node.data;
            // 只要不是最后一个节点，那么就在每个节点的数据域后面添加一个分号，用于分隔字符串
            if (node.next != null) {
                str += ", ";
            }
            // 继续链表的下一个节点
            node = node.next;
        }
        str += "]";
        // 打印链表
        System.out.println(str);
    }
}

/**
 * 单链表的节点
 */
class LNode {
    /**
     * 链表的数据域，暂时指定为 int 类型，因为 Java 支持泛型，可以指定为泛型，就能支持更多的类型了
     */
    int data;
    /**
     * 链表的指针域，指向该节点的下一个节点
     */
    LNode next;
}