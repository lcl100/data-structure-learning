# Example001

## 题目

键盘输入 `n` 个英文字母，输入格式为`n、c1、c2、.…、cn`，其中 `n` 表示字母的个数。请编程用这些输入数据建立一个单链表，并要求将字母不重复地存入链表。

## 分析

本题考查的知识点：
- 单链表
- 单链表的创建
- 判断某元素是否在链表中出现过

**分析**：

- 输入一个字符，首先判断该字符是否在链表中出现。
- 如果该字符已经在链表中出现则跳过该字符，即什么也不做。
- 如果该字符在链表中从没有出现过，则将该字符作为数据域创建节点插入到链表中。

**注意**：

- 判断字符是否在链表中出现，则循环遍历单链表所有节点，比较正在遍历的节点的数据域与传入的字符，如果存在相等的情况则表示该字符出现过，否则没有。
- 如果使用 Java 实现则为了去重不要考虑已经准备好的数据结构 `Set` 集合。

## 图解

略。

## C实现

核心代码：

```c
/**
 * 根据字符数组创建单链表，采用尾插法
 * @param n 数组中字符的实际个数
 * @param letters 字符数组
 * @return 创建成功的单链表
 */
LNode *createList(int n, char letters[]) {
    // 创建单链表，初始化头节点
    LNode *list = (LNode *) malloc(sizeof(LNode) * n);
    list->next = NULL;
    // 保存链表的尾节点
    LNode *tailNode = list;
    // 循环遍历字符数组，将字符插入到单链表中，采用尾插法
    for (int i = 0; i < n; i++) {
        char letter = letters[i];
        // 链表的第一个节点
        LNode *node = list->next;
        // 创建新节点
        LNode *newNode = (LNode *) malloc(sizeof(LNode));
        newNode->data = letter;
        newNode->next = NULL;
        // 标志，判断是否该字符在链表中是否存在，如果为 1 表示已经出现过，为 0 则表示没有出现过
        int isExist = 0;
        // 检查该字符是否已经在链表中出现过
        while (node != NULL) {
            // 比较当前节点的数据域是否等于指定字符
            if (node->data == letter) {
                // 如果相等则表示指定字符在链表中出现过，将标记 isExist 置为 1，然后跳出循环
                isExist = 1;
                break;
            }
            // 继续链表的下一个节点
            node = node->next;
        }
        // 如果标志为 1 表示该字符已经存在于链表中则跳过，否则插入到链表中
        if (!isExist) {
            tailNode->next = newNode;
            tailNode = newNode;
        }
    }
    // 返回创建成功的单链表
    return list;
}
```

完整代码：

```c
#include <stdio.h>
#include <malloc.h>

/**
 * 单链表的节点
 */
typedef struct LNode {
    // 节点的数据域
    char data;
    // next 指针指向节点的后继节点
    struct LNode *next;
} LNode;

/**
 * 根据字符数组创建单链表，采用尾插法
 * @param n 数组中字符的实际个数
 * @param letters 字符数组
 * @return 创建成功的单链表
 */
LNode *createList(int n, char letters[]) {
    // 创建单链表，初始化头节点
    LNode *list = (LNode *) malloc(sizeof(LNode) * n);
    list->next = NULL;
    // 保存链表的尾节点
    LNode *tailNode = list;
    // 循环遍历字符数组，将字符插入到单链表中，采用尾插法
    for (int i = 0; i < n; i++) {
        char letter = letters[i];
        // 链表的第一个节点
        LNode *node = list->next;
        // 创建新节点
        LNode *newNode = (LNode *) malloc(sizeof(LNode));
        newNode->data = letter;
        newNode->next = NULL;
        // 标志，判断是否该字符在链表中是否存在，如果为 1 表示已经出现过，为 0 则表示没有出现过
        int isExist = 0;
        // 检查该字符是否已经在链表中出现过
        while (node != NULL) {
            // 比较当前节点的数据域是否等于指定字符
            if (node->data == letter) {
                // 如果相等则表示指定字符在链表中出现过，将标记 isExist 置为 1，然后跳出循环
                isExist = 1;
                break;
            }
            // 继续链表的下一个节点
            node = node->next;
        }
        // 如果标志为 1 表示该字符已经存在于链表中则跳过，否则插入到链表中
        if (!isExist) {
            tailNode->next = newNode;
            tailNode = newNode;
        }
    }
    // 返回创建成功的单链表
    return list;
}

/**
 * 打印单链表所有节点的数据值
 * @param list 带打印的单链表
 */
void print(LNode *list) {
    // 链表的第一个节点
    LNode *node = list->next;
    // 循环单链表所有节点，输出数据值
    printf("\n[");
    while (node != NULL) {
        printf("%c", node->data);
        if (node->next != NULL) {
            printf(", ");
        }
        node = node->next;
    }
    printf("]\n");
}

int main() {
    // 从键盘输入字符数组的长度
    int n;
    printf("请输入 n：");
    scanf("%d", &n);
    getchar();// 吸收掉换行符
    // 从键盘输入 n 个字符
    char letters[n];
    printf("请输入 %d 个英文字母：\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%c", &letters[i]);
        getchar();// 吸收掉空格字符或者换行符
    }

    // 创建单链表
    LNode *list = createList(n, letters);
    // 打印单链表
    print(list);
}
```

执行结果：

```text
请输入 n：5
请输入 5 个英文字母：
a b c d e
[a, b, c, d, e]

请输入 n：6
请输入 6 个英文字母：
a b a c b e
[a, b, c, e]
```

## Java实现

核心代码：

```java
    /**
     * 使用 n 个字符创建单链表，通过尾插法
     *
     * @param n       字符数组的长度
     * @param letters 字符数组
     * @return 创建成功的单链表，带头节点
     */
    public LNode createList(int n, char[] letters) {
        // 初始化单链表，即创建头节点
        list = new LNode();
        list.next = null;
        // 保存链表的尾节点
        LNode tailNode = list;
        // 循环数组插入元素
        for (int i = 0; i < n; i++) {
            // 正在遍历的字符
            char letter = letters[i];
            // 链表的第一个节点
            LNode node = list.next;
            // 创建新节点
            LNode newNode = new LNode();
            newNode.data = letter;
            newNode.next = null;
            // 将新节点插入到链表中，注意考虑重复字母的问题
            boolean isExist = false;
            // 判断链表中是否已经存在该节点，则修改 isExist 标记
            while (node != null) {
                // 判断当前节点的数据域是否等于指定字符，如果相等则表示该字符在链表中已经出现过
                if (node.data == letter) {
                    // 则将标记 isExist 置为 true，然后跳出循环
                    isExist = true;
                    break;
                }
                // 继续链表的下一个节点
                node = node.next;
            }
            // 如果存在则跳过该字符，否则插入到链表中
            if (!isExist) {
                tailNode.next = newNode;
                tailNode = newNode;
            }
        }
        return list;
    }
```

完整代码：

```java
/**
 * @author lcl100
 * @create 2022-02-23 10:17
 */
public class LinkedList {
    private LNode list;

    /**
     * 使用 n 个字符创建单链表，通过尾插法
     *
     * @param n       字符数组的长度
     * @param letters 字符数组
     * @return 创建成功的单链表，带头节点
     */
    public LNode createList(int n, char[] letters) {
        // 初始化单链表，即创建头节点
        list = new LNode();
        list.next = null;
        // 保存链表的尾节点
        LNode tailNode = list;
        // 循环数组插入元素
        for (int i = 0; i < n; i++) {
            // 正在遍历的字符
            char letter = letters[i];
            // 链表的第一个节点
            LNode node = list.next;
            // 创建新节点
            LNode newNode = new LNode();
            newNode.data = letter;
            newNode.next = null;
            // 将新节点插入到链表中，注意考虑重复字母的问题
            boolean isExist = false;
            // 判断链表中是否已经存在该节点，则修改 isExist 标记
            while (node != null) {
                // 判断当前节点的数据域是否等于指定字符，如果相等则表示该字符在链表中已经出现过
                if (node.data == letter) {
                    // 则将标记 isExist 置为 true，然后跳出循环
                    isExist = true;
                    break;
                }
                // 继续链表的下一个节点
                node = node.next;
            }
            // 如果存在则跳过该字符，否则插入到链表中
            if (!isExist) {
                tailNode.next = newNode;
                tailNode = newNode;
            }
        }
        return list;
    }

    /**
     * 打印单链表
     */
    public void print() {
        // 链表的第一个节点
        LNode node = list.next;
        // 循环遍历所有节点
        String str = "[";
        while (node != null) {
            str += node.data;
            if (node.next != null) {
                str += ", ";
            }
            node = node.next;
        }
        str += "]";
        System.out.println(str);
    }
}

/**
 * 单链表的节点
 */
class LNode {
    /**
     * 节点的数据域，是字符类型
     */
    char data;
    /**
     * 节点的指针域，指向节点的后继节点
     */
    LNode next;
}
```

测试代码：
```java
public class LinkedListTest {
    public static void main(String[] args) {
        // 从键盘输入指定个数的字符
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入 n：");
        int n = scanner.nextInt();
        System.out.println("请输入 " + n + " 个英文字母：");
        char[] letters = new char[n];
        for (int i = 0; i < letters.length; i++) {
            letters[i] = scanner.next().charAt(0);
        }

        // 创建单链表实例对象
        LinkedList list = new LinkedList();
        // 根据字符数组创建单链表
        list.createList(n, letters);
        // 打印单链表中的所有节点
        list.print();
    }
}
```

执行结果：

```text
请输入 n：
5
请输入 5 个英文字母：
a b c d e
[a, b, c, d, e]

请输入 n：
6
请输入 6 个英文字母：
a a c a b e
[a, c, b, e]
```