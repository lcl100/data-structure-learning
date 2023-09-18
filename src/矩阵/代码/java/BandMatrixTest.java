package 矩阵.代码.java;

public class BandMatrixTest {
    public static void main(String[] args) throws Exception {
        // 测试print方法
        System.out.println("----------测试print方法----------");
        testPrint();

        // 测试saveBandMatrix方法
        System.out.println("----------测试saveBandMatrix方法----------");
        testSaveBandMatrix();

        // 测试restoreBandMatrix方法
        System.out.println("----------测试restoreBandMatrix方法----------");
        testRestoreBandMatrix();
    }

    public static void testPrint() {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {1, 2, -1, -1, -1},
                {3, 4, 5, -1, -1},
                {-1, 6, 7, 8, -1},
                {-1, -1, 9, 10, 11},
                {-1, -1, -1, 12, 13}
        };
        System.out.println("带状矩阵: ");
        BandMatrix.print(matrix);
    }

    public static void testSaveBandMatrix() throws Exception {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {1, 2, -1, -1, -1},
                {3, 4, 5, -1, -1},
                {-1, 6, 7, 8, -1},
                {-1, -1, 9, 10, 11},
                {-1, -1, -1, 12, 13}
        };
        System.out.println("带状矩阵: ");
        BandMatrix.print(matrix);

        // 调用函数将二维的对称矩阵压缩成一维数组
        int[] array = BandMatrix.saveBandMatrix(matrix);

        // 打印结果
        System.out.println("压缩后的矩阵: ");
        int k = 0;
        for (int row = 0; row < matrix.length; row++) {
            for (int column = 2; column <= row; column++) {
                System.out.printf("   ");
            }
            for (int column = row - 1; column < row + 2; column++) {
                if (column == -1 || column == matrix[0].length) continue;
                System.out.printf("%2d ", array[k]);
                k++;
            }
            System.out.printf("\n");
        }
    }

    public static void testRestoreBandMatrix() throws Exception {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {1, 2, -1, -1, -1},
                {3, 4, 5, -1, -1},
                {-1, 6, 7, 8, -1},
                {-1, -1, 9, 10, 11},
                {-1, -1, -1, 12, 13}
        };
        System.out.println("带状矩阵: ");
        BandMatrix.print(matrix);
        int[] array = BandMatrix.saveBandMatrix(matrix);

        // 调用函数恢复成原矩阵
        int m = matrix.length;
        int n = matrix[0].length;
        int[][] restoredMatrix = BandMatrix.restoreBandMatrix(array, m, n);

        // 输出恢复后的矩阵
        System.out.println("还原后的矩阵: ");
        BandMatrix.print(restoredMatrix);
    }
}
