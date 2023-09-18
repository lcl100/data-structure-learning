package 矩阵.代码.java;

/**
 * 稀疏矩阵（伪地址法存储）
 */
public class SparseMatrixByTuple {

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
     * 通过伪地址存储稀疏矩阵
     * @param matrix 稀疏矩阵
     * @return 二元组
     */
    public static int[][] saveSparseMatrixToTuple(int[][] matrix) {
        // 计算稀疏矩阵中非零元素的个数，由于必须指定二维数组的行数所以必须计算非零元素的个数
        int notZeroCount = 0;
        for (int row = 0; row < matrix.length; row++) {
            for (int column = 0; column < matrix[0].length; column++) {
                if (matrix[row][column] != 0) {
                    notZeroCount++;
                }
            }
        }

        // 新建一个二元组，即只有两个分量的二维数组
        // notZeroCount 表示稀疏矩阵中的非零元素的个数
        // +1 表示需要额外的一行存储稀疏矩阵的基本信息
        // 第一列存储稀疏矩阵中非零元素的值，第二列存储元素所代表的伪地址
        int[][] tuple = new int[notZeroCount + 1][2];
        // 记录二元组中空位置的下标，从 0 开始
        int k = 1;
        // 稀疏矩阵的行数
        int m = matrix.length;
        // 稀疏矩阵的列数
        int n = matrix[0].length;
        for (int row = 0; row < m; row++) {
            for (int column = 0; column < n; column++) {
                if (matrix[row][column] != 0) {
                    tuple[k][0] = matrix[row][column];
                    tuple[k][1] = getDummyAddress(n, row, column);
                    k++;
                }
            }
        }
        // 不要忘了用第一行存储稀疏矩阵的行数和列数，这是很重要的信息
        tuple[0][0] = m;
        tuple[0][1] = n;

        return tuple;
    }

    /**
     * 将伪地址还原成稀疏矩阵
     * @param tuple 二元组
     * @return 稀疏矩阵
     */
    public static int[][] restoreTupleToSparseMatrix(int[][] tuple) {
        // 创建稀疏矩阵
        int m = tuple[0][0];
        int n = tuple[0][1];
        int[][] matrix = new int[m][n];

        // 从伪地址的第二行开始，因为第一行存储了稀疏矩阵的基本信息
        for (int i = 1; i < tuple.length; i++) {
            int val = tuple[i][0];
            int row = getRow(n, tuple[i][1]);
            int column = getColumn(n, tuple[i][1]);
            matrix[row][column] = val;
        }

        return matrix;
    }

    /**
     * 计算稀疏矩阵中的非零元素的伪地址
     * @param n 稀疏矩阵的列数
     * @param i 非零元素的行下标
     * @param j 非零元素的列下标
     * @return 计算出的伪地址
     */
    private static int getDummyAddress(int n, int i, int j) {
        return n * i + j;
    }

    /**
     * 通过伪地址反推非零元素在稀疏矩阵中的行下标
     * @param n 稀疏矩阵的列数
     * @param a 非零元素的伪地址
     * @return 非零元素在稀疏矩阵中的行下标
     */
    private static int getRow(int n, int a) {
        return a / n;
    }

    /**
     * 通过伪地址反推非零元素在稀疏矩阵中的列下标
     * @param n 稀疏矩阵的列数
     * @param a 非零元素的伪地址
     * @return 非零元素在稀疏矩阵中的列下标
     */
    private static int getColumn(int n, int a) {
        return a % n;
    }
}
