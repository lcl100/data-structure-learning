# Example018

## 题目

在带头结点的单链表 L 中，删除所有值为 x 的结点，并释放其空间，假设值为 x 的结点不唯一，试编写算法实现上述操作。

## 分析

本题考查的知识点：

- 单链表
- 单链表删除节点

**分析**：

- 用变量 `node` 从头到尾扫描单链表，而 `preNode` 指向 `node` 节点的前驱节点。
- 若 `node` 节点的值是 x，则删除该节点，并让 `node` 移向下一个节点。
- 否则 `preNode` 和 `node` 指针同步后移一个节点。

**注意**：

- 上面的解法是原地修改单链表，我们还可以创建一条新的单链表，然后将那些不是 x 的元素插入到这个新单链表中。但注意采用尾插法，保持原结点顺序。

## 图解

![image-20220313222314433](image-Example018/image-20220313222314433.png)

## C实现

解法一核心代码：

```c
/**
 * 删除单链表中所有值为 x 的节点
 * @param list 单链表
 * @param x 指定值
 */
void deleteAllByEle(LNode **list, int x) {
    // 变量，记录链表的每个节点，从头到尾进行扫描
    LNode *node = (*list)->next;
    // 变量，记录 node 节点的前驱节点
    LNode *preNode = *list;

    // 从头到尾扫描单链表
    while (node != NULL) {
        // 判断当前节点的数据域是 x
        if (node->data == x) {
            // 保存待删除的节点，用于释放空间
            LNode *temp = node;
            // 删除 node 节点
            preNode->next = node->next;
            // 继续链表的下一个节点
            node = node->next;
            // 释放被删除节点的空间
            free(temp);
        }
        // 如果当前节点的数据域不是 x
        else {
            // 保存前驱节点
            preNode = node;
            // 继续链表的下一个节点
            node = node->next;
        }
    }
}
```

解法二核心代码：

```c 
/**
 * 删除单链表中所有值为 x 的节点
 * @param list 单链表
 * @param x 指定值
 */
void deleteAllByEle(LNode **list, int x) {
    // 单链表的第一个结点
    LNode *node = (*list)->next;

    // 初始化另外一个单链表
    (*list)->next = NULL;
    // 保存新链表的尾节点
    LNode *tailNode = *list;

    // 从头到尾遍历 node 所表示的单链表，然后将值不是 x 的结点插入到新链表中
    while (node != NULL) {
        // 如果当前节点的值不为 x 则插入到新链表中
        if (node->data != x) {
            // 临时保存当前节点的后继节点，用于继续遍历链表的下一个节点
            LNode *temp = node->next;

            // 创建新节点并指定数据域和指针域
            LNode *newNode = (LNode *) malloc(sizeof(LNode));
            newNode->next = NULL;
            newNode->data = node->data;
            // 将新节点插入到新链表的尾部
            tailNode->next = newNode;
            tailNode = newNode;// 将 tailNode 指向新节点，记录新节点才是链表的尾节点

            // 释放当前节点的空间
            free(node);
            // 继续链表的下一个节点
            node = temp;
        } else {
            // 继续链表的下一个节点
            node = node->next;
        }
    }
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
 * 删除单链表中所有值为 x 的节点
 * @param list 单链表
 * @param x 指定值
 */
void deleteAllByEle(LNode **list, int x) {
    // 变量，记录链表的每个节点，从头到尾进行扫描
    LNode *node = (*list)->next;
    // 变量，记录 node 节点的前驱节点
    LNode *preNode = *list;

    // 从头到尾扫描单链表
    while (node != NULL) {
        // 判断当前节点的数据域是 x
        if (node->data == x) {
            // 保存待删除的节点，用于释放空间
            LNode *temp = node;
            // 删除 node 节点
            preNode->next = node->next;
            // 继续链表的下一个节点
            node = node->next;
            // 释放被删除节点的空间
            free(temp);
        }
            // 如果当前节点的数据域不是 x
        else {
            // 保存前驱节点
            preNode = node;
            // 继续链表的下一个节点
            node = node->next;
        }
    }
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
    LNode *list;
    int nums[] = {1, 2, 2, 3, 2, 4, 2, 5};
    int n = 8;
    createByTail(&list, nums, n);
    print(list);

    // 调用函数，删除值为 x 的所有结点
    int x = 2;
    deleteAllByEle(&list, x);
    print(list);
}
```

执行结果：

```text
[1, 2, 2, 3, 2, 4, 2, 5]
[1, 3, 4, 5]
```

注意：在数据结构题目中更倾向于使用 `*&` 引用来修改单链表，而不是使用指向指针的指针 `**`。尽管那属于 C++ 中的知识。

```c++
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
LNode *createByTail(LNode *&list, int nums[], int n) {
    // 1.初始化单链表
    // 创建链表必须要先初始化链表，也可以选择直接调用 init() 函数
    list = (LNode *) malloc(sizeof(LNode));
    list->next = NULL;

    // 尾插法，必须知道链表的尾节点（即链表的最后一个节点），初始时，单链表的头结点就是尾节点
    // 因为在单链表中插入节点我们必须知道前驱节点，而头插法中的前驱节点一直是头节点，但尾插法中要在单链表的末尾插入新节点，所以前驱节点一直都是链表的最后一个节点，而链表的最后一个节点由于链表插入新节点会一直变化
    LNode *node = list;

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
    return list;
}

/**
 * 删除单链表中所有值为 x 的节点
 * @param list 单链表
 * @param x 指定值
 */
void deleteAllByEle(LNode *&list, int x) {
    // 变量，记录链表的每个节点，从头到尾进行扫描
    LNode *node = list->next;
    // 变量，记录 node 节点的前驱节点
    LNode *preNode = list;

    // 从头到尾扫描单链表
    while (node != NULL) {
        // 判断当前节点的数据域是 x
        if (node->data == x) {
            // 保存待删除的节点，用于释放空间
            LNode *temp = node;
            // 删除 node 节点
            preNode->next = node->next;
            // 继续链表的下一个节点
            node = node->next;
            // 释放被删除节点的空间
            free(temp);
        }
            // 如果当前节点的数据域不是 x
        else {
            // 保存前驱节点
            preNode = node;
            // 继续链表的下一个节点
            node = node->next;
        }
    }
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
    LNode *list;
    int nums[] = {1, 2, 2, 3, 2, 4, 2, 5};
    int n = 8;
    createByTail(list, nums, n);
    print(list);

    // 调用函数，删除值为 x 的所有结点
    int x = 2;
    deleteAllByEle(list, x);
    print(list);
}
```

## Java实现

核心代码：

```java
    /**
 * 删除单链表中所有值为 x 的节点
 *
 * @param x 指定值
 */
public void deleteAllByEle(int x){
        // 变量，记录链表的每一个节点，初始为链表的第一个节点
        LNode node=list.next;
        // 变量，记录前驱节点，初始为链表的头结点
        LNode preNode=list;

        // 循环单链表
        while(node!=null){
        // 找到值为 x 的节点
        if(node.data==x){
        // 保存待删除结点，用于释放空间
        LNode temp=node;
        // 删除节点
        preNode.next=node.next;
        // 继续链表的下一个节点
        node=node.next;
        // 释放被删除节点的空间
        temp.next=null;
        temp=null;
        }
        // 如果不是值为 x 的节点
        else{
        // 则保存前驱节点
        preNode=node;
        // 继续写链表的下一个节点
        node=node.next;
        }
        }
        }
```

完整代码：

```java
/**
 * @author lcl100
 * @create 2022-03-01 21:32
 */
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
     * 删除单链表中所有值为 x 的节点
     *
     * @param x 指定值
     */
    public void deleteAllByEle(int x) {
        // 变量，记录链表的每一个节点，初始为链表的第一个节点
        LNode node = list.next;
        // 变量，记录前驱节点，初始为链表的头结点
        LNode preNode = list;

        // 循环单链表
        while (node != null) {
            // 找到值为 x 的节点
            if (node.data == x) {
                // 保存待删除结点，用于释放空间
                LNode temp = node;
                // 删除节点
                preNode.next = node.next;
                // 继续链表的下一个节点
                node = node.next;
                // 释放被删除节点的空间
                temp.next = null;
                temp = null;
            }
            // 如果不是值为 x 的节点
            else {
                // 则保存前驱节点
                preNode = node;
                // 继续写链表的下一个节点
                node = node.next;
            }
        }
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
        // 创建单链表
        LinkedList list = new LinkedList();
        list.createByTail(1, 2, 2, 5, 2, 7, 2);
        list.print();

        // 删除链表中所有值为 x 的节点
        int x = 2;
        list.deleteAllByEle(x);
        list.print();
    }
}
```

执行结果：

```text
[1, 2, 2, 5, 2, 7, 2]
[1, 5, 7]
```