package 矩阵.代码.java;

/**
 * 下三角矩阵
 */
public class LowerTriangularMatrix {
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
     * 将下三角矩阵保存成一维数组
     * @param matrix 下三角矩阵
     * @return 压缩后的下三角矩阵，即一维数组
     * @throws Exception 如果下三角矩阵的行数和列数不相等（任何三角矩阵，包括下三角矩阵和下三角矩阵，都必然是方阵）则抛出该异常
     */
    public static int[] saveLowerTriangularMatrix(int[][] matrix) throws Exception {
        // 参数校验
        int m = matrix.length;
        int n = matrix[0].length;
        if (m != n) {
            throw new Exception("参数不合法!");
        }

        // 存储主对角线下三角区域的所有元素（包括对角线上的元素）
        int k = 0;
        int[] array = new int[(n * (n + 1) / 2) + 1];
        for (int row = 0; row < m; row++) {
            // 注意列下标最多可以与行下标相等
            // 第一行有1列有效元素，第二行有2列，第三行有3列，第四行有4列，第五行有5列，因此 column<=row
            for (int column = 0; column <= row; column++) {
                // 将每个元素都存储到一维数组中
                array[k] = matrix[row][column];
                // 将下标加一，指向一维数组的下一个空位置
                k++;
            }
        }
        // 不要忘了存储主对角线上方三角区域（不包括对角线）的元素值，都是同一个值，我们通常用一维数组的最后一个位置来存储它
        // 上三角区域（不包括对角线）任意下标位置的元素都可以
        array[k] = matrix[0][n - 1];

        return array;
    }

    /**
     * 将一维数组还原成下三角矩阵
     * @param array 一维数组
     * @param m 下三角矩阵的行数
     * @param n 下三角矩阵的列数，实际上行数和列数应该相等
     * @return 还原成功的下三角矩阵
     */
    public static int[][] restoreLowerTriangularMatrix(int[] array, int m, int n) {
        // 创建还原后的矩阵，大小仍然是 m 行 n 列
        int[][] matrix = new int[m][n];
        // 下标，指向一维数组 array 的下标
        int k = 0;
        // 注意初始量（行下标每次从 0 开始，到 m-1 结束；列下标每次从 0 开始，结束却是一个递增数列）
        // 这个双层for循环相当于是将二维下三角矩阵压缩成一维数组的逆运算
        for (int row = 0; row < m; row++) {
            for (int column = 0; column <= row; column++) {
                matrix[row][column] = array[k];
                // 下标加一
                k++;
            }
        }
        // 注意初始量（行下标每次从 0 开始，到 m-1 结束；列下标是以一个递增数列开始，到 n-1 结束）
        // 不要忘了将主对角线上方三角区域（不包括主对角线）的元素都置为同一个值
        // 但最多只会到达第 m-1 行，因为主对角线的最后一个元素位于最后一行，而上三角区域不包括主对角线上的元素
        for (int row = 0; row < m; row++) {// 因此可以是 row<m，也可以是 row<=m-1
            // 从第二列开始，因为主对角线的第一个元素位于第一列，而上三角区域不包括主对角线上的元素
            // 假设上三角区域的值都为0，那么会第一行有4个零，第二行有3个零，第三行有2个零，第四行有1个零
            for (int column = row + 1; column < n; column++) {
                // 此时的 array[k] 其实是指一维数组的最后一个元素，这里也可以替换成 array[array.length-1]
                matrix[row][column] = array[k];
            }
        }

        return matrix;
    }
}
