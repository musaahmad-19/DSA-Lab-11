#include <iostream>
using namespace std;

static long long comparisons = 0;
static bool trace = false;

void printArray(const int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) cout << arr[i] << (i + 1 < n ? ", " : "");
    cout << "]";
}

void swapInt(int& a, int& b) { int t = a; a = b; b = t; }

static int gN = 0;  // full array size, only used for trace printing

// Lomuto partition: pivot = arr[high]; returns pivot's final index
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;                       // end of "<= pivot" region
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swapInt(arr[i], arr[j]);
        }
    }
    swapInt(arr[i + 1], arr[high]);        // pivot to its final spot
    int pi = i + 1;
    if (trace) {
        cout << "  pivot = " << pivot << ", pi = " << pi << ", array = ";
        printArray(arr, gN);
        cout << "\n";
    }
    return pi;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);       // exclude pi
        quickSort(arr, pi + 1, high);      // exclude pi
    }
}

void runTrace(const char* name, int arr[], int n) {
    cout << "\n=== Trace: " << name << " ===\nBefore: ";
    printArray(arr, n);
    cout << "\n";
    gN = n; trace = true; comparisons = 0;
    quickSort(arr, 0, n - 1);
    trace = false;
    cout << "After:  ";
    printArray(arr, n);
    cout << "\nComparisons: " << comparisons << "\n";
}

void runCount(const char* name, int arr[], int n) {
    comparisons = 0;
    quickSort(arr, 0, n - 1);
    cout << name << " -> sorted ";
    printArray(arr, n);
    cout << ", comparisons = " << comparisons << "\n";
}

// Hand trace of first partition of {2,1,5,4,6,3} (pivot = 3), printed by code
void firstPartitionTrace() {
    int a[] = {2, 1, 5, 4, 6, 3};
    int low = 0, high = 5, pivot = a[high], i = low - 1;
    cout << "\n=== First partition pass of {2,1,5,4,6,3}, pivot = 3 ===\n";
    for (int j = low; j < high; j++) {
        cout << "  j=" << j << " arr[j]=" << a[j];
        if (a[j] <= pivot) {
            i++;
            swapInt(a[i], a[j]);
            cout << " <= pivot -> i=" << i << ", swap arr[" << i << "] & arr[" << j << "]";
        } else {
            cout << " >  pivot -> no swap (i=" << i << ")";
        }
        cout << " : ";
        printArray(a, 6);
        cout << "\n";
    }
    swapInt(a[i + 1], a[high]);
    cout << "  final swap arr[" << i + 1 << "] & arr[" << high << "] : ";
    printArray(a, 6);
    cout << "  -> pi = " << i + 1 << "\n";
}

int main() {
    int t1[] = {2, 1, 5, 4, 6, 3};
    int t2[] = {35, 12, 43, 8, 51, 27, 19};
    runTrace("{2, 1, 5, 4, 6, 3}", t1, 6);
    runTrace("{35, 12, 43, 8, 51, 27, 19}", t2, 7);

    cout << "\n=== Comparison counts ===\n";
    int random_[]   = {5, 1, 4, 2, 8};
    int sorted_[]   = {1, 2, 4, 5, 8};
    int reversed_[] = {8, 5, 4, 2, 1};
    int same_[]     = {7, 7, 7, 7, 7};
    int one_[]      = {9};
    runCount("Random   {5,1,4,2,8}", random_, 5);
    runCount("Sorted   {1,2,4,5,8}", sorted_, 5);
    runCount("Reverse  {8,5,4,2,1}", reversed_, 5);
    runCount("Repeated {7,7,7,7,7}", same_, 5);
    runCount("n = 1    {9}        ", one_, 1);

    int* empty = nullptr;
    comparisons = 0;
    quickSort(empty, 0, -1);
    cout << "n = 0                 -> comparisons = " << comparisons << "\n";

    firstPartitionTrace();
    return 0;
}