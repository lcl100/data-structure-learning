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

int size(LNode *list);

int remove(LNode **list, int i, int *ele);

/**
 * 初始化单链表
 * @param list 待初始化的单链表
 */
void init(LNode **list) {
    // 创建头结点，分配空间
    *list = (LNode *) malloc(sizeof(LNode));
    // 同时将头节点的 next 指针指向 NULL，因为空链表没有任何节点
    (*list)->next = NULL;
}

/**
 * 通过头插法创建单链表
 * @param list 单链表
 * @param nums 数据数组
 * @param n 数组长度
 * @return 创建成功的单链表
 */
LNode *createByHead(LNode **list, int nums[], int n) {
    // 1.初始化单链表
    // 创建链表必须要先初始化链表，也可以选择直接调用 init() 函数
    *list = (LNode *) malloc(sizeof(LNode));
    (*list)->next = NULL;

    // 2.通过循环将数组中所有值通过头插法插入到单链表中
    for (int i = 0; i < n; i++) {
        // 2.1 创建新节点，并指定数据域和指针域
        // 2.1.1 创建新结点，分配空间
        LNode *newNode = (LNode *) malloc(sizeof(LNode));
        // 2.1.2 给新节点的数据域指定值
        newNode->data = nums[i];
        // 2.1.3 给新节点的指针域指定为 null
        newNode->next = NULL;

        // 2.2 将新节点插入到单链表的头部，但是在头结点的后面
        // 2.2.1 获取到单链表的第一个节点，即头结点的后继节点
        LNode *firstNode = (*list)->next;// 单链表的第一个节点
        // 2.2.2 将头结点的 next 指针指向新节点
        newNode->next = firstNode;
        // 2.2.3 将新节点的 next 指针指向原单链表的第一个节点，此时新节点成为了单链表头结点的后继节点
        (*list)->next = newNode;
    }
    return *list;
}

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
 * 在单链表的第 i 个结点（从 1 开始）前插入一个结点
 * @param list 单链表
 * @param i 节点序号，从 1 开始
 * @param ele 待插入的数据
 * @return 如果插入成功则返回 1，如果插入失败则返回 0
 */
int insert(LNode **list, int i, int ele) {
    // 0.校验参数
    if (i < 1 || i > size(*list) + 1) {// 当 i=1 并且单链表为空时也能有效插入
        return 0;
    }

    // 1.计算第 i 个节点的前驱节点。注意，第一个节点的前驱节点是头结点
    // 1.1 声明三个变量
    LNode *iPreNode = *list;// 用来保存第 i 个节点的前驱节点，初始时链表第一个节点的前驱节点是头结点
    LNode *node = (*list)->next;// 用来保存链表中的每一个节点为了遍历循环，初始时链表的第一个节点
    int count = 1;// 计数器，记录遍历次数，初始为 1 而不能是 0，因为 i 表示节点的序号（序号从 1 开始的）
    // 1.2 找到第 i 个节点的前驱节点，循环 i-1 次
    while (count < i) {
        // 1.2.1 计数器加 1，表示已经遍历 1 次
        count++;
        // 1.2.2 保存当前节点为前驱节点
        iPreNode = node;
        // 1.2.3 继续下一个节点
        node = node->next;
    }

    // 2.将新节点插入到链表中
    // 2.1 创建新节点
    // 2.1.1 为新节点分配空间
    LNode *newNode = (LNode *) malloc(sizeof(LNode));
    // 2.1.2 为新节点指定数据域
    newNode->data = ele;
    // 2.1.3 为新节点指定指针域，初始时都指向 null
    newNode->next = NULL;
    // 2.2 将新节点连接到链表中
    // 2.2.1 将新节点的 next 指针指向第 i 个节点的前驱节点的后继节点（实际上就是第 i 个节点）上
    newNode->next = iPreNode->next;
    // 2.2.2 将第 i 个节点的 next 指针指向新节点
    iPreNode->next = newNode;
    return 1;
}

/**
 * 删除单链表中第 i 个结点
 * @param list 单链表
 * @param i 节点序号，从 1 开始
 * @param ele 被删除节点的数据
 * @return 如果删除成功则返回 1，如果删除失败则返回 0
 */
int remove(LNode **list, int i, int *ele) {
    // 0.校验参数
    if (i < 1 || i > size(*list)) {
        return 0;
    }

    // 1.计算第 i 个节点的前驱节点。注意，第一个节点的前驱节点是头结点
    // 1.1 声明三个变量
    LNode *iPreNode = *list;// 用来保存第 i 个节点的前驱节点，初始时链表第一个节点的前驱节点是头结点
    LNode *node = (*list)->next;// 用来保存链表中的每一个节点为了遍历循环，初始时链表的第一个节点
    int count = 1;// 计数器，记录遍历次数，初始为 1 而不能是 0，因为 i 表示节点的序号（序号从 1 开始的）
    // 1.2 找到第 i 个节点的前驱节点，循环 i-1 次
    while (count < i) {
        // 1.2.1 计数器加 1，表示已经遍历 1 次
        count++;
        // 1.2.2 保存当前节点为前驱节点
        iPreNode = node;
        // 1.2.3 继续下一个节点
        node = node->next;
    }

    // 2.删除第 i 个节点
    // 2.1 得到第 i 个节点
    LNode *iNode = iPreNode->next;
    // 2.2 保存被删除节点的数据
    *ele = iNode->data;
    // 2.3 删除第 i 个节点，即将第 i 个节点的前驱节点的 next 指针指向第 i 个节点的后继节点
    iPreNode->next = iNode->next;
    // 2.4 释放被删除节点的空间
    free(iNode);

    return 1;
}

/**
 * 删除单链表中指定值的结点。
 * 注意，只会删除找到的第一个节点，如果有多个节点的值都等于指定值则只会删除第一个。
 * @param list 单链表
 * @param ele 指定值
 * @return 如果删除成功则返回 1，否则返回 0
 */
int removeEle(LNode **list, int ele) {
    // 链表的第一个节点
    LNode *node = (*list)->next;
    // 保存前驱节点，链表第一个节点的前驱节点是头结点
    LNode *pre = *list;
    // 循环单链表
    while (node != NULL) {
        // 发现待删除的节点
        if (node->data == ele) {
            // 删除节点，即将被删除节点的前驱节点的 next 指针指向被删除节点的后后继节点
            pre->next = node->next;
            // 释放被删除节点的空间
            free(node);
            return 1;
        }
        pre = node;
        node = node->next;
    }
    return 0;
}

/**
 * 删除单链表中结点值等于 ele 的所有结点
 * @param list 单链表
 * @param ele 待删除节点的值
 */
void removeAllEle(LNode **list, int ele) {
    // 链表的第一个节点
    LNode *node = (*list)->next;
    // 保存前驱节点，初始化链表第一个节点的前驱节点就是链表的头结点
    LNode *pre = *list;
    // 循环链表
    while (node != NULL) {
        // 如果查找到要删除的节点
        if (node->data == ele) {
            // 保存被删除的节点
            LNode *temp = node;
            // 删除节点，但这里不能用 pre->next = node->next; 来删除节点
            node = node->next;
            pre->next = node;
            // 释放被删除节点的空间
            free(temp);
        } else {
            // 如果没有找到则继续判断链表的下一个节点，但注意更新 node 和 pre
            node = node->next;
            pre = pre->next;
        }
    }
}

/**
 * 计算单链表的长度，即节点个数
 * @param list 单链表
 * @return 链表节点个数
 */
int size(LNode *list) {
    // 计数器，记录链表的节点个数
    int count = 0;
    // 链表的第一个节点
    LNode *node = list->next;
    // 循环遍历链表
    while (node != NULL) {
        // 计数器加1
        count++;
        // 继续链表的下一个节点
        node = node->next;
    }
    // 返回链表节点个数
    return count;
}

/**
 * 判断单链表是否为空
 * @param list 单链表
 * @return 如果链表为空则返回 1，否则返回 0
 */
int isEmpty(LNode *list) {
    // 只需要判断链表的第一个节点是否存在即可
    return list->next == NULL;
}

/**
 * 清空单链表
 * @param list 单链表
 */
void clear(LNode **list) {
    // 链表的第一个节点
    LNode *node = (*list)->next;
    // 循环遍历单链表所有节点
    while (node != NULL) {
        // 保存当前节点的下一个节点
        LNode *temp = node->next;
        // 释放当前节点的空间
        free(node);
        // 继续链表的下一个节点
        node = temp;
    }
    // 最重要的是，将链表的头结点的 next 指针指向 null
    (*list)->next = NULL;
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

    // 初始化单链表
    printf("初始化单链表：\n");
    init(&list);
    print(list);

    // 通过头插法创建单链表
    printf("\n通过头插法创建单链表：\n");
    int nums1[] = {11, 22, 33, 44, 55};
    int n1 = 5;
    createByHead(&list, nums1, n1);
    print(list);

    // 通过尾插法创建单链表
    printf("\n通过尾插法创建单链表：\n");
    int nums2[] = {11, 22, 33, 44, 55};
    int n2 = 5;
    createByTail(&list, nums2, n2);
    print(list);

    // 在链表指定位置插入新元素
    printf("\n在链表指定位置插入新元素：\n");
    insert(&list, 1, 999);
    print(list);
    insert(&list, 4, 888);
    print(list);
    insert(&list, size(list), 777);
    print(list);

    // 删除链表指定位置的元素
    printf("\n删除链表指定位置的元素：\n");
    int ele;
    remove(&list, 1, &ele);
    print(list);
    remove(&list, 3, &ele);
    print(list);
    remove(&list, size(list), &ele);
    print(list);

    // 删除链表中指定值的元素
    printf("\n删除链表中指定值的元素：\n");
    removeEle(&list, 33);
    print(list);
    removeEle(&list, 777);
    print(list);

    // 删除链表中所有等于指定值的节点
    printf("\n删除链表中所有等于指定值的节点：\n");
    int nums3[] = {11, 22, 11, 33, 11, 11, 44, 11};
    int n3 = 8;
    createByTail(&list, nums3, n3);
    removeAllEle(&list, 11);
    print(list);

    // 链表的长度
    printf("\n链表的长度：\n");
    int len = size(list);
    printf("%d\n", len);

    // 链表是否为空
    printf("\n链表是否为空：\n");
    int empty = isEmpty(list);
    printf("%d\n", empty);

    // 清空链表所有元素
    printf("\n清空链表所有元素：\n");
    clear(&list);
    print(list);
}