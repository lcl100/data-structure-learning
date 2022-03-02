package 线性表.代码;

/**
 * @author lcl100
 * @desc 双链表
 * @create 2022-03-02 20:13
 */
public class DoubleLinkedList {
    DLNode list;

    /**
     * 初始化双链表
     */
    public void init() {
        // 给双链表头结点分配空间
        list = new DLNode();
        // 将双链表的指针域都指向 null，不需要理会数据域
        list.prior = null;
        list.next = null;
    }

    /**
     * 通过尾插法创建双链表
     *
     * @param nums 会放入到双链表中的数据
     * @return 创建成功的双链表
     */
    public DLNode createByTail(int... nums) {
        // 1.初始化链表，即创建双链表的头结点，也可以直接调用 init 方法进行初始化
        // 1.1 给双链表头结点分配空间
        list = new DLNode();
        // 1.2 将双链表的 prior 指针指向 null
        list.prior = null;
        // 1.3 将双链表的 next 指针指向 null
        list.next = null;

        // 使用尾插法，最重要的是知道链表的尾节点，初始时为链表的头结点
        DLNode tailNode = list;

        // 2.循环数组中元素，然后插入到链表的尾部
        for (int i = 0; i < nums.length; i++) {
            // 2.1 创建新节点
            // 2.1.1 为新节点分配空间
            DLNode newNode = new DLNode();
            // 2.1.2 指定新节点的数据域
            newNode.data = nums[i];
            // 2.1.3 将新节点的 prior 指针指向 null
            newNode.prior = null;
            // 2.1.4 将新节点的 next 指针指向 null
            newNode.next = null;

            // 2.2 将新节点连接到链表中
            // 2.2.1 将原尾节点的 next 指针指向新节点
            tailNode.next = newNode;
            // 2.2.2 将新节点的 prior 指针指向原尾节点，这时已经将新节点连接到链表的尾部了
            newNode.prior = tailNode;
            // 2.2.3 不要忘记更新尾节点，让新节点成为新的尾节点，才能进行下一次插入
            tailNode = newNode;
        }
        return list;
    }

    /**
     * 通过头插法创建双链表
     *
     * @param nums 会放入到双链表中的数据
     * @return 创建成功的双链表
     */
    public DLNode createByHead(int... nums) {
        // 1.初始化链表，即创建双链表的头结点，也可以直接调用 init 方法进行初始化
        // 1.1 给双链表头结点分配空间
        list = new DLNode();
        // 1.2 将双链表的 prior 指针指向 null
        list.prior = null;
        // 1.3 将双链表的 next 指针指向 null
        list.next = null;

        // 2.循环数组中元素，然后插入到链表的头部
        for (int i = 0; i < nums.length; i++) {
            // 2.1 创建新节点
            // 2.1.1 为新节点分配空间
            DLNode newNode = new DLNode();
            // 2.1.2 指定新节点的数据域
            newNode.data = nums[i];
            // 2.1.3 将新节点的 prior 指针指向 null
            newNode.prior = null;
            // 2.1.4 将新节点的 next 指针指向 null
            newNode.next = null;

            // 2.2 将新节点插入到链表的头部，但是在头结点的后面
            // 2.2.1 需要考虑链表为空的情况，当链表为空时新节点只能插入到头结点的后面
            if (list.next == null) {
                // 2.2.1.1 链表为空，只需要将头结点的 next 指针指向新节点
                list.next = newNode;
                // 2.2.1.2 然后将新节点的 prior 指针指向头结点，即完成了头结点和新节点的连接
                newNode.prior = list;
            }
            // 2.2.2 如果链表不为空，则直接在头结点后面插入新节点即可，注意新节点和头结点和原链表第一个节点的连接
            else {
                // 2.2.2.1 保存原链表的第一个节点，必定不为 null
                DLNode firstNode = list.next;
                // 2.2.2.2 将原链表的第一个节点的 prior 指针指向新节点
                firstNode.prior = newNode;
                // 2.2.2.3 将新节点的 next 指针指向原链表的第一个节点，已经完成了新节点与原链表第一个节点的连接
                newNode.next = firstNode;
                // 2.2.2.4 将头结点的 next 指针指向新节点
                list.next = newNode;
                // 2.2.2.5 将新节点的 prior 指针指向头结点，已经完成了新节点与头结点的连接
                newNode.prior = list;
            }
        }
        return list;
    }

    /**
     * 通过节点数据检索双链表中的节点
     *
     * @param ele 节点数据值
     * @return 查找到的节点
     */
    public DLNode findByEle(int ele) {
        // 链表的第一个节点
        DLNode node = list.next;
        // 1.循环链表所有节点，查找能够匹配值的节点
        while (node != null) {
            // 1.1 如果正在迭代的节点的数据域值等于指定值，表示找到该节点，则返回
            if (node.data == ele) {
                return node;
            }
            // 1.2 如果不等于则继续双链表的下一个节点
            node = node.next;
        }
        return null;
    }

    /**
     * 通过节点序号检索双链表中的节点
     *
     * @param i 节点序号，从 1 开始
     * @return 查找到的节点
     */
    public DLNode findByNum(int i) {
        // 计数器，记录当前遍历到第几个节点
        int count = 0;
        // 链表的第一个节点
        DLNode node = list.next;
        // 循环遍历链表
        while (node != null) {
            // 计数器加1，记录已经遍历的节点个数
            count++;
            // 查找到第 i 个节点，然后返回该节点
            if (count == i) {
                return node;
            }
            // 继续链表的下一个节点
            node = node.next;
        }
        return null;
    }

    /**
     * 向双链表中的指定序号位置插入节点
     *
     * @param i   指定序号，从 1 开始
     * @param ele 节点数据值
     * @throws Exception 如果序号不符合则抛出异常
     */
    public void insert(int i, int ele) throws Exception {
        // 0.参数校验
        if (i < 1 || i > size()) {
            throw new Exception("不存在第 " + i + " 个节点！");
        }

        // 1.首先查找第 i 个节点，直接调用我们已经写好的函数即可。在双链表中插入不需要找第 i-1 个节点，因为可以通过第 i 个节点的 prior 指针得到它的前驱节点
        DLNode node = findByNum(i);
        if (node == null) {
            throw new Exception("第 " + i + " 个节点为 null！");
        }

        // 2.将新节点插入到链表指定位置
        // 2.1 创建新节点
        // 2.1.1 为新节点分配空间
        DLNode newNode = new DLNode();
        // 2.1.2 指定新节点的数据域
        newNode.data = ele;
        // 2.1.3 将新节点的 prior 指针指向 null
        newNode.prior = null;
        // 2.1.4 将新节点的 next 指针指向 null
        newNode.next = null;
        // 2.2 将新节点插入到链表中
        // 2.2.1 保存第 i 个节点的前驱节点，即第 i-1 个节点
        DLNode temp = node.prior;
        // 2.2.2 将第 i 个节点的 prior 指针指向新节点
        node.prior = newNode;
        // 2.2.3 将新界的的 next 指针指向第 i 个节点，此时完成了新节点与第 i 个节点的连接
        newNode.next = node;
        // 2.2.4 将第 i-1 个节点的 next 指针指向新节点
        temp.next = newNode;
        // 2.2.5 将新节点的 prior 指针指向第 i-1 个节点，此时完成了新节点与第 i-1 个节点的连接
        newNode.prior = temp;
    }

    /**
     * 向双链表的尾部附加一个新节点
     *
     * @param ele 新节点的数据值
     */
    public void append(int ele) {
        // 1.获取到链表的最后一个节点，使用下面的方式能有效处理空链表的情况
        // 1.1 保存链表的最后一个节点，初始时为链表的头结点
        DLNode lastNode = list;
        // 1.2 链表的第一个节点，用于遍历循环
        DLNode node = list.next;
        // 1.3 循环遍历链表每一个节点
        while (node != null) {
            // 1.3.1 保存正在迭代的节点
            lastNode = node;
            // 1.3.2 继续链表的下一个节点
            node = node.next;
        }

        // 2.将新节点插入到链表的尾部
        // 2.1 创建新节点
        // 2.1.1 为新节点分配空间
        DLNode newNode = new DLNode();
        // 2.1.2 指定新节点的数据域
        newNode.data = ele;
        // 2.1.3 将新节点的 prior 指针指向 null
        newNode.prior = null;
        // 2.1.4 将新节点的 next 指针指向 null
        newNode.next = null;
        // 2.2 将新节点附加到链表的尾部
        // 2.2.1 将新节点的 prior 指针指向原链表最后一个节点
        newNode.prior = lastNode;
        // 2.2.2 将原链表最后一个节点的 next 指针指向新节点，此时完成了新节点和原链表最后一个节点的连接
        lastNode.next = newNode;
    }

    /**
     * 删除双链表中指定序号的节点
     *
     * @param i 指定序号，从 1 开始
     * @return 被删除的节点
     * @throws Exception 如果序号不符合则抛出异常
     */
    public DLNode remove(int i) throws Exception {
        // 0.参数校验
        if (i < 1 || i > size()) {
            throw new Exception("不存在第 " + i + " 个节点！");
        }

        // 1.找到第 i 个节点，利用我们已经写好的函数即可。也不需要找到第 i-1 个节点，因为我们通过第 i 个节点的 prior 指针获得
        DLNode node = findByNum(i);
        if (node == null) {
            throw new Exception("第 " + i + " 个节点为 null！");
        }

        // 2.移除第 i 个节点
        // 2.1 需要判断待删除的节点是否还有后继节点，如果没有后继节点则表示该节点是链表的最后一个节点则需要特殊处理
        if (node.next == null) {
            // 2.1.1 如果被删除节点是最后一个节点，则只需要将第 i-1 个节点的 next 指针指向 null
            node.prior.next = null;
        }
        // 2.2 如果被删除节点不是链表的最后一个节点，则需要通过被删除节点的前驱节点和后继节点进行删除
        else {
            // 将第 i+1 个节点的 prior 指针指向第 i-1 个节点
            node.next.prior = node.prior;
            // 将第 i-1 个节点的 next 指针指向第 i+1 个节点，完成第 i 个节点的删除
            node.prior.next = node.next;
        }
        // 2.3 返回被删除的节点
        return node;
    }

    /**
     * 双链表是否为空链表
     *
     * @return 如果为空则返回true，否则返回false
     */
    public boolean isEmpty() {
        // 只需要判断链表的第一个节点是否存在即可
        return list.next == null;
    }

    /**
     * 获取双链表中的节点个数
     *
     * @return 节点个数
     */
    public int size() {
        // 计数器，记录链表的节点个数
        int count = 0;
        // 链表的第一个节点
        DLNode node = list.next;
        // 循环双链表，统计节点个数
        while (node != null) {
            count++;
            node = node.next;
        }
        return count;
    }

    public void clear() {
        // 链表的第一个节点
        DLNode node = list.next;
        // 循环遍历链表所有节点，回收空间
        while (node != null) {
            DLNode temp = node.next;
            node.next = null;
            node.prior = null;
            node.data = 0;
            node = temp;
        }
        list.next = null;
    }

    /**
     * 打印双链表中所有节点数据
     */
    public void print() {
        // 链表的第一个节点
        DLNode node = list.next;
        // 循环遍历链表的所有节点
        String str = "[";
        while (node != null) {
            str += node.data;
            if (node.next != null) {
                str += ", ";
            }
            node = node.next;
        }
        str += "]";
        // 打印结果
        System.out.println(str);
    }

}

/**
 * 双链表节点，包括一个数据域和两个指针域（分别指向前驱节点和后继节点）
 */
class DLNode {
    /**
     * 双链表节点的数据域
     */
    int data;
    /**
     * 双链表节点的前驱节点
     */
    DLNode prior;
    /**
     * 双链表节点的后继节点
     */
    DLNode next;
}

