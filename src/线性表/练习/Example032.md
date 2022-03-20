# Example032

## 题目

将一个带头结点的单链表 A 分解为带头结点的单链表 A 和 B，使得 A 表中含有原表中序号为奇数的元素，而 B 表中含有原表中序号为偶数的元素，且保持其相对顺序不变。

## 分析

设置一个变量 `num` 记录序号，初始值为 0，每访问一个节点则序号变量 `num` 加 1，然后根据序号的奇偶性来做处理，如果是奇数则通过尾插法插入到链表 A 中；如果是偶数则通过尾插法插入到链表 B 中。重复以上操作直至表尾。

## 图解

略。

## C实现

核心代码：

```c
/**
 * 拆分链表 A，使得链表 A 中只有序号为奇数的节点，链表 B 中只有序号为偶数的节点
 * @param A 初始包含所有节点，分解后只保留有序号为奇数的节点
 * @param B 保存有序号为偶数的节点
 */
void splitLinkedList(LNode **A, LNode **B) {
    // 初始化单链表 B，为其分配空间，并且将头结点的 next 指针指向 null
    *B = (LNode *) malloc(sizeof(LNode));
    (*B)->next = NULL;

    // 变量，记录链表 A 的尾节点
    LNode *aTailNode = *A;
    // 变量，记录链表 B 的尾节点
    LNode *bTailNode = *B;

    // 链表 A 的第一个节点
    LNode *node = (*A)->next;

    // 变量，记录链表中节点的序号
    int num = 0;
    // 从头到尾扫描单链表 A，从第一个节点开始扫描
    while (node != NULL) {
        // 计数器加一，记录当前扫描到第几个节点了
        num++;
        // 判断节点序号是奇数还是偶数
        if (num % 2 != 0) {// 奇数
            // 如果序号是奇数，则使用尾插法插入到链表 A 的尾部
            aTailNode->next = node;
            aTailNode = node;// 并且更新 aTailNode
        } else {// 偶数
            // 如果序号是偶数，则使用尾插法插入到链表 B 的尾部
            bTailNode->next = node;
            bTailNode = node;// 并且更新 bTailNode
        }
        // 继续原链表 A 的下一个节点
        node = node->next;
    }
    // 注意结束后将 aTailNode 和 bTailNode 的 next 指针指向 null，因为是将原链表 A 中的节点插入到新链表 A 和 B 中，那么原节点的 next 指针可能指向一些我们不需要的数据，所以将他们指向 null，表示是一个新链表
    aTailNode->next = NULL;
    bTailNode->next = NULL;
}
```

完整代码：

```c
#include <stdio.h>
#include <malloc.h>

/**
 * 单链表节点
 */
typedef struct LNode {
    /**
     * 单链表节点的数据域
     */
    int data;
    /**
     * 单链表节点的的指针域，指向当前节点的后继节点
     */
    struct LNode *next;
} LNode;

/**
 * 通过尾插法创建单链表
 * @param list 单链表
 * @param nums 创建单链表时插入的数据数组
 * @param n 数组长度
 * @return 创建好的单链表
 */
LNode *createByTail(LNode **list, int nums[], int n) {
    // 1.初始化单链表
    // 创建链表必须要先初始化链表，也可以选择直接调用 init() 函数
    *list = (LNode *) malloc(sizeof(LNode));
    (*list)->next = NULL;

    // 尾插法，必须知道链表的尾节点（即链表的最后一个节点），初始时，单链表的头结点就是尾节点
    // 因为在单链表中插入节点我们必须知道前驱节点，而头插法中的前驱节点一直是头节点，但尾插法中要在单链表的末尾插入新节点，所以前驱节点一直都是链表的最后一个节点，而链表的最后一个节点由于链表插入新节点会一直变化
    LNode *node = (*list);

    // 2.循环数组，将所有数依次插入到链表的尾部
    for (int i = 0; i < n; i++) {
        // 2.1 创建新节点，并指定数据域和指针域
        // 2.1.1 创建新节点，为其分配空间
        LNode *newNode = (LNode *) malloc(sizeof(LNode));
        // 2.1.2 为新节点指定数据域
        newNode->data = nums[i];
        // 2.1.3 为新节点指定指针域，新节点的指针域初始时设置为 null
        newNode->next = NULL;

        // 2.2 将新节点插入到单链表的尾部
        // 2.2.1 将链表原尾节点的 next 指针指向新节点
        node->next = newNode;
        // 2.2.2 将新节点置为新的尾节点
        node = newNode;
    }
    return *list;
}

/**
 * 拆分链表 A，使得链表 A 中只有序号为奇数的节点，链表 B 中只有序号为偶数的节点
 * @param A 初始包含所有节点，分解后只保留有序号为奇数的节点
 * @param B 保存有序号为偶数的节点
 */
void splitLinkedList(LNode **A, LNode **B) {
    // 初始化单链表 B，为其分配空间，并且将头结点的 next 指针指向 null
    *B = (LNode *) malloc(sizeof(LNode));
    (*B)->next = NULL;

    // 变量，记录链表 A 的尾节点
    LNode *aTailNode = *A;
    // 变量，记录链表 B 的尾节点
    LNode *bTailNode = *B;

    // 链表 A 的第一个节点
    LNode *node = (*A)->next;

    // 变量，记录链表中节点的序号
    int num = 0;
    // 从头到尾扫描单链表 A，从第一个节点开始扫描
    while (node != NULL) {
        // 计数器加一，记录当前扫描到第几个节点了
        num++;
        // 判断节点序号是奇数还是偶数
        if (num % 2 != 0) {// 奇数
            // 如果序号是奇数，则使用尾插法插入到链表 A 的尾部
            aTailNode->next = node;
            aTailNode = node;// 并且更新 aTailNode
        } else {// 偶数
            // 如果序号是偶数，则使用尾插法插入到链表 B 的尾部
            bTailNode->next = node;
            bTailNode = node;// 并且更新 bTailNode
        }
        // 继续原链表 A 的下一个节点
        node = node->next;
    }
    // 注意结束后将 aTailNode 和 bTailNode 的 next 指针指向 null，因为是将原链表 A 中的节点插入到新链表 A 和 B 中，那么原节点的 next 指针可能指向一些我们不需要的数据，所以将他们指向 null，表示是一个新链表
    aTailNode->next = NULL;
    bTailNode->next = NULL;
}

/**
 * 打印链表的所有节点
 * @param list 单链表
 */
void print(LNode *list) {
    printf("[");
    // 链表的第一个节点
    LNode *node = list->next;
    // 循环单链表所有节点，打印值
    while (node != NULL) {
        printf("%d", node->data);
        if (node->next != NULL) {
            printf(", ");
        }
        node = node->next;
    }
    printf("]\n");
}

int main() {
    // 声明单链表
    LNode *A;
    LNode *B;
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = 8;
    createByTail(&A, nums, n);
    print(A);

    // 调用函数，拆分链表
    splitLinkedList(&A, &B);
    print(A);
    print(B);
}
```

执行结果：

```text
[1, 2, 3, 4, 5, 6, 7, 8]
[1, 3, 5, 7]
[2, 4, 6, 8]
```

## Java实现

核心代码：

```java
    /**
     * 拆分链表 A，使得链表 A 中只有序号为奇数的节点，链表 B 中只有序号为偶数的节点
     *
     * @param A 初始包含所有节点，分解后只保留有序号为奇数的节点
     * @param B 保存有序号为偶数的节点
     */
    public void splitLinkedList(LinkedList A, LinkedList B) {
        // 初始化单链表 B，为其分配空间，并且将头结点的 next 指针指向 null
        B.list = new LNode();
        B.list.next = null;

        // 变量，记录链表 A 的尾节点
        LNode aTailNode = A.list;
        // 变量，记录链表 B 的尾节点
        LNode bTailNode = B.list;

        // 链表 A 的第一个节点
        LNode node = A.list.next;

        // 变量，记录链表中节点的序号
        int num = 0;
        // 从头到尾扫描单链表 A，从第一个节点开始扫描
        while (node != null) {
            // 计数器加一，记录当前扫描到第几个节点了
            num++;
            // 判断节点序号是奇数还是偶数
            if (num % 2 != 0) {// 奇数
                // 如果序号是奇数，则使用尾插法插入到链表 A 的尾部
                aTailNode.next = node;
                aTailNode = node;// 并且更新 aTailNode
            } else {// 偶数
                // 如果序号是偶数，则使用尾插法插入到链表 B 的尾部
                bTailNode.next = node;
                bTailNode = node;// 并且更新 bTailNode
            }
            // 继续原链表 A 的下一个节点
            node = node.next;
        }
        // 注意结束后将 aTailNode 和 bTailNode 的 next 指针指向 null，因为是将原链表 A 中的节点插入到新链表 A 和 B 中，那么原节点的 next 指针可能指向一些我们不需要的数据，所以将他们指向 null，表示是一个新链表
        aTailNode.next = null;
        bTailNode.next = null;
    }
```

完整代码：

```java
public class LinkedList {
    /**
     * 单链表
     */
    private LNode list;

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
     * 拆分链表 A，使得链表 A 中只有序号为奇数的节点，链表 B 中只有序号为偶数的节点
     *
     * @param A 初始包含所有节点，分解后只保留有序号为奇数的节点
     * @param B 保存有序号为偶数的节点
     */
    public void splitLinkedList(LinkedList A, LinkedList B) {
        // 初始化单链表 B，为其分配空间，并且将头结点的 next 指针指向 null
        B.list = new LNode();
        B.list.next = null;

        // 变量，记录链表 A 的尾节点
        LNode aTailNode = A.list;
        // 变量，记录链表 B 的尾节点
        LNode bTailNode = B.list;

        // 链表 A 的第一个节点
        LNode node = A.list.next;

        // 变量，记录链表中节点的序号
        int num = 0;
        // 从头到尾扫描单链表 A，从第一个节点开始扫描
        while (node != null) {
            // 计数器加一，记录当前扫描到第几个节点了
            num++;
            // 判断节点序号是奇数还是偶数
            if (num % 2 != 0) {// 奇数
                // 如果序号是奇数，则使用尾插法插入到链表 A 的尾部
                aTailNode.next = node;
                aTailNode = node;// 并且更新 aTailNode
            } else {// 偶数
                // 如果序号是偶数，则使用尾插法插入到链表 B 的尾部
                bTailNode.next = node;
                bTailNode = node;// 并且更新 bTailNode
            }
            // 继续原链表 A 的下一个节点
            node = node.next;
        }
        // 注意结束后将 aTailNode 和 bTailNode 的 next 指针指向 null，因为是将原链表 A 中的节点插入到新链表 A 和 B 中，那么原节点的 next 指针可能指向一些我们不需要的数据，所以将他们指向 null，表示是一个新链表
        aTailNode.next = null;
        bTailNode.next = null;
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
```

测试代码：

```java
public class LinkedListTest {
    public static void main(String[] args) {
        // 创建单链表 A
        LinkedList A = new LinkedList();
        A.createByTail(1, 2, 3, 4, 5, 6, 7);
        A.print();

        LinkedList B = new LinkedList();
        LinkedList list = new LinkedList();
        // 调用函数分解链表 A
        list.splitLinkedList(A, B);
        A.print();
        B.print();
    }
}
```

执行结果：

```text
[1, 2, 3, 4, 5, 6, 7]
[1, 3, 5, 7]
[2, 4, 6]
```