#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

/**
 * 每行的单链表节点定义
 */
typedef struct ALNode {
    // 非零元素的值
    int val;
    // 非零元素的列下标
    int col;
    // 指向该节点的下一个非零元素节点
    struct ALNode *next;
} ALNode;

/**
 * 邻接表的定义
 */
typedef struct AdjacencyList {
    //  存储所有行，每一行都是一个单独的单链表
    ALNode *rowArray[MAX_SIZE];
    // 稀疏矩阵的行数
    int m;
    // 稀疏矩阵的列数
    int n;
} AdjacencyList;

/**
 * 打印输出矩阵中的所有元素
 * @param matrix 矩阵，即一个二维数组
 * @param m 矩阵的行数
 * @param n 矩阵的列数
 */
void print(int matrix[][MAX_SIZE], int m, int n) {
    // row 表示行下标
    for (int row = 0; row < m; row++) {
        // column 表示列下标
        for (int column = 0; column < n; ++column) {
            printf("%2d ", matrix[row][column]);
        }
        // 换行
        printf("\n");
    }
}

AdjacencyList *saveSparseMatrixToAdjacencyList(int matrix[][MAX_SIZE], int m, int n) {
    // 创建一个邻接表并为其分配存储空间
    AdjacencyList *list = (AdjacencyList *) malloc(sizeof(AdjacencyList));
    // 为邻接表初始化
    list->m = m;
    list->n = n;
    for (int row = 0; row < m; row++) {
        list->rowArray[row] = NULL;
    }

    for (int row = 0; row < m; ++row) {
        // 获取每行单链表的第一个节点
        ALNode *node = list->rowArray[row];
        for (int column = 0; column < n; ++column) {
            if (matrix[row][column] != 0) {
                // 将非零元素创建成邻接表节点
                ALNode *newNode;
                newNode = (ALNode *) malloc(sizeof(ALNode));
                newNode->val = matrix[row][column];
                newNode->col = column;
                newNode->next = NULL;
                // 将新节点添加到每行的单链表的尾部，采用尾插法
                if (node == NULL) {
                    list->rowArray[row] = newNode;
                    node = newNode;
                } else {
                    node->next = newNode;
                    node = newNode;
                }
            }
        }
    }

    return list;
}

void restoreAdjacencyListToSparseMatrix(AdjacencyList *list, int matrix[][MAX_SIZE], int m, int n) {
    for (int row = 0; row < m; row++) {
        ALNode *node = list->rowArray[row];
        while (node != NULL) {
            int column = node->col;
            int val = node->val;
            matrix[row][column] = val;
            node = node->next;
        }
    }
}
