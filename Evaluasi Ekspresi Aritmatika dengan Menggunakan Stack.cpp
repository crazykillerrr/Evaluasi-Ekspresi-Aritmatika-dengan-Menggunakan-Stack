#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <random>

using namespace std;
using namespace std::chrono;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(arr[min_idx], arr[i]);
    }
}

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void generateData(vector<int>& arr, int size, const string& type) {
    arr.resize(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, size);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    if (type == "reverse") {
        sort(arr.begin(), arr.end(), greater<int>());
    } else if (type == "sorted") {
        sort(arr.begin(), arr.end());
    }
}

void measureSortingTime(void (*sortFunc)(vector<int>&), vector<int>& arr, const string& algorithm, int size, const string& type) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << setw(12) << algorithm << setw(12) << type << setw(12) << size << setw(12) << duration << endl;
}

int main() {
    vector<int> sizes = {10, 100, 500, 1000, 10000};
    vector<string> dataTypes = {"random", "reverse", "sorted"};
    vector<void(*)(vector<int>&)> sortFunctions = {bubbleSort, insertionSort, selectionSort, mergeSort, quickSort};
    vector<string> sortNames = {"BubbleSort", "InsertionSort", "SelectionSort", "MergeSort", "QuickSort"};

    cout << setw(12) << "Algorithm" << setw(12) << "DataType" << setw(12) << "Size" << setw(12) << "Time (us)" << endl;
    cout << string(48, '-') << endl;

    for (const auto& size : sizes) {
        for (const auto& type : dataTypes) {
            for (size_t i = 0; i < sortFunctions.size(); ++i) {
                vector<int> arr;
                generateData(arr, size, type);
                measureSortingTime(sortFunctions[i], arr, sortNames[i], size, type);
            }
        }
    }

    return 0;
}
