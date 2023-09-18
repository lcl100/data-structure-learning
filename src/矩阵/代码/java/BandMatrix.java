package 矩阵.代码.java;

/**
 * 带状矩阵
 */
public class BandMatrix {
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
     * 将带状矩阵矩阵保存成一维数组
     * @param matrix 带状矩阵矩阵
     * @return 压缩后的带状矩阵矩阵，即一维数组
     * @throws Exception 如果带状矩阵矩阵的行数和列数不相等（任何三角矩阵，包括带状矩阵矩阵和带状矩阵矩阵，都必然是方阵）则抛出该异常
     */
    public static int[] saveBandMatrix(int[][] matrix) throws Exception {
        // 参数校验
        int m = matrix.length;
        int n = matrix[0].length;
        if (m != n) {
            throw new Exception("参数不合法!");
        }

        // 存储主对角线带状矩阵区域的所有元素（包括对角线上的元素）
        int k = 0;
        int[] array = new int[3 * n - 1];
        // 注意初始量（行下标从 0 开始，到 m-1 结束；列下标以一个递增数列开始，每次只记录三列的数据，所以也是以一个递增数列结束的）
        for (int row = 0; row < m; row++) {
            for (int column = row - 1; column < row + 2; column++) {
                // 很重要，否则数组会越界
                if (column == -1 || column == n) continue;
                // 将每个元素都存储到一维数组中
                array[k] = matrix[row][column];
                // 将下标加一，指向一维数组的下一个空位置
                k++;
            }
        }
        // 不要忘了存储带状区域之外的相同元素的值，上三角或下三角区域内任意元素的值都可以
        array[k] = matrix[0][n - 1];

        return array;
    }

    /**
     * 将一维数组还原成带状矩阵矩阵
     * @param array 一维数组
     * @param m 带状矩阵矩阵的行数
     * @param n 带状矩阵矩阵的列数，实际上行数和列数应该相等
     * @return 还原成功的带状矩阵矩阵
     */
    public static int[][] restoreBandMatrix(int[] array, int m, int n) {
        // 创建还原后的矩阵，大小仍然是 m 行 n 列
        int[][] matrix = new int[m][n];
        // 下标，指向一维数组 array 的下标
        int k = 0;
        // 这个双层for循环相当于是将二维带状矩阵矩阵压缩成一维数组的逆运算
        for (int row = 0; row < m; row++) {
            for (int column = row - 1; column < row + 2; column++) {
                // 必须跳过，否则抛出数组下标越界异常
                if (column == -1 || column == n) continue;
                matrix[row][column] = array[k];
                // 下标加一
                k++;
            }
        }
        // 不要忘了将上三角和下三角区域的所有元素置为同一个值
        // 因为下三角区域是从第二行开始的，所以行下标起始量是 2
        for (int row = 2; row < m; row++) {
            // 列下标的结束量是一个变化量，每次以等差数列递增
            for (int column = 0; column <= row - 2; column++) {
                // 此时的 array[k] 其实是指一维数组的最后一个元素，这里也可以替换成 array[array.length-1]
                matrix[row][column] = array[k];
                // 由于带状矩阵的上三角和下三角区域是对称的，所以可以不用循环两次，只需要交换行列下标就可以完成赋值
                matrix[column][row] = array[k];
            }
        }

        return matrix;
    }
}
/*
(0,-1)  (0,0)   (0,1)
        (1,0)   (1,1)   (1,2)
                (2,1)   (2,2)   (2,3)
                        (3,2)   (3,3)   (3,4)
                                (4,3)   (4,4)   (4,5)
 */