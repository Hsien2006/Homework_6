#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// 此處不可修改
// 定義常數
#define SIZE 1000        // 最終隨機陣列的大小
#define RANGE_START 1    // 範圍的起始數字
#define RANGE_END 10000   // 範圍的結束數字

// 此處不可修改
// 在全域宣告計數器
static int linearSearch_count = 0;
static int binarySearch_count = 0;
static int newSearch_count = 0;

// 此處不可修改
// 效能提升計算函數
double calculate_improvement(double original, double optimized) {
    return ((original - optimized) / original) * 100.0;
}

// 此處不可修改
// Fisher-Yates 洗牌演算法函數
void fisherYatesShuffle(int arr[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// 此處不可修改
// 生成不重複隨機數組的函數
void generateUniqueRandomArray(int arr[], int size, int rangeStart, int rangeEnd, unsigned int seed) {
    if (rangeEnd - rangeStart + 1 < size) {
        printf("錯誤：指定範圍內的數字不足以生成所需數量的不重複隨機數\n");
        return;
    }

    srand(seed);
    int* allNumbers = (int*)malloc((rangeEnd - rangeStart + 1) * sizeof(int));
    if (allNumbers == NULL) {
        printf("錯誤：記憶體分配失敗\n");
        return;
    }

    for (int i = 0; i < rangeEnd - rangeStart + 1; i++) {
        allNumbers[i] = i + rangeStart;
    }

    fisherYatesShuffle(allNumbers, rangeEnd - rangeStart + 1);

    for (int i = 0; i < size; i++) {
        arr[i] = allNumbers[i];
    }

    free(allNumbers);
}

// 此處不可修改
// 時間測量函數
double get_high_resolution_time() {
    LARGE_INTEGER frequency;
    LARGE_INTEGER count;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&count);
    return ((double)count.QuadPart / (double)frequency.QuadPart);
}

// 此處不可修改
// 氣泡排序 (bubbleSort) 函數
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 線性搜尋 (linearSearch) 函數，請在此撰寫範例程式的linearSearch函數
int linearSearch(int arr[], int size, int target) {
    linearSearch_count = 0; //初始化計數器
    for (int i = 0; i <= size; i++) {
        linearSearch_count++; //每次比較時計數器加1
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}


// 二元搜尋 (binarySearch) 函數，請在此撰寫範例程式的binarySearch函數
int binarySearch(int arr[], int size, int target) {
    binarySearch_count = 0;  //
    int left = 0;
    int right = size - 1;

    while (left <= target) {
        int mid = left + (right - left) / 2; //
        binarySearch_count++;

        if (arr[mid] == target) {
            return mid;  //
        }
        if (arr[mid] < target) {
            left = mid + 1;//
        }
        else {
            right = mid - 1;//
        }
    }
    return -1;
}

// 新搜尋演算法 (newSearch) 函數，請在此撰寫新的搜尋演算法程式
int newSearch() {

}

// 此處不可修改，但可以修改int newSearchResult = newSearch();裡的參數呼叫
int main(void) {
    int arr[SIZE];
    generateUniqueRandomArray(arr, SIZE, RANGE_START, RANGE_END, 12345);
    bubbleSort(arr, SIZE);

    // 印出前20個數字以驗證結果
    printf("前20個已排序且不重複的隨機數：\n");
    for (int i = 0; i < 20; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    double start_time;
    double end_time;
    int target = 6164;  // 搜尋目標

    // 線性搜尋的時間測試
    start_time = get_high_resolution_time();
    int linearSearchResult = linearSearch(arr, SIZE, target);
    end_time = get_high_resolution_time();
    double  linearSearchResult_time = (end_time - start_time) * 1000000.0;

    // 二元搜尋的時間測試
    start_time = get_high_resolution_time();
    int binarySearchResult = binarySearch(arr, SIZE, target);
    end_time = get_high_resolution_time();
    double  binarySearchResult_time = (end_time - start_time) * 1000000.0;

    // 新搜尋演算法的時間測試
    start_time = get_high_resolution_time();
    int newSearchResult = newSearch();
    end_time = get_high_resolution_time();
    double  newSearch_time = (end_time - start_time) * 1000000.0;

    // 計算線性/新搜尋演算法效能提升百分比
    double linear_new_improvement = calculate_improvement(linearSearchResult_time, newSearch_time);
    // 計算二元/新搜尋演算法效能提升百分比
    double binary_new_improvement = calculate_improvement(binarySearchResult_time, newSearch_time);

    printf("線性搜尋結果：找到於索引 %d\n", linearSearchResult);
    printf("線性搜尋執行時間：%.4f microseconds\n", linearSearchResult_time);
    printf("線性搜尋執行次數：%d\n\n", linearSearch_count);

    printf("二元搜尋結果：找到於索引 %d\n", binarySearchResult);
    printf("二元搜尋執行時間：%.4f microseconds\n", binarySearchResult_time);
    printf("二元搜尋執行次數：%d\n\n", binarySearch_count);

    /* 實作新搜尋演算法，需拿掉此段註解
    printf("新搜尋演算法搜尋結果：找到於索引 %d\n", newSearchResult);
    printf("新搜尋演算法執行時間：%.4f microseconds\n", newSearch_time);
    printf("新搜尋演算法執行次數：%d\n\n", newSearch_count);

    printf("新搜尋演算法比線性效能提升: %.4f%%\n", linear_new_improvement);
    printf("新搜尋演算法比二元效能提升: %.4f%%\n", binary_new_improvement);
    */

    return 0;
}