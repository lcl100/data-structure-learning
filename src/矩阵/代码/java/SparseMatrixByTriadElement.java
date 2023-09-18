package 矩阵.代码.java;

public class SparseMatrixByTriadElement {

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
    public static TriadElement[] saveSparseMatrixToTriad(int[][] matrix) {
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
        TriadElement[] triads = new TriadElement[notZeroCount + 1];
        // 记录三元组中空位置的下标，从 1 开始
        int k = 1;
        for (int row = 0; row < matrix.length; row++) {
            for (int column = 0; column < matrix[0].length; column++) {
                if (matrix[row][column] != 0) {
                    TriadElement element = new TriadElement();
                    element.val = matrix[row][column];
                    element.i = row;
                    element.j = column;
                    triads[k] = element;
                    k++;
                }
            }
        }
        // 不要忘了在三元组的第一行记录稀疏矩阵的非零元素个数、稀疏矩阵的行数和列数
        TriadElement element = new TriadElement();
        element.val = k - 1;// 因为 k 是从 1 开始的，所以需要减去 1 才是实际非零元素的个数
        element.i = matrix.length;
        element.j = matrix[0].length;
        triads[0] = element;

        return triads;
    }

    /**
     * 将三元组还原成稀疏矩阵
     * @param triads 三元组
     * @return 稀疏矩阵
     */
    public static int[][] restoreTriadToSparseMatrix(TriadElement[] triads) {
        int m = triads[0].i;
        int n = triads[0].j;
        int[][] matrix = new int[m][n];
        // 从三元组的第二行开始，因为第一行存储了三元组的基本信息
        for (int i = 1; i < triads.length; i++) {
            int val = triads[i].val;
            int row = triads[i].i;
            int column = triads[i].j;
            matrix[row][column] = val;
        }

        return matrix;
    }
}

/**
 * 三元组中的元素
 */
class TriadElement {
    int val;// 表示元素在稀疏矩阵中的值
    int i;// 表示元素在稀疏矩阵中的行下标
    int j;// 表示元素在稀疏矩阵中的列下标
}