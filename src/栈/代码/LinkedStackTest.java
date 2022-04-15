package 栈.代码;

/**
 * @author lcl100
 * @desc 链栈测试类
 * @create 2022-04-15 22:00
 */
public class LinkedStackTest {
    public static void main(String[] args) throws Exception {
        // 声明链栈
        LinkedStack stack = new LinkedStack();

        // 初始化链栈
        System.out.println("\n初始化链栈：");
        stack.init();
        stack.print();

        // 将元素入栈
        System.out.println("\n将元素入栈：");
        stack.push(11);
        stack.print();
        stack.push(22);
        stack.print();
        stack.push(33);
        stack.print();
        stack.push(44);
        stack.print();
        stack.push(55);
        stack.print();

        // 将元素出栈
        System.out.println("\n将元素出栈：");
        int ele;
        ele = stack.pop();
        stack.print();
        ele = stack.pop();
        stack.print();
        ele = stack.pop();
        stack.print();

        // 链栈是否为空
        System.out.println("\n链栈是否为空：");
        boolean empty;
        empty = stack.isEmpty();
        System.out.println(empty);

        // 获取栈顶结点数据
        System.out.println("\n获取栈顶结点数据：");
        int top;
        top = stack.getTop();
        System.out.println(top);

        // 获取链栈中元素个数
        System.out.println("\n获取链栈中元素个数：");
        int len;
        len = stack.size();
        System.out.println(len);

        // 清空链栈
        System.out.println("\n清空链栈：");
        stack.clear();
        stack.print();

        // 销毁链栈
        System.out.println("\n销毁链栈：");
        stack.destroy();
    }
}
