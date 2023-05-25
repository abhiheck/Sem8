#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Parallel Bubble Sort
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; ++i) {
        swapped = false;

        #pragma omp parallel for shared(arr, swapped)
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                #pragma omp critical
                {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
        }

        if (!swapped) {
            break;
        }
    }
}

int main() {
    vector<int> arr = {9, 7, 5, 11, 12, 2, 14, 3, 10, 6};

    cout << "Original Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // Parallel Bubble Sort
    parallelBubbleSort(arr);

    cout << "Sorted Array (Parallel Bubble Sort): ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

