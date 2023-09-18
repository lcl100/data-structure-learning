package 矩阵.代码.java;

public class MatrixTest {
    public static void main(String[] args) throws Exception {
        // 测试print方法
        System.out.println("----------测试print方法----------");
        testPrint();

        // 测试add方法
        System.out.println("----------测试add方法----------");
        testAdd();

        // 测试transpose方法
        System.out.println("----------测试transpose方法----------");
        testTranspose();

        // 测试multiply方法
        System.out.println("----------测试multiply方法----------");
        testMultiply();
    }

    public static void testPrint() {
        // 构造测试用例
        int[][] matrixA = new int[][]{
                {1, 2, 3},
                {4, 6, 7}
        };
        System.out.println("矩阵A: ");
        Matrix.print(matrixA);
    }

    public static void testAdd() throws Exception {
        // 构造测试用例
        int[][] matrixA = new int[][]{
                {1, 2, 3},
                {4, 6, 7}
        };
        System.out.println("矩阵A: ");
        Matrix.print(matrixA);

        int[][] matrixB = new int[][]{
                {11, 12, 13},
                {14, 16, 17}
        };
        System.out.println("矩阵B: ");
        Matrix.print(matrixB);

        // 调用函数，得到测试结果
        int[][] matrixC = Matrix.add(matrixA, matrixB);

        // 打印测试结果
        System.out.println("矩阵C: ");
        Matrix.print(matrixC);
    }

    public static void testTranspose() throws Exception {
        // 构造测试用例一
        int[][] matrixA = new int[][]{
                {1, 2, 3},
                {4, 6, 7}
        };
        System.out.println("矩阵A: ");
        Matrix.print(matrixA);
        // 调用函数
        int[][] transposeA = Matrix.transpose(matrixA);
        // 打印调用结果
        System.out.println("转置后的矩阵A: ");
        Matrix.print(transposeA);

        // 构造测试用例二
        int[][] matrixB = new int[][]{
                {1, 2, 3},
                {4, 6, 7},
                {8, 5, 0}
        };
        System.out.println("矩阵B: ");
        Matrix.print(matrixB);
        // 调用函数
        int[][] transposeB = Matrix.transpose(matrixB);
        // 打印调用结果
        System.out.println("转置后的矩阵B: ");
        Matrix.print(transposeB);
    }

    public static void testMultiply() throws Exception {
        // 构造测试用例
        int[][] matrixA = new int[][]{
                {1, 2, 3},
                {4, 6, 7}
        };
        System.out.println("矩阵A: ");
        Matrix.print(matrixA);

        int[][] matrixB = new int[][]{
                {1, 2, 3},
                {4, 6, 7},
                {8, 5, 0}
        };
        System.out.println("矩阵B: ");
        Matrix.print(matrixB);

        // 调用函数，得到测试结果
        int[][] multiplyC = Matrix.multiply(matrixA, matrixB);

        // 打印测试结果
        System.out.println("矩阵C: ");
        Matrix.print(multiplyC);
    }
}
