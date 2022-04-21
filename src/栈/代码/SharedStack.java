package 栈.代码;

/**
 * @author lcl100
 * @desc 共享栈
 * @create 2022-04-21 22:40
 */
public class SharedStack {
    /**
     * 常量，顺序栈所能容纳的最大元素个数
     */
    private final int MAXSIZE = 100;

    /**
     * 声明一个顺序栈
     */
    private Stack stack;

    /**
     * 初始化共享栈
     */
    public void init() {
        // 0.实例化对象，并为数组分配空间
        stack = new Stack();
        stack.data = new int[MAXSIZE];
        stack.top = new int[2];

        // 1.需要同时初始化 0 号栈和 1 号栈
        // 1.1 将 0 号栈的栈顶指针指向 -1，表示 0 号栈是空栈
        stack.top[0] = -1;
        // 1.2 将 1 号栈的栈顶指针指向 MAXSIZE，表示 1 号栈是空栈
        stack.top[1] = MAXSIZE;
    }

    /**
     * 判断指定序号的栈是否是空栈
     *
     * @param NUM 栈序号，只能传入 0 或者 1
     * @return 如果指定栈是空栈则返回 true，否则返回 false 表示非空栈
     * @throws Exception 如果序号不合法则抛出此异常
     */
    public boolean isEmpty(int NUM) throws Exception {
        // 参数校验，如果 NUM 为其他不合法值则抛出异常
        if (NUM < 0 || NUM > 1) {
            throw new Exception("栈序号 NUM 非法：" + NUM);
        }
        if (NUM == 0) {
            // 0 号栈为空栈的条件是，栈顶指针指向 -1
            return stack.top[0] == -1;
        } else {
            // 1 号栈为空栈的条件是，栈顶指针指向 MAXSIZE
            return stack.top[1] == MAXSIZE;
        }
    }

    /**
     * 判断共享栈是否满
     *
     * @return 如果是栈满则返回 1，否则返回 0 表示栈未满
     */
    public boolean isFull() {
        // 如果 0 号栈和 1 号栈的栈顶元素相邻，则表示栈已满
        return stack.top[1] - stack.top[0] == 1;
    }

    /**
     * 将元素压入栈
     *
     * @param NUM 栈序号，只能传入 0 或者 1
     * @param ele 新元素
     * @throws Exception 如果栈满再入栈则抛出此异常
     */
    public void push(int NUM, int ele) throws Exception {
        // 0.参数校验，如果栈满则不能入栈
        if (isFull()) {
            throw new Exception("栈满则不能出栈！");
        }
        // 1.根据栈序号是 0 还是 1，来决定将元素存入哪个栈
        // 1.1 将元素存入 0 号栈
        if (NUM == 0) {
            // 1.1.1 先移动 0 号栈的栈顶指针。由于 0 号栈是从 -1 开始的，所以栈顶指针是往后增
            stack.top[0]++;
            // 1.1.2 再赋值
            stack.data[stack.top[0]] = ele;
        }
        // 1.2 将元素存入 1 号栈
        else if (NUM == 1) {
            // 1.2.1 先移动 1 号栈的栈顶指针。由于 1 号栈是从 MAXSIZE 开始的，所以栈顶指针是往前减
            stack.top[1]--;
            // 1.2.2 再赋值
            stack.data[stack.top[1]] = ele;
        }
    }

    /**
     * 将元素出栈
     *
     * @param NUM 栈序号，只能传入 0 或者 1
     * @return 返回栈顶元素
     * @throws Exception 如果栈空则抛出此异常或者栈序号不合法也会抛出该异常
     */
    public int pop(int NUM) throws Exception {
        // 0.参数校验，如果任何一个栈栈空则不能出栈
        if (isEmpty(NUM)) {
            throw new Exception("栈空没有可出栈元素！");
        }

        // 变量，存储栈顶元素
        int top = 0;

        // 1.根据栈序号来决定将哪个栈的栈顶元素出栈
        // 1.1 如果要将 0 号栈的栈顶元素出栈
        if (NUM == 0) {
            // 1.1.1 用 ele 保存 0 号栈的栈顶元素
            top = stack.data[stack.top[0]];
            // 1.1.2 移动栈顶指针删除元素
            stack.top[0]--;
        }
        // 1.2 如果要将 1 号栈的栈顶元素出栈
        else if (NUM == 1) {
            // 1.2.1 用 ele 保存 1 号栈的栈顶元素
            top = stack.data[stack.top[1]];
            // 1.2.2 移动栈顶指针删除元素
            stack.top[1]++;
        }
        return top;
    }

    /**
     * 获取指定序号栈的栈顶元素，但不出栈
     *
     * @param NUM 栈序号，只能传入 0 或者 1
     * @return 如果栈空则返回 0 表示出栈失败；否则返回 1 表示出栈成功
     * @throws Exception 如果栈空或者序号不合法则会抛出此异常
     */
    public int getTop(int NUM) throws Exception {
        // 0.参数校验，如果任何一个栈栈空则不能出栈
        if (isEmpty(NUM)) {
            throw new Exception("栈空没有可出栈元素！");
        }

        // 变量，存储栈顶元素
        int top = 0;

        // 1.用 ele 保存栈顶元素
        // 1.1 用 ele 保存 0 号栈的栈顶元素
        if (NUM == 0) {
            top = stack.data[stack.top[0]];
        }
        // 1.2 用 ele 保存 1 号栈的栈顶元素
        else if (NUM == 1) {
            top = stack.data[stack.top[1]];
        }
        return top;
    }

    /**
     * 获取共享栈中指定序号栈的元素个数
     *
     * @param NUM 栈序号，只能传入 0 或者 1
     * @return 指定序号栈的元素个数
     */
    public int size(int NUM) {
        // 变量，记录栈中结点个数
        int len = 0;
        // 1.获取指定序号栈的元素个数
        // 1.1 获取 0 号栈的元素个数
        if (NUM == 0) {
            // 下标从 0 开始，所以元素个数就是下标加一
            len = stack.top[0] + 1;
        }
        // 1.2 获取 1 号栈的元素个数
        else if (NUM == 1) {
            // 1 号栈的元素从后往前，所以计算栈的元素个数是 MAXSIZE 减去 1 号栈的栈顶指针
            len = MAXSIZE - stack.top[1];
        }
        return len;
    }

    /**
     * 打印指定序号栈中的所有元素
     *
     * @param NUM 栈序号，只能传入 0 或者 1
     */
    public void print(int NUM) {
        System.out.print("[");
        // 变量，记录栈顶指针
        int top;
        if (NUM == 0) {
            top = stack.top[0];
            for (int i = top; i >= 0; i--) {
                System.out.print(stack.data[i]);
                if (i != 0) {
                    System.out.print(", ");
                }
            }
        } else if (NUM == 1) {
            top = stack.top[1];
            for (int i = top; i < MAXSIZE; i++) {
                System.out.print(stack.data[i]);
                if (i != MAXSIZE - 1) {
                    System.out.print(", ");
                }
            }
        }
        System.out.print("]\n");
    }

    /**
     * 清空 0 号栈的所有元素
     *
     * @param NUM 栈序号，只能传入 0 或者 1
     */
    public void clear(int NUM) {
        if (NUM == 0) {
            // 直接将 0 号的栈顶指针指向 -1，就表示是空栈
            stack.top[0] = -1;
        } else if (NUM == 1) {
            // 直接将 1 号的栈顶指针指向 MAXSIZE，就表示是空栈
            stack.top[1] = MAXSIZE;
        }
    }
}

/**
 * 栈定义
 */
class Stack {
    /**
     * 数据域，存储栈中元素
     */
    int[] data;
    /**
     * 指针域，存储 0 号栈和 1 号栈的栈顶指针
     */
    int[] top;
}
