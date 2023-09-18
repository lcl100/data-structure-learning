package 矩阵.代码.java;

public class LowerTriangularMatrixTest {
    public static void main(String[] args) throws Exception {
        // 测试print方法
        System.out.println("----------测试print方法----------");
        testPrint();

        // 测试saveLowerTriangularMatrix方法
        System.out.println("----------测试saveLowerTriangularMatrix方法----------");
        testSaveLowerTriangularMatrix();

        // 测试restoreLowerTriangularMatrix方法
        System.out.println("----------测试restoreLowerTriangularMatrix方法----------");
        testRestoreLowerTriangularMatrix();
    }

    public static void testPrint() {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {1, -1, -1, -1, -1},
                {2, 3, -1, -1, -1},
                {4, 5, 6, -1, -1},
                {7, 8, 9, 10, -1},
                {11, 12, 13, 14, 15}
        };
        System.out.println("下三角矩阵: ");
        LowerTriangularMatrix.print(matrix);
    }

    public static void testSaveLowerTriangularMatrix() throws Exception {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {1, -1, -1, -1, -1},
                {2, 3, -1, -1, -1},
                {4, 5, 6, -1, -1},
                {7, 8, 9, 10, -1},
                {11, 12, 13, 14, 15}
        };
        System.out.println("下三角矩阵: ");
        LowerTriangularMatrix.print(matrix);

        // 调用函数将二维的对称矩阵压缩成一维数组
        int[] array = LowerTriangularMatrix.saveLowerTriangularMatrix(matrix);

        // 打印结果
        System.out.println("压缩后的矩阵: ");
        int k = 0;
        for (int row = 0; row < matrix.length; row++) {
            for (int column = 0; column <= row; column++) {
                System.out.printf("%2d ", array[k]);
                k++;
            }
            System.out.printf("\n");
        }
    }

    public static void testRestoreLowerTriangularMatrix() throws Exception {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {1, -1, -1, -1, -1},
                {2, 3, -1, -1, -1},
                {4, 5, 6, -1, -1},
                {7, 8, 9, 10, -1},
                {11, 12, 13, 14, 15}
        };
        System.out.println("下三角矩阵: ");
        LowerTriangularMatrix.print(matrix);
        int[] array = LowerTriangularMatrix.saveLowerTriangularMatrix(matrix);

        // 调用函数恢复成原矩阵
        int m = matrix.length;
        int n = matrix[0].length;
        int[][] restoredMatrix = LowerTriangularMatrix.restoreLowerTriangularMatrix(array, m, n);

        // 输出恢复后的矩阵
        System.out.println("还原后的矩阵: ");
        LowerTriangularMatrix.print(restoredMatrix);
    }
}
