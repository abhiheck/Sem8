#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void parallelReduction(const vector<int>& arr, int& minVal, int& maxVal, int& sum, double& average) {
    int n = arr.size();
    int localMin = arr[0];
    int localMax = arr[0];
    int localSum = 0;

    #pragma omp parallel for reduction(min : localMin) reduction(max : localMax) reduction(+: localSum)
    for (int i = 0; i < n; i++) {
        localMin = min(localMin, arr[i]);
        localMax = max(localMax, arr[i]);
        localSum += arr[i];

        int threadNum = omp_get_thread_num();
        cout << "Thread " << threadNum << " processed element " << i << endl;
    }

    minVal = localMin;
    maxVal = localMax;
    sum = localSum;
    average = static_cast<double>(localSum) / n;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> numbers(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    int minVal, maxVal, sum;
    double average;

    parallelReduction(numbers, minVal, maxVal, sum, average);

    cout << "Min: " << minVal << endl;
    cout << "Max: " << maxVal << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}
