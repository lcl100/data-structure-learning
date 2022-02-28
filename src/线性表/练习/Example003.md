# Example003

## 题目

设计一个算法删除单链表 L（有头节点）中的一个最小值节点（假设最小值节点是唯一的）。

## 分析

本题考查的知识点：
- 单链表
- 删除单链表中的节点
- 计算最小值

**分析**：
- 如果想要删除单链表中的一个节点，必须知道被删除节点和它的前驱节点。
- 在单链表中找最小值节点和在数组中找最小值的方法是一样：先将第一个元素设为最小值，然后遍历数组或链表，将正在迭代的元素值与最小值比较，如果比最小值还要小则将该值置为最小值，如果比最小值还要大则继续比较下一个元素。
- 在数组中我们只需要记录最小值元素即可，但是在单链表中我们必须记录最小值节点的前驱节点，才能删除最小值节点。

**步骤**：
- 声明两个节点记录单链表的最小值节点和最小值节点的前驱节点，初始时它们分别为单链表的第一个节点和头节点。
- 循环遍历单链表所有节点，将正在迭代的节点的数据域值与最小值节点的数据域值进行比较，如果前者更小则将该节点置为最小值节点并且保存它的前驱节点，如果后者更小则继续判断比较下一个节点。但注意保存每个节点的前驱节点。
- 循环完成后，根据最小值节点的前驱节点删除最小值节点。注意，释放被删除的最小值节点空间。

## 图解

略。

## C实现

核心代码：

```c
/**
 * 删除单链表中的最小值节点
 * @param list 单链表
 */
void deleteMin(LNode **list) {
    // 链表的最小值节点和最小值节点的前驱节点
    LNode *minNode = (*list)->next;
    LNode *minPreNode = *list;
    // 链表的第一个节点和其前驱节点
    LNode *node = (*list)->next;
    LNode *preNode = *list;
    // 循环单链表，比较最小值节点
    while (node != NULL) {
        // 将当前节点的数据域与最小值节点的数据域进行比较
        if (node->data < minNode->data) {
            // 如果更小，则重置最小值节点和最小值节点的前驱节点
            minPreNode = preNode;
            minNode = node;
        }
        // 继续下一个节点
        preNode = node;
        node = node->next;
    }
    // 删除最小值节点
    minPreNode->next = minNode->next;
    // 释放被删除节点的空间
    free(minNode);
}
```

完整代码：

```c
#include <stdio.h>
#include <malloc.h>

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode;

/**
 * 使用尾插法创建单链表
 * @param list 单链表
 * @param nums 待插入到单链表中的数组
 * @param n 数组长度
 */
void createByTail(LNode **list, int nums[], int n) {
    // 初始化单链表
    *list = (LNode *) malloc(sizeof(LNode) * n);
    (*list)->next = NULL;
    // 链表的尾节点，初始时链表的尾节点就是头节点
    LNode *tailNode = (*list);
    // 循环数组 nums 中所有数据
    for (int i = 0; i < n; i++) {
        // 创建新节点并指定数据域和指针域
        LNode *newNode = (LNode *) malloc(sizeof(LNode));
        newNode->data = nums[i];
        newNode->next = NULL;
        // 将新节点插入到链表的尾部
        tailNode->next = newNode;
        tailNode = newNode;
    }
}

/**
 * 删除单链表中的最小值节点
 * @param list 单链表
 */
void deleteMin(LNode **list) {
    // 链表的最小值节点和最小值节点的前驱节点
    LNode *minNode = (*list)->next;
    LNode *minPreNode = *list;
    // 链表的第一个节点和其前驱节点
    LNode *node = (*list)->next;
    LNode *preNode = *list;
    // 循环单链表，比较最小值节点
    while (node != NULL) {
        // 将当前节点的数据域与最小值节点的数据域进行比较
        if (node->data < minNode->data) {
            // 如果更小，则重置最小值节点和最小值节点的前驱节点
            minPreNode = preNode;
            minNode = node;
        }
        // 继续下一个节点
        preNode = node;
        node = node->next;
    }
    // 删除最小值节点
    minPreNode->next = minNode->next;
    // 释放被删除节点的空间
    free(minNode);
}

/**
 * 打印单链表所有节点
 * @param list 单链表
 */
void print(LNode list) {
    printf("[");
    // 链表的第一个节点
    LNode *node = list.next;
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
    LNode *list;
    int nums[] = {0, 2, 3, 4, 1, 7, 9};
    int n = 7;

    // 创建单链表
    createByTail(&list, nums, n);
    print(*list);

    // 删除最小值节点
    deleteMin(&list);
    print(*list);
}
```

执行结果：

```text
[0, 2, 3, 4, 1, 7, 9]
[2, 3, 4, 1, 7, 9]
```

注意：在数据结构题目中更倾向于使用 `*&` 引用来修改单链表，而不是使用指向指针的指针 `**`。尽管那属于 C++ 中的知识。

```c++
#include <stdio.h>
#include <malloc.h>

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode;

/**
 * 使用尾插法创建单链表
 * @param list 单链表
 * @param nums 待插入到单链表中的数组
 * @param n 数组长度
 */
void createByTail(LNode *&list, int nums[], int n) {
    // 初始化单链表
    list = (LNode *) malloc(sizeof(LNode) * n);
    list->next = NULL;
    // 链表的尾节点，初始时链表的尾节点就是头节点
    LNode *tailNode = list;
    // 循环数组 nums 中所有数据
    for (int i = 0; i < n; i++) {
        // 创建新节点并指定数据域和指针域
        LNode *newNode = (LNode *) malloc(sizeof(LNode));
        newNode->data = nums[i];
        newNode->next = NULL;
        // 将新节点插入到链表的尾部
        tailNode->next = newNode;
        tailNode = newNode;
    }
}

/**
 * 删除单链表中的最小值节点
 * @param list 单链表
 */
void deleteMin(LNode *&list) {
    // 链表的最小值节点和最小值节点的前驱节点
    LNode *minNode = list->next;
    LNode *minPreNode = list;
    // 链表的第一个节点和其前驱节点
    LNode *node = list->next;
    LNode *preNode = list;
    // 循环单链表，比较最小值节点
    while (node != NULL) {
        // 将当前节点的数据域与最小值节点的数据域进行比较
        if (node->data < minNode->data) {
            // 如果更小，则重置最小值节点和最小值节点的前驱节点
            minPreNode = preNode;
            minNode = node;
        }
        // 继续下一个节点
        preNode = node;
        node = node->next;
    }
    // 删除最小值节点
    minPreNode->next = minNode->next;
    // 释放被删除节点的空间
    free(minNode);
}

/**
 * 打印单链表所有节点
 * @param list 单链表
 */
void print(LNode list) {
    printf("[");
    // 链表的第一个节点
    LNode *node = list.next;
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
    LNode *list;
    int nums[] = {0, 2, 3, 4, 1, 7, 9};
    int n = 7;

    // 创建单链表
    createByTail(list, nums, n);
    print(*list);

    // 删除最小值节点
    deleteMin(list);
    print(*list);
}
```

## Java实现

核心代码：

```java
    /**
     * 删除链表中的最小值节点
     */
    public void deleteMin() {
        // 0.声明一些变量
        // 链表的第一个节点和第一个节点的前驱节点
        Node node = list.next;
        Node pre = list;
        // 保存链表中的最小值节点和最小值节点的前驱节点
        Node minNode = node;// 初始时，将链表的第一个节点置为最小值节点
        Node minPreNode = pre;// 初始时，则链表的头节点是最小值节点的前驱节点
        // 1.找到链表中的最小值节点和它的前驱节点
        // 遍历链表的所有节点
        while (node != null) {
            // 找到最小值节点
            if (node.data < minNode.data) {
                // 保存最小值节点
                minNode = node;
                // 保存最小值节点的前驱节点
                minPreNode = pre;
            }
            pre = node;
            node = node.next;
        }
        // 2.删除最小值节点
        minPreNode.next = minNode.next;
        // 3.释放节点空间
        minNode.next = null;
        minNode.data = 0;
    }
```

完整代码：

```java
public class LinkedList {
    private Node list;

    /**
     * 通过尾插法创建单链表
     *
     * @param nums 创建单链表时插入的数据
     * @return 创建好的单链表
     */
    public Node createByTail(int... nums) {
        // 初始化单链表
        list = new Node();
        list.next = null;
        // 单链表的尾节点
        Node tailNode = list;

        // 通过循环将数组中所有值添加到链表中
        for (int i = 0; i < nums.length; i++) {
            // 创建新节点，并指定数据域和指针域
            Node newNode = new Node();
            newNode.data = nums[i];
            newNode.next = null;
            // 将新节点插入到单链表的尾部
            tailNode.next = newNode;
            tailNode = newNode;
        }

        return list;
    }

    /**
     * 删除链表中的最小值节点
     */
    public void deleteMin() {
        // 0.声明一些变量
        // 链表的第一个节点和第一个节点的前驱节点
        Node node = list.next;
        Node pre = list;
        // 保存链表中的最小值节点和最小值节点的前驱节点
        Node minNode = node;// 初始时，将链表的第一个节点置为最小值节点
        Node minPreNode = pre;// 初始时，则链表的头节点是最小值节点的前驱节点
        // 1.找到链表中的最小值节点和它的前驱节点
        // 遍历链表的所有节点
        while (node != null) {
            // 找到最小值节点
            if (node.data < minNode.data) {
                // 保存最小值节点
                minNode = node;
                // 保存最小值节点的前驱节点
                minPreNode = pre;
            }
            pre = node;
            node = node.next;
        }
        // 2.删除最小值节点
        minPreNode.next = minNode.next;
        // 3.释放节点空间
        minNode.next = null;
        minNode.data = 0;
    }

    /**
     * 打印单链表所有节点
     */
    public void print() {
        // 链表的第一个节点
        Node node = list.next;
        // 循环打印
        String str = "[";
        while (node != null) {
            str += node.data;
            if (node.next != null) {
                str += ", ";
            }
            node = node.next;
        }
        str += "]";
        System.out.println(str);
    }
}

class Node {
    /**
     * 链表的数据域，暂时指定为 int 类型，因为 Java 支持泛型，可以指定为泛型，就能支持更多的类型了
     */
    int data;
    /**
     * 链表的指针域，指向该节点的下一个节点
     */
    Node next;
}
```

测试代码：

```java
/**
 * @author lcl100
 * @create 2022-02-24 10:05
 */
public class LinkedListTest {
    public static void main(String[] args) {
        LinkedList list = new LinkedList();

        // 创建单链表
        list.createByTail(2, 3, 4, 1, 7, 9);
        list.print();

        // 删除最小值节点
        list.deleteMin();
        list.print();
    }
}
```

执行结果：

```text
[2, 3, 4, 1, 7, 9]
[2, 3, 4, 7, 9]
```