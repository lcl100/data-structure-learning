package 矩阵.代码.java;

public class SparseMatrixByTriadElementTest {
    public static void main(String[] args) throws Exception {
        // 测试print方法
        System.out.println("----------测试print方法----------");
        testPrint();

        // 测试saveSparseMatrixToTriad方法
        System.out.println("----------测试saveSparseMatrixToTriad方法----------");
        testSaveSparseMatrixToTriad();

        // 测试restoreTriadToSparseMatrix方法
        System.out.println("----------测试restoreTriadToSparseMatrix方法----------");
        testRestoreTriadToSparseMatrix();
    }

    public static void testPrint() {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {0, 0, 0, 1},
                {0, 0, 3, 2},
                {1, 0, 0, 0},
                {0, 2, 0, 0}
        };
        System.out.println("稀疏矩阵: ");
        SparseMatrixByTriad.print(matrix);
    }

    public static void testSaveSparseMatrixToTriad() throws Exception {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {0, 0, 0, 1},
                {0, 0, 3, 2},
                {1, 0, 0, 0},
                {0, 2, 0, 0}
        };
        System.out.println("稀疏矩阵: ");
        SparseMatrixByTriadElement.print(matrix);

        // 调用函数将二维的对称矩阵压缩成一维数组
        TriadElement[] triad = SparseMatrixByTriadElement.saveSparseMatrixToTriad(matrix);

        // 打印结果
        System.out.println("三元组: ");
        for (int i = 0; i < triad.length; i++) {
            System.out.printf("%2d %2d %2d\n", triad[i].val, triad[i].i, triad[i].j);
        }
    }

    public static void testRestoreTriadToSparseMatrix() {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {0, 0, 0, 1},
                {0, 0, 3, 2},
                {1, 0, 0, 0},
                {0, 2, 0, 0}
        };
        System.out.println("稀疏矩阵: ");
        SparseMatrixByTriadElement.print(matrix);
        TriadElement[] triad = SparseMatrixByTriadElement.saveSparseMatrixToTriad(matrix);

        // 调用函数恢复成原矩阵
        int[][] restoredMatrix = SparseMatrixByTriadElement.restoreTriadToSparseMatrix(triad);

        // 输出恢复后的矩阵
        System.out.println("还原后的矩阵: ");
        SparseMatrixByTriadElement.print(restoredMatrix);
    }
}
