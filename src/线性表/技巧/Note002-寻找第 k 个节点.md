# 找到第 k 个节点

有时候我们需要寻找单链表的第 k 个节点，当然这个 k 在 `[1, n]` 范围内，可以采用计数的方式：

```c
LNode* findKthNode(LNode* list,int k){
    // 变量，记录链表节点用于循环，初始为链表的第一个节点
    LNode* node=list->next;
    // 计数器，记录已经遍历到第几个节点了，用于同 k 进行比较
    int count=0;

    // 从头到尾扫描单链表，寻找第 k 个节点
    while(node!=NULL){
        count++;
        // 找到第 k 个节点进行返回
        if(count==k){
            return node;
        }
        node=node->next;
    }
    return NULL;
}
```

上面的代码还是比较冗余的，我们可以更简化点：

```c
LNode* findKthNode(LNode* list,int k){
    // 变量，记录链表节点用于循环，初始为链表的第一个节点
    LNode* node=list->next;
    // 计数器，记录已经遍历到第几个节点了，用于同 k 进行比较
    int count=1;// 注意，这里是从 1 开始的，因为 node 此时已经表示链表的第一个节点了，如果 node=list 那么 count 就应该从 0 开始

    // 从头到尾扫描单链表，寻找第 k 个节点
    while(node!=NULL&&count<k){
        count++;
        node=node->next;
    }
    // 结束循环后，node 恰好是链表中第 k 个节点
    return node;
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
 * 得到链表的尾节点
 * @param list 带头节点的单链表
 * @param k 链表中节点序号，从 1 开始
 * @return 如果找到则返回第 k 个节点，否则返回 NULL
 */
LNode* findKthNode(LNode* list,int k){
    // 变量，记录链表节点用于循环，初始为链表的第一个节点
    LNode* node=list->next;
    // 计数器，记录已经遍历到第几个节点了，用于同 k 进行比较
    int count=0;

    // 从头到尾扫描单链表，寻找第 k 个节点
    while(node!=NULL){
        count++;
        // 找到第 k 个节点进行返回
        if(count==k){
            return node;
        }
        node=node->next;
    }
    return NULL;
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
    int k=3;
    LNode* kNode=findKthNode(list, k);
    printf("链表的第%d个节点：%d\n",k,kNode->data);
}
```