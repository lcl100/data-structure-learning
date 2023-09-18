package 矩阵.代码.java;

/**
 * 稀疏矩阵（邻接表存储）
 */
public class SparseMatrixByAdjacencyList {

    /**
     * 打印矩阵（默认行优先输出）
     *
     * @param matrix 矩阵，即二维数组
     */
    public static void print(int[][] matrix) {
        // row表示行下标
        for (int row = 0; row < matrix.length; row++) {
            // column表示列下标
            for (int column = 0; column < matrix[row].length; column++) {
                System.out.printf("%2d ", matrix[row][column]);
            }
            System.out.print("\n");
        }
        System.out.print("\n");
    }

    /**
     * 通过邻接表存储稀疏矩阵
     *
     * @param matrix 稀疏矩阵
     * @return 邻接表
     */
    public static AdjacencyList saveSparseMatrixToAdjacencyList(int[][] matrix) {
        // 新建一个邻接表
        AdjacencyList list = new AdjacencyList();
        // 初始化邻接表的各属性
        list.m = matrix.length;
        list.n = matrix[0].length;
        list.rowArray = new ALNode[matrix.length];
        ALNode[] rowArray = list.rowArray;
        for (int i = 0; i < rowArray.length; i++) {
            rowArray[i] = null;
        }

        // 记录邻接表中空位置的下标，从 1 开始
        for (int row = 0; row < matrix.length; row++) {
            ALNode node = rowArray[row];
            for (int column = 0; column < matrix[0].length; column++) {
                if (matrix[row][column] != 0) {
                    // 将非零元素创建成邻接表节点
                    ALNode newNode = new ALNode();
                    newNode.val = matrix[row][column];
                    newNode.col = column;
                    newNode.next = null;
                    // 将新结点添加到每行的单链表的尾部，采用尾插法
                    if (node == null) {
                        rowArray[row] = newNode;
                        node = newNode;
                    } else {
                        node.next = newNode;
                        node = newNode;
                    }
                }
            }
        }
        return list;
    }

    /**
     * 将邻接表还原成稀疏矩阵
     *
     * @param list 邻接表
     * @return 稀疏矩阵
     */
    public static int[][] restoreAdjacencyListToSparseMatrix(AdjacencyList list) {
        int m = list.m;
        int n = list.n;
        int[][] matrix = new int[m][n];
        // 遍历邻接表的每一行
        ALNode[] rowArray = list.rowArray;
        for (int row = 0; row < rowArray.length; row++) {
            ALNode node = rowArray[row];
            // 循环单链表
            while (node != null) {
                int column = node.col;
                int val = node.val;
                matrix[row][column] = val;
                node = node.next;
            }
        }
        return matrix;
    }
}

/**
 * 每行的单链表节点定义
 */
class ALNode {
    // 非零元素的值
    int val;
    // 非零元素的列下标
    int col;
    // 指向该节点的下一个非零元素节点
    ALNode next;
}

/**
 * 邻接表的定义
 */
class AdjacencyList {
    // 存储所有行，每一行都是一个单独的单链表
    ALNode[] rowArray;
    // 稀疏矩阵的行数
    int m;
    // 稀疏矩阵的列数
    int n;
}