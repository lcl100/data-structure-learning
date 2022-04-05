#include<stdio.h>

#define MAXSIZE 100

/**
 * 静态链表节点
 */
typedef struct SLNode {
    /**
     * 静态链表节点的数据域
     */
    int data;
    /**
     * 静态链表节点的游标，存储下一个节点的下标
     */
    int cur;
} SLNode;

int size(SLNode *list);

int mallocNode(SLNode *list);

void freeNode(SLNode *list, int i);

/**
 * 初始化静态链表
 * @param list 待初始化的静态链表
 */
void init(SLNode *list) {
    // 初始情况下，静态链表是空链表，除了最后一个节点之外（最后一个节点要用作数据链表的头结点），每一个节点的游标cur都指向后面一个节点的下标
    for (int i = 0; i < MAXSIZE; i++) {// 注意，这里赋值了数组最后一个元素的游标cur，但在循环结束之后更改了它的游标值
        // 初始时每个节点的游标 cur 的值为下一个节点的下标
        list[i].cur = i + 1;
    }
    // 将最后一个节点的游标置为0，表示这是一个空静态链表
    list[MAXSIZE - 1].cur = 0;
}

/**
 * 根据数组创建静态链表
 * @param list 静态链表
 * @param nums 数组
 * @param n 数组长度
 * @return 如果创建成功则返回 1，否则返回 0
 */
int createList(SLNode *list, int nums[], int n) {
    // 参数校验
    if (n < 1 || n > MAXSIZE - 2) {
        return 0;
    }

    // 注意，下标为 0 的元素要存储备用链表的头结点，它的数据域不存放如何东西
    for (int i = 0; i < n; i++) {
        // 这里之所以是list[i+1]，是因为list[0]要存储备用链表的头结点，所以要从数组的第二个元素开始
        list[i + 1].data = nums[i];
    }
    // 数据链表最后一个元素的游标cur指向备用链表的头结点（即数组下标为0的元素）
    list[n].cur = 0;
    // 数组最后一个元素存储的是数据链表的头结点（即第一个有数据元素位置的）
    list[MAXSIZE - 1].cur = 1;// 即数组下标为1的元素
    // 数组下标为0的元素（即备用链表的头结点）的游标cur存储着备用链表第一个可用元素的位置，即数组长度加1后面的节点是空的
    list[0].cur = n + 1;

    return 1;
}

/**
 * 在静态链表中的第 i 个节点处插入新节点
 * @param list 静态链表
 * @param i 序号，从 1 开始
 * @param ele 新节点的数据域值
 * @return 如果插入成功则返回 1，否则返回 0
 */
int insert(SLNode *list, int i, int ele) {
    // 参数校验
    if (i < 1 || i > size(list)) {
        return 0;
    }
    // 去从静态链表中获得一个空节点
    int newIndex = mallocNode(list);
    // 如果该下标有效则插入
    if (newIndex != 0) {
        // 将新节点添加到链表中并为数据域赋值
        list[newIndex].data = ele;

        // 第一个数据节点的下标
        int index = list[MAXSIZE - 1].cur;
        // 计数器，记录数据节点个数
        int count = 0;
        // 记录第 i 个节点的前驱节点的下标
        int preIndex = MAXSIZE - 1;// 初始值为数据链表的头结点在数组中的下标
        // 找到第 i 个节点的前驱节点（即第 i-1 个节点）
        while (index != 0) {
            if (count == i - 1) {
                break;
            }
            count++;
            preIndex = index;
            // 继续下一个节点
            index = list[index].cur;
        }

        // 插入第 i 个节点
        list[newIndex].cur = list[preIndex].cur;// 将新节点的游标指向原第 i 个节点的前驱节点的游标
        list[preIndex].cur = newIndex;// 将第 i 个节点的前驱节点的游标指向新节点
        return 1;
    }

    return 0;
}

/**
 * 向静态链表的尾部追加元素
 * @param list 静态链表
 * @param ele 待追加的元素
 */
void append(SLNode *list, int ele) {
    // 为新节点分配空间，即在数组中找到一个空节点出来
    int newIndex = mallocNode(list);
    // 将新节点填充到分配出来的空间中并为数据域赋值
    list[newIndex].data = ele;

    // 将新节点连接到链表中
    int lastNodeIndex = MAXSIZE - 1;// 保存数据链表最后一个节点的下标
    int index = list[MAXSIZE - 1].cur;// 数据链表第一个节点的下标
    while (index != 0) {
        lastNodeIndex = index;
        // 继续下一个数据节点
        index = list[index].cur;
    }
    list[newIndex].cur = list[lastNodeIndex].cur;// 其实数据链表最后一个节点的游标cur一直都是0，都指向备用链表的头结点（即数组的第一个元素）
    list[lastNodeIndex].cur = newIndex;
}

/**
 * 除静态链表中序号为 i 的节点
 * @param list 静态链表
 * @param i 序号，从 1 开始
 * @param ele 保存被删除节点的数据域值
 * @return 被移除节点的数据域值
 */
int remove(SLNode *list, int i, int *ele) {
    // 参数校验
    if (i < 1 || i > size(list)) {
        return 0;
    }

    // 第一个数据节点的下标
    int index = list[MAXSIZE - 1].cur;
    // 计数器，记录数据节点个数
    int count = 0;
    // 记录第 i 个节点的前驱节点的下标
    int preIndex = MAXSIZE - 1;// 初始值为数据链表的头结点在数组中的下标
    // 找到第 i 个节点的前驱节点（即第 i-1 个节点）
    while (index != 0) {
        if (count == i - 1) {
            break;
        }
        count++;
        preIndex = index;
        // 继续下一个节点
        index = list[index].cur;
    }

    list[preIndex].cur = list[index].cur;// 删除节点
    *ele = list[index].data;// 保存待删除节点的数据域值
    freeNode(list, index);// 释放节点空间，必须释放，否则即使删除节点空间仍然不会被利用起来
    return 1;
}

/**
 * 根据序号查找第 i 个节点
 * @param list 静态链表
 * @param i 序号，从 1 开始
 * @return 如果找到则返回该节点
 */
SLNode findByNum(SLNode *list, int i) {
    SLNode node;
    // 参数校验
    if (i < 1 || i > size(list)) {
        return node;
    }

    // 数据链表的第一个节点
    int index = list[MAXSIZE - 1].cur;
    // 计数器，记录当前是第几个数据节点
    int count = 0;
    // 循环遍历数据链表
    while (index != 0) {
        // 计数器加1，表示已经遍历一个节点
        count++;
        // 判断第 i 个节点
        if (count == i) {
            node = list[index];
        }
        // 继续下一个节点
        index = list[index].cur;
    }
    return node;
}

/**
 * 根据指定值查找节点
 * @param list 静态链表
 * @param ele 指定值
 * @return 如果找到则返回该节点
 */
SLNode findByEle(SLNode *list, int ele) {
    SLNode node;
    // 数据链表的第一个节点
    int index = list[MAXSIZE - 1].cur;
    // 循环遍历数据链表
    while (index != 0) {
        // 当前节点的数据域值是否与输出的参数相等，如果相等则表示找到然后返回该节点
        if (list[index].data == ele) {
            node = list[index];
        }
        // 继续下一个节点
        index = list[index].cur;
    }
    return node;
}

/**
 * 获取到空闲节点的下标
 * @param list 静态链表
 * @return 可用节点的下标
 */
int mallocNode(SLNode *list) {
    // 获取备用链表头结点的游标cur，该游标指向了备用链表中第一个可用节点的下标
    int i = list[0].cur;
    // 因为这个节点被使用后，就不应该留在备用链表中，所以要将该节点的后继节点作为新的备用链表中的第一个可用节点，所以将数组中第一个元素的游标cur指向备用链表中下一个可用节点的游标
    if (i != 0) {
        list[0].cur = list[i].cur;
    }
    // 返回这个可用节点的下标
    return i;
}

/**
 * 释放下标为 i 的节点
 * @param list 静态链表
 * @param i 下标，从 0 开始
 */
void freeNode(SLNode *list, int i) {
    // 将被释放的节点插入到备用链表中
    list[i].cur = list[0].cur;
    list[i].data = 0;// 将数据域恢复为 0
    list[0].cur = i;
}

/**
 *  获取静态链表的长度
 * @param list 静态链表
 * @return 静态链表的长度
 */
int size(SLNode *list) {
    // 计数器，记录有效数据节点个数
    int count = 0;
    // 第一个数据节点的下标
    int i = list[MAXSIZE - 1].cur;
    // 遍历数据链表
    while (i != 0) {
        // 计数器加1
        count++;
        // 继续下一个节点
        i = list[i].cur;
    }
    // 返回长度
    return count;
}

/**
 * 判断静态链表是否为空
 * @param list 静态链表
 * @return 如果为空则返回 1，否则返回 0
 */
int isEmpty(SLNode *list) {
    // 即判断最后一个节点的游标cur是否等于0，如果等于0则表示这是一个空静态链表
    return list[MAXSIZE - 1].cur == 0;
}

/**
 * 打印静态链表所有数据节点
 * @param list 静态链表
 */
void print(SLNode *list) {
    int i = list[MAXSIZE - 1].cur;
    // 循环静态链表
    printf("[");
    while (i != 0) {
        printf("%d", list[i].data);
        if (list[list[i].cur].cur != 0) {
            printf(", ");
        }
        i = list[i].cur;
    }
    printf("]\n");
}

int main() {
    SLNode list[MAXSIZE];

    // 初始化静态链表
    printf("初始化静态链表：\n");
    init(list);
    print(list);

    // 创建静态链表
    printf("\n创建静态链表：\n");
    int nums[] = {1, 2, 3, 4, 5, 6, 7};
    int n = 7;
    createList(list, nums, n);
    print(list);

    // 向静态链表指定位置插入元素
    printf("\n向静态链表指定位置插入元素：\n");
    insert(list, 1, 11);
    print(list);
    insert(list, 4, 44);
    print(list);
    insert(list, size(list), 88);
    print(list);

    // 向静态链表尾部插入元素
    printf("\n向静态链表尾部插入元素：\n");
    append(list, 555);
    print(list);
    append(list, 666);
    print(list);

    // 移除静态链表指定位置的元素
    printf("\n移除静态链表指定位置的元素：\n");
    int ele;
    remove(list, 1, &ele);
    print(list);
    remove(list, 5, &ele);
    print(list);
    remove(list, size(list), &ele);
    print(list);

    // 查询静态链表中指定序号的节点
    printf("\n查询静态链表中指定序号的节点：\n");
    SLNode nodeByNum = findByNum(list, 3);
    printf("%d\n", nodeByNum.data);

    // 查询静态链表中指定值的节点
    printf("\n查询静态链表中指定值的节点：\n");
    SLNode nodeByEle = findByEle(list, 88);
    printf("%d\n", nodeByEle.data);

    // 静态链表的长度
    printf("\n静态链表的长度：\n");
    int len = size(list);
    printf("%d\n", len);

    // 静态链表是否为空
    printf("\n静态链表是否为空：\n");
    int empty = isEmpty(list);
    printf("%d\n", empty);
}