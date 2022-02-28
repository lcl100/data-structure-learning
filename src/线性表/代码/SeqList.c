#include <stdio.h>

#define MAXSIZE 20

/**
 * 顺序表的结构体
 */
typedef struct {
    /**
     * 顺序表，实际上一个长度为 MAXSIZE 的数组，存储的数据类型为整型，当然可以设置为其他类型，但推荐使用宏定义类型，方便替换
     */
    int data[MAXSIZE];
    /**
     * 顺序表长度，即数组中实际元素个数
     */
    int length;
} SeqList;

/**
 * 初始化顺序表，仅需要将 length 置为 0 即可
 * @param list 待初始化的顺序表
 */
void init(SeqList *list) {
    // 仅需要将 length 置为 0 即可
    (*list).length = 0;
    // 或者可以用下面的语法
    // list->length=0;
}

/**
 * 查找顺序表中指定索引所表示的元素
 * @param list 待查询的顺序表
 * @param index 索引，即数组的下标，从 0 开始
 * @param ele 保存查找到的元素
 * @return 如果查询成功则返回 1，如果查找失败则返回 0
 */
int findByIndex(SeqList list, int index, int *ele) {
    // 0.参数校验
    // 0.1 如果索引小于 0 或者大于等于设定的最大长度，则无法获取到元素
    if (index < 0 || index >= MAXSIZE) {
        return 0;
    }
    // 0.2 如果索引在 [0, MAXSIZE) 范围内，但超过了实际元素个数，也是无法获取到的
    if (index >= list.length) {
        return 0;
    }
    // 1.查找指定索引所表示的元素
    // 1.1 直接返回下标为 index 的元素值即可，不需要遍历循环
    *ele = list.data[index];
    return 1;
}

/**
 * 查找指定元素在顺序表中的索引
 * @param list 待查询的顺序表
 * @param ele 指定元素
 * @param index 保存查询成功的索引
 * @return 如果查询成功则返回 1，查询失败则返回 0
 */
int findByEle(SeqList list, int ele, int *index) {
    // 循环顺序表中的所有元素
    for (int i = 0; i < list.length; i++) {
        // 比较迭代的每一个元素的值是否等于传入的参数值，如果相等则返回对应的索引（下标）
        if (list.data[i] == ele) {
            // 保存索引
            *index = i;
            // 结束程序
            return 1;
        }
    }
    return 0;
}

/**
 * 向顺序表指定索引处插入一个新元素。原索引处的元素及之后的所有元素都向后移动一位。
 * @param list 顺序表
 * @param index 指定插入位置
 * @param ele 待插入的新元素
 * @return 如果插入成功则返回 1，如果插入失败则返回 0
 */
int insert(SeqList *list, int index, int ele) {
    // 0.参数校验
    // 0.1 如果索引小于 0 或者大于等于设定的最大长度，则插入失败
    if (index < 0 || index >= MAXSIZE) {
        return 0;
    }
    // 0.2 向顺序表中插入元素要检查顺序表是否已经满了，如果已经满了则不能再插入新元素则插入失败
    if (list->length == MAXSIZE) {
        return 0;
    }
    // 0.3 如果插入的索引超过了数组长度的范围也不行
    if (index > list->length) {
        return 0;
    }
    // 1.如果顺序表没有满，则继续插入元素
    // 1.1 循环顺序表，从后往前遍历，将指定索引及之后的所有元素（包括指定索引）向后移动一位
    for (int i = list->length - 1; i >= index; i--) {
        list->data[i + 1] = list->data[i];
    }
    // 1.2 将移动后空出来的位置（即指定索引所在的位置）插入新元素
    list->data[index] = ele;
    // 1.3 不要忘记将 length 加 1 表示顺序表新增一个元素
    list->length++;
    return 1;
}

/**
 * 直接添加新元素到顺序表的尾部
 * @param list 顺序表
 * @param ele 待添加的新元素
 * @return 如果插入成功则返回 1，否则返回 0
 */
int add(SeqList *list, int ele) {
    // 0.校验
    // 0.1 向顺序表中插入元素要检查顺序表是否已经满了，如果已经满了则不能再插入新元素则添加失败
    if (list->length == MAXSIZE) {
        return 0;
    }
    // 1.插入新元素
    // 1.1 直接获取顺序表的 length，然后将新元素的值赋予到 length 位置即可
    list->data[list->length] = ele;
    // 1.2 注意修改 length
    list->length++;
    return 1;
}

/**
 * 移除顺序表中指定索引的元素
 * @param list 顺序表
 * @param index 指定索引，即下标，从 0 开始
 * @param ele 被删除元素的数据值
 * @return 如果删除成功则返回 1，删除失败则返回 0
 */
int removeByIndex(SeqList *list, int index, int *ele) {
    // 0.参数校验
    // 0.1 判断输入的索引是否超出范围
    if (index < 0 || index >= MAXSIZE) {
        return 0;
    }
    // 0.2 在删除顺序表元素之前，要判断顺序表是否为空，如果为空则不能进行删除
    if (list->length == 0) {
        return 0;
    }
    // 0.3 判断输入的索引虽然在数组范围内，但是否存在元素
    if (index >= list->length) {
        return 0;
    }
    // 1.删除指定索引的元素
    // 1.1 保存待删除索引所表示的元素的数据值
    *ele = list->data[index];
    // 1.2 循环遍历顺序表，从前往后，将指定索引之后的所有元素（不包括指定索引）向前移动一步
    for (int i = index; i < list->length; i++) {
        list->data[i] = list->data[i + 1];// 后面的元素覆盖前面的元素
    }
    // 1.3 将记录数组实际元素个数的 length 减去 1，表示已经删除了一个元素
    list->length--;
    return 1;
}

/**
 * 获取顺序表的长度
 * @param list 顺序表
 * @return 顺序表中实际元素个数
 */
int size(SeqList list) {
    return list.length;
}

/**
 * 顺序表是否为空
 * @param list 顺序表
 * @return 如果为空则返回 0，不为空则返回 1
 */
int isEmpty(SeqList list) {
    return list.length == 0;
}

/**
 * 打印顺序表
 * @param list 待打印的顺序表
 */
void print(SeqList list) {
    printf("[");
    for (int i = 0; i < list.length; i++) {
        printf("%d", list.data[i]);
        if (i != list.length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    // 声明顺序表
    SeqList list;

    // 初始化顺序表
    printf("初始化顺序表：\n");
    init(&list);
    print(list);

    // 在顺序表指定索引处插入新元素
    printf("\n在顺序表指定索引处插入新元素：\n");
    insert(&list, 0, 1);
    print(list);
    insert(&list, 1, 2);
    print(list);
    insert(&list, 2, 3);
    print(list);
    insert(&list, 2, 4);
    print(list);

    // 直接在顺序表的后面添加新元素
    printf("\n直接在顺序表的后面添加新元素：\n");
    add(&list, 55);
    print(list);
    add(&list, 66);
    add(&list, 77);
    print(list);

    // 删除顺序表中指定索引的元素
    printf("\n删除顺序表中指定索引的元素：\n");
    int del;
    removeByIndex(&list, 0, &del);
    print(list);
    removeByIndex(&list, 1, &del);
    print(list);
    removeByIndex(&list, 4, &del);
    print(list);

    // 通过索引查找顺序表中的元素
    printf("\n通过索引查找顺序表中的元素：\n");
    int ele;
    findByIndex(list, 2, &ele);
    printf("%d\n", ele);

    // 通过值查找顺序表中的元素在顺序表中的索引
    printf("\n通过值查找顺序表中的元素在顺序表中的索引：\n");
    int index;
    findByEle(list, 66, &index);
    printf("%d\n", index);

    // 顺序表的长度
    printf("\n顺序表的长度：\n");
    int len;
    len = size(list);
    printf("%d\n", len);

    // 顺序表是否为空
    printf("\n顺序表是否为空：\n");
    int empty;
    empty = isEmpty(list);
    printf("%d\n", empty);
}