# Example028

## 题目

线性表 `[a1, a2, a3, ..., an]` 中的元素递增有序且按顺序存储于计算机内。要求设计一个算法，完成用最少时间在表中查找数值为 `x`
的元素，若找到，则将其与后继元素位置相交换，若找不到，则将其插入表中并使表中元素仍递增有序。

## 分析

本题考查的知识点：

- 二分查找
- 交换数组元素
- 在数组中插入新元素

**分析**：

- 顺序存储的线性表递增有序，要求用最少的时间在表中查找数值为 x 的元素，所有要采用二分查找。
- 所以本题的难点在于二分查找，是一个综合性比较高的题目。

## 图解

略。

## C实现

核心代码：

```c
/**
 * 有序顺序表
 * @param A 数组
 * @param n 数组长度
 * @param x 指定数值
 */
void binarySearch(int A[], int n, int x) {
    // 利用二分查找来找到数组中等于 x 的元素
    int low = 0;
    int high = n - 1;
    int mid = -1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (A[mid] == x) {
            break;
        } else if (A[mid] > x) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    // 下面两个 if 语句只会执行一个
    // 如果找到则将其与后继元素位置相交换
    if (A[mid] == x && mid != n - 1) {// 若最后一个元素与 x 相等，则不存在与其后继交换的操作
        int temp = A[mid];
        A[mid] = A[mid + 1];
        A[mid + 1] = temp;
    }
    // 如果没有找到，则将其插入到顺序表指定位置
    if (low > high) {
        int i;
        // 后移元素
        for (i = n - 1; i > high; i--) {
            A[i + 1] = A[i];
        }
        // 插入 x
        A[i + 1] = x;
    }
}
```

完整代码：

```c
#include <stdio.h>

/**
 * 有序顺序表
 * @param A 数组
 * @param n 数组长度
 * @param x 指定数值
 */
void binarySearch(int A[], int n, int x) {
    // 利用二分查找来找到数组中等于 x 的元素
    int low = 0;
    int high = n - 1;
    int mid = -1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (A[mid] == x) {
            break;
        } else if (A[mid] > x) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    // 下面两个 if 语句只会执行一个
    // 如果找到则将其与后继元素位置相交换
    if (A[mid] == x && mid != n - 1) {// 若最后一个元素与 x 相等，则不存在与其后继交换的操作
        int temp = A[mid];
        A[mid] = A[mid + 1];
        A[mid + 1] = temp;
    }
    // 如果没有找到，则将其插入到顺序表指定位置
    if (low > high) {
        int i;
        // 后移元素
        for (i = n - 1; i > high; i--) {
            A[i + 1] = A[i];
        }
        // 插入 x
        A[i + 1] = x;
    }
}

/**
 * 打印数组
 * @param arr 数组
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
    int A[] = {1, 2, 3, 5, 6, 7};
    int n = 6;
    print(A, n);

    // 调用函数
    int x = 4;
    binarySearch(A, n, x);
    print(A, 7);
}
```

执行结果：

```text
[1, 2, 3, 5, 6, 7]
[1, 2, 3, 4, 5, 6, 7]
```

## Java实现

核心代码：

```java
    /**
 * 有序顺序表
 *
 * @param A 数组
 * @param n 数组长度
 * @param x 指定数值
 */
public static void binarySearch(int[]A,int n,int x){
        // 利用二分查找来找到数组中等于 x 的元素
        int low=0;
        int high=n-1;
        int mid=-1;
        while(low<=high){
        mid=(low+high)/2;
        if(A[mid]==x){
        break;
        }else if(A[mid]>x){
        high=mid-1;
        }else{
        low=mid+1;
        }
        }
        // 下面两个 if 语句只会执行一个
        // 如果找到则将其与后继元素位置相交换
        if(A[mid]==x&&mid!=n-1){// 若最后一个元素与 x 相等，则不存在与其后继交换的操作
        int temp=A[mid];
        A[mid]=A[mid+1];
        A[mid+1]=temp;
        }
        // 如果没有找到，则将其插入到顺序表指定位置
        if(low>high){
        int i;
        // 后移元素
        for(i=n-1;i>high;i--){
        A[i+1]=A[i];
        }
        // 插入 x
        A[i+1]=x;
        }
        }
```

完整代码：

```java
public class Test {
    public static void main(String[] args) throws Exception {
        int[] A = new int[]{1, 2, 3, 4, 5, 6, 7};
        int n = 7;
        System.out.println(Arrays.toString(A));

        // 调用函数
        int x = 4;
        binarySearch(A, n, x);
        System.out.println(Arrays.toString(A));
    }

    /**
     * 有序顺序表
     *
     * @param A 数组
     * @param n 数组长度
     * @param x 指定数值
     */
    public static void binarySearch(int[] A, int n, int x) {
        // 利用二分查找来找到数组中等于 x 的元素
        int low = 0;
        int high = n - 1;
        int mid = -1;
        while (low <= high) {
            mid = (low + high) / 2;
            if (A[mid] == x) {
                break;
            } else if (A[mid] > x) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        // 下面两个 if 语句只会执行一个
        // 如果找到则将其与后继元素位置相交换
        if (A[mid] == x && mid != n - 1) {// 若最后一个元素与 x 相等，则不存在与其后继交换的操作
            int temp = A[mid];
            A[mid] = A[mid + 1];
            A[mid + 1] = temp;
        }
        // 如果没有找到，则将其插入到顺序表指定位置
        if (low > high) {
            int i;
            // 后移元素
            for (i = n - 1; i > high; i--) {
                A[i + 1] = A[i];
            }
            // 插入 x
            A[i + 1] = x;
        }
    }
}
```

执行结果：

```text
[1, 2, 3, 4, 5, 6, 7]
[1, 2, 3, 5, 4, 6, 7]
```