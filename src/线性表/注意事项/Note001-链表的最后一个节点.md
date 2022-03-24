# 找到单链表的尾节点

通常我们遍历单链表的代码如下：

```c
// list 指向单链表的头节点，因此 list->next 指向链表的第一个节点
LNode* node=list->next;
while(node!=NULL){
    node=node->next;
}
```

如图：

![image-20220324222825820](image-Note001-%E9%93%BE%E8%A1%A8%E7%9A%84%E6%9C%80%E5%90%8E%E4%B8%80%E4%B8%AA%E8%8A%82%E7%82%B9/image-20220324222825820.png)

结束后，`node` 为 `NULL`，不是链表的尾节点。当然我们可以考虑计数的方法：先遍历一趟单链表统计节点个数 `n`，然后再遍历一趟单链表寻找到第 `n`
个节点，就是链表的尾节点了，代码如下，发现需要扫描两遍链表，时间复杂度为 `O(2n)`。

```c
LNode* getTail(LNode* list){
    // 1.先遍历单链表统计节点个数
    // list 指向单链表的头节点，因此 list->next 指向链表的第一个节点
    LNode* node=list->next;
    // 变量，计数器，统计节点个数
    int n=0;
    // 扫描单链表，统计节点个数
    while(node!=NULL){
        n++;
        node=node->next;
    }

    // 2.找到单链表中第 n 个节点
    // 变量，计数器，记录已经扫描过的节点个数，用来与 n 进行比较
    int count=0;
    // 注意，由于上面的循环 node 已经为 NULL，要为它重新赋值为链表的第一个节点
    node=list->next;
    // 扫描单链表，寻找第 n 个节点
    while(node!=NULL){
        count++;
        // 找到第 n 个节点，返回
        if(count==n){
            return node;
        }
        node=node->next;
    }
    return NULL;
}
```

事实上找到链表的尾节点，完全不需要像上面算法那样，只需要修改遍历链表的循环结束条件，当循环结束后，`node` 自然就是链表的尾节点，如下：

```c
LNode* getTail(LNode* list){
    // list 指向单链表的头节点，因此 list->next 指向链表的第一个节点
    LNode* node=list->next;
    // 扫描单链表，注意，循环结束的条件变成了 node->next!=NULL
    while(node->next!=NULL){
        node=node->next;
    }
    return node;
}
```

如图：

![image-20220324223409700](image-Note001-%E9%93%BE%E8%A1%A8%E7%9A%84%E6%9C%80%E5%90%8E%E4%B8%80%E4%B8%AA%E8%8A%82%E7%82%B9/image-20220324223409700.png)

完整代码如下：

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
 * 得到链表的尾节点
 * @param list 带头节点的单链表
 * @return 链表的尾节点
 */
LNode* getTail(LNode* list){
    // list 指向单链表的头节点，因此 list->next 指向链表的第一个节点
    LNode* node=list->next;
    // 扫描单链表，注意，循环结束的条件变成了 node->next!=NULL
    while(node->next!=NULL){
        node=node->next;
    }
    return node;
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
    int nums[] = {1,2,3,4,5,6};
    int n = 6;
    createByTail(&list, nums, n);
    print(list);

    // 调用函数
    LNode* tail=getTail(list);
    printf("链表的尾节点：%d\n",tail->data);
}
```