package 栈.代码;

/**
 * @author lcl100
 * @desc 顺序栈测试类
 * @create 2022-04-12 21:59
 */
public class SeqStackTest {
    public static void main(String[] args) throws Exception {
        // 声明一个栈
        SeqStack stack = new SeqStack();

        // 初始化栈
        System.out.println("初始化栈：");
        stack.init();
        stack.print();

        // 将元素入栈
        System.out.println("将元素入栈：");
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
        int ele;
        System.out.println("将元素出栈：");
        ele = stack.pop();
        stack.print();
        ele = stack.pop();
        stack.print();
        ele = stack.pop();
        stack.print();

        // 栈是否为空
        boolean empty;
        System.out.println("栈是否为空：");
        empty = stack.isEmpty();
        System.out.println(empty);

        // 获取栈顶元素
        int top;
        System.out.println("获取栈顶元素：");
        top = stack.getTop();
        System.out.println(top);

        // 获取栈中元素个数
        int len;
        System.out.println("获取栈中元素个数：");
        len = stack.size();
        System.out.println(len);

        // 清空栈
        System.out.println("清空栈：");
        stack.clear();
        stack.print();
    }
}
