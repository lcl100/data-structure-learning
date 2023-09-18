package 矩阵.代码.java;

public class SparseMatrixByTupleTest {
    public static void main(String[] args) throws Exception {
        // 测试print方法
        System.out.println("----------测试print方法----------");
        testPrint();

        // 测试saveSparseMatrixToTuple方法
        System.out.println("----------测试saveSparseMatrixToTuple方法----------");
        testSaveSparseMatrixToTuple();

        // 测试restoreTupleToSparseMatrix方法
        System.out.println("----------测试restoreTupleToSparseMatrix方法----------");
        testRestoreTupleToSparseMatrix();
    }

    public static void testPrint() {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {0, 0, 0, 1},
                {0, 0, 3, 2},
                {1, 0, 0, 0},
                {0, 2, 0, 0},
                {0, 0, 0, 5}
        };
        System.out.println("稀疏矩阵: ");
        SparseMatrixByTuple.print(matrix);
    }

    public static void testSaveSparseMatrixToTuple() throws Exception {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {0, 0, 0, 1},
                {0, 0, 3, 2},
                {1, 0, 0, 0},
                {0, 2, 0, 0},
                {0, 0, 0, 5}
        };
        System.out.println("稀疏矩阵: ");
        SparseMatrixByTuple.print(matrix);

        // 调用函数将二维的对称矩阵压缩成一维数组
        int[][] triad = SparseMatrixByTuple.saveSparseMatrixToTuple(matrix);

        // 打印结果
        System.out.println("二元组: ");
        for (int i = 0; i < triad.length; i++) {
            for (int j = 0; j < triad[0].length; j++) {
                System.out.printf("%2d ", triad[i][j]);
            }
            System.out.print("\n");
        }
    }

    public static void testRestoreTupleToSparseMatrix() throws Exception {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {0, 0, 0, 1},
                {0, 0, 3, 2},
                {1, 0, 0, 0},
                {0, 2, 0, 0},
                {0, 0, 0, 5}
        };
        System.out.println("稀疏矩阵: ");
        SparseMatrixByTuple.print(matrix);
        int[][] tuple = SparseMatrixByTuple.saveSparseMatrixToTuple(matrix);

        // 调用函数恢复成原矩阵
        int[][] restoredMatrix = SparseMatrixByTuple.restoreTupleToSparseMatrix(tuple);

        // 输出恢复后的矩阵
        System.out.println("还原后的矩阵: ");
        SparseMatrixByTuple.print(restoredMatrix);
    }
}
