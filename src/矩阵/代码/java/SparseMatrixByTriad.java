package 矩阵.代码.java;

/**
 * 稀疏矩阵（三元组法存储）
 */
public class SparseMatrixByTriad {

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
     * 通过三元组存储稀疏矩阵
     * @param matrix 稀疏矩阵
     * @return 三元组
     */
    public static int[][] saveSparseMatrixToTriad(int[][] matrix) {
        // 计算稀疏矩阵中非零元素的个数，由于必须指定二维数组的行数所以必须计算非零元素的个数
        int notZeroCount = 0;
        for (int row = 0; row < matrix.length; row++) {
            for (int column = 0; column < matrix[0].length; column++) {
                if (matrix[row][column] != 0) {
                    notZeroCount++;
                }
            }
        }

        // 新建一个三元组
        // notZeroCount 表示稀疏矩阵中的非零元素的个数
        // +1 表示需要额外的一行存储稀疏矩阵的基本信息
        int[][] triad = new int[notZeroCount + 1][3];
        // 记录三元组中空位置的下标，从 1 开始
        int k = 1;
        for (int row = 0; row < matrix.length; row++) {
            for (int column = 0; column < matrix[0].length; column++) {
                if (matrix[row][column] != 0) {
                    triad[k][0] = matrix[row][column];
                    triad[k][1] = row;
                    triad[k][2] = column;
                    k++;
                }
            }
        }
        // 不要忘了在三元组的第一行记录稀疏矩阵的非零元素个数、稀疏矩阵的行数和列数
        triad[0][0] = k - 1;// 因为 k 是从 1 开始的，所以需要减去 1 才是实际非零元素的个数
        triad[0][1] = matrix.length;
        triad[0][2] = matrix[0].length;

        return triad;
    }

    /**
     * 将三元组还原成稀疏矩阵
     * @param triad 三元组
     * @return 稀疏矩阵
     */
    public static int[][] restoreTriadToSparseMatrix(int[][] triad) {
        int m = triad[0][1];
        int n = triad[0][2];
        int[][] matrix = new int[m][n];
        // 从三元组的第二行开始，因为第一行存储了三元组的基本信息
        for (int i = 1; i < triad.length; i++) {
            int val = triad[i][0];
            int row = triad[i][1];
            int column = triad[i][2];
            matrix[row][column] = val;
        }

        return matrix;
    }
}
