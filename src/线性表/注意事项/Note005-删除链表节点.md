# 删除链表节点

如果我们要删除带头结点单链表中的给定节点 `node`，通常有两种方法：

- 第一种方法，从链表的头结点开始按顺序找到其前驱节点 `pre`，然后执行删除操作（即 `pre->next=node->next`）。
- 第二种方法，删除节点 `node` 的操作可以用删除 `node` 节点的后继节点操作来实现，实质就是将其后继节点的值赋予给 `node` 节点，然后删除后继节点。**但注意，这种方法无法删除链表的尾节点**。

解法一图解：

![image-20220325233640217](image-Note005-%E5%88%A0%E9%99%A4%E9%93%BE%E8%A1%A8%E8%8A%82%E7%82%B9/image-20220325233640217.png)

解法一核心代码：

```c 
/**
 * 删除链表中值为 ele 的节点，假设值为 ele 的节点只有一个，如果有多个也只会删除第一个
 * @param list 待删除结点的链表
 * @param ele 指定值
 */
void removeByEle(LNode **list, int ele) {
    // 变量，记录链表中的每个结点，初始为链表的第一个结点
    LNode *node = (*list)->next;
    // 变量，记录 node 的前驱节点，用于删除节点
    LNode *pre = *list;
    // 从头到尾扫描单链表，查找指定值的节点，然后删除它
    while (node != NULL) {
        // 找到值为 ele 的节点
        if (node->data == ele) {
            LNode *temp = node->next;

            // 则通过前驱节点删除　node 节点
            pre->next = node->next;
            free(node);

            node = temp;
        }
        // 如果没有找到则更新 pre 和 node 节点
        else {
            pre = node;
            node = node->next;
        }
    }
}
```

解法二图解：

![image-20220325234517567](image-Note005-%E5%88%A0%E9%99%A4%E9%93%BE%E8%A1%A8%E8%8A%82%E7%82%B9/image-20220325234517567.png)

解法二核心代码：

```c
/**
 * 删除链表中值为 ele 的节点，假设值为 ele 的节点只有一个，如果有多个也只会删除第一个
 * @param list 待删除结点的链表
 * @param ele 指定值
 */
void removeByEle(LNode **list, int ele) {
    // 变量，记录链表中的每个结点，初始为链表的第一个结点
    LNode *node = (*list)->next;
    // 从头到尾扫描单链表，查找指定值的节点，然后删除它
    while (node != NULL) {
        // 找到值为 ele 的节点
        if (node->data == ele) {
            // 得到 node 节点的后继节点
            LNode *back = node->next;
            // 将后继节点的数据域赋给 node 节点
            node->data = node->next->data;
            // 将 back 节点断开，即让 node 节点的 next 指针指向 back 节点的后继节点
            node->next = back->next;
            // 释放 back 节点空间
            free(back);
        }
        node = node->next;
    }
}
```

所以最后的完整代码是：

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
 * 删除链表中值为 ele 的节点，假设值为 ele 的节点只有一个，如果有多个也只会删除第一个
 * @param list 待删除结点的链表
 * @param ele 指定值
 */
void removeByEle(LNode **list, int ele) {
    // 变量，记录链表中的每个结点，初始为链表的第一个结点
    LNode *node = (*list)->next;
    // 从头到尾扫描单链表，查找指定值的节点，然后删除它
    while (node != NULL) {
        // 找到值为 ele 的节点
        if (node->data == ele) {
            // 得到 node 节点的后继节点
            LNode *back = node->next;
            // 将后继节点的数据域赋给 node 节点
            node->data = node->next->data;
            // 将 back 节点断开，即让 node 节点的 next 指针指向 back 节点的后继节点
            node->next = back->next;
            // 释放 back 节点空间
            free(back);
        }
        node = node->next;
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
    int nums[] = {1, 2, 3, 4, 5, 6};
    int n = 6;
    createByTail(&list, nums, n);
    print(list);

    // 调用函数
    removeByEle(&list, 3);
    print(list);
}
```



