# Example031

## 题目

定义三元组 `(a, b, c)`（a、b、c 均为正数）的距离 `D = |a-b| + |b-c| + |c-d|`。给定 3 个非空整数集合 S1、S2 和 S3，按升序分别存储在 3 个数组中。请设计一个尽可能高效的算法，计算并输出所有可能的三元组 `(a, b, c)`（a 属于 S1，b 属于 S2，c 属于 S3）中的最小距离。例如 `S1 = {-1, 0, 9}`，`S2 = {-25, -10, 10, 11}`，`S3 = {2, 9, 17 ,30, 41}`，则最小距离为 2，相应的三元组为 `(9, 10, 9)`。

## 分析

**解法一分析**： 

直接三重 for 循环，遍历完所有可能的三元组，然后计算最小距离。但时间复杂度非常高，为 `O(n1*n2*n3)`。

**解法二分析**： 

算法的基本思想是，设置三个指针，分别用于遍历这三个数组。因为数组已有序，我们的算法实际上是找到一个尽可能接近的三元组，设三个数组分别为 S1、S2、S3，我们遍历使用的下标变量分别为x、y、z，则我们在 `S1[x]` 小于 `S2[y]` 和 `S3[z]` 的时候，更新 x，其它两个下标变量 y 和 z 更新同理，同时，对于每一组三个下标变量，我们计算其对应元素的距离值，然后与上一次的距离值比较，并取其中较小的一个作为更新的距离值。时间复杂度为 `O(n1+n2+n3)`。

参考资料：
- [三元组最小距离](https://blog.csdn.net/qq_41317652/article/details/103875926)
- [如何求最小三元组距离](https://www.cnblogs.com/mukekeheart/p/5727106.html)

## 图解

略。

## C实现

解法一核心代码：

```c
/**
 * 求一个数的绝对值
 *
 * @param num 指定整数，可以是正数，也可以是负数
 * @return 绝对值
 */
int abs(int num) {
    if (num < 0) {
        return -num;
    } else {
        return num;
    }
}

/**
  * 求所有可能的三元组中的最小距离
  *
  * @param S1 第一个非空整数集合
  * @param n1 第一个数组的长度
  * @param S2 第二个非空整数集合
  * @param n2 第二个数组的长度
  * @param S3 第三个非空整数集合
  * @param n3 第三个数组的长度
  * @return 三元组中的最小距离
  */
int minDistance(int S1[], int n1, int S2[], int n2, int S3[], int n3) {
    // 变量，记录 S1 中的元素
    int a = S1[0];
    // 变量，记录 S2 中的元素
    int b = S2[0];
    // 变量，记录 S3 中的元素
    int c = S3[0];
    // 变量，记录三元组中的最小距离
    int minD = abs(a - b) + abs(b - c) + abs(c - a);

    // 三重 for 循环遍历三个非空整数集合
    for (int x = 0; x < n1; x++) {
        for (int y = 0; y < n2; y++) {
            for (int z = 0; z < n3; z++) {
                // 计算由 S1[x]、S2[y] 和 S3[z] 组成的三元组的最小距离
                int min = abs(S1[x] - S2[y]) + abs(S2[y] - S3[z]) + abs(S3[z] - S1[x]);
                // 如果比 minD 更小，那么更新
                if (min < minD) {
                    minD = min;
                    a = S1[x];
                    b = S2[y];
                    c = S3[z];
                }
            }
        }
    }
    printf("最小距离为 %d，相应的三元组为 (%d, %d, %d)。", minD, a, b, c);
    return minD;
}
```

解法二核心代码：

```c 
/**
 * 判断 a 是否是三个数中的最小值
 *
 * @param a 第一个数
 * @param b 第二个数
 * @param c 第三个数
 * @return 如果 a 是三个数中的最小值则返回 1，否则返回 0
 */
int minA(int a, int b, int c) {
    if (a <= b && a <= c) {
        return 1;
    }
    return 0;
}

/**
 * 求一个数的绝对值
 *
 * @param num 指定整数，可以是正数，也可以是负数
 * @return 绝对值
 */
int abs(int num) {
    if (num < 0) {
        return -num;
    } else {
        return num;
    }
}

/**
 * 求所有可能的三元组中的最小距离
 *
 * @param S1 第一个非空整数集合
 * @param n1 第一个数组的长度
 * @param S2 第二个非空整数集合
 * @param n2 第二个数组的长度
 * @param S3 第三个非空整数集合
 * @param n3 第三个数组的长度
 * @return 三元组中的最小距离
 */
int minDistance(int S1[], int n1, int S2[], int n2, int S3[], int n3) {
    int x = 0, y = 0, z = 0;
    // 变量，记录三元组中的最小距离
    int minD = abs(S1[x] - S2[y]) + abs(S2[y] - S3[z]) + abs(S3[z] - S1[x]);

    while (x < n1 && y < n2 && z < n3) {
        int min = abs(S1[x] - S2[y]) + abs(S2[y] - S3[z]) + abs(S3[z] - S1[x]);
        if (min < minD) {
            minD = min;// 更新最小距离
        }
        if (minA(S1[x], S2[y], S3[z]) == 1) {// 如果 S1[x] 是三个数中的最小值，则 x 前进
            x++;
        } else if (minA(S2[y], S3[z], S1[x]) == 1) {// 如果 S2[y] 是三个数中的最小值，则 y 前进
            y++;
        } else {// 如果 S3[z] 是三个数中的最小值，则 z 前进
            z++;
        }
    }

    return minD;
}
```

完整代码：

```c
#include <stdio.h>

/**
 * 求一个数的绝对值
 *
 * @param num 指定整数，可以是正数，也可以是负数
 * @return 绝对值
 */
int abs(int num) {
    if (num < 0) {
        return -num;
    } else {
        return num;
    }
}

/**
  * 求所有可能的三元组中的最小距离
  *
  * @param S1 第一个非空整数集合
  * @param n1 第一个数组的长度
  * @param S2 第二个非空整数集合
  * @param n2 第二个数组的长度
  * @param S3 第三个非空整数集合
  * @param n3 第三个数组的长度
  * @return 三元组中的最小距离
  */
int minDistance(int S1[], int n1, int S2[], int n2, int S3[], int n3) {
    // 变量，记录 S1 中的元素
    int a = S1[0];
    // 变量，记录 S2 中的元素
    int b = S2[0];
    // 变量，记录 S3 中的元素
    int c = S3[0];
    // 变量，记录三元组中的最小距离
    int minD = abs(a - b) + abs(b - c) + abs(c - a);

    // 三重 for 循环遍历三个非空整数集合
    for (int x = 0; x < n1; x++) {
        for (int y = 0; y < n2; y++) {
            for (int z = 0; z < n3; z++) {
                // 计算由 S1[x]、S2[y] 和 S3[z] 组成的三元组的最小距离
                int min = abs(S1[x] - S2[y]) + abs(S2[y] - S3[z]) + abs(S3[z] - S1[x]);
                // 如果比 minD 更小，那么更新
                if (min < minD) {
                    minD = min;
                    a = S1[x];
                    b = S2[y];
                    c = S3[z];
                }
            }
        }
    }
    printf("最小距离为 %d，相应的三元组为 (%d, %d, %d)。", minD, a, b, c);
    return minD;
}

int main() {
    int A[] = {-1, 0, 9};
    int an = 3;
    int B[] = {-25, -10, 10, 11};
    int bn = 4;
    int C[] = {2, 9, 17, 30, 41};
    int cn = 5;

    // 调用函数
    minDistance(A, an, B, bn, C, cn);
}
```

执行结果：

```text
最小距离为 2，相应的三元组为 (9, 10, 9)。
```

## Java实现

解法一核心代码：

```java
    /**
     * 求所有可能的三元组中的最小距离
     *
     * @param S1 第一个非空整数集合
     * @param n1 第一个数组的长度
     * @param S2 第二个非空整数集合
     * @param n2 第二个数组的长度
     * @param S3 第三个非空整数集合
     * @param n3 第三个数组的长度
     * @return 三元组中的最小距离
     */
    public static int minDistance(int S1[], int n1, int S2[], int n2, int S3[], int n3) {
        // 变量，记录 S1 中的元素
        int a = S1[0];
        // 变量，记录 S2 中的元素
        int b = S2[0];
        // 变量，记录 S3 中的元素
        int c = S3[0];
        // 变量，记录三元组中的最小距离
        int minD = abs(a - b) + abs(b - c) + abs(c - a);

        // 三重 for 循环遍历三个非空整数集合
        for (int x = 0; x < n1; x++) {
            for (int y = 0; y < n2; y++) {
                for (int z = 0; z < n3; z++) {
                    // 计算由 S1[x]、S2[y] 和 S3[z] 组成的三元组的最小距离
                    int min = abs(S1[x] - S2[y]) + abs(S2[y] - S3[z]) + abs(S3[z] - S1[x]);
                    // 如果比 minD 更小，那么更新
                    if (min < minD) {
                        minD = min;
                        a = S1[x];
                        b = S2[y];
                        c = S3[z];
                    }
                }
            }
        }
        System.out.println("最小距离为 " + minD + "，相应的三元组为 (" + a + ", " + b + ", " + c + ")。");
        return minD;
    }

    /**
     * 求一个数的绝对值
     *
     * @param num 指定整数，可以是正数，也可以是负数
     * @return 绝对值
     */
    private static int abs(int num) {
        if (num < 0) {
            return -num;
        } else {
            return num;
        }
    }
```

解法二核心代码：

```java
    /**
     * 求所有可能的三元组中的最小距离
     *
     * @param S1 第一个非空整数集合
     * @param n1 第一个数组的长度
     * @param S2 第二个非空整数集合
     * @param n2 第二个数组的长度
     * @param S3 第三个非空整数集合
     * @param n3 第三个数组的长度
     * @return 三元组中的最小距离
     */
    public static int minDistance(int S1[], int n1, int S2[], int n2, int S3[], int n3) {
        int x = 0, y = 0, z = 0;
        // 变量，记录三元组中的最小距离
        int minD = abs(S1[x] - S2[y]) + abs(S2[y] - S3[z]) + abs(S3[z] - S1[x]);

        while (x < n1 && y < n2 && z < n3) {
            int min = abs(S1[x] - S2[y]) + abs(S2[y] - S3[z]) + abs(S3[z] - S1[x]);
            if (min < minD) {
                minD = min;// 更新最小距离
            }
            if (minA(S1[x], S2[y], S3[z]) == 1) {// 如果 S1[x] 是三个数中的最小值，则 x 前进
                x++;
            } else if (minA(S2[y], S3[z], S1[x]) == 1) {// 如果 S2[y] 是三个数中的最小值，则 y 前进
                y++;
            } else {// 如果 S3[z] 是三个数中的最小值，则 z 前进
                z++;
            }
        }

        return minD;
    }

    /**
     * 判断 a 是否是三个数中的最小值
     *
     * @param a 第一个数
     * @param b 第二个数
     * @param c 第三个数
     * @return 如果 a 是三个数中的最小值则返回 1，否则返回 0
     */
    private static int minA(int a, int b, int c) {
        if (a <= b && a <= c) {
            return 1;
        }
        return 0;
    }

    /**
     * 求一个数的绝对值
     *
     * @param num 指定整数，可以是正数，也可以是负数
     * @return 绝对值
     */
    private static int abs(int num) {
        if (num < 0) {
            return -num;
        } else {
            return num;
        }
    }
```

完整代码：

```java
public class Test {
    public static void main(String[] args) {
        int[] A = new int[]{-1, 0, 9};
        int[] B = new int[]{-25, -10, 10, 11};
        int[] C = new int[]{2, 9, 17, 30, 41};

        // 调用函数
        minDistance(A, A.length, B, B.length, C, C.length);
    }

    /**
     * 求所有可能的三元组中的最小距离
     *
     * @param S1 第一个非空整数集合
     * @param n1 第一个数组的长度
     * @param S2 第二个非空整数集合
     * @param n2 第二个数组的长度
     * @param S3 第三个非空整数集合
     * @param n3 第三个数组的长度
     * @return 三元组中的最小距离
     */
    public static int minDistance(int S1[], int n1, int S2[], int n2, int S3[], int n3) {
        // 变量，记录 S1 中的元素
        int a = S1[0];
        // 变量，记录 S2 中的元素
        int b = S2[0];
        // 变量，记录 S3 中的元素
        int c = S3[0];
        // 变量，记录三元组中的最小距离
        int minD = abs(a - b) + abs(b - c) + abs(c - a);

        // 三重 for 循环遍历三个非空整数集合
        for (int x = 0; x < n1; x++) {
            for (int y = 0; y < n2; y++) {
                for (int z = 0; z < n3; z++) {
                    // 计算由 S1[x]、S2[y] 和 S3[z] 组成的三元组的最小距离
                    int min = abs(S1[x] - S2[y]) + abs(S2[y] - S3[z]) + abs(S3[z] - S1[x]);
                    // 如果比 minD 更小，那么更新
                    if (min < minD) {
                        minD = min;
                        a = S1[x];
                        b = S2[y];
                        c = S3[z];
                    }
                }
            }
        }
        System.out.println("最小距离为 " + minD + "，相应的三元组为 (" + a + ", " + b + ", " + c + ")。");
        return minD;
    }

    /**
     * 求一个数的绝对值
     *
     * @param num 指定整数，可以是正数，也可以是负数
     * @return 绝对值
     */
    private static int abs(int num) {
        if (num < 0) {
            return -num;
        } else {
            return num;
        }
    }
}
```

执行结果：

```text
最小距离为 2，相应的三元组为 (9, 10, 9)。
```