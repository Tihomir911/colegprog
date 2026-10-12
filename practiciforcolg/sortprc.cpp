#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>
#include <string>
#include <limits>

using namespace std;
using namespace std::chrono;

using ull = unsigned long long;

// ---------- Сортировка пузырьком ----------
void bubbleSort(vector<int>& a, ull& ops) {
    int n = (int)a.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                ++ops;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// ---------- Сортировка выбором ----------
void selectionSort(vector<int>& a, ull& ops) {
    int n = (int)a.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            swap(a[i], a[minIdx]);
            ++ops;
        }
    }
}

// ---------- Сортировка вставками ----------
void insertionSort(vector<int>& a, ull& ops) {
    int n = (int)a.size();
    for (int i = 1; i < n; ++i) {
        int key = a[i];
        int j = i - 1;
        int shifts = 0;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            ++ops;
            ++shifts;
            --j;
        }
        if (shifts > 0) {
            a[j + 1] = key;
            ++ops;
        }
    }
}

// ---------- Быстрая сортировка ----------
void quickSortRecursive(vector<int>& a, int left, int right, ull& ops) {
    if (left >= right) return;

    int i = left, j = right;
    int pivot = a[left + (right - left) / 2];

    while (i <= j) {
        while (a[i] < pivot) ++i;
        while (a[j] > pivot) --j;
        if (i <= j) {
            if (i != j) {
                swap(a[i], a[j]);
                ++ops;
            }
            ++i;
            --j;
        }
    }

    quickSortRecursive(a, left, j, ops);
    quickSortRecursive(a, i, right, ops);
}

void quickSort(vector<int>& a, ull& ops) {
    if (!a.empty())
        quickSortRecursive(a, 0, (int)a.size() - 1, ops);
}

// ---------- Сортировка слиянием ----------
void mergeSortRecursive(vector<int>& a, vector<int>& tmp, int left, int right, ull& ops) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSortRecursive(a, tmp, left, mid, ops);
    mergeSortRecursive(a, tmp, mid + 1, right, ops);

    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
        }
        ++ops;
    }
    while (i <= mid) {
        tmp[k++] = a[i++];
        ++ops;
    }
    while (j <= right) {
        tmp[k++] = a[j++];
        ++ops;
    }
    for (i = left; i <= right; ++i) {
        a[i] = tmp[i];
        ++ops;
    }
}

void mergeSort(vector<int>& a, ull& ops) {
    if (a.empty()) return;
    vector<int> tmp(a.size());
    mergeSortRecursive(a, tmp, 0, (int)a.size() - 1, ops);
}

// ---------- Шейкерная сортировка ----------
void shakerSort(vector<int>& a, ull& ops) {
    int n = (int)a.size();
    int left = 0, right = n - 1;

    while (left < right) {
        bool swapped = false;

        for (int i = left; i < right; ++i) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                ++ops;
                swapped = true;
            }
        }
        --right;
        if (!swapped) break;

        swapped = false;
        for (int i = right; i > left; --i) {
            if (a[i - 1] > a[i]) {
                swap(a[i - 1], a[i]);
                ++ops;
                swapped = true;
            }
        }
        ++left;
        if (!swapped) break;
    }
}

// ---------- Замер времени ----------
struct Result {
    double ms = 1e100;
    ull ops = 0;
};

template <typename Func>
Result measure(const vector<int>& original, Func sortFunc, int runs) {
    Result best;
    for (int r = 0; r < runs; ++r) {
        vector<int> arr = original;
        ull ops = 0;

        auto start = steady_clock::now();
        sortFunc(arr, ops);
        auto end = steady_clock::now();

        double ms = duration<double, milli>(end - start).count();
        if (ms < best.ms) {
            best.ms = ms;
            best.ops = ops;
        }
    }
    return best;
}

void printResult(const string& name, const Result& res) {
    cout << left << setw(18) << name
         << right << setw(12) << fixed << setprecision(3) << res.ms
         << setw(18) << res.ops << "\n";
}

int main() {
    vector<int> sizes = {1000, 10000, 100000};
    const int RUNS = 5;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 1000000);

    for (int size : sizes) {
        vector<int> original(size);
        for (int& x : original) x = dist(gen);

        cout << "Array size: " << size << "\n";
        cout << left << setw(18) << "Sort"
             << right << setw(12) << "Time, ms"
             << setw(18) << "Swaps/Moves" << "\n";
        cout << string(48, '-') << "\n";

        printResult("Bubble sort",
                    measure(original, [](vector<int>& a, ull& ops) { bubbleSort(a, ops); }, RUNS));

        printResult("Selection sort",
                    measure(original, [](vector<int>& a, ull& ops) { selectionSort(a, ops); }, RUNS));

        printResult("Insertion sort",
                    measure(original, [](vector<int>& a, ull& ops) { insertionSort(a, ops); }, RUNS));

        printResult("Quick sort",
                    measure(original, [](vector<int>& a, ull& ops) { quickSort(a, ops); }, RUNS));

        printResult("Merge sort",
                    measure(original, [](vector<int>& a, ull& ops) { mergeSort(a, ops); }, RUNS));

        printResult("Shaker sort",
                    measure(original, [](vector<int>& a, ull& ops) { shakerSort(a, ops); }, RUNS));

        cout << "\n";
    }

    return 0;
}