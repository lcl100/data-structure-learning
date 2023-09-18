package 矩阵.代码.java;

/**
 * 对称矩阵
 */
public class SymmetricMatrix {

    /**
     * 打印矩阵（默认行优先输出）
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
     * 将对称矩阵保存成一维数组
     * @param matrix 对称矩阵
     * @return 压缩后的对称矩阵，即一维数组
     * @throws Exception 如果对称矩阵的行数和列数不相等则抛出该异常
     */
    public static int[] saveSymmetricMatrix(int[][] matrix) throws Exception {
        // 参数校验
        int m = matrix.length;
        int n = matrix[0].length;
        if (m != n) {
            throw new Exception("参数不合法!");
        }

        // 存储主对角线下三角区域的所有元素，
        int k = 0;
        int[] array = new int[(m * (m + 1) / 2)];
        for (int row = 0; row < m; row++) {
            for (int column = 0; column <= row; column++) {
                array[k] = matrix[row][column];
                k++;
            }
        }
        return array;
    }

    /**
     * 将一维数组还原成对称矩阵
     * @param array 一维数组
     * @param m 对称矩阵的行数
     * @param n 对称矩阵的列数，实际上行数和列数应该相等
     * @return 还原成功的对称矩阵
     */
    public static int[][] restoreSymmetricMatrix(int[] array, int m, int n) {
        // 创建还原后的矩阵，大小仍然是 m 行 n 列
        int[][] matrix = new int[m][n];
        // 下标，指向一维数组 array 的下标
        int k = 0;
        // 这个双层for循环相当于是将二维对称矩阵压缩成一维数组的逆运算
        for (int row = 0; row < m; row++) {
            for (int column = 0; column <= row; column++) {
                // 对称矩阵中 A[i][j]=A[j][i]，因此可以利用这点来复原对称矩阵
                matrix[row][column] = array[k];
                matrix[column][row] = array[k];
                // 下标加一
                k++;
            }
        }
        return matrix;
    }
}