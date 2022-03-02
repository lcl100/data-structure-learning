#include <stdio.h>
#include <malloc.h>

/**
 * 双链表节点结构体
 */
typedef struct DLNode {
    /**
     * 双链表节点数据域
     */
    int data;
    /**
     * 双链表节点的前驱节点，数据域
     */
    struct DLNode *prior;
    /**
     * 双链表节点的后继节点，数据域
     */
    struct DLNode *next;
} DLNode;

int size(DLNode *list);

/**
 * 初始化单链表
 * @param list 单链表
 */
void init(DLNode **list) {
    // 给双链表头结点分配空间
    *list = (DLNode *) malloc(sizeof(DLNode));
    // 将双链表的指针域都指向 null，不需要理会数据域
    (*list)->prior = NULL;
    (*list)->next = NULL;
}

/**
 * 通过尾插法创建双链表
 * @param list 双链表
 * @param nums 会放入到双链表中的数据
 * @param n 数组长度
 * @return 创建成功的双链表
 */
DLNode *createByTail(DLNode **list, int nums[], int n) {
    // 1.初始化链表，即创建双链表的头结点，也可以直接调用 init 方法进行初始化
    // 1.1 给双链表头结点分配空间
    *list = (DLNode *) malloc(sizeof(DLNode));
    // 1.2 将双链表的 prior 指针指向 null
    (*list)->prior = NULL;
    // 1.3 将双链表的 next 指针指向 null
    (*list)->next = NULL;

    // 使用尾插法，最重要的是知道链表的尾节点，初始时为链表的头结点
    DLNode *tailNode = *list;

    // 2.循环数组中元素，然后插入到链表的尾部
    for (int i = 0; i < n; i++) {
        // 2.1 创建新节点
        // 2.1.1 为新节点分配空间
        DLNode *newNode = (DLNode *) malloc(sizeof(DLNode));
        // 2.1.2 指定新节点的数据域
        newNode->data = nums[i];
        // 2.1.3 将新节点的 prior 指针指向 null
        newNode->prior = NULL;
        // 2.1.4 将新节点的 next 指针指向 null
        newNode->next = NULL;

        // 2.2 将新节点连接到链表中
        // 2.2.1 将原尾节点的 next 指针指向新节点
        tailNode->next = newNode;
        // 2.2.2 将新节点的 prior 指针指向原尾节点，这时已经将新节点连接到链表的尾部了
        newNode->prior = tailNode;
        // 2.2.3 不要忘记更新尾节点，让新节点成为新的尾节点，才能进行下一次插入
        tailNode = newNode;
    }
    return *list;
}

/**
 * 通过头插法创建双链表
 * @param list 双链表
 * @param nums 会放入到双链表中的数据
 * @param n 数组长度
 * @return 创建成功的双链表
 */
DLNode *createByHead(DLNode **list, int nums[], int n) {
    // 1.初始化链表，即创建双链表的头结点，也可以直接调用 init 方法进行初始化
    // 1.1 给双链表头结点分配空间
    *list = (DLNode *) malloc(sizeof(DLNode));
    // 1.2 将双链表的 prior 指针指向 null
    (*list)->prior = NULL;
    // 1.3 将双链表的 next 指针指向 null
    (*list)->next = NULL;

    // 2.循环数组中元素，然后插入到链表的头部
    for (int i = 0; i < n; i++) {
        // 2.1 创建新节点
        // 2.1.1 为新节点分配空间
        DLNode *newNode = (DLNode *) malloc(sizeof(DLNode));
        // 2.1.2 指定新节点的数据域
        newNode->data = nums[i];
        // 2.1.3 将新节点的 prior 指针指向 null
        newNode->prior = NULL;
        // 2.1.4 将新节点的 next 指针指向 null
        newNode->next = NULL;

        // 2.2 将新节点插入到链表的头部，但是在头结点的后面
        // 2.2.1 需要考虑链表为空的情况，当链表为空时新节点只能插入到头结点的后面
        if ((*list)->next == NULL) {
            // 2.2.1.1 链表为空，只需要将头结点的 next 指针指向新节点
            (*list)->next = newNode;
            // 2.2.1.2 然后将新节点的 prior 指针指向头结点，即完成了头结点和新节点的连接
            newNode->prior = *list;
        }
        // 2.2.2 如果链表不为空，则直接在头结点后面插入新节点即可，注意新节点和头结点和原链表第一个节点的连接
        else {
            // 2.2.2.1 保存原链表的第一个节点，必定不为 null
            DLNode *firstNode = (*list)->next;
            // 2.2.2.2 将原链表的第一个节点的 prior 指针指向新节点
            firstNode->prior = newNode;
            // 2.2.2.3 将新节点的 next 指针指向原链表的第一个节点，已经完成了新节点与原链表第一个节点的连接
            newNode->next = firstNode;
            // 2.2.2.4 将头结点的 next 指针指向新节点
            (*list)->next = newNode;
            // 2.2.2.5 将新节点的 prior 指针指向头结点，已经完成了新节点与头结点的连接
            newNode->prior = *list;
        }
    }
    return *list;
}

/**
 * 通过节点数据检索双链表中的节点
 * @param list 双链表
 * @param ele 节点数据值
 * @return 查找到的节点
 */
DLNode *findByEle(DLNode *list, int ele) {
    // 链表的第一个节点
    DLNode *node = list->next;
    // 1.循环链表所有节点，查找能够匹配值的节点
    while (node != NULL) {
        // 1.1 如果正在迭代的节点的数据域值等于指定值，表示找到该节点，则返回
        if (node->data == ele) {
            return node;
        }
        // 1.2 如果不等于则继续双链表的下一个节点
        node = node->next;
    }
    return NULL;
}

/**
 * 通过节点序号检索双链表中的节点
 * @param list 双链表
 * @param i 节点序号，从 1 开始
 * @return 查找到的节点
 */
DLNode *findByNum(DLNode *list, int i) {
    // 链表的第一个节点
    DLNode *node = list->next;
    // 计数器，记录当前遍历到第几个节点
    int count = 0;
    // 循环遍历链表
    while (node != NULL) {
        // 计数器加1，记录已经遍历的节点个数
        count++;
        // 查找到第 i 个节点，然后返回该节点
        if (count == i) {
            return node;
        }
        // 继续链表的下一个节点
        node = node->next;
    }
    return NULL;
}

/**
 * 向双链表中的指定序号位置插入节点
 * @param list 双链表
 * @param i 指定序号，从 1 开始
 * @param ele 节点数据值
 * @return 如果插入成功则返回 1，否则返回 0
 */
int insert(DLNode **list, int i, int ele) {
    // 0.参数校验
    if (i < 1 || i > size(*list)) {
        return 0;
    }

    // 1.首先查找第 i 个节点，直接调用我们已经写好的函数即可。在双链表中插入不需要找第 i-1 个节点，因为可以通过第 i 个节点的 prior 指针得到它的前驱节点
    DLNode *node = findByNum(*list, i);
    if (node == NULL) {
        return 0;
    }

    // 2.将新节点插入到链表指定位置
    // 2.1 创建新节点
    // 2.1.1 为新节点分配空间
    DLNode *newNode = (DLNode *) malloc(sizeof(DLNode));
    // 2.1.2 指定新节点的数据域
    newNode->data = ele;
    // 2.1.3 将新节点的 prior 指针指向 null
    newNode->prior = NULL;
    // 2.1.4 将新节点的 next 指针指向 null
    newNode->next = NULL;

    // 2.2 将新节点插入到链表中
    // 2.2.1 保存第 i 个节点的前驱节点，即第 i-1 个节点
    DLNode *temp = node->prior;
    // 2.2.2 将第 i 个节点的 prior 指针指向新节点
    node->prior = newNode;
    // 2.2.3 将新界的的 next 指针指向第 i 个节点，此时完成了新节点与第 i 个节点的连接
    newNode->next = node;
    // 2.2.4 将第 i-1 个节点的 next 指针指向新节点
    temp->next = newNode;
    // 2.2.5 将新节点的 prior 指针指向第 i-1 个节点，此时完成了新节点与第 i-1 个节点的连接
    newNode->prior = temp;
    return 1;
}

/**
 * 向双链表的尾部附加一个新节点
 * @param list 双链表
 * @param ele 新节点的数据值
 */
void append(DLNode **list, int ele) {
    // 1.获取到链表的最后一个节点，使用下面的方式能有效处理空链表的情况
    // 1.1 保存链表的最后一个节点，初始时为链表的头结点
    DLNode *node = (*list)->next;
    // 1.2 链表的第一个节点，用于遍历循环
    DLNode *lastNode = *list;
    // 1.3 循环遍历链表每一个节点
    while (node != NULL) {
        // 1.3.1 保存正在迭代的节点
        lastNode = node;
        // 1.3.2 继续链表的下一个节点
        node = node->next;
    }

    // 2.将新节点插入到链表的尾部
    // 2.1 创建新节点
    // 2.1.1 为新节点分配空间
    DLNode *newNode = (DLNode *) malloc(sizeof(DLNode));
    // 2.1.2 指定新节点的数据域
    newNode->data = ele;
    // 2.1.3 将新节点的 prior 指针指向 null
    newNode->prior = NULL;
    // 2.1.4 将新节点的 next 指针指向 null
    newNode->next = NULL;
    // 2.2 将新节点附加到链表的尾部
    // 2.2.1 将新节点的 prior 指针指向原链表最后一个节点
    newNode->prior = lastNode;
    // 2.2.2 将原链表最后一个节点的 next 指针指向新节点，此时完成了新节点和原链表最后一个节点的连接
    lastNode->next = newNode;
}

/**
 * 删除双链表中指定序号的节点
 * @param list 双链表
 * @param i 指定序号，从 1 开始
 * @param ele 保存被删除节点的数据值
 * @return 如果删除成功则返回 1，否则返回 0
 */
int removeByNum(DLNode **list, int i, int *ele) {
    // 0.参数校验
    if (i < 1 || i > size(*list)) {
        return 0;
    }

    // 1.找到第 i 个节点，利用我们已经写好的函数即可。也不需要找到第 i-1 个节点，因为我们通过第 i 个节点的 prior 指针获得
    DLNode *node = findByNum(*list, i);
    if (node == NULL) {
        return 0;
    }

    // 2.移除第 i 个节点
    // 2.1 需要判断待删除的节点是否还有后继节点，如果没有后继节点则表示该节点是链表的最后一个节点则需要特殊处理
    if (node->next == NULL) {
        // 2.1.1 如果被删除节点是最后一个节点，则只需要将第 i-1 个节点的 next 指针指向 null
        node->prior->next = NULL;
    }
    // 2.2 如果被删除节点不是链表的最后一个节点，则需要通过被删除节点的前驱节点和后继节点进行删除
    else {
        // 将第 i+1 个节点的 prior 指针指向第 i-1 个节点
        node->next->prior = node->prior;
        // 将第 i-1 个节点的 next 指针指向第 i+1 个节点，完成第 i 个节点的删除
        node->prior->next = node->next;
    }
    // 2.3 保存被删除节点的数据
    *ele = node->data;
    // 2.4 释放空间
    free(node);
    return 1;
}

/**
 * 双链表是否为空链表
 * @param list 双链表
 * @return 如果链表为空则返回 1，否则返回 0
 */
int isEmpty(DLNode *list) {
    return list->next == NULL;
}

/**
 * 获取双链表中的节点个数
 * @param list 双链表
 * @return 节点个数
 */
int size(DLNode *list) {
    // 计数器，记录链表的节点个数
    int count = 0;
    // 链表的第一个节点
    DLNode *node = list->next;
    // 循环双链表，统计节点个数
    while (node != NULL) {
        count++;
        node = node->next;
    }
    return count;
}

/**
 * 清空双链表
 * @param list 双链表
 */
void clear(DLNode **list) {
    // 链表的第一个节点
    DLNode *node = (*list)->next;
    // 循环遍历链表所有节点，回收空间
    while (node != NULL) {
        // 临时保存当前节点的后继节点
        DLNode *temp = node->next;
        // 释放当前节点的空间
        free(temp);
        // 继续链表的下一个节点
        node = temp;
    }
    // 将头节点的 next 指针指向 null
    (*list)->next = NULL;
}

/**
 * 打印双链表中所有节点数据
 * @param list 双链表
 */
void print(DLNode *list) {
    // 链表的第一个节点
    DLNode *node = list->next;
    // 循环遍历链表的所有节点
    printf("[");
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
    // 双链表一定要注意头结点和尾节点的考虑
    DLNode *list;

    // 初始化双链表
    printf("\n初始化双链表：\n");
    init(&list);
    print(list);

    // 通过尾插法创建双链表
    printf("\n通过尾插法创建双链表：\n");
    int nums1[] = {111, 222, 333, 444, 555};
    int n1 = 5;
    createByTail(&list, nums1, n1);
    print(list);

    // 通过头插法创建双链表
    printf("\n通过头插法创建双链表：\n");
    int nums2[] = {55, 44, 33, 22, 11};
    int n2 = 5;
    createByHead(&list, nums2, n2);
    print(list);

    // 向双链表插入元素
    printf("\n向双链表插入元素：\n");
    insert(&list, 1, 111);
    print(list);
    insert(&list, 3, 333);
    print(list);
    insert(&list, size(list), 777);
    print(list);

    // 向链表追加元素
    printf("\n向链表追加元素：\n");
    append(&list, 9999);
    print(list);

    // 删除双链表中的元素
    printf("\n删除双链表中的元素：\n");
    int ele;
    removeByNum(&list, 1, &ele);
    print(list);
    removeByNum(&list, 3, &ele);
    print(list);
    removeByNum(&list, size(list), &ele);
    print(list);

    // 双链表的长度
    printf("\n双链表中的节点个数：\n");
    int len;
    len = size(list);
    printf("%d\n", len);

    // 根据序号查找双链表中的元素
    printf("\n根据序号查找双链表中的元素：\n");
    DLNode *nodeByNum = findByNum(list, 3);
    printf("%d\n", nodeByNum->data);

    // 根据值查找双链表中的元素
    printf("\n根据值查找双链表中的元素：\n");
    DLNode *nodeByEle = findByEle(list, 777);
    printf("%d\n", nodeByEle->data);

    // 清空链表
    printf("\n清空双链表：\n");
    clear(&list);
    print(list);

    // 判断链表是否为空
    printf("\n双链表是否为空：\n");
    int empty = isEmpty(list);
    printf("%d\n", empty);
}