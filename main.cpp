#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include <vector>

using std::vector;
using std::cout;
using std::random_device;
using std::uniform_int_distribution;

random_device dev;
std::mt19937 rng(dev());


int* createRandomArray(int length, int begin, int end) {
    std::uniform_int_distribution<std::mt19937::result_type> dist(begin, end);

    int* arr = new int[length];

    for (int i = 0; i < length; i++) {
        arr[i] = dist(rng);
    }

    return arr;
}

int* copyArray(int arr[], int length) {
    int* dest = new int[length];

    std::copy(arr, arr + length, dest);
    
    return dest;
}

void print(int* arr, int length) {
    cout << "[ ";
    for (int i = 0; i < length; i++) {
        cout << arr[i] << ", ";
    }

    cout << "]\n";
}

void sortAndPrintExecutionTime(int arr[], int length, int* (*sortingFunction)(int[], int)) {
    int* copy = copyArray(arr, length);

    auto startTime = std::chrono::system_clock::now();
    
    copy = sortingFunction(copy, length);

    auto endTime = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsedTime = endTime - startTime;

    print(copy, length);

    cout<< "----------------------\n";
    cout << "Time taken: " << elapsedTime.count() << "\n";
}

int* bubbleSort(int arr[], int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length -i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
            }
        }
    }

    return arr;
}

int* selectionSort(int arr[], int length) {
    for (int i = 0; i < length - 1; i++) {
        int min = i;

        for (int j = i + 1; j < length; j++) {
            if (arr[min] > arr[j]) {
                min = j;
            }
        }
        
        int aux = arr[min];
        arr[min] = arr[i];
        arr[i] = aux;
    }

    return arr;
}

int* insertionSort(int arr[], int length) {
    for (int i = 1; i < length; i++) {
        int aux = arr[i];
        int j = i - 1;

        while (j >=0 && arr[j] > aux) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = aux;
    }

    return arr;
}

int* shellSort(int arr[], int length) {
    for (int gap = length / 2; gap > 0; gap = gap / 2) {
        for (int i = gap; i < length; i++) {
            int aux = arr[i];
            int j = i - gap;

            while (j >= 0 && arr[j] > aux) {
                arr[j + gap] = arr[j];
                j -= gap;
            }

            arr[j + gap] = aux;
        }
    }

    return arr;
}

int partition(int arr[], int length) {
    int pivot = arr[length - 1];

    int i = -1;

    for (int j = 0; j < length; j++) {
        if (arr[j] < pivot) {
            ++i;
            int aux = arr[i];
            arr[i] = arr[j];
            arr[j] = aux;
        }
    }

    ++i;
    int aux = arr[i];
    arr[i] = arr[length - 1];
    arr[length - 1] = aux;

    return i;
}

int* quickSort(int arr[], int length) {
    if (length <= 1)
        return arr;
    
    int pivot = partition(arr, length);

    quickSort(arr, pivot);
    quickSort(arr + pivot + 1, length - pivot - 1);

    return arr;
}

int* merge(int letftArray[], int leftLength, int rightArray[], int rightLength) {
    int* result = (int*)malloc(sizeof(int) * (leftLength + rightLength));
    
    int left = 0;
    int right = 0;
    int k = 0;

    while (left < leftLength && right < rightLength) {
        if (letftArray[left] < rightArray[right]) {
            result[k] = letftArray[left];
            ++left;
        }
        else {
            result[k] = rightArray[right];
            ++right;
        }
        ++k;
    }

    while (left < leftLength) {
        result[k] = letftArray[left];
        ++left;
        ++k;
    }

    while (right < rightLength) {
        result[k] = rightArray[right];
        ++right;
        ++k;
    }
    
    return result;
}

int* mergeSort(int array[], int length) {
    if (length <= 1)
        return array;
    
    int leftLength = length / 2 + (length % 2);
    int rightLength = length / 2;

    int* left = array;
    int* right = array + leftLength;

    left = mergeSort(left, leftLength);
    right = mergeSort(right, rightLength);

    return merge(left, leftLength, right, rightLength);
}

int main() {
    const int length = 20;
    int* arr = createRandomArray(length, 0, 1000);

    print(arr, length);
    cout << "===========\n\n";

    cout << "Bubble Sort: " << "\n";
    sortAndPrintExecutionTime(arr, length, bubbleSort);
    cout << "===========\n\n";

    cout << "Selection Sort: " << "\n";
    sortAndPrintExecutionTime(arr, length, selectionSort);
    cout << "===========\n\n";

    cout << "Insertion Sort: " << "\n";
    sortAndPrintExecutionTime(arr, length, insertionSort);
    cout << "===========\n\n";

    cout << "Shell Sort: " << "\n";
    sortAndPrintExecutionTime(arr, length, shellSort);
    cout << "===========\n\n";

    cout << "Quick Sort: " << "\n";
    sortAndPrintExecutionTime(arr, length, quickSort);
    cout << "===========\n\n";

    cout << "Merge Sort: " << "\n";
    sortAndPrintExecutionTime(arr, length, mergeSort);
    cout << "===========\n\n";
}