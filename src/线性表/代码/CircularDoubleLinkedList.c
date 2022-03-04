#include <stdio.h>
#include <malloc.h>

/**
 * 循环双链表的节点
 */
typedef struct CDLNode {
    /**
     * 节点的数据域
     */
    int data;
    /**
     * 节点的指针域，指向前驱节点
     */
    struct CDLNode *prior;
    /**
     * 节点的指针域，指向后继节点
     */
    struct CDLNode *next;
} CDLNode;

int size(CDLNode *list);

CDLNode *findByEle(CDLNode *list, int ele);

/**
 * 循环双链表的初始化函数
 * @param list 带初始化的循环双链表
 */
void init(CDLNode **list) {
    // 1.初始化循环双链表，即创建头结点。头结点的前驱节点指针和后继节点指针都指向自身，表示循环
    // 1.1 为头结点分配空间
    *list = (CDLNode *) malloc(sizeof(struct CDLNode));
    // 1.2 将头结点的 prior 指针指向自身
    (*list)->prior = *list;
    // 1.3 将头结点的 next 指针指向自身
    (*list)->next = *list;
}

/**
 * 通过头插法创建循环双链表
 * @param list 循环双链表
 * @param nums 待插入到双链表中的数据数组
 * @param n 数组长度
 * @return 创建成功的循环双链表
 */
CDLNode *createByHead(CDLNode **list, int nums[], int n) {
    // 1. 初始化循环双链表，即创建头结点，也可以直接调用 init 方法进行初始化
    // 1.1 为头结点分配空间
    *list = (CDLNode *) malloc(sizeof(CDLNode));
    // 1.2 将头结点的 prior 指针指向自身
    (*list)->prior = *list;// 注意，将头结点的 prior 和 next 指针指向自身
    // 1.3 将头结点的 next 指针指向自身
    (*list)->next = *list;

    /// 2.循环输入数组 nums，将每个元素插入到链表中
    for (int i = 0; i < n; i++) {
        // 2.1 创建新节点
        // 2.1.1 给新节点分配空间
        CDLNode *newNode = (CDLNode *) malloc(sizeof(CDLNode));
        // 2.1.2 给新节点的数据域指定内容
        newNode->data = nums[i];
        // 2.1.3 将新节点的 prior 指针指向 null
        newNode->prior = NULL;
        // 2.1.4 将新节点的 next 指针指向 null
        newNode->next = NULL;

        // 2.2 将新节点插入到链表的头部，即头结点的后面
        // 2.2.1 修改新节点的 next 指针，指向原链表的第一个节点
        newNode->next = (*list)->next;
        // 2.2.2 修改新节点的 prior 指针，指向原链表的头结点
        newNode->prior = *list;
        // 2.2.3 将原链表的第一个节点的 prior 指针指向新节点
        (*list)->next->prior = newNode;
        // 2.2.4 将头节点的 next 指针指向新节点
        (*list)->next = newNode;
    }

    // 3.返回创建成功的循环双链表
    return *list;
}

/**
 * 通过尾插法创建循环双链表
 * @param list 循环双链表
 * @param nums 待插入到双链表中的数据数组
 * @param n 数组长度
 * @return 创建成功的循环双链表
 */
CDLNode *createByTail(CDLNode **list, int nums[], int n) {
    // 1. 初始化循环双链表，即创建头结点，也可以直接调用 init 方法进行初始化
    // 1.1 为头结点分配空间
    *list = (CDLNode *) malloc(sizeof(CDLNode));
    // 1.2 将头结点的 prior 指针指向自身
    (*list)->prior = *list;// 注意，将头结点的 prior 和 next 指针指向自身
    // 1.3 将头结点的 next 指针指向自身
    (*list)->next = *list;

    // 保存链表的尾节点，其实可以利用循环双链表的特性，直接使用 list.prior 来获得链表的尾节点
    CDLNode *tailNode = *list;

    // 2.循环输入数组 nums，将每个元素插入到链表中
    for (int i = 0; i < n; i++) {
        // 2.1 创建新节点
        // 2.1.1 给新节点分配空间
        CDLNode *newNode = (CDLNode *) malloc(sizeof(CDLNode));
        // 2.1.2 给新节点的数据域指定内容
        newNode->data = nums[i];
        // 2.1.3 将新节点的 prior 指针指向 null
        newNode->prior = NULL;
        // 2.1.4 将新节点的 next 指针指向 null
        newNode->next = NULL;

        // 2.2 将新节点插入到链表的尾部
        // 2.2.1 将链表原尾节点的 next 指针指向新节点
        tailNode->next = newNode;
        // 2.2.2 将新节点的 prior 指针指向链表原尾节点
        newNode->prior = tailNode;
        // 2.2.3 将新节点的 next 指针指向链表的头结点
        newNode->next = *list;
        // 2.2.4 注意，将头结点的 prior 指针指向新节点（即新的尾节点），这样才能循环起来
        (*list)->prior = newNode;
        // 2.2.5 更新记录链表尾节点的变量 tailNode
        tailNode = newNode;
    }

    // 3.返回创建成功的链表
    return *list;
}

/**
 * 在第 i 个位置插入新节点
 * @param list 循环双链表
 * @param i 待插入新节点的序号位置，从 1 开始
 * @param ele 新节点的数据值
 * @return 如果插入成功则返回 1，否则返回 0
 */
int insert(CDLNode **list, int i, int ele) {
    // 0.参数校验
    if (i < 1 || i > size(*list)) {
        return 0;
    }

    // 变量，记录链表的每一个节点，从第一个节点开始
    CDLNode *node = (*list)->next;
    // 变量，计数器，记录已经迭代的节点个数
    int count = 0;

    // 1.循环遍历链表，寻找第 i 个节点
    while (node != *list) {
        // 1.1 计数器加 1，表示已经迭代一个节点
        count++;
        // 1.2 找到第 i 个节点
        if (count == i) {
            // 1.2.1 创建新节点
            // 1.2.1.1 为新节点分配空间
            CDLNode *newNode = (CDLNode *) malloc(sizeof(CDLNode));
            // 1.2.1.2 为新节点指定数据域
            newNode->data = ele;
            // 1.2.1.3 将新节点的 prior 指针指向 null
            newNode->prior = NULL;
            // 1.2.1.4 将新节点的 next 指针指向 null
            newNode->next = NULL;

            // 1.2.2 将新节点插入到链表中
            // 1.2.2.1 将第 i-1 个节点的 next 指针指向新节点
            node->prior->next = newNode;
            // 1.2.2.2 将新节点的 prior 指针指向第 i-1 个节点（即第 i 个节点的前驱节点）
            newNode->prior = node->prior;
            // 1.2.2.3 将新节点的 next 指针指向第 i 个节点
            newNode->next = node;
            // 1.2.2.4 将第 i 个节点的 prior 指针指向新节点，此时完成了新节点与第 i 个节点的链接
            node->prior = newNode;

            return 1;
        }
        // 1.3 继续链表的下一个节点
        node = node->next;
    }
    return 0;
}

/**
 * 插入新节点在链表中第一个节点的位置
 * @param list 循环双链表
 * @param ele 新节点的数据值
 */
void insertFirst(CDLNode **list, int ele) {
    // 变量，记录链表的第一个节点
    CDLNode *firstNode = (*list)->next;

    // 1.创建新节点
    // 1.1 为新节点分配空间
    CDLNode *newNode = (CDLNode *) malloc(sizeof(CDLNode));
    // 1.2 为新节点的数据域指定内容
    newNode->data = ele;
    // 1.3 将新节点的 prior 指针指向 null
    newNode->prior = NULL;
    // 1.4 将新节点的 next 指针指向 null
    newNode->next = NULL;

    // 2.将新节点插入到链表的头部，即头结点的后面
    // 2.1 将新节点的 next 指针指向原链表的第一个节点
    newNode->next = firstNode;
    // 2.2 将原链表的第一个节点的 prior 指针指向新节点，此时完成了新节点与原链表第一个节点的链接
    firstNode->prior = newNode;
    // 2.3 将头结点的 next 指针指向新节点，即让新节点成为链表的第一个节点
    (*list)->next = newNode;
    // 2.4 将新节点的 prior 指针指向链表头结点，此时完成了新节点与链表头结点的链接
    newNode->prior = *list;
}

/**
 * 插入新节点在链表中最后一个节点的位置
 * @param list 循环双链表
 * @param ele 新节点的数据值
 */
void insertLast(CDLNode **list, int ele) {
    // 1.创建新节点
    // 1.1 为新节点分配空间
    CDLNode *newNode = (CDLNode *) malloc(sizeof(CDLNode));
    // 1.2 为新节点的数据域指定内容
    newNode->data = ele;
    // 1.3 将新节点的 prior 指针指向 null
    newNode->prior = NULL;
    // 1.4 将新节点的 next 指针指向 null
    newNode->next = NULL;

    // 2.把新节点插入到链表的尾部
    // 2.1 变量，记录循环双链表的尾节点，这里就是通过 list.prior 获得的链表尾节点
    CDLNode *lastNode = (*list)->prior;
    // 2.2 将链表尾节点的 next 指针指向新节点
    lastNode->next = newNode;
    // 2.3 将新节点的 prior 指针指向原尾节点，此时完成了原链表尾节点与新节点的链接（链接成功后，新节点就成为了链表的尾节点）
    newNode->prior = lastNode;
    // 2.4 将链表头结点的 prior 指针指向新节点，为了循环
    (*list)->prior = newNode;
    // 2.5 将新节点的 next 指针指向头结点，为了循环
    newNode->next = *list;
}

/**
 * 删除第 i 个位置的节点
 * @param list 循环双链表
 * @param i 待删除节点的序号，从 1 开始
 * @param ele 如果删除成功则返回被删除的节点，否则返回 null
 */
int removeByNum(CDLNode **list, int i, int *ele) {
    // 0.参数校验
    // 0.1 判断链表是否为空
    if ((*list)->next == *list) {
        return 0;
    }
    // 0.2 判断序号是否在范围内
    if (i < 1 || i > size(*list)) {
        return 0;
    }

    // 变量，记录链表中每个节点，初始为链表第一个节点
    CDLNode *node = (*list)->next;
    // 变量，记录已经迭代的节点个数
    int count = 0;

    // 1.循环遍历双链表，注意循环结束的条件
    while (node != *list) {
        // 1.1 计数器加1
        count++;
        // 1.2 找到第 i 个节点
        if (count == i) {
            // 1.2.1 局部变量，记录第 i-1 个节点
            CDLNode *preNode = node->prior;
            // 1.2.2 局部变量，记录第 i+1 个节点
            CDLNode *nextNode = node->next;
            // 1.2.3 将第 i-1 个节点的 next 指针指向第 i+1 个节点
            preNode->next = nextNode;
            // 1.2.4 将第 i+1 个节点的 prior 指针指向第 i-1 个节点
            nextNode->prior = preNode;
            // 1.2.5 保存被删除节点的数据值
            *ele = node->data;
            // 1.2.6 释放节点空间
            free(node);
            // 1.2.7 返回，结束程序
            return 1;
        }
        // 1.3 继续链表的下一个节点
        node = node->next;
    }

    return 0;
}

/**
 * 删除值为 ele 的节点
 * @param list 循环双链表
 * @param ele 指定值
 * @return 如果删除成功则返回 1，否则返回 0
 */
int removeByEle(CDLNode **list, int ele) {
    // 0.参数校验
    if ((*list)->next == *list) {
        return 0;
    }

    // 变量，记录链表中的每一个节点，从链表的第一个节点开始
    CDLNode *node = (*list)->next;

    // 1.循环遍历链表所有节点
    while (node != *list) {
        // 1.1 找到值等于 ele 的节点
        if (node->data == ele) {
            // 1.1.1 局部变量，记录第 i-1 个节点
            CDLNode *preNode = node->prior;
            // 1.1.2 局部变量，记录第 i+1 个节点
            CDLNode *nextNode = node->next;
            // 1.1.3 将第 i-1 个节点的 next 指针指向第 i+1 个节点
            preNode->next = nextNode;
            // 1.1.4 将第 i+1 个节点的 prior 指针指向第 i-1 个节点
            nextNode->prior = preNode;
            // 1.1.5 释放节点空间
            free(node);
            // 1.1.6 结束程序
            return 1;
        }
        // 1.2 继续链表的下一个节点
        node = node->next;
    }

    return 0;
}

/**
 * 删除链表的第一个节点
 * @param list 循环双链表
 * @param ele 保存被删除节点的数据域值
 */
int removeFirst(CDLNode **list, int *ele) {
    // 0.参数校验
    if ((*list)->next == *list) {
        return 0;
    }

    // 1.删除链表第一个节点
    // 1.1 变量，记录链表的第一个节点
    CDLNode *firstNode = (*list)->next;
    // 1.2 将头结点的 next 指针指向第一个节点的后继节点
    (*list)->next = firstNode->next;
    // 1.3 将第一个节点的后继节点的 prior 指针指向链表的头结点，这样就删除了链表的第一个节点
    firstNode->next->prior = *list;
    // 1.4 保存第一个节点的数据域值
    *ele = firstNode->data;
    // 1.5 释放节点空间
    free(firstNode);

    return 1;
}

/**
 * 删除链表最后一个节点
 * @param list 循环双链表
 * @param ele 保存被删除节点的数据域值
 */
int removeLast(CDLNode **list, int *ele) {
    // 0.参数校验
    if ((*list)->next == *list) {
        return 0;
    }

    // 1.删除链表最后一个节点
    // 1.1 变量，记录链表的最后一个节点
    CDLNode *tailNode = (*list)->prior;
    // 1.2 将链表头结点的 prior 指针指向 lastNode 节点的前驱节点
    (*list)->prior = tailNode->prior;
    // 1.3 将 lastNode 节点的 next 指针指向链表头结点，这样就删除了链表的最后一个节点
    tailNode->prior->next = *list;
    // 1.4 保存被删除节点的数据域值
    *ele = tailNode->data;
    // 1.5 释放节点空间
    free(tailNode);

    return 1;
}

/**
 * 求第一个值为 ele 的节点的前驱节点
 * @param list 循环双链表
 * @param ele 指定值
 * @return 如果找到值为 ele 的节点则返回它的前驱节点，否则返回 null
 */
CDLNode *getPrior(CDLNode *list, int ele) {
    // 1.找到值为 ele 的节点
    // 1.1 直接利用已经写好的函数查找值为 ele 的节点
    CDLNode *node = findByEle(list, ele);

    // 2.获取值为 ele 的节点的前驱节点。如果返回结果为 null，表示不存在值为 ele 的节点，则直接返回 null
    if (node != NULL) {
        // 2.1 直接返回 node 节点的 prior 指针所指向的节点，就是它的前驱节点
        return node->prior;
    }
    return NULL;
}

/**
 * 求第一个值为 ele 的节点的后继节点
 * @param list 循环双链表
 * @param ele 指定值
 * @return 如果找到值为 ele 的节点则返回它的后继节点，否则返回 null
 */
CDLNode *getNext(CDLNode *list, int ele) {
    // 1.找到值为 ele 的节点
    // 1.1 直接利用已经写好的函数查找值为 ele 的节点
    CDLNode *node = findByEle(list, ele);

    // 2.获取值为 ele 的节点的后继节点。如果返回结果为 null，表示不存在值为 ele 的节点，则直接返回 null
    if (node != NULL) {
        // 2.1 直接返回 node 节点的 next 指针所指向的节点，就是它的后继节点
        return node->next;
    }
    return NULL;
}

/**
 * 根据序号查找第 i 个节点
 * @param list 循环双链表
 * @param i 指定序号，从 1 开始
 * @return 如果成功查找到节点则返回，否则返回 null
 */
CDLNode *findByNum(CDLNode *list, int i) {
    // 0.参数校验
    if (i < 1 || i > size(list)) {
        return NULL;
    }

    // 变量，记录链表的每一个节点，从链表的第一个节点开始
    CDLNode *node = list->next;
    // 变量，计数器，记录节点个数
    int count = 0;

    // 1.遍历链表所有节点
    while (node != list) {
        // 1.1 计数器加1，表示已经遍历一个节点
        count++;
        // 1.2 比较计数器的值与参数传入的值是否相等，如果相等则表示找到第 i 个节点了
        if (count == i) {
            return node;
        }
        // 1.3 继续链表的下一个节点
        node = node->next;
    }
    return NULL;
}

/**
 * 根据值查找指定节点
 * @param list 循环双链表
 * @param ele 指定值
 * @return 如果查找成功则返回对应值的节点，否则返回 null
 */
CDLNode *findByEle(CDLNode *list, int ele) {
    // 链表的第一个节点
    CDLNode *node = list->next;
    // 遍历链表所有节点，寻找节点值等于 ele 的节点
    while (node != list) {
        // 判断当前节点的数据域值是否等于指定值
        if (node->data == ele) {
            return node;
        }
        // 继续下一个节点
        node = node->next;
    }
    return NULL;
}

/**
 * 获取链表节点个数
 * @param list 循环双链表
 * @return 链表长度
 */
int size(CDLNode *list) {
    // 记录链表的节点个数
    int count = 0;
    // 链表的第一个节点
    CDLNode *node = list->next;
    // 遍历链表所有节点，统计个数
    while (node != list) {
        // 节点个数加 1
        count++;
        // 继续下一个节点
        node = node->next;
    }
    // 返回统计结果
    return count;
}

/**
 * 判断循环双链表是否为空
 * @param list 循环双链表
 * @return 如果循环双链表为空则返回 1，否则返回 0
 */
int isEmpty(CDLNode *list) {
    // 即判断链表的头节点是否指向自身，或者 list.prior==list 也是可以的
    return list->next == list;
}

/**
 * 清空双链表
 * @param list 循环双链表
 */
void clear(CDLNode **list) {
    // 链表的第一个节点
    CDLNode *node = (*list)->next;
    // 遍历链表所有节点
    while (node != *list) {
        // 临时保存当前节点的后继节点
        CDLNode *temp = node->next;
        // 释放当前节点的空间
        free(node);
        // 继续下一个节点
        node = temp;
    }
    // 将链表头结点的 prior 和 next 指针指向自身
    (*list)->prior = *list;
    (*list)->next = *list;
}

/**
 * 打印循环双链表
 * @param list 循环双链表
 */
void print(CDLNode *list) {
    printf("[");
    CDLNode *node = list->next;
    while (node != list) {// 注意，判断循环结束的条件是不等于头结点
        printf("%d", node->data);
        if (node->next != list) {
            printf(", ");
        }
        node = node->next;
    }
    printf("]\n");
}

int main() {
    CDLNode *list;

    // 初始化循环双链表
    printf("初始化循环双链表：\n");
    init(&list);
    print(list);

    // 通过头插法创建循环双链表
    printf("\n通过头插法创建循环双链表：\n");
    int nums1[] = {11, 22, 33, 44, 55};
    int n1 = 5;
    createByHead(&list, nums1, n1);
    print(list);

    // 通过尾插法创建循环双链表
    printf("\n通过尾插法创建循环双链表：\n");
    int nums2[] = {111, 222, 333, 444, 555};
    int n2 = 5;
    createByTail(&list, nums2, n2);
    print(list);

    // 向链表中指定位置插入新节点
    printf("\n向链表中指定位置插入新节点：\n");
    insert(&list, 1, 1111);
    print(list);
    insert(&list, 2, 2222);
    print(list);
    insert(&list, size(list), 7777);
    print(list);

    // 向链表头部插入新节点
    printf("\n向链表头部插入新节点：\n");
    insertFirst(&list, 6666);
    print(list);

    // 向链表尾部插入新节点
    printf("\n向链表尾部插入新节点：\n");
    insertLast(&list, 9999);
    print(list);

    // 删除指定位置的节点
    printf("\n删除指定位置的节点：\n");
    int ele;
    removeByNum(&list, 1, &ele);
    print(list);
    removeByNum(&list, 4, &ele);
    print(list);
    removeByNum(&list, size(list), &ele);
    print(list);

    // 删除指定值的节点
    printf("\n删除指定值的节点：\n");
    removeByEle(&list, 2222);
    print(list);

    // 删除链表的第一个节点
    printf("\n删除链表的第一个节点：\n");
    removeFirst(&list, &ele);
    print(list);

    // 删除链表的最后一个节点
    printf("\n删除链表的最后一个节点：\n");
    removeLast(&list, &ele);
    print(list);

    // 获取指定值的前驱节点
    printf("\n获取指定值的前驱节点：\n");
    CDLNode *prior = getPrior(list, 333);
    printf("%d\n", prior->data);

    // 获取指定值的后继节点
    printf("\n获取指定值的后继节点：\n");
    CDLNode *next = getNext(list, 333);
    printf("%d\n", next->data);

    // 通过序号查找节点
    printf("\n通过序号查找节点：\n");
    CDLNode *nodeByNum = findByNum(list, 1);
    printf("%d\n", nodeByNum->data);

    // 通过值查找节点
    printf("\n通过值查找节点：\n");
    CDLNode *nodeByEle = findByEle(list, 444);
    printf("%d\n", nodeByEle->data);

    // 获取链表的长度
    printf("\n获取链表的长度：\n");
    int len = size(list);
    printf("%d\n", len);

    // 清空链表
    printf("\n清空链表：\n");
    clear(&list);
    print(list);

    // 链表是否为空
    printf("\n链表是否为空：\n");
    int empty = isEmpty(list);
    printf("%d\n", empty);
}