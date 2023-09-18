package 矩阵.代码.java;

/**
 * 矩阵
 */
public class Matrix {

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
     * 两个矩阵相加得到一个新的矩阵
     * @param matrixA 第一个矩阵
     * @param matrixB 第二个矩阵
     * @return 两个矩阵相加返回的新矩阵
     * @throws Exception 如果两个矩阵大小不一致则会抛出该异常
     */
    public static int[][] add(int[][] matrixA, int[][] matrixB) throws Exception {
        // 参数校验
        if (matrixA.length != matrixB.length) {
            throw new Exception("参数不合法!");
        }
        if ((matrixA.length >= 1 && matrixB.length >= 1) && matrixA[0].length != matrixB[0].length) {
            throw new Exception("参数不合法!");
        }

        // 创建一个新的矩阵C来存储两个矩阵的和
        int[][] matrixC = new int[matrixA.length][matrixA[0].length];
        // 获取行下标和列下标，这里是遍历的矩阵A的行下标和列下标，由于矩阵A和B行数列数相等，所以遍历任何一个都可以
        for (int row = 0; row < matrixA.length; row++) {
            for (int column = 0; column < matrixA[0].length; column++) {
                // 将A和B矩阵相同行下标列下标位置的元素之和存储到矩阵C中
                matrixC[row][column] = matrixA[row][column] + matrixB[row][column];
            }
        }
        return matrixC;
    }

    /**
     * 矩阵转置
     * @param matrix 原矩阵
     * @return 将原矩阵转置后生成的新矩阵
     * @throws Exception 如果矩阵为空则抛出异常
     */
    public static int[][] transpose(int[][] matrix) throws Exception {
        if (matrix.length == 0) {
            throw new Exception("参数不合法!");
        }
        // 创建一个新的矩阵来存储转置后的矩阵
        // 注意，如果原矩阵的大小是m*n，那么新矩阵的大小应该是n*m
        // matrix.length 表示矩阵matrix的行数
        // matrix[0].length 表示矩阵的列数，即第一行元素的个数就表示该矩阵的总列数
        int[][] resultMatrix = new int[matrix[0].length][matrix.length];
        for (int row = 0; row < matrix.length; row++) {
            for (int column = 0; column < matrix[0].length; column++) {
                resultMatrix[column][row] = matrix[row][column];
            }
        }
        return resultMatrix;
    }

    /**
     * 矩阵相乘
     * @param matrixA 第一个矩阵
     * @param matrixB 第二个矩阵
     * @return 两个矩阵相乘返回的新矩阵
     * @throws Exception 如果矩阵A的列数不等于矩阵B的行数则会抛出该异常
     */
    public static int[][] multiply(int[][] matrixA, int[][] matrixB) throws Exception {
        // 校验参数，两个矩阵能相乘的条件是A矩阵的列数必须与B矩阵的行数相等，即矩阵A大小是m*n，矩阵B的大小应该是n*k
        // 相乘后新矩阵的大小应该是m*k
        if (matrixA.length == 0 || matrixB.length == 0) {
            throw new Exception("参数不合法!");
        }
        if (matrixA[0].length != matrixB.length) {
            throw new Exception("参数不合法!");
        }

        // 创建新矩阵C，用来存储两个矩阵A和B相乘后的结果
        int m = matrixA.length;// 矩阵A的行数
        int n = matrixA[0].length;// 矩阵A的列数，也等于矩阵B的行数
        int k = matrixA[0].length;// 矩阵B的列数
        int[][] matrixC = new int[m][k];

        // row和column分别表示新矩阵C的行下标和列下标
        // row又表示矩阵A的行下标，column又表示矩阵B的列下标
        for (int row = 0; row < m; row++) {
            for (int column = 0; column < k; column++) {
                int sum = 0;
                // 由于矩阵A和矩阵B的列数和行数相等，所以index即表示矩阵A的列下标，又表示矩阵B的行下标
                // 计算第row行与第column列对应下标位置的元素相乘的总和
                for (int index = 0; index < n; index++) {
                    sum += matrixA[row][index] * matrixB[index][column];
                }
                // 将计算得到的值存储到新矩阵中
                matrixC[row][column] = sum;
            }
        }
        return matrixC;
    }
}
