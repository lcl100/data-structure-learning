# 寻找链表的中间节点

通常我们可能需要寻找链表的中间节点，但对于链表节点个数是偶数还是奇数有所不同。

如果链表节点个数是奇数个，则 L/2+1 是中间节点（如 `{1, 2, 3}` 中 2 是中间节点）；如果链表节点个数是偶数个，则 L/2 和 L/2+1 都是中间节点（如 `{1, 2, 3, 4}` 中 2 和 3 都是中间节点）。

有两种思路：

- 第一种思路，先统计链表节点个数 `L`。如果链表节点个数是奇数则第 `L/2+1` 个节点 是链表的中间节点；如果链表节点个数是偶数个，则 `L/2` 和 `L/2+1` 都是中间节点。
- 第二种思路，使用快慢指针的方式，快指针 `fast` 前进两步，慢指针 `slow` 前进一步，当快指针 `fast` 到达链表尾部时，慢指针 `slow` 刚好到达链表的中间。如果链表节点个数是奇数则 `slow` 是链表的中间节点；如果链表节点个数是偶数则 `slow` 和 `slow->next` 都是链表的中间节点。（注意，带头结点的单链表，初始情况下 `fast` 和 `slow` 都是从头结点开始的）

解法二图解：

![image-20220324231855970](image-Note003-%E5%AF%BB%E6%89%BE%E9%93%BE%E8%A1%A8%E7%9A%84%E4%B8%AD%E9%97%B4%E8%8A%82%E7%82%B9/image-20220324231855970.png)

![image-20220324232544414](image-Note003-%E5%AF%BB%E6%89%BE%E9%93%BE%E8%A1%A8%E7%9A%84%E4%B8%AD%E9%97%B4%E8%8A%82%E7%82%B9/image-20220324232544414.png)

解法一核心代码：

```c
/**
 * 寻找单链表的中间节点。
 * 如果链表节点个数是奇数个，则 L/2+1 是中间节点（如 `{1, 2, 3}` 中 2 是中间节点）；
 * 如果链表节点个数是偶数个，则 L/2 和 L/2+1 都是中间节点（如 `{1, 2, 3, 4}` 中 2 和 3 都是中间节点）。
 * @param list 带头节点的单链表
 */
int findMid(LNode* list){
    // 统计链表中的节点个数
    int len=0;
    LNode* node=list->next;
    while(node!=NULL){
        len++;
        node=node->next;
    }

    // 计算链表中间节点的序号，如果是偶数则是 L/2，如果是奇数则是 L/2+1
    int num;
    if(len%2==0){
        num=len/2;
    }else{
        num=len/2+1;
    }
    
    // 扫描链表，查找第 num 个节点就是链表的中间节点
    int count=0;
    node=list->next;
    while(node!=NULL){
        count++;
        if(count==num){
            break;
        }
        node=node->next;
    }
    return node->data;
}
```

解法二核心代码：

```c
/**
 * 寻找单链表的中间节点。
 * 如果链表节点个数是奇数个，则 L/2+1 是中间节点（如 `{1, 2, 3}` 中 2 是中间节点）；
 * 如果链表节点个数是偶数个，则 L/2 和 L/2+1 都是中间节点（如 `{1, 2, 3, 4}` 中 2 和 3 都是中间节点）。
 * @param list 带头节点的单链表
 */
int findMid(LNode* list){
    // 初始快慢指针都指向链表的头节点，不要指向链表第一个节点，否则如果链表节点是偶数个则最终快指针会指向 L/2+1 这个节点
    LNode* fast=list;
    LNode* slow=list;
    // 以快指针到链表尾结束循环。注意，first->next!=NULL 是为了避免 fast->next 如果为 NULL，再获取它的后继节点报错，所以需要判断first->next!=NULL。
    while(fast!=NULL&&fast->next!=NULL){
        // 快指针移动两步
        fast=fast->next->next;
        // 慢指针移动一步
        slow=slow->next;
    }
    // 结束循环后，快指针刚好走到链表尾，此时慢指针指向链表的中间节点
    // 如果链表节点个数为奇数个，则慢指针指向链表的第 L/2+1 个节点
    // 如果链表节点个数为偶数个，则慢指针指向链表的第 L/2 个节点
    return slow->data;
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
 * 寻找单链表的中间节点。
 * 如果链表节点个数是奇数个，则 L/2+1 是中间节点（如 `{1, 2, 3}` 中 2 是中间节点）；
 * 如果链表节点个数是偶数个，则 L/2 和 L/2+1 都是中间节点（如 `{1, 2, 3, 4}` 中 2 和 3 都是中间节点）。
 * @param list 带头节点的单链表
 */
int findMid(LNode *list) {
    // 初始快慢指针都指向链表的头节点，不要指向链表第一个节点，否则如果链表节点是偶数个则最终快指针会指向 L/2+1 这个节点
    LNode *fast = list;
    LNode *slow = list;
    // 以快指针到链表尾结束循环。注意，first->next!=NULL 是为了避免 fast->next 如果为 NULL，再获取它的后继节点报错，所以需要判断first->next!=NULL。
    while (fast != NULL && fast->next != NULL) {
        // 快指针移动两步
        fast = fast->next->next;
        // 慢指针移动一步
        slow = slow->next;
    }
    // 结束循环后，快指针刚好走到链表尾，此时慢指针指向链表的中间节点
    // 如果链表节点个数为奇数个，则慢指针指向链表的第 L/2+1 个节点
    // 如果链表节点个数为偶数个，则慢指针指向链表的第 L/2 个节点
    return slow->data;
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
    // 链表节点个数为奇数个的情况
    // 声明单链表
    LNode *list1;
    int nums1[] = {1, 2, 3, 4, 5};
    int n1 = 5;
    createByTail(&list1, nums1, n1);
    print(list1);
    // 调用函数
    int mid1 = findMid(list1);
    printf("中间节点：%d\n", mid1);

    // 链表节点个数为偶数个的情况
    // 声明单链表
    LNode *list2;
    int nums2[] = {1, 2, 3, 4, 5, 6};
    int n2 = 6;
    createByTail(&list2, nums2, n2);
    print(list2);
    // 调用函数
    int mid2 = findMid(list2);
    printf("中间节点：%d\n", mid2);
}
```