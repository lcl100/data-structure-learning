package 栈.代码;

/**
 * @author lcl100
 * @desc 共享栈测试类
 * @create 2022-04-21 22:59
 */
public class SharedStackTest {
    public static void main(String[] args) throws Exception {
        // 声明并初始化共享栈
        SharedStack stack = new SharedStack();
        stack.init();

        // 将元素存入0号栈
        System.out.println("\n将元素存入0号栈：");
        stack.push(0, 11);
        stack.print(0);
        stack.push(0, 22);
        stack.print(0);
        stack.push(0, 33);
        stack.print(0);
        stack.push(0, 44);
        stack.print(0);
        stack.push(0, 55);
        stack.print(0);

        // 将元素存入1号栈
        System.out.println("\n将元素存入1号栈：");
        stack.push(1, 555);
        stack.print(1);
        stack.push(1, 444);
        stack.print(1);
        stack.push(1, 333);
        stack.print(1);
        stack.push(1, 222);
        stack.print(1);
        stack.push(1, 111);
        stack.print(1);

        // 共享栈是否满
        System.out.println("\n共享栈是否满：");
        boolean full;
        full = stack.isFull();
        System.out.println(full);

        // 将0号栈的元素出栈
        System.out.println("\n将0号栈的元素出栈：");
        int top0;
        top0 = stack.pop(0);
        System.out.println("top0: " + top0);
        stack.print(0);
        top0 = stack.pop(0);
        System.out.println("top0: " + top0);
        stack.print(0);
        top0 = stack.pop(0);
        System.out.println("top0: " + top0);
        stack.print(0);

        // 将1号栈的元素出栈
        System.out.println("\n将1号栈的元素出栈：");
        int top1;
        top1 = stack.pop(1);
        System.out.println("top1: " + top1);
        stack.print(1);
        top1 = stack.pop(1);
        System.out.println("top1: " + top1);
        stack.print(1);
        top1 = stack.pop(1);
        System.out.println("top1: " + top1);
        stack.print(1);

        // 0号栈是否空
        System.out.println("\n0号栈是否空：");
        boolean empty0;
        empty0 = stack.isEmpty(0);
        System.out.println(empty0);

        // 1号栈是否空
        System.out.println("\n1号栈是否空：");
        boolean empty1;
        empty1 = stack.isEmpty(1);
        System.out.println(empty1);

        // 获取0号栈栈顶元素
        System.out.println("\n获取0号栈栈顶元素：");
        top0 = stack.getTop(0);
        System.out.println(top0);

        // 获取1号栈栈顶元素
        System.out.println("\n获取1号栈栈顶元素：");
        top1 = stack.getTop(1);
        System.out.println(top1);

        // 获取0号栈中元素个数
        System.out.println("\n获取0号栈中元素个数：");
        int len0;
        len0 = stack.size(0);
        System.out.println(len0);

        // 获取1号栈中元素个数
        System.out.println("\n获取1号栈中元素个数：");
        int len1;
        len1 = stack.size(1);
        System.out.println(len1);

        // 获取共享栈中的总元素个数
        System.out.println("\n获取共享栈中的总元素个数：");
        int len;
        len = stack.size(0) + stack.size(1);
        System.out.println(len);

        // 清空0号栈
        System.out.println("\n清空0号栈：");
        stack.clear(0);
        stack.print(0);

        // 清空1号栈
        System.out.println("\n清空1号栈：");
        stack.clear(1);
        stack.print(1);
    }
}
