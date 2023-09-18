package 矩阵.代码.java;

public class UpperTriangularMatrixTest {
    public static void main(String[] args) throws Exception {
        // 测试print方法
        System.out.println("----------测试print方法----------");
        testPrint();

        // 测试saveUpperTriangularMatrix方法
        System.out.println("----------测试saveUpperTriangularMatrix方法----------");
        testSaveUpperTriangularMatrix();

        // 测试restoreUpperTriangularMatrix方法
        System.out.println("----------测试restoreUpperTriangularMatrix方法----------");
        testRestoreUpperTriangularMatrix();
    }

    public static void testPrint() {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {1, 2, 3, 4, 5},
                {-1, 6, 7, 8, 9},
                {-1, -1, 10, 11, 12},
                {-1, -1, -1, 13, 14},
                {-1, -1, -1, -1, 15}
        };
        System.out.println("上三角矩阵: ");
        UpperTriangularMatrix.print(matrix);
    }

    public static void testSaveUpperTriangularMatrix() throws Exception {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {1, 2, 3, 4, 5},
                {-1, 6, 7, 8, 9},
                {-1, -1, 10, 11, 12},
                {-1, -1, -1, 13, 14},
                {-1, -1, -1, -1, 15}
        };
        System.out.println("上三角矩阵: ");
        UpperTriangularMatrix.print(matrix);

        // 调用函数将二维的对称矩阵压缩成一维数组
        int[] array = UpperTriangularMatrix.saveUpperTriangularMatrix(matrix);

        // 打印结果
        System.out.println("压缩后的矩阵: ");
        int k = 0;
        for (int row = 0; row < matrix.length; row++) {
            for (int column = 0; column < row; column++) {
                System.out.printf("   ");
            }
            for (int column = row; column < matrix[0].length; column++) {
                System.out.printf("%2d ", array[k]);
                k++;
            }
            System.out.printf("\n");
        }
    }

    public static void testRestoreUpperTriangularMatrix() throws Exception {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {1, 2, 3, 4, 5},
                {-1, 6, 7, 8, 9},
                {-1, -1, 10, 11, 12},
                {-1, -1, -1, 13, 14},
                {-1, -1, -1, -1, 15}
        };
        System.out.println("上三角矩阵: ");
        UpperTriangularMatrix.print(matrix);
        int[] array = UpperTriangularMatrix.saveUpperTriangularMatrix(matrix);

        // 调用函数恢复成原矩阵
        int m = matrix.length;
        int n = matrix[0].length;
        int[][] restoredMatrix = UpperTriangularMatrix.restoreUpperTriangularMatrix(array, m, n);

        // 输出恢复后的矩阵
        System.out.println("还原后的矩阵: ");
        UpperTriangularMatrix.print(restoredMatrix);
    }
}
