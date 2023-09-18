package 矩阵.代码.java;

public class SparseMatrixByAdjacencyListTest {
    public static void main(String[] args) throws Exception {
        // 测试print方法
        System.out.println("----------测试print方法----------");
        testPrint();

        // 测试saveSparseMatrixToAdjacencyList方法
        System.out.println("----------测试saveSparseMatrixToAdjacencyList方法----------");
        testSaveSparseMatrixToAdjacencyList();

        // 测试restoreAdjacencyListToSparseMatrix方法
        System.out.println("----------测试restoreAdjacencyListToSparseMatrix方法----------");
        testRestoreAdjacencyListToSparseMatrix();
    }

    public static void testPrint() {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {0, 0, 0, 1},
                {0, 0, 3, 2},
                {1, 0, 1, 0},
                {0, 2, 0, 0},
                {1, 0, 3, 5}
        };
        System.out.println("稀疏矩阵: ");
        SparseMatrixByAdjacencyList.print(matrix);
    }

    public static void testSaveSparseMatrixToAdjacencyList() throws Exception {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {0, 0, 0, 1},
                {0, 0, 3, 2},
                {1, 0, 1, 0},
                {0, 2, 0, 0},
                {1, 0, 3, 5}
        };
        System.out.println("稀疏矩阵: ");
        SparseMatrixByAdjacencyList.print(matrix);

        // 调用函数将二维的稀疏矩阵压缩成邻接表存储
        AdjacencyList adjacencyList = SparseMatrixByAdjacencyList.saveSparseMatrixToAdjacencyList(matrix);

        // 打印结果
        System.out.println("邻接表: ");
        ALNode[] rowArray = adjacencyList.rowArray;
        for (ALNode node : rowArray) {
            if (node == null) {
                System.out.printf("\n");
            } else {
                while (node != null) {
                    System.out.printf("%2d ", node.val);
                    node = node.next;
                }
                System.out.print("\n");
            }
        }
    }

    public static void testRestoreAdjacencyListToSparseMatrix() throws Exception {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {0, 0, 0, 1},
                {0, 0, 3, 2},
                {1, 0, 1, 0},
                {0, 2, 0, 0},
                {1, 0, 3, 5}
        };
        System.out.println("稀疏矩阵: ");
        SparseMatrixByAdjacencyList.print(matrix);
        AdjacencyList adjacencyList = SparseMatrixByAdjacencyList.saveSparseMatrixToAdjacencyList(matrix);

        // 调用函数恢复成原矩阵
        int[][] restoredMatrix = SparseMatrixByAdjacencyList.restoreAdjacencyListToSparseMatrix(adjacencyList);

        // 输出恢复后的矩阵
        System.out.println("还原后的矩阵: ");
        SparseMatrixByAdjacencyList.print(restoredMatrix);
    }
}