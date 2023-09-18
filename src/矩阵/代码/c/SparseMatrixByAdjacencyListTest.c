#include <stdio.h>
#include <stdlib.h>
#include "SparseMatrixByAdjacencyList.c"

#define MAX_SIZE 10
#define ROW 5
#define COL 4

/**
 * 测试 print 方法
 */
void testPrint() {
    int m = ROW;
    int n = COL;
    int matrix[][MAX_SIZE] = {
            {0, 0, 0, 1},
            {0, 0, 3, 2},
            {1, 0, 1, 0},
            {0, 2, 0, 0},
            {1, 0, 3, 5}
    };
    printf("稀疏矩阵: \n");
    print(matrix, m, n);
}

/**
 * 测试saveSparseMatrixToAdjacencyList方法
 */
void testSaveSparseMatrixToAdjacencyList() {
    int m = ROW;
    int n = COL;
    int matrix[][MAX_SIZE] = {
            {0, 0, 0, 1},
            {0, 0, 3, 2},
            {1, 0, 1, 0},
            {0, 2, 0, 0},
            {1, 0, 3, 5}
    };
    printf("稀疏矩阵: \n");
    print(matrix, m, n);

    // 调用函数将二维的稀疏矩阵压缩成邻接表存储
    AdjacencyList *list = saveSparseMatrixToAdjacencyList(matrix, m, n);

    // 打印结果
    printf("邻接表: \n");
    for (int row = 0; row < m; ++row) {
        ALNode *node = list->rowArray[row];
        if (node == NULL) {
            printf("\n");
        } else {
            while (node != NULL) {
                printf("%2d ", node->val);
                node = node->next;
            }
            printf("\n");
        }
    }
}

/**
 * 测试restoreAdjacencyListToSparseMatrix方法
 */
void testRestoreAdjacencyListToSparseMatrix() {
    int m = ROW;
    int n = COL;
    int matrix[][MAX_SIZE] = {
            {0, 0, 0, 1},
            {0, 0, 3, 2},
            {1, 0, 1, 0},
            {0, 2, 0, 0},
            {1, 0, 3, 5}
    };
    printf("稀疏矩阵: \n");
    print(matrix, m, n);
    AdjacencyList *adjacencyList = saveSparseMatrixToAdjacencyList(matrix, m, n);

    // 调用函数恢复成原矩阵
    int resultMatrix[][MAX_SIZE] = {};
    restoreAdjacencyListToSparseMatrix(adjacencyList, resultMatrix, m, n);

    // 输出恢复后的矩阵
    printf("还原后的矩阵: \n");
    print(resultMatrix, m, n);
}

int main() {
    // 由于我自己本地使用的是 CLion 编辑器会有中文乱码的情况，所以添加下面这行代码设置编码正常显示
    system("chcp 65001");
    // 测试print方法
    printf("----------测试print方法----------\n");
    testPrint();

    // 测试saveSparseMatrixToAdjacencyList方法
    printf("----------测试saveSparseMatrixToAdjacencyList方法----------\n");
    testSaveSparseMatrixToAdjacencyList();

    // 测试restoreAdjacencyListToSparseMatrix方法
    printf("----------测试restoreAdjacencyListToSparseMatrix方法----------\n");
    testRestoreAdjacencyListToSparseMatrix();
}