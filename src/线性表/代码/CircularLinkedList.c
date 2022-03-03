#include <stdio.h>
#include <stdlib.h>

/**
 * 循环单链表的节点
 */
typedef struct CLNode {
    /**
     * 链表节点的数据域
     */
    int data;
    /**
     * 链表节点的指针域，指向后继节点
     */
    struct CLNode *next;
} CLNode;

int size(CLNode *list);

/**
 * 对循环单链表进行初始化
 * @param list 循环单链表
 */
void init(CLNode **list) {
    // 为链表的头节点分配空间
    *list = (CLNode *) malloc(sizeof(CLNode));
    // 指定头节点的指针域，将其指向自身，表示是循环单链表，而普通单链表是指向 null
    (*list)->next = *list;// 注意，指向头结点本身
}

/**
 * 通过头插法创建循环单链表
 * @param list 已经初始化后的循环单链表
 * @param nums 待插入到单链表中的数据数组
 * @param n 数组长度
 * @return 创建成功的循环单链表
 */
CLNode *createByHead(CLNode **list, int nums[], int n) {
    // 1.初始化循环单链表，即创建循环单链表的头结点。也可以直接调用 init 函数来初始化
    // 1.1 为头结点分配空间
    *list = (CLNode *) malloc(sizeof(CLNode));
    // 1.2 修改头结点的 next 指针，将其指向自己，而普通单链表是指向 null
    (*list)->next = *list;// 注意，指向头结点本身

    // 2.遍历 nums 数组中所有元素，将其添加到链表中，完成链表的创建
    for (int i = 0; i < n; i++) {
        // 2.1 创建新节点
        // 2.1.1 给新节点分配空间
        CLNode *newNode = (CLNode *) malloc(sizeof(CLNode));
        // 2.1.2 指定新节点的数据域
        newNode->data = nums[i];
        // 2.1.3 将新节点的指针域置为 null，指向空
        newNode->next = NULL;

        // 2.2 将新节点插入到链表中，但是插入到头结点的后面
        // 2.2.1 将新节点的 next 指针指向链表第一个节点，此时完成了新节点和链表第一个节点链接
        newNode->next = (*list)->next;
        // 2.2.2 将链表头节点的 next 指针指向新节点，此时完成了链表头节点和新节点的链接
        (*list)->next = newNode;
    }

    return *list;
}

/**
 * 通过尾插法创建循环单链表
 * @param list  循环单链表
 * @param nums 待插入到单链表中的数据数组
 * @param n 数组长度
 * @return 创建成功的循环单链表
 */
CLNode *createByTail(CLNode **list, int nums[], int n) {
    // 1.初始化循环单链表，即创建循环单链表的头结点。也可以直接调用 init 函数来初始化
    // 1.1 为头结点分配空间
    *list = (CLNode *) malloc(sizeof(CLNode));
    // 1.2 修改头结点的 next 指针，将其指向自己，而普通单链表是指向 null
    (*list)->next = *list;// 注意，指向头结点本身

    // 保存链表的尾节点，初始为链表的头节点，即空链表的尾节点就是链表的头节点
    CLNode *tailNode = *list;

    // 2.循环数组 nums 中所有数据，插入到单链表中
    for (int i = 0; i < n; i++) {
        // 2.1 创建新节点
        // 2.1.1 给新节点分配空间
        CLNode *newNode = (CLNode *) malloc(sizeof(CLNode));
        // 2.1.2 指定新节点的数据域
        newNode->data = nums[i];
        // 2.1.3 将新节点的指针域置为 null，指向空
        newNode->next = NULL;

        // 2.2 将新节点追加到链表的尾部
        // 2.2.1 将链表原尾节点的 next 指针指向新节点，即让新节点成为链表的尾节点
        tailNode->next = newNode;
        // 2.2.2 然后将新节点（即链表新的尾节点）指向链表的头节点
        newNode->next = *list;
        // 2.2.3 然后将 tailNode 指向新节点（即新的尾节点）
        tailNode = newNode;
    }

    // 3.返回创建成功的链表
    return *list;
}

/**
 * 向链表的第 i 个位置插入新节点
 * 注意，如果是空链表（已经初始化），插入第 1 个节点会失败
 * @param list 循环单链表
 * @param i 序号，从 1 开始
 * @param ele 新节点的数据值
 * @return 如果插入成功则返回 1，否则返回 0
 */
int insert(CLNode **list, int i, int ele) {
    // 0.参数校验
    if (i < 0 || i > size(*list)) {
        return 0;
    }

    // 1.声明一些变量
    // 1.1 链表的第一个节点
    CLNode *node = (*list)->next;// 链表的第一个节点
    // 1.2 保存前驱节点，初始为链表的头节点
    CLNode *pre = *list;// 保存前驱节点
    // 1.3 计数器，记录当前节点是链表的第几个节点
    int count = 0;

    // 注意，使用下面的方式插入第 1 个节点时，如果链表为空则会失败
    // 找到第 i 个节点的前驱节点（即第 i-1 个节点），因为插入节点必须知道它的前驱节点
    // 2.遍历链表所有节点，找到第 i 个节点，然后插入新节点
    while (node != *list) {
        // 2.1 计数器加 1，表示已经迭代一个节点了
        count++;
        // 2.2 找到第 i 个节点，那么就可以插入新节点了
        if (count == i) {
            // 2.2.1 创建新节点
            // 2.2.1.1 给新节点分配空间
            CLNode *newNode = (CLNode *) malloc(sizeof(CLNode));
            // 2.2.1.2 给新节点的数据域赋值
            newNode->data = ele;
            // 2.2.1.3 给新节点的指针域赋为 null
            newNode->next = NULL;

            // 2.2.2 将新节点插入到链表中
            // 2.2.2.1 将第 i-1 个节点的 next 指针指向新节点
            pre->next = newNode;
            // 2.2.2.2 将新节点的 next 指针指向原第 i 个节点
            newNode->next = node;

            // 2.2.3 结束循环，跳出程序
            break;
        }
        // 2.3 保存当前节点为前驱节点
        pre = node;
        // 2.4 继续下一个节点
        node = node->next;
    }

    return 1;
}

/**
 * 在循环单链表的头部插入新节点
 * @param list 循环单链表
 * @param ele 待插入的元素
 */
void insertFirst(CLNode **list, int ele) {
    // 1.创建新节点
    // 1.1 为新节点分配空间
    CLNode *newNode = (CLNode *) malloc(sizeof(CLNode));
    // 1.2 为新节点的数据域指定内容
    newNode->data = ele;
    // 1.3 将新节点的指针域指向 null
    newNode->next = NULL;

    // 2.将新节点插入到链表的头部，成为新的链表第一个节点
    // 2.1 将新节点的 next 指针指向原链表的第一个节点
    newNode->next = (*list)->next;
    // 2.2 将头节点的 next 指针指向新节点，即让新节点成为链表的第一个节点
    (*list)->next = newNode;
}

/**
 * 向循环单链表末尾追加一个新节点
 * @param list 循环单链表
 * @param ele 新节点的数据值
 */
void insertLast(CLNode **list, int ele) {
    // 1.先找到链表的最后一个节点，即尾节点
    // 1.1 链表的第一个节点
    CLNode *node = (*list)->next;
    // 1.2 通过循环找到链表的最后一个节点，注意这里循环结束的条件是 node.next!=list，在循环结束之后，node 就是链表的尾节点
    while (node->next != *list) {
        node = node->next;
    }

    // 2.创建新节点然后插入到链表的尾部
    // 2.1 创建新节点
    // 2.1.1 为新节点分配空间
    CLNode *newNode = (CLNode *) malloc(sizeof(CLNode));
    // 2.1.2 为新节点的数据域指定内容
    newNode->data = ele;
    // 2.1.3 将新节点的指针域指向 null
    newNode->next = NULL;

    // 2.2 将新节点追加到循环单链表的末尾
    // 2.2.1 将链表的原尾节点的 next 指针指向新节点，已经完成了新节点链接到链表中
    newNode->next = node->next;// 其实 node->next 就是链表的头结点，所以 newNode->next=*list 也是可以的
    // 2.2.2 将新节点的 next 指针指向链表的头节点，完成了尾节点与头节点的链接
    node->next = newNode;
}

/**
 * 删除循环单链表中第 i 个节点
 * @param list 循环单链表
 * @param i 指定序号，从 1 开始
 * @param ele 保存被删除节点的数据域
 * @return 如果删除成功则返回 1，否则返回 0
 */
int removeByNum(CLNode **list, int i, int *ele) {
    // 0.参数校验
    if (i < 0 || i > size(*list)) {
        return 0;
    }

    // 1.声明一些变量
    // 1.1 链表的第一个节点
    CLNode *node = (*list)->next;
    // 1.2 保存前驱节点，初始为链表的头节点
    CLNode *pre = *list;
    // 1.3 计数器，记录当前是链表的第几个节点
    int count = 0;

    // 2.遍历链表，寻找第 i 个节点，通过循环计数的方式来找到
    while (node != *list) {
        // 2.1 计数器加 1
        count++;
        // 2.2 找到待删除节点，即比较计数器与参数值是否相等，如果相等则删除节点
        if (count == i) {
            // 2.2.1 删除 node 节点，即将第 i-1 个节点的 next 指针指向第 i+1 个节点，这样就删除了第 i 个节点
            pre->next = node->next;
            // 2.2.2 保存被删除节点的数据域值
            *ele = node->data;
            // 2.2.3 释放节点空间
            free(node);
            // 2.2.4 删除成功则返回 1
            return 1;
        }
        // 2.3 保存当前节点为前驱节点
        pre = node;
        // 2.4 继续下一个节点
        node = node->next;
    }

    return 0;
}

/**
 * 根据值删除循环单链表元素
 * @param list 循环单链表
 * @param ele 被删除节点的数据域值
 */
void removeByEle(CLNode **list, int ele) {
    // 0.声明一些变量
    // 0.1 链表的第一个节点，其实主要用于遍历链表
    CLNode *node = (*list)->next;
    // 0.1 保存值等于 ele 的节点的前驱节点
    CLNode *pre = *list;

    // 1.循环链表，查找节点值等于 ele 的节点，然后进行删除
    while (node != *list) {
        // 1.1 如果找到值等于 ele 的节点
        if (node->data == ele) {
            // 1.1.1 删除 node 节点，即将第 i-1 个节点的 next 指针指向第 i+1 个节点，这样就删除了第 i 个节点
            pre->next = node->next;
            // 1.1.2 释放节点空间
            free(node);
            // 1.1.3 跳出循环
            break;
        }
        // 1.2 保存当前节点为前驱节点
        pre = node;
        // 1.3 继续链表的下一个节点
        node = node->next;
    }
}

/**
 * 删除链表的第一个节点
 * @param list 循环单链表
 * @param ele 被删除的节点的数据域值
 */
void removeFirst(CLNode **list, int *ele) {
    // 链表的第一个节点
    CLNode *node = (*list)->next;
    // 删除第一个节点，即将链表的头节点的 next 指针指向原链表的第二个节点（即让原链表第二个节点成为新的链表第一个节点）
    (*list)->next = node->next;
    // 保存被删除节点的数据域值
    *ele = node->data;
    // 释放节点空间
    free(node);
}

/**
 * 删除循环单链表的尾节点
 * @param list 循环单链表
 * @param ele 被删除节点的数据域值
 */
void removeLast(CLNode **list, int *ele) {
    // 0.声明一些变量
    // 0.1 链表的第一个节点
    CLNode *node = (*list)->next;
    // 0.2 记录尾节点的前驱节点
    CLNode *pre = *list;

    // 1.找到链表的尾节点和尾节点的前驱节点
    while (node->next != *list) {// 注意循环结束的条件是 node.next!=list，当循环结束之后 node 就是链表的尾节点
        // 1.1 保存当前节点为前驱节点
        pre = node;
        // 1.2 继续链表的下一个节点
        node = node->next;
    }

    // 2.删除链表的最后一个节点
    // 2.1 删除节点 node
    pre->next = node->next;// 其实等价于 pre->next=*list
    // 2.2 保存被删除节点的数据域值
    *ele = node->data;
    // 2.3 释放节点空间
    free(node);
}

/**
 * 通过序号在链表中检索节点
 * @param list 循环单链表
 * @param i 序号，从 1 开始
 * @return 如果找到第 i 个节点则返回，否则返回 NULL
 */
CLNode *findByNum(CLNode *list, int i) {
    // 0.参数校验
    if (i < 1 || i > size(list)) {
        return NULL;
    }

    // 1.声明一些变量
    // 1.1 链表的第一个节点
    CLNode *node = list->next;
    // 1.2 计数器，记录当前正在遍历的节点是链表的第几个节点
    int count = 0;

    // 2.遍历链表所有节点，找到第 i 个节点
    while (node != list) {
        // 2.1 计数器加 1，表示已经迭代了一个节点
        count++;
        // 2.2 比较计数器的值与参数值是否相等，如果相等则表示找到了第 i 个节点则返回该节点
        if (count == i) {
            return node;
        }
        // 2.3 继续下一个节点
        node = node->next;
    }
    return NULL;
}

/**
 * 通过数据值在链表中检索节点
 * @param list 循环单链表
 * @param ele 指定数据值
 * @return 如果找到则返回对应值的节点，如果没有找到则返回 NULL
 */
CLNode *findByEle(CLNode *list, int ele) {
    // 链表的第一个节点
    CLNode *node = list->next;

    // 1.遍历链表所有节点，比较节点的值与输入的参数值是否相等，如果相等则返回该节点
    while (node != list) {
        // 1.1 比较当前节点的数据域是否与参数值相等，如果相等则表示找到指定值的节点，那么返回即可
        if (node->data == ele) {
            return node;
        }
        // 1.2 继续下一个节点
        node = node->next;
    }
    return NULL;
}

/**
 * 统计循环单链表的节点个数
 * @param list 循环单链表
 * @return 链表的长度
 */
int size(CLNode *list) {
    // 计数器，记录链表的节点个数
    int count = 0;
    // 链表的第一个节点
    CLNode *node = list->next;
    // 遍历链表所有节点，统计个数，注意结束循环的条件
    while (node != list) {
        // 统计个数
        count++;
        // 继续下一个节点
        node = node->next;
    }
    // 返回节点个数
    return count;
}

/**
 * 判断链表是否为空
 * @param list 待判断的循环单链表
 * @return 如果为空则返回 1，否则返回 0
 */
int isEmpty(CLNode *list) {
    // 判断链表的第一个节点是否又是头结点，如果是则表示链表为空
    return list->next == list;
}

/**
 * 清空循环单链表
 * @param list 待清空的循环单链表
 */
void clear(CLNode **list) {
    // 链表的第一个节点
    CLNode *node = (*list)->next;
    // 循环链表所有节点，删除节点，释放空间
    while (node != *list) {
        // 临时保存当前节点的后继节点
        CLNode *temp = node->next;
        // 释放空间
        free(node);
        // 继续下一个节点
        node = temp;
    }
    // 最后重新将链表的头结点的 next 指针指向自身，仍然是循环单链表
    (*list)->next = *list;
}

/**
 * 打印循环单链表
 * @param list 待打印的循环单链表
 */
void print(CLNode *list) {
    printf("[");
    CLNode *node = list->next;
    while (node != list) {
        printf("%d", node->data);
        if (node->next != list) {
            printf(", ");
        }
        node = node->next;
    }
    printf("]\n");
}

int main() {
    // 声明循环单链表
    CLNode *list;

    // 初始化循环单链表
    printf("初始化循环单链表：\n");
    init(&list);
    print(list);

    // 通过头插法创建循环单链表
    printf("\n通过头插法创建循环单链表：\n");
    int nums1[] = {11, 22, 33, 44, 55};
    int n1 = 5;
    createByHead(&list, nums1, n1);
    print(list);

    // 通过尾插法创建循环单链表
    printf("\n通过尾插法创建循环单链表：\n");
    int nums2[] = {111, 222, 333, 444, 555};
    int n2 = 5;
    createByTail(&list, nums2, n2);
    print(list);

    // 在指定位置插入新节点
    printf("\n在指定位置插入新节点：\n");
    insert(&list, 1, 6666);
    print(list);
    insert(&list, 3, 7777);
    print(list);
    insert(&list, size(list), 8888);
    print(list);

    // 在链表的头部插入节点
    printf("\n在链表的头部插入节点：\n");
    insertFirst(&list, 9999);
    print(list);

    // 在链表的尾部插入节点
    printf("\n在链表的尾部插入节点：\n");
    insertLast(&list, 99999);
    print(list);

    // 删除指定位置的节点
    printf("\n删除指定位置的节点：\n");
    int ele;
    removeByNum(&list, 1, &ele);
    print(list);
    removeByNum(&list, 3, &ele);
    print(list);
    removeByNum(&list, size(list), &ele);
    print(list);

    // 删除指定值的节点
    printf("\n删除指定值的节点：\n");
    removeByEle(&list, 333);
    print(list);

    // 删除链表第一个节点
    printf("\n删除链表第一个节点：\n");
    removeFirst(&list, &ele);
    print(list);

    // 删除链表最后一个节点
    printf("\n删除链表最后一个节点：\n");
    removeLast(&list, &ele);
    print(list);

    // 查找指定位置的节点
    printf("\n查找指定位置的节点：\n");
    CLNode *nodeByNum = findByNum(list, 2);
    printf("%d\n", nodeByNum->data);

    // 查找指定值的节点
    printf("\n查找指定值的节点：\n");
    CLNode *nodeByEle = findByEle(list, 8888);
    printf("%d\n", nodeByEle->data);

    // 链表的长度
    printf("\n链表的长度：\n");
    int len = size(list);
    printf("%d\n", len);

    // 清空循环单链表
    printf("\n清空循环单链表：\n");
    clear(&list);
    print(list);

    // 循环单链表是否为空
    printf("\n循环单链表是否为空：\n");
    int empty = isEmpty(list);
    printf("%d\n", empty);
}