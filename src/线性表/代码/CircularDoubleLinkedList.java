package 线性表.代码;

/**
 * @author lcl100
 * @create 2022-03-04 21:41
 */
public class CircularDoubleLinkedList {
    CDLNode list;

    /**
     * 循环双链表的初始化函数
     */
    public void init() {
        // 1.初始化循环双链表，即创建头结点。头结点的前驱节点指针和后继节点指针都指向自身，表示循环
        // 1.1 为头结点分配空间
        list = new CDLNode();
        // 1.2 将头结点的 prior 指针指向自身
        list.prior = list;// 注意，将头结点的 prior 和 next 指针指向自身
        // 1.3 将头结点的 next 指针指向自身
        list.next = list;
    }

    /**
     * 通过头插法创建循环双链表
     *
     * @param nums 待插入到双链表中的数据数组
     * @return 创建成功的循环双链表
     */
    public CDLNode createByHead(int... nums) {
        // 1. 初始化循环双链表，即创建头结点，也可以直接调用 init 方法进行初始化
        // 1.1 为头结点分配空间
        list = new CDLNode();
        // 1.2 将头结点的 prior 指针指向自身
        list.prior = list;// 注意，将头结点的 prior 和 next 指针指向自身
        // 1.3 将头结点的 next 指针指向自身
        list.next = list;

        // 2.循环输入数组 nums，将每个元素插入到链表中
        for (int i = 0; i < nums.length; i++) {
            // 2.1 创建新节点
            // 2.1.1 给新节点分配空间
            CDLNode newNode = new CDLNode();
            // 2.1.2 给新节点的数据域指定内容
            newNode.data = nums[i];
            // 2.1.3 将新节点的 prior 指针指向 null
            newNode.prior = null;
            // 2.1.4 将新节点的 next 指针指向 null
            newNode.next = null;

            // 2.2 将新节点插入到链表的头部，即头结点的后面
            // 2.2.1 修改新节点的 next 指针，指向原链表的第一个节点
            newNode.next = list.next;
            // 2.2.2 修改新节点的 prior 指针，指向原链表的头结点
            newNode.prior = list;
            // 2.2.3 将原链表的第一个节点的 prior 指针指向新节点
            list.next.prior = newNode;
            // 2.2.4 将头节点的 next 指针指向新节点
            list.next = newNode;
        }

        // 3.返回创建成功的循环双链表
        return list;
    }

    /**
     * 通过尾插法创建循环双链表
     *
     * @param nums 待插入到双链表中的数据数组
     * @return 创建成功的循环双链表
     */
    public CDLNode createByTail(int... nums) {
        // 1. 初始化循环双链表，即创建头结点，也可以直接调用 init 方法进行初始化
        // 1.1 为头结点分配空间
        list = new CDLNode();
        // 1.2 将头结点的 prior 指针指向自身
        list.prior = list;// 注意，将头结点的 prior 和 next 指针指向自身
        // 1.3 将头结点的 next 指针指向自身
        list.next = list;

        // 保存链表的尾节点，其实可以利用循环双链表的特性，直接使用 list.prior 来获得链表的尾节点
        CDLNode tailNode = list;

        // 2.循环输入数组 nums，将每个元素插入到链表中
        for (int i = 0; i < nums.length; i++) {
            // 2.1 创建新节点
            // 2.1.1 给新节点分配空间
            CDLNode newNode = new CDLNode();
            // 2.1.2 给新节点的数据域指定内容
            newNode.data = nums[i];
            // 2.1.3 将新节点的 prior 指针指向 null
            newNode.prior = null;
            // 2.1.4 将新节点的 next 指针指向 null
            newNode.next = null;

            // 2.2 将新节点插入到链表的尾部
            // 2.2.1 将链表原尾节点的 next 指针指向新节点
            tailNode.next = newNode;
            // 2.2.2 将新节点的 prior 指针指向链表原尾节点
            newNode.prior = tailNode;
            // 2.2.3 将新节点的 next 指针指向链表的头结点
            newNode.next = list;
            // 2.2.4 注意，将头结点的 prior 指针指向新节点（即新的尾节点），这样才能循环起来
            list.prior = newNode;
            // 2.2.5 更新记录链表尾节点的变量 tailNode
            tailNode = newNode;
        }

        // 3.返回创建成功的链表
        return list;
    }

    /**
     * 在第 i 个位置插入新节点
     *
     * @param i   待插入新节点的序号位置，从 1 开始
     * @param ele 新节点的数据值
     */
    public void insert(int i, int ele) throws Exception {
        // 0.参数校验
        if (i < 1 || i > size()) {
            throw new Exception("不存在第 " + i + " 个节点！");
        }

        // 1.查找第 i 个节点
        // 1.1 直接利用写好的函数查找第 i 个节点
        CDLNode node = findByNum(i);

        // 2.在第 i 个位置插入新节点。注意判断如果该节点存在才继续操作
        if (node != null) {
            // 2.1 创建新节点
            // 2.1.1 给新节点分配空间
            CDLNode newNode = new CDLNode();
            // 2.1.2 给新节点的数据域指定内容
            newNode.data = ele;
            // 2.1.3 将新节点的 prior 指针指向 null
            newNode.prior = null;
            // 2.1.4 将新节点的 next 指针指向 null
            newNode.next = null;

            // 2.2 将新节点插入到链表中
            // 2.2.1 将新节点的 prior 指针指向第 i-1 个节点（即第 i 个节点的前驱节点）
            newNode.prior = node.prior;
            // 2.2.2 将第 i-1 个节点的 next 指针指向新节点，此时完成了新节点与第 i-1 个节点的链接
            node.prior.next = newNode;
            // 2.2.3 将新节点的 next 指针指向第 i 个节点
            newNode.next = node;
            // 2.2.4 将第 i 个节点的 prior 指针指向新节点，此时完成了新节点与第 i 个节点的链接
            node.prior = newNode;
        }
    }

    /**
     * 插入新节点在链表中第一个节点的位置
     *
     * @param ele 新节点的数据值
     */
    public void insertFirst(int ele) {
        // 1 创建新节点
        // 1.1 给新节点分配空间
        CDLNode newNode = new CDLNode();
        // 1.2 给新节点的数据域指定内容
        newNode.data = ele;
        // 1.3 将新节点的 prior 指针指向 null
        newNode.prior = null;
        // 1.4 将新节点的 next 指针指向 null
        newNode.next = null;

        // 2.将新节点插入到链表的头部，即头结点的后面
        // 2.1 将新节点的 next 指针指向原链表的第一个节点
        newNode.next = list.next;
        // 2.2 将原链表的第一个节点的 prior 指针指向新节点，此时完成了新节点与原链表第一个节点的链接
        list.next.prior = newNode;
        // 2.3 将头结点的 next 指针指向新节点，即让新节点成为链表的第一个节点
        list.next = newNode;
        // 2.4 将新节点的 prior 指针指向链表头结点，此时完成了新节点与链表头结点的链接
        newNode.prior = list;
    }

    /**
     * 插入新节点在链表中最后一个节点的位置
     *
     * @param ele 新节点的数据值
     */
    public void insertLast(int ele) {
        // 1 创建新节点
        // 1.1 给新节点分配空间
        CDLNode newNode = new CDLNode();
        // 1.2 给新节点的数据域指定内容
        newNode.data = ele;
        // 1.3 将新节点的 prior 指针指向 null
        newNode.prior = null;
        // 1.4 将新节点的 next 指针指向 null
        newNode.next = null;

        // 2.把新节点插入到链表的尾部
        // 2.1 变量，记录循环双链表的尾节点，这里就是通过 list.prior 获得的链表尾节点
        CDLNode tailNode = list.prior;
        // 2.2 将链表尾节点的 next 指针指向新节点
        tailNode.next = newNode;
        // 2.3 将新节点的 prior 指针指向原尾节点，此时完成了原链表尾节点与新节点的链接（链接成功后，新节点就成为了链表的尾节点）
        newNode.prior = tailNode;
        // 2.4 将链表头结点的 prior 指针指向新节点，为了循环
        list.prior = newNode;
        // 2.5 将新节点的 next 指针指向头结点，为了循环
        newNode.next = list;
    }

    /**
     * 删除第 i 个位置的节点
     *
     * @param i 待删除节点的序号，从 1 开始
     * @return 如果删除成功则返回被删除的节点，否则返回 null
     */
    public CDLNode removeByNum(int i) throws Exception {
        // 0.参数校验
        // 0.1 判断链表是否为空
        if (list.next == list) {
            throw new Exception("链表为空不能删除！");
        }
        // 0.2 判断序号是否在范围内
        if (i < 1 || i > size()) {
            throw new Exception("不存在第 " + i + " 个节点！");
        }

        // 1.获取链表中第 i 个节点
        // 1.1 直接利用写好的函数获取第 i 个节点
        CDLNode node = findByNum(i);

        // 2.删除指定序号的节点。如果被删除节点存在则继续操作，否则直接返回 null
        if (node != null) {
            // 2.1 删除节点 node
            // 2.1.1 将被删除节点的后继节点的 prior 指针指向被删除节点的前驱节点
            node.next.prior = node.prior;
            // 2.1.2 将被删除节点的前驱节点的 next 指针指向被删除节点的后继节点
            node.prior.next = node.next;

            // 2.2返回被删除的节点
            return node;
        }

        return null;
    }

    /**
     * 删除值为 ele 的节点
     *
     * @param ele 指定值
     * @return 如果删除成功则返回被删除的节点，否则返回 null
     */
    public CDLNode removeByEle(int ele) throws Exception {
        // 0.参数校验
        if (list.next == list) {
            throw new Exception("链表为空不能删除！");
        }

        // 变量，保存链表的第一个节点，遍历循环需要
        CDLNode node = list.next;

        // 1.遍历链表所有节点，查找值等于 ele 的节点，也可以直接使用 findByEle 函数来获取该节点
        while (node != list) {// 注意，循环结束的条件
            // 1.1 如果找到值等于 ele 的链表节点
            if (node.data == ele) {
                // 1.1.1 变量，获取 node 节点的前驱节点和后继节点
                // 1.1.1.1 记录 node 节点的前驱节点
                CDLNode preNode = node.prior;
                // 1.1.1.2 记录 node 节点的后继节点
                CDLNode nextNode = node.next;

                // 1.1.2 删除 node 节点
                // 1.1.2.1 将节点 preNode 的 next 指针指向节点 nextNode
                preNode.next = nextNode;
                // 1.1.2.2 将节点 nextNode 的 prior 指针指向节点 preNode
                nextNode.prior = preNode;

                // 1.1.3 返回被删除的节点
                return node;
            }
            // 1.2 继续链表的下一个节点
            node = node.next;
        }
        return null;
    }

    /**
     * 删除链表的第一个节点
     *
     * @return 返回被删除的节点
     */
    public CDLNode removeFirst() throws Exception {
        // 0.参数校验
        if (list.next == list) {
            throw new Exception("链表为空不能删除！");
        }

        // 1.删除链表第一个节点
        // 1.1 变量，记录链表的第一个节点
        CDLNode firstNode = list.next;
        // 1.2 将头结点的 next 指针指向第一个节点的后继节点
        list.next = firstNode.next;
        // 1.3 将第一个节点的后继节点的 prior 指针指向链表的头结点，这样就删除了链表的第一个节点
        firstNode.next.prior = list;
        // 1.4 返回被删除节点，即链表的第一个节点
        return firstNode;
    }

    /**
     * 删除链表的最后一个节点
     *
     * @return 返回被删除的节点
     * @throws Exception 如果链表为空则抛出异常
     */
    public CDLNode removeLast() throws Exception {
        // 0.参数校验
        if (list.next == list) {
            throw new Exception("链表为空不能删除！");
        }

        // 1.删除链表最后一个节点
        // 1.1 变量，记录链表的最后一个节点
        CDLNode lastNode = list.prior;
        // 1.2 将链表头结点的 prior 指针指向 lastNode 节点的前驱节点
        list.prior = lastNode.prior;
        // 1.3 将 lastNode 节点的 next 指针指向链表头结点，这样就删除了链表的最后一个节点
        lastNode.prior.next = list;
        // 1.4 返回被删除节点，即链表的最后一个节点
        return lastNode;
    }

    /**
     * 求第一个值为 ele 的节点的前驱节点
     *
     * @param ele 指定值
     * @return 如果找到值为 ele 的节点则返回它的前驱节点，否则返回 null
     */
    public CDLNode getPrior(int ele) {
        // 1.找到值为 ele 的节点
        // 1.1 直接利用已经写好的函数查找值为 ele 的节点
        CDLNode node = findByEle(ele);

        // 2.获取值为 ele 的节点的前驱节点。如果返回结果为 null，表示不存在值为 ele 的节点，则直接返回 null
        if (node != null) {
            // 2.1 直接返回 node 节点的 prior 指针所指向的节点，就是它的前驱节点
            return node.prior;
        }
        return null;
    }

    /**
     * 求第一个值为 ele 的节点的后继节点
     *
     * @param ele 指定值
     * @return 如果找到值为 ele 的节点则返回它的后继节点，否则返回 null
     */
    public CDLNode getNext(int ele) {
        // 1.找到值为 ele 的节点
        // 1.1 直接利用已经写好的函数查找值为 ele 的节点
        CDLNode node = findByEle(ele);

        // 2.获取值为 ele 的节点的后继节点。如果返回结果为 null，表示不存在值为 ele 的节点，则直接返回 null
        if (node != null) {
            // 2.1 直接返回 node 节点的 next 指针所指向的节点，就是它的后继节点
            return node.next;
        }
        return null;
    }

    /**
     * 根据序号查找第 i 个节点
     *
     * @param i 指定序号，从 1 开始
     * @return 如果成功查找到节点则返回，否则返回 null
     * @throws Exception 如果序号超出指定范围，则抛出异常
     */
    public CDLNode findByNum(int i) throws Exception {
        // 0.参数校验
        if (i < 1 || i > size()) {
            throw new Exception("不存在第 " + i + " 个节点！");
        }

        // 变量，记录链表的每一个节点，从链表的第一个节点开始
        CDLNode node = list.next;
        // 变量，计数器，记录节点个数
        int count = 0;

        // 1.遍历链表所有节点
        while (node != null) {
            // 1.1 计数器加1，表示已经遍历一个节点
            count++;
            // 1.2 比较计数器的值与参数传入的值是否相等，如果相等则表示找到第 i 个节点了
            if (count == i) {
                return node;
            }
            // 1.3 继续链表的下一个节点
            node = node.next;
        }
        return null;
    }

    /**
     * 根据值查找指定节点
     *
     * @param ele 指定值
     * @return 如果查找成功则返回对应值的节点，否则返回 null
     */
    public CDLNode findByEle(int ele) {
        // 链表的第一个节点
        CDLNode node = list.next;
        // 遍历链表所有节点，寻找节点值等于 ele 的节点
        while (node != list) {
            // 判断当前节点的数据域值是否等于指定值
            if (node.data == ele) {
                return node;
            }
            // 继续下一个节点
            node = node.next;
        }
        return null;
    }

    /**
     * 获取链表节点个数
     *
     * @return 链表长度
     */
    public int size() {
        // 记录链表的节点个数
        int count = 0;
        // 链表的第一个节点
        CDLNode node = list.next;
        // 遍历链表所有节点，统计个数
        while (node != list) {
            // 节点个数加 1
            count++;
            // 继续下一个节点
            node = node.next;
        }
        // 返回统计结果
        return count;
    }

    /**
     * 判断循环双链表是否为空
     *
     * @return 如果循环双链表为空则返回 true，否则返回 false
     */
    public boolean isEmpty() {
        // 即判断链表的头节点是否指向自身，或者 list.prior==list 也是可以的
        return list.next == list;
    }

    /**
     * 清空循环双链表所有节点
     */
    public void clear() {
        // 链表的第一个节点
        CDLNode node = list.next;
        // 遍历链表所有节点
        while (node != list) {
            // 临时保存当前节点的后继节点
            CDLNode temp = node.next;
            // 释放当前节点的空间
            node.prior = null;
            node.next = null;
            node.data = 0;
            // 继续下一个节点
            node = temp;
        }
        // 将链表头结点的 prior 和 next 指针指向自身
        list.prior = list;
        list.next = list;
    }

    /**
     * 打印循环双链表的所有节点
     */
    public void print() {
        // 链表的第一个节点
        CDLNode node = list.next;
        // 循环链表，输出链表所有节点值
        String str = "[";
        while (node != list) {// 注意，判断循环结束的条件是不等于头结点
            str += node.data;
            if (node.next != list) {
                str += ", ";
            }
            node = node.next;
        }
        str += "]";
        System.out.println(str);
    }
}

/**
 * 循环双链表节点
 */
class CDLNode {
    /**
     * 数据域
     */
    int data;
    /**
     * 指针域，指向当前节点的前驱节点
     */
    CDLNode prior;
    /**
     * 指针域，指向当前节点的后继节点
     */
    CDLNode next;
}
