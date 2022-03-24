# 原地逆置单链表

通常是以某个节点为基点（通常是头节点），将该节点之后的所有节点逆置。如：`head -> 1 -> 2 -> 3 -> 4 -> 5` 逆置整个单链表后结果是 `head -> 5 -> 4 -> 3 -> 2 -> 1`。

有时候我们也会遇到不是逆置整个单链表的情况，而是只逆置单链表中一部分节点。如链表 `head -> 1 -> 2 -> 3 -> 4 -> 5` 仅逆置后半部分的节点（即逆置`4 -> 5`，以 `3`
为基点），结果为 `head -> 1 -> 2 -> 3 -> 5 -> 4`。

逆置单链表的步骤如下：

- 第一步，记录基点的后继节点 `node`，即要逆置的链表节点中的第一个节点（如 `head -> 1 -> 2 -> 3 -> 4 -> 5` 中的 `1`；如 `head -> 1 -> 2 -> 3 -> 5 -> 4`
  逆置后半部分节点中的 `5`）。
- 第二步，将基点的 next 指针指向 null，因为要重新插入节点，所以相当于初始化链表的工作
- 第三步，遍历 `node` 及之后的所有节点，通过头插法重新插入到基点之后。

![image-20220324224943803](image-Note004-%E9%80%86%E7%BD%AE%E5%8D%95%E9%93%BE%E8%A1%A8/image-20220324224943803.png)

逆置整个单链表的代码如下：

```c
void reverse(LNode **list){
    // 变量，记录基点的后继节点
    LNode *node=(*list)->next;
    // 将基点的 next 指针指向 null
    (*list)->next=NULL;
    // 遍历 node 及之后所有节点，通过头插法重新插入到基点之后
    while(node!=NULL){
        LNode* temp=node->next;

        node->next=(*list)->next;
        (*list)->next=node;

        node=temp;
    }
}
```

如果只是逆置后半个链表（如 `head -> 1 -> 2 -> 3 -> 4` 只逆置后半个链表后结果是 `head -> 1 -> 2 -> 4 -> 3`；如 `head -> 1 -> 2 -> 3 -> 4 -> 5`
只逆置后半个链表后结果是 `head -> 1 -> 2 -> 3 -> 5 -> 4`），那么代码如下：

```c
void reverseHalf(LNode** list){
    // 第一步，先找到链表的中间节点，即基点，使用快慢指针来找中间节点
    LNode *fast=*list;
    LNode *slow=*list;
    while(fast!=NULL&&fast->next!=NULL){
        fast=fast->next->next;
        slow=slow->next;
    }
    LNode* mid=slow;// 慢指针所指向的节点就是中间节点，即基点

    // 第二步，遍历基点之后的所有节点，通过头插法重新插入
    LNode* node=mid->next;// 基点的后继节点
    mid->next=NULL;// 将基点的 next 指针指向 null
    while(node!=NULL){
        LNode* temp=node->next;

        node->next=mid->next;
        mid->next=node;

        node=temp;
    }
}
```

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
 * 逆置整个单链表
 * @param list 待逆置的单链表
 */
void reverse(LNode **list){
    // 变量，记录基点的后继节点
    LNode *node=(*list)->next;
    // 将基点的 next 指针指向 null
    (*list)->next=NULL;
    // 遍历 node 及之后所有节点，通过头插法重新插入到基点之后
    while(node!=NULL){
        LNode* temp=node->next;

        node->next=(*list)->next;
        (*list)->next=node;

        node=temp;
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
    int nums[] = {1,2,3,4,5,6};
    int n = 6;
    createByTail(&list, nums, n);
    print(list);

    // 调用函数
    reverse(&list);
    print(list);
}
```
