# Example017

## 题目
已知一个整数序列 `A=(a0, a1, ..., a(n-1))`，其中 `0<=a(i)<n`（`0<=i<n`）。若存在 `a(p1)=a(p2)=...=a(pm)=x` 且 `m>n/2`（`0<=p(k)<n`，`1<=k<=m`），则称 `x` 为 `A` 的主元素。例如，`A=(0, 5, 5, 3, 5, 7, 5, 5)`，则 `5` 为主元素；又如，`A=(0, 5, 5, 3, 5, 1, 5, 7)`，则 `A` 中没有主元素。假设 `A` 中的 `n` 个元素保存在一个一维数组中，请设计一个尽可能高效的算法，找出 `A` 的主元素。若存在主元素，则输出该元素；否则输出 `-1`。

> 注：题目中的`a()`括号内的都表示下标。

## 分析

本题考查的知识点：
- 顺序表

本题解法还是挺多的，但如果要考虑时间复杂度，那么就比较难了。不过作为考研题目，首先是要做出来，其次再考虑更加高效优化的解法。各解法思路如下：
- 第一种解法：双层 `for` 循环，统计每个数的出现次数，然后与 `n/2` 进行比较，然后找出那个数。时间复杂度为 `O(n^2)`。
- 第二种解法：先对数组中所有元素进行排序，那么主元素一定是连续相邻的。我们可以设定两根指针 `i` 和 `j`，其中 `i` 指向元素第一次出现的下标，而 `j` 指向元素最后一次出现的下标加 1 的位置，那么 `j-i` 就是该元素在数组中的出现次数，就可以与 `n/2` 相比较，然后找出主元素。该解法的效率其实也不高，而且如果使用的排序算法时间复杂度比较高（如下面冒泡排序算法的时间复杂度是 `O(n^2)`）那么效果不会比解法一更优。
- 第二种解法的优化：先对数组中所有元素进行排序。如果存在主元素那么主元素一定是数组的中间元素（因为主元素的个数是大于 `n/2`）；但可能存在没有主元素的情况，所以需要再循环一次判断数组的中间元素是否真的是主元素。
- 第三种解法：从前向后扫描数组元素，标记出一个可能成为主元素的元素 `num`，然后重新计数，确认 `num` 是否是主元素。算法步骤如下：第一步，选取候选的主元素，依次扫描所给数组中的每个整数，将第一个遇到的整数 `num` 保存到变量 `c` 中，记录 `num` 的出现次数为 1；若遇到的下一个整数仍等于 `num`，则计数加 1，否则计数减 1；当计数减到 0 时，将遇到的下一个整数保存到 `c` 中，计数重新标记为 1，开始新一轮计数，即从当前位置开始重复上述过程，直到扫描完全部数组元素。第二步，判断 `c` 表示的元素是否是真正的主元素，再次扫描该数组，统计 `c` 中元素出现的次数，若大于 `n/2` 则为主元素；否则，数组中不存在主元素。



## 图解
略。

## C实现

解法一核心代码：

```c
/**
 * 寻找顺序表中的主元素
 * @param A 数组
 * @param n 数组长度
 * @return 如果找到主元素则返回；如果没有找到则返回 -1
 */
int findMainEle(int A[], int n) {
    for (int i = 0; i < n; i++) {
        // 计数器，记录 A[i] 在数组 A 中的出现次数
        int count = 0;
        // 统计 A[i] 在数组 A 中的出现次数
        for (int j = 0; j < n; j++) {
            if (A[i] == A[j]) {
                count++;
            }
        }
        // 判断 A[i] 是否是主元素
        if (count > n / 2) {
            // 如果是主元素则返回
            return A[i];
        }
    }
    // 不存在主元素则返回 -1
    return -1;
}
```

解法二核心代码：

```c
// 同下面的Java代码一致
```

解法二优化核心代码：

```c
// 同下面的Java代码一致
```

解法三核心代码：

```c
// 同下面的Java代码一致
```


完整代码：

```c
#include <stdio.h>

/**
 * 寻找顺序表中的主元素
 * @param A 数组
 * @param n 数组长度
 * @return 如果找到主元素则返回；如果没有找到则返回 -1
 */
int findMainEle(int A[], int n) {
    // 先对数组进行排序，这里采用冒泡排序的方式（它的时间复杂度是 O(n^2)），可以选择更优性能的排序算法
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (A[j] > A[j + 1]) {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }

    int mid = A[n / 2];// 获取数组的中间元素
    // 由于可能存在没有主元素的情况，所以要判断数组的中间元素是否真的是主元素
    int count = 0;// 计数器，记录中间元素的出现次数
    for (int i = 0; i < n; i++) {
        if (mid == A[i]) {
            count++;
        }
    }
    // 判断中间元素是否是主元素
    if (count > n / 2) {
        return mid;
    } else {
        return -1;
    }
}

/**
 * 打印数组
 * @param arr 待打印的数组
 * @param n 数组长度
 */
void print(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i != n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    // 存在主元素的数组
    int A[] = {0, 5, 5, 3, 5, 7, 5, 5};
    int an = 8;
    print(A, an);// 打印数组
    int aEle = findMainEle(A, an);// 调用函数，寻找主元素
    if (aEle != -1) {// 打印结果
        printf("主元素：%d", aEle);
    } else {
        printf("不存在主元素！");
    }

    printf("\n");

    // 不存在主元素的数组
    int B[] = {0, 5, 5, 3, 5, 1, 5, 7};
    int bn = 8;
    print(B, bn);// 打印数组
    int bEle = findMainEle(B, bn);// 调用函数，寻找主元素
    if (bEle != -1) {// 打印结果
        printf("主元素：%d", aEle);
    } else {
        printf("不存在主元素！");
    }
}
```

执行结果：

```text
[0, 5, 5, 3, 5, 7, 5, 5]
主元素：5
[0, 5, 5, 3, 5, 1, 5, 7]
不存在主元素！
```

## Java实现

解法一核心代码：

```java
    /**
     * 寻找顺序表中的主元素
     *
     * @param A 数组
     * @param n 数组长度
     * @return 如果找到主元素则返回；如果不存在主元素则返回 -1
     */
    public static int findMainEle(int[] A, int n) {
        // 双层 for 循环
        for (int i = 0; i < n; i++) {
            // 计数器，记录 A[i] 在数组中的出现次数
            int count = 0;
            // 统计 A[i] 在数组 A 中的出出现次数
            for (int j = 0; j < n; j++) {
                if (A[i] == A[j]) {
                    count++;
                }
            }
            // 判断 count 是否是主元素
            if (count > n / 2) {
                // 如果是主元素则返回
                return A[i];
            }
        }
        // 如果不存在主元素则返回 -1
        return -1;
    }
```

解法二核心代码：

````java
    /**
     * 寻找顺序表中的主元素
     *
     * @param A 数组
     * @param n 数组长度
     * @return 如果找到主元素则返回；如果不存在主元素则返回 -1
     */
    public static int findMainEle(int[] A, int n) {
        // 先对数组进行排序，这里采用冒泡排序的方式
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (A[j] > A[j + 1]) {
                    int temp = A[j];
                    A[j] = A[j + 1];
                    A[j + 1] = temp;
                }
            }
        }

        // 声明两根指针 i 和 j，来统计每个数的出现次数
        int i = 0;// 记录一个元素的起始下标
        int j = 0;// 记录一个元素的结束下标之后的元素的下标
        while (j < n) {
            // 如果相等则指针 j 继续前进
            if (A[j] == A[i]) {
                j++;
            } else {
                // 一旦不等的情况发生，那么 j-i 就是 A[i] 这个元素在数组中的出现次数，那么判断它是否是主元素
                if (j - i > n / 2) {
                    return A[i];
                }
                // 如果不是主元素，则需要继续判断，所以得更新 i 指针为现 j 指针的位置，作为新元素的起始下标
                i = j;
            }
        }
        // 注意可能有 [1, 2, 3, 3, 3] 这样的情况，即主元素在数组的最后，所以特殊处理
        if (j == n) {
            if (j - i > n / 2) {
                return A[i];
            }
        }

        return -1;
    }
````

解法二优化核心代码：

```java
    /**
     * 寻找顺序表中的主元素
     *
     * @param A 数组
     * @param n 数组长度
     * @return 如果找到主元素则返回；如果不存在主元素则返回 -1
     */
    public static int findMainEle(int[] A, int n) {
        // 先对数组进行排序，这里采用冒泡排序的方式（它的时间复杂度是 O(n^2)），可以选择更优性能的排序算法
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (A[j] > A[j + 1]) {
                    int temp = A[j];
                    A[j] = A[j + 1];
                    A[j + 1] = temp;
                }
            }
        }

        int mid = A[n / 2];// 获取数组的中间元素
        // 由于可能存在没有主元素的情况，所以要判断数组的中间元素是否真的是主元素
        int count = 0;// 计数器，记录中间元素的出现次数
        for (int i = 0; i < n; i++) {
            if (mid == A[i]) {
                count++;
            }
        }
        // 判断中间元素是否是主元素
        if (count > n / 2) {
            return mid;
        } else {
            return -1;
        }
    }
```

解法三核心代码：
```java
    /**
     * 寻找顺序表中的主元素
     *
     * @param A 数组
     * @param n 数组长度
     * @return 如果找到主元素则返回；如果不存在主元素则返回 -1
     */
    public static int findMainEle(int[] A, int n) {
        int count = 1;// 用来计数
        int temp = A[0];// 用来保存候选主元素，初始时第一个元素就是主元素

        // 循环数组查找主元素
        for (int i = 1; i < n; i++) {
            if (A[i] == temp) {
                count++;// 对数组 A 中的候选主元素进行计数
            } else {
                count--;// 处理不是候选主元素的情况
                if (count == 0) {// 更换候选主元素，重新计数
                    count = 1;
                    temp = A[i];
                }
            }
        }

        // 统计候选主元素的实际出现次数，判断是否真的是主元素
        int c = 0;// 记录候选主元素 temp 的实际出现次数
        for (int i = 0; i < n; i++) {
            if (A[i] == temp) {
                c++;
            }
        }
        return c > n / 2 ? temp : -1;
    }
```

完整代码：

```java
public class Test {
    public static void main(String[] args) {
        // 存在主元素的数组
        int[] A = new int[]{0, 5, 5, 3, 5, /*7,*/ 5, 5};
        int an = A.length;
        System.out.println(Arrays.toString(A));// 打印数组
        int aEle = findMainEle(A, an);// 调用函数，寻找主元素
        if (aEle != -1) {// 打印结果
            System.out.println("主元素：" + aEle);
        } else {
            System.out.println("不存在主元素！");
        }

        System.out.println();

        // 不存在主元素的数组
        int[] B = new int[]{0, 5, 5, 3, 5, 1, 5, 7};
        int bn = B.length;
        System.out.println(Arrays.toString(B));// 打印数组
        int bEle = findMainEle(B, bn);// 调用函数，寻找主元素
        if (bEle != -1) {// 打印结果
            System.out.println("主元素：" + aEle);
        } else {
            System.out.println("不存在主元素！");
        }
    }

    /**
     * 寻找顺序表中的主元素
     *
     * @param A 数组
     * @param n 数组长度
     * @return 如果找到主元素则返回；如果不存在主元素则返回 -1
     */
    public static int findMainEle(int[] A, int n) {
        int count = 1;// 用来计数
        int temp = A[0];// 用来保存候选主元素，初始时第一个元素就是主元素

        // 循环数组查找主元素
        for (int i = 1; i < n; i++) {
            if (A[i] == temp) {
                count++;// 对数组 A 中的候选主元素进行计数
            } else {
                count--;// 处理不是候选主元素的情况
                if (count == 0) {// 更换候选主元素，重新计数
                    count = 1;
                    temp = A[i];
                }
            }
        }

        // 统计候选主元素的实际出现次数，判断是否真的是主元素
        int c = 0;// 记录候选主元素 temp 的实际出现次数
        for (int i = 0; i < n; i++) {
            if (A[i] == temp) {
                c++;
            }
        }
        return c > n / 2 ? temp : -1;
    }
}
```

执行结果：

```text
[0, 5, 5, 3, 5, 5, 5]
主元素：5

[0, 5, 5, 3, 5, 1, 5, 7]
不存在主元素！
```