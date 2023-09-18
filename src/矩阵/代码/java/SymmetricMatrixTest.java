package 矩阵.代码.java;

public class SymmetricMatrixTest {
    public static void main(String[] args) throws Exception {
        // 测试print方法
        System.out.println("----------测试print方法----------");
        testPrint();

        // 测试saveSymmetricMatrix方法
        System.out.println("----------测试saveSymmetricMatrix方法----------");
        testSaveSymmetricMatrix();

        // 测试restoreSymmetricMatrix方法
        System.out.println("----------测试restoreSymmetricMatrix方法----------");
        testRestoreSymmetricMatrix();
    }

    public static void testPrint() {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {0, 1, 2, 3, 4, 5},
                {1, 9, 1, 2, 3, 4},
                {2, 1, 8, 1, 2, 3},
                {3, 2, 1, 7, 1, 2},
                {4, 3, 2, 1, 6, 1},
                {5, 4, 3, 2, 1, 0}

        };
        System.out.println("对称矩阵: ");
        SymmetricMatrix.print(matrix);
    }

    public static void testSaveSymmetricMatrix() throws Exception {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {0, 1, 2, 3, 4, 5},
                {1, 9, 1, 2, 3, 4},
                {2, 1, 8, 1, 2, 3},
                {3, 2, 1, 7, 1, 2},
                {4, 3, 2, 1, 6, 1},
                {5, 4, 3, 2, 1, 0}
        };
        System.out.println("对称矩阵: ");
        SymmetricMatrix.print(matrix);

        // 调用函数将二维的对称矩阵压缩成一维数组
        int[] array = SymmetricMatrix.saveSymmetricMatrix(matrix);

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

    public static void testRestoreSymmetricMatrix() throws Exception {
        // 构造测试用例
        int[][] matrix = new int[][]{
                {0, 1, 2, 3, 4, 5},
                {1, 9, 1, 2, 3, 4},
                {2, 1, 8, 1, 2, 3},
                {3, 2, 1, 7, 1, 2},
                {4, 3, 2, 1, 6, 1},
                {5, 4, 3, 2, 1, 0}
        };
        System.out.println("对称矩阵: ");
        SymmetricMatrix.print(matrix);
        int[] array = SymmetricMatrix.saveSymmetricMatrix(matrix);

        // 调用函数恢复成原矩阵
        int m = matrix.length;
        int n = matrix[0].length;
        int[][] restoredMatrix = SymmetricMatrix.restoreSymmetricMatrix(array, m, n);

        // 输出恢复后的矩阵
        System.out.println("还原后的矩阵: ");
        SymmetricMatrix.print(restoredMatrix);
    }
}
