package 线性表.代码;

/**
 * @author lcl100
 * @desc 循环单链表
 * @create 2022-03-03 20:20
 */
public class CircularLinkedList {
    private CLNode list;

    /**
     * 初始化循环单链表
     */
    public void init() {
        // 初始化循环单链表
        // 1.1 为头结点分配空间
        list = new CLNode();
        // 1.2 修改头结点的 next 指针，将其指向自己，而普通单链表是指向 null
        list.next = list;// 注意，这里同单链表不同的是，指向了自己
    }

    /**
     * 通过头插法创建循环单链表
     *
     * @param nums 待插入到单链表中的数据数组
     * @return 创建成功的循环单链表
     */
    public CLNode createByHead(int... nums) {
        // 1.初始化循环单链表，即创建循环单链表的头结点。也可以直接调用 init 函数来初始化
        // 1.1 为头结点分配空间
        list = new CLNode();
        // 1.2 修改头结点的 next 指针，将其指向自己，而普通单链表是指向 null
        list.next = list;// 注意，这里同单链表不同的是，指向了自己

        // 2.遍历 nums 数组中所有元素，将其添加到链表中，完成链表的创建
        for (int i = 0; i < nums.length; i++) {
            // 2.1 创建新节点
            // 2.1.1 给新节点分配空间
            CLNode newNode = new CLNode();
            // 2.1.2 指定新节点的数据域
            newNode.data = nums[i];
            // 2.1.3 将新节点的指针域置为 null，指向空
            newNode.next = null;

            // 2.2 将新节点插入到链表中，但是插入到头结点的后面
            // 2.2.1 临时节点，保存头节点的后继节点（即链表的第一个节点）
            CLNode temp = list.next;
            // 2.2.2 将头结点的 next 指针指向新节点，即将让新节点成为链表的第一个节点
            list.next = newNode;
            // 2.2.3 将新节点的 next 指针指向临时节点（即原来的第一个节点）
            newNode.next = temp;
        }

        // 3.返回创建成功的单链表
        return list;
    }

    /**
     * 通过尾插法创建循环单链表
     *
     * @param nums 待插入到单链表中的数据数组
     * @return 创建成功的循环单链表
     */
    public CLNode createByTail(int... nums) {
        // 1.初始化循环单链表，即创建循环单链表的头结点。也可以直接调用 init 函数来初始化
        // 1.1 为头结点分配空间
        list = new CLNode();
        // 1.2 修改头结点的 next 指针，将其指向自己，而普通单链表是指向 null
        list.next = list;// 注意，这里同单链表不同的是，指向了自己

        // 保存链表的尾节点，初始为链表的头节点，即空链表的尾节点就是链表的头节点
        CLNode tailNode = list;

        // 2.循环数组 nums 中所有数据，插入到单链表中
        for (int i = 0; i < nums.length; i++) {
            // 2.1 创建新节点
            // 2.1.1 给新节点分配空间
            CLNode newNode = new CLNode();
            // 2.1.2 指定新节点的数据域
            newNode.data = nums[i];
            // 2.1.3 将新节点的指针域置为 null，指向空
            newNode.next = null;

            // 2.2 将新节点追加到链表的尾部
            // 2.2.1 将链表原尾节点的 next 指针指向新节点，即让新节点成为链表的尾节点
            tailNode.next = newNode;
            // 2.2.2 然后将新节点（即链表新的尾节点）指向链表的头节点
            newNode.next = list;
            // 2.2.3 然后将 tailNode 指向新节点（即新的尾节点）
            tailNode = newNode;
        }

        // 3.返回创建成功的链表
        return list;
    }

    /**
     * 向链表的第 i 个位置插入新节点
     *
     * @param i   序号，从 1 开始
     * @param ele 新节点的数据值
     * @throws Exception 如果序号 i 超过范围则抛出该异常
     */
    public void insert(int i, int ele) throws Exception {
        // 0.参数校验
        if (i < 1 || i > size()) {
            throw new Exception("不存在第 " + i + " 个节点！");
        }

        // 1.声明一些变量
        // 1.1 链表的第一个节点
        CLNode node = list.next;
        // 1.2 保存前驱节点，初始为链表的头节点
        CLNode pre = list;
        // 1.3 计数器，记录当前节点是链表的第几个节点
        int count = 0;

        // 2.遍历链表所有节点，找到第 i 个节点，然后插入新节点
        while (node != list) {
            // 2.1 计数器加 1，表示已经迭代一个节点了
            count++;
            // 2.2 找到第 i 个节点，那么就可以插入新节点了
            if (count == i) {
                // 2.2.1 创建新节点
                // 2.2.1.1 给新节点分配空间
                CLNode newNode = new CLNode();
                // 2.2.1.2 给新节点的数据域赋值
                newNode.data = ele;
                // 2.2.1.3 给新节点的指针域赋为 null
                newNode.next = null;

                // 2.2.2 将新节点插入到链表中
                // 2.2.2.1 将第 i-1 个节点的 next 指针指向新节点
                pre.next = newNode;
                // 2.2.2.2 将新节点的 next 指针指向原第 i 个节点
                newNode.next = node;

                // 2.2.3 结束循环，跳出程序
                break;
            }
            // 2.3 保存当前节点为前驱节点
            pre = node;
            // 2.4 继续下一个节点
            node = node.next;
        }
    }

    /**
     * 在循环单链表的头部插入新节点
     *
     * @param ele 待插入的元素
     */
    public void insertFirst(int ele) {
        // 1.创建新节点
        // 1.1 为新节点分配空间
        CLNode newNode = new CLNode();
        // 1.2 为新节点的数据域指定内容
        newNode.data = ele;
        // 1.3 将新节点的指针域指向 null
        newNode.next = null;

        // 2.将新节点插入到链表的头部，成为新的链表第一个节点
        // 2.1 将新节点的 next 指针指向原链表的第一个节点
        newNode.next = list.next;
        // 2.2 将头节点的 next 指针指向新节点，即让新节点成为链表的第一个节点
        list.next = newNode;
    }

    /**
     * 向循环单链表末尾追加一个新节点
     *
     * @param ele 新节点的数据值
     */
    public void insertLast(int ele) {
        // 1.先找到链表的最后一个节点，即尾节点
        // 1.1 链表的第一个节点
        CLNode node = list.next;
        // 1.2 通过循环找到链表的最后一个节点，注意这里循环结束的条件是 node.next!=list，在循环结束之后，node 就是链表的尾节点
        while (node.next != list) {
            node = node.next;
        }

        // 2.创建新节点然后插入到链表的尾部
        // 2.1 创建新节点
        // 2.1.1 为新节点分配空间
        CLNode newNode = new CLNode();
        // 2.1.2 为新节点的数据域指定内容
        newNode.data = ele;
        // 2.1.3 将新节点的指针域指向 null
        newNode.next = null;

        // 2.2 将新节点追加到循环单链表的末尾
        // 2.2.1 将链表的原尾节点的 next 指针指向新节点，已经完成了新节点链接到链表中
        node.next = newNode;
        // 2.2.2 将新节点的 next 指针指向链表的头节点，完成了尾节点与头节点的链接
        newNode.next = list;
    }

    /**
     * 删除循环单链表中第 i 个节点
     *
     * @param i 指定序号，从 1 开始
     * @return 如果找到被删除节点并删除成功则返回该节点，否则返回 null
     * @throws Exception 如果序号 i 超过范围则抛出异常
     */
    public CLNode removeByNum(int i) throws Exception {
        // 0.参数校验
        if (i < 1 || i > size()) {
            throw new Exception("不存在第 " + i + " 个节点！");
        }

        // 1.声明一些变量
        // 1.1 链表的第一个节点
        CLNode node = list.next;
        // 1.2 保存前驱节点，初始为链表的头节点
        CLNode pre = list;
        // 1.3 计数器，记录当前是链表的第几个节点
        int count = 0;

        // 2.遍历链表，寻找第 i 个节点，通过循环计数的方式来找到
        while (node != list) {
            // 2.1 计数器加 1
            count++;
            // 2.2 找到待删除节点，即比较计数器与参数值是否相等，如果相等则删除节点
            if (count == i) {
                // 2.2.1 删除 node 节点，即将第 i-1 个节点的 next 指针指向第 i+1 个节点，这样就删除了第 i 个节点
                pre.next = node.next;
                // 2.2.2 返回被删除的节点
                return node;
            }
            // 2.3 保存当前节点为前驱节点
            pre = node;
            // 2.4 继续下一个节点
            node = node.next;
        }
        return null;
    }

    /**
     * 根据值删除循环单链表元素
     *
     * @param ele 指定值
     * @return 被删除节点
     */
    public CLNode removeByEle(int ele) {
        // 0.声明一些变量
        // 0.1 链表的第一个节点，其实主要用于遍历链表
        CLNode node = list.next;
        // 0.1 保存值等于 ele 的节点的前驱节点
        CLNode pre = list;

        // 1.循环链表，查找节点值等于 ele 的节点，然后进行删除
        while (node != list) {
            // 1.1 如果找到值等于 ele 的节点
            if (node.data == ele) {
                // 1.1.1 删除 node 节点，即将第 i-1 个节点的 next 指针指向第 i+1 个节点，这样就删除了第 i 个节点
                pre.next = node.next;
                // 1.1.2 返回被删除节点
                return node;
            }
            // 1.2 保存当前节点为前驱节点
            pre = node;
            // 1.3 继续链表的下一个节点
            node = node.next;
        }
        return null;
    }

    /**
     * 删除链表的第一个节点
     *
     * @return 被删除的节点
     */
    public CLNode removeFirst() {
        // 链表的第一个节点
        CLNode node = list.next;
        // 删除第一个节点，即将链表的头节点的 next 指针指向原链表的第二个节点（即让原链表第二个节点成为新的链表第一个节点）
        list.next = node.next;
        // 其中 node 就是被删除的节点，最后返回被删除的节点
        return node;
    }

    /**
     * 删除循环单链表的尾节点
     *
     * @return 被删除的节点
     */
    public CLNode removeLast() {
        // 0.声明一些变量
        // 0.1 链表的第一个节点
        CLNode node = list.next;
        // 0.2 记录尾节点的前驱节点
        CLNode pre = list;

        // 1.找到链表的尾节点和尾节点的前驱节点
        while (node.next != list) {// 注意循环结束的条件是 node.next!=list，当循环结束之后 node 就是链表的尾节点
            // 1.1 保存当前节点为前驱节点
            pre = node;
            // 1.2 继续链表的下一个节点
            node = node.next;
        }

        // 2.删除链表的尾节点，即将倒数第二个节点的 next 指针指向链表的头节点，这样就删除了链表的最后一个节点
        pre.next = list;

        // 3.返回被删除节点，即尾节点
        return node;
    }

    /**
     * 通过序号在链表中检索节点
     *
     * @param i 序号，从 1 开始
     * @return 果找到则返回对应序号的节点，如果没有找到则返回 null
     * @throws Exception 如果序号 i 超出范围则抛出该异常
     */
    public CLNode findByNum(int i) throws Exception {
        //0.参数校验
        if (i < 1 || i > size()) {
            throw new Exception("不存在第 " + i + " 个节点！");
        }

        // 1.声明一些变量
        // 1.1 链表的第一个节点
        CLNode node = list.next;
        // 1.2 计数器，记录当前正在遍历的节点是链表的第几个节点
        int count = 0;

        // 2.遍历链表所有节点，找到第 i 个节点
        while (node != list) {
            // 2.1 计数器加 1，表示已经迭代了一个节点
            count++;
            // 2.2 比较计数器的值与参数值是否相等，如果相等则表示找到了第 i 个节点则返回该节点
            if (count == i) {
                return node;
            }
            // 2.3 继续下一个节点
            node = node.next;
        }

        return null;
    }

    /**
     * 通过数据值在链表中检索节点
     *
     * @param ele 指定数据值
     * @return 如果找到则返回对应值的节点，如果没有找到则返回 null
     */
    public CLNode findByEle(int ele) {
        // 链表的第一个节点
        CLNode node = list.next;

        // 1.遍历链表所有节点，比较节点的值与输入的参数值是否相等，如果相等则返回该节点
        while (node != list) {
            // 1.1 比较当前节点的数据域是否与参数值相等，如果相等则表示找到指定值的节点，那么返回即可
            if (node.data == ele) {
                return node;
            }
            // 1.2 继续下一个节点
            node = node.next;
        }

        return null;
    }

    /**
     * 统计循环单链表的节点个数
     *
     * @return 链表的长度
     */
    public int size() {
        // 计数器，记录链表的节点个数
        int count = 0;
        // 链表的第一个节点
        CLNode node = list.next;
        // 遍历链表所有节点，统计个数，注意结束循环的条件
        while (node != list) {
            // 统计个数
            count++;
            // 继续下一个节点
            node = node.next;
        }
        // 返回节点个数
        return count;
    }

    /**
     * 判断链表是否为空
     *
     * @return 如果为空则返回 true，否则返回 false
     */
    public boolean isEmpty() {
        // 判断链表的第一个节点是否又是头结点，如果是则表示链表为空
        return list.next == list;
    }

    /**
     * 清空单链表
     */
    public void clear() {
        // 链表的第一个节点
        CLNode node = list.next;
        // 循环遍历链表所有节点，释放空间
        while (node != list) {
            // 临时保存当前节点的后继节点
            CLNode temp = node.next;
            // 释放当前节点
            node.next = null;
            node.data = 0;
            // 继续处理当前节点的下一个节点
            node = temp;
        }
        // 将头节点的 next 指针指向本身，仍然是循环单链表
        list.next = list;
    }

    /**
     * 打印循环单链表
     */
    public void print() {
        // 链表的第一个节点
        CLNode node = list.next;
        // 循环单链表，打印单链表的每个节点的数据值
        String str = "[";
        while (node != list) {
            str += node.data;
            if (node.next != list) {
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
 * 循环单链表节点
 */
class CLNode {
    /**
     * 节点的数据域
     */
    int data;
    /**
     * 节点的指针域，指向后继节点
     */
    CLNode next;
}
