# Example021

## 题目

从顺序表中删除具有最小值的元素（假设唯一）并由函数返回被删除元素的值。空出的位置由最后一个元素填补，若顺序表为空，则显示出错信息并退出运行。

## 分析

本题考查的知识点：

- 顺序表
- 顺序表删除元素
- 求数组的最小值

**分析**：

- 参数校验，如果顺序表为空则输出错误提示信息。如果顺序表只有一个元素，则直接删除顺序表中唯一的一个元素，即修改顺序表的 `length` 属性值为 0。这属于一种优化。
- 声明两个变量 `min` 和 `minIndex`，其中 `min` 记录顺序表中的最小值元素，而 `minIndex` 记录最小值元素在顺序表中的下标（索引）。
- 从头到尾扫描顺序表，找到顺序表中的最小值元素，用 `min` 和 `minIndex` 记录最小值元素和最小值元素在顺序表中的下标。
- 所谓的删除最小值元素就是将顺序表最后一个元素填充到最小值元素的位置上，然后将顺序表的 `length` 属性值减去 1，但事实上顺序表的最后一个元素值仍然存在。
- 最后返回最小值元素。其实可以考虑优化掉 `min` 变量，而只使用 `minIndex` 变量。

## 图解

略。

## C实现

核心代码：

```c
/**
 * 删除顺序表中的最小值元素
 * @param list 顺序表
 * @return 被删除元素的值
 */
int deleteMin(SeqList *list) {
    // 0.参数校验
    // 0.1 检测顺序表是否为空，如果为空则不能删除
    if (list->length == 0) {
        printf("顺序表为空，不能删除！");
        exit(0);
    }
    // 0.2 检测顺序表是否只有一个元素，如果只有一个元素则该元素就是最小值元素，直接返回然后修改顺序表的长度
    if (list->length == 1) {
        // 0.2.1 删除唯一的一个元素，只需要将 length 属性置为 0 即可，不需要用最后一个元素覆盖
        list->length = 0;
        // 0.2.2 然后直接返回顺序表的第一个元素，注意，虽然修改了 length，但实际上 data[0] 的值并没有被修改，仍然存在
        return list->data[0];
    }

    // 变量，记录最小值元素，初始将顺序表的第一个元素置为最小值
    int min = list->data[0];
    // 变量，记录最小值元素在顺序表中的索引（下标）
    int minIndex = 0;

    // 1.从头到尾扫描顺序表
    for (int i = 0; i < list->length; i++) {
        // 1.1 如果当前元素的值比最小值还要小，那么则更新 min 变量，记录当前元素为最小值
        if (list->data[i] < min) {
            // 1.1.1 保存最小值元素
            min = list->data[i];
            // 1.1.2 保存最小值元素的索引
            minIndex = i;
        }
    }

    // 2.返回被删除元素的值，然后用最后一个元素覆盖被删除元素，修改顺序表的 length 属性
    // 2.1 用最后一个元素覆盖被删除元素
    list->data[minIndex] = list->data[list->length - 1];
    // 2.2 修改顺序表的 length 属性，因为删除了一个元素，所以要更新 length 属性
    list->length--;
    // 2.3 返回最小值元素
    return min;
}
```

完整代码：

```c
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20

/**
 * 顺序表的结构体
 */
typedef struct {
    /**
     * 顺序表，实际上一个长度为 MAXSIZE 的数组，存储的数据类型为整型，当然可以设置为其他类型，但推荐使用宏定义类型，方便替换
     */
    int data[MAXSIZE];
    /**
     * 顺序表长度，即数组中实际元素个数
     */
    int length;
} SeqList;

/**
 * 初始化顺序表，仅需要将 length 置为 0 即可
 * @param list 待初始化的顺序表
 */
void init(SeqList *list) {
    // 仅需要将 length 置为 0 即可
    (*list).length = 0;
    // 或者可以用下面的语法
    // list->length=0;
}

/**
 * 直接添加新元素到顺序表的尾部
 * @param list 顺序表
 * @param ele 待添加的新元素
 * @return 如果插入成功则返回 1，否则返回 0
 */
int add(SeqList *list, int ele) {
    // 0.校验
    // 0.1 向顺序表中插入元素要检查顺序表是否已经满了，如果已经满了则不能再插入新元素则添加失败
    if (list->length == MAXSIZE) {
        return 0;
    }
    // 1.插入新元素
    // 1.1 直接获取顺序表的 length，然后将新元素的值赋予到 length 位置即可
    list->data[list->length] = ele;
    // 1.2 注意修改 length
    list->length++;
    return 1;
}

/**
 * 删除顺序表中的最小值元素
 * @param list 顺序表
 * @return 被删除元素的值
 */
int deleteMin(SeqList *list) {
    // 0.参数校验
    // 0.1 检测顺序表是否为空，如果为空则不能删除
    if (list->length == 0) {
        printf("顺序表为空，不能删除！");
        exit(0);
    }
    // 0.2 检测顺序表是否只有一个元素，如果只有一个元素则该元素就是最小值元素，直接返回然后修改顺序表的长度
    if (list->length == 1) {
        // 0.2.1 删除唯一的一个元素，只需要将 length 属性置为 0 即可，不需要用最后一个元素覆盖
        list->length = 0;
        // 0.2.2 然后直接返回顺序表的第一个元素，注意，虽然修改了 length，但实际上 data[0] 的值并没有被修改，仍然存在
        return list->data[0];
    }

    // 变量，记录最小值元素，初始将顺序表的第一个元素置为最小值
    int min = list->data[0];
    // 变量，记录最小值元素在顺序表中的索引（下标）
    int minIndex = 0;

    // 1.从头到尾扫描顺序表
    for (int i = 0; i < list->length; i++) {
        // 1.1 如果当前元素的值比最小值还要小，那么则更新 min 变量，记录当前元素为最小值
        if (list->data[i] < min) {
            // 1.1.1 保存最小值元素
            min = list->data[i];
            // 1.1.2 保存最小值元素的索引
            minIndex = i;
        }
    }

    // 2.返回被删除元素的值，然后用最后一个元素覆盖被删除元素，修改顺序表的 length 属性
    // 2.1 用最后一个元素覆盖被删除元素
    list->data[minIndex] = list->data[list->length - 1];
    // 2.2 修改顺序表的 length 属性，因为删除了一个元素，所以要更新 length 属性
    list->length--;
    // 2.3 返回最小值元素
    return min;
}

/**
 * 打印顺序表
 * @param list 待打印的顺序表
 */
void print(SeqList list) {
    printf("[");
    for (int i = 0; i < list.length; i++) {
        printf("%d", list.data[i]);
        if (i != list.length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    // 声明顺序表
    SeqList list;
    init(&list);
    // 添加测试数据
    add(&list, 1);
    add(&list, 3);
    add(&list, 2);
    add(&list, -1);
    add(&list, 6);
    add(&list, 4);
    print(list);

    // 调用函数删除顺序表中的最小值
    deleteMin(&list);
    print(list);
}
```

执行结果：

```text
[1, 3, 2, -1, 6, 4]
[1, 3, 2, 4, 6]
```

## Java实现

核心代码：

```java
    /**
 * 删除顺序表中的最小值元素
 *
 * @return 被删除元素的值
 *
 * @throws Exception 如果顺序表为空则抛出异常
 */
public int deleteMin()throws Exception{
        // 0.参数校验
        // 0.1 检测顺序表是否为空，如果为空则不能删除
        if(list.length==0){
        throw new Exception("顺序表为空，不能删除元素！");
        }
        // 0.2 检测顺序表是否只有一个元素，如果只有一个元素则该元素就是最小值元素，直接返回然后修改顺序表的长度
        if(list.length==1){
        // 0.2.1 删除唯一的一个元素，只需要将 length 属性置为 0 即可，不需要用最后一个元素覆盖
        list.length=0;
        // 0.2.2 然后直接返回顺序表的第一个元素，注意，虽然修改了 length，但实际上 data[0] 的值并没有被修改，仍然存在
        return list.data[0];
        }

        // 变量，记录最小值元素，初始将顺序表的第一个元素置为最小值
        int min=list.data[0];
        // 变量，记录最小值元素在顺序表中的索引（下标）
        int minIndex=0;

        // 1.从头到尾扫描顺序表
        for(int i=0;i<list.length;i++){
        // 1.1 如果当前元素的值比最小值还要小，那么则更新 min 变量，记录当前元素为最小值
        if(list.data[i]<min){
        // 1.1.1 保存最小值元素
        min=list.data[i];
        // 1.1.2 保存最小值元素的索引
        minIndex=i;
        }
        }

        // 2.返回被删除元素的值，然后用最后一个元素覆盖被删除元素，修改顺序表的 length 属性
        // 2.1 用最后一个元素覆盖被删除元素
        list.data[minIndex]=list.data[list.length-1];
        // 2.2 修改顺序表的 length 属性，因为删除了一个元素，所以要更新 length 属性
        list.length--;
        // 2.3 返回最小值元素
        return min;
        }
```

完整代码：

```java
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
     * 删除顺序表中的最小值元素
     *
     * @return 被删除元素的值
     *
     * @throws Exception 如果顺序表为空则抛出异常
     */
    public int deleteMin() throws Exception {
        // 0.参数校验
        // 0.1 检测顺序表是否为空，如果为空则不能删除
        if (list.length == 0) {
            throw new Exception("顺序表为空，不能删除元素！");
        }
        // 0.2 检测顺序表是否只有一个元素，如果只有一个元素则该元素就是最小值元素，直接返回然后修改顺序表的长度
        if (list.length == 1) {
            // 0.2.1 删除唯一的一个元素，只需要将 length 属性置为 0 即可，不需要用最后一个元素覆盖
            list.length = 0;
            // 0.2.2 然后直接返回顺序表的第一个元素，注意，虽然修改了 length，但实际上 data[0] 的值并没有被修改，仍然存在
            return list.data[0];
        }

        // 变量，记录最小值元素，初始将顺序表的第一个元素置为最小值
        int min = list.data[0];
        // 变量，记录最小值元素在顺序表中的索引（下标）
        int minIndex = 0;

        // 1.从头到尾扫描顺序表
        for (int i = 0; i < list.length; i++) {
            // 1.1 如果当前元素的值比最小值还要小，那么则更新 min 变量，记录当前元素为最小值
            if (list.data[i] < min) {
                // 1.1.1 保存最小值元素
                min = list.data[i];
                // 1.1.2 保存最小值元素的索引
                minIndex = i;
            }
        }

        // 2.返回被删除元素的值，然后用最后一个元素覆盖被删除元素，修改顺序表的 length 属性
        // 2.1 用最后一个元素覆盖被删除元素
        list.data[minIndex] = list.data[list.length - 1];
        // 2.2 修改顺序表的 length 属性，因为删除了一个元素，所以要更新 length 属性
        list.length--;
        // 2.3 返回最小值元素
        return min;
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
```

测试代码：

```java
public class SeqListTest {
    public static void main(String[] args) throws Exception {
        // 实例化顺序表对象
        SeqList list = new SeqList();
        list.init();
        // 为顺序表添加测试数据
        list.add(3);
        list.add(1);
        list.add(2);
        list.add(-5);
        list.add(4);
        list.add(-1);
        list.print();

        // 调用函数删除最小值元素
        list.deleteMin();
        list.print();
    }
}
```

执行结果：

```text
[3, 1, 2, -5, 4, -1]
[3, 1, 2, -1, 4]
```