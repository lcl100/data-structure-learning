package 栈.代码;

/**
 * @author lcl100
 * @desc 链栈
 * @create 2022-04-15 22:00
 */
public class LinkedStack {
    /**
     * 声明链栈
     */
    private LNode stack;

    /**
     * 初始化链栈
     */
    public void init() {
        // 1.创建链栈头结点，为其分配空间
        stack = new LNode();
        // 2.将链栈头结点的 next 指针指向 null，表示是空栈
        stack.next = null;
    }

    /**
     * 判断链栈是否为空
     *
     * @return 如果链栈为空则返回 true，否则返回 false
     */
    public boolean isEmpty() {
        // 即只需要判断链栈的栈顶结点是否为空
        return stack.next == null;
    }

    /**
     * 将元素入栈
     *
     * @param ele 待入栈的元素值
     */
    public void push(int ele) {
        // 1.创建新结点
        // 1.1 为新结点分配空间
        LNode newNode = new LNode();
        // 1.2 为新结点指定数据域
        newNode.data = ele;
        // 1.3 为新结点指定初始指针域，即指向 null
        newNode.next = null;

        // 2.将新结点入栈
        // 2.1 将新结点的 next 指针指向原栈顶结点，完成新结点与原栈顶结点的链接
        newNode.next = stack.next;
        // 2.2 将链栈头结点的 next 指针指向新结点，即新结点成为了链栈的新栈顶结点
        stack.next = newNode;
    }

    /**
     * 将元素出栈
     *
     * @return 栈顶结点的元素值
     * @throws Exception 如果链栈为空则不能出栈抛出该异常
     */
    public int pop() throws Exception {
        // 0.变量，记录栈顶结点
        LNode topNode = stack.next;
        // 1.判断链栈是否为空，分情况处理
        // 1.1 如果栈空，则抛出异常
        if (topNode == null) {
            throw new Exception("栈为空，不能出栈！");
        }
        // 1.2 如果栈不为空，则出栈栈顶元素
        else {
            // 1.2.1 保存栈顶结点的数据值，待返回
            int topNodeData = topNode.data;
            // 1.2.2 删除栈顶结点
            stack.next = topNode.next;
            // 1.2.3 释放栈顶结点空间
            topNode.next = null;
            topNode = null;
            // 1.2.4 返回栈顶结点的数据值
            return topNodeData;
        }
    }

    /**
     * 获取栈顶结点的数据值
     *
     * @return 栈顶结点的数据值
     * @throws Exception
     */
    public int getTop() throws Exception {
        // 1.如果链栈为空，则抛出异常
        if (stack.next == null) {
            throw new Exception("栈为空，没有栈顶元素！");
        }
        // 2.如果链栈不为空，则返回栈顶结点值
        return stack.next.data;
    }

    /**
     * 获取链栈的结点个数
     *
     * @return 链栈结点个数
     */
    public int size() {
        // 0.变量，计数器，记录链栈中结点个数
        int len = 0;
        // 0.变量，记录链栈的栈顶结点
        LNode topNode = stack.next;
        // 1.从栈顶扫描到栈底，统计链栈中结点个数
        while (topNode != null) {
            len++;
            topNode = topNode.next;
        }
        // 2.返回结点个数
        return len;
    }

    /**
     * 打印链栈所有结点
     */
    public void print() {
        System.out.print("[");
        LNode topNode = stack.next;
        while (topNode != null) {
            System.out.print(topNode.data);
            if (topNode.next != null) {
                System.out.print(", ");
            }
            topNode = topNode.next;
        }
        System.out.print("]\n");
    }

    /**
     * 清空链栈
     */
    public void clear() {
        // 变量，记录链栈的栈顶结点
        LNode topNode = stack.next;
        // 从栈顶到栈底扫描栈中所有结点
        while (topNode != null) {
            // 记录当前结点的后继结点
            LNode temp = topNode.next;
            // 释放当前结点的存储空间
            topNode.next = null;
            topNode = null;
            // 继续栈的下一个结点
            topNode = temp;
        }
        // 最后将链栈头结点的 next 指针指向 null，表示这是一个空栈
        stack.next = null;
    }

    /**
     * 销毁链栈
     */
    public void destroy() {
        // 即将链栈的头结点指向 null
        stack.next = null;
        stack = null;
    }
}

/**
 * 链栈结点定义
 */
class LNode {
    /**
     * 结点数据域，数据类型为整型，也可以定义为其他类型
     */
    int data;
    /**
     * 结点指针域，指向结点的后继结点
     */
    LNode next;
}