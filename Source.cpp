#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int*& arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int*& arr, int low, int high)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);

        quickSort(arr, low, pivot - 1);
        quickSort(arr, pivot + 1, high);
    }
}

void writeArr(const string& filename, int*& arr, const unsigned& n) {
    ofstream fs;

    fs.open(filename, ios::trunc);
    if (fs.is_open()) {
        for (int i = 0; i < n; i++)
            fs << arr[i] << " ";
        fs << endl;

        fs.close();
    }
}

void writeResult(const string& filename, int*& arr, const unsigned& n) {
    ofstream fs;
    
    fs.open(filename, ios::app);
    if (fs.is_open()) {
        for (int i = 0; i < n; i++)
            fs << arr[i] << " ";
        fs << endl;

        fs.close();
    }
}

void readFile(const string filename, int*& arr, const unsigned& n) {
    fstream fs;

    fs.open(filename);
    if (fs.is_open()) {
        for (int i = 0; i < n; i++)
            fs >> arr[i];
    }
}
 
int main()
{
    const string filename_a = "array_sort_1.txt";
    const string filename_b = "array_sort_2.txt";
    const string filename_c = "array_sort_3.txt";
    const string filename_d = "array_sort_4.txt";
    const string filename = "array_result.txt";
    const unsigned size = 5000000;
    int* arr = new int[size];

    srand(time(nullptr));
    int left_bor = 1500000000, right_bor = 2000000000;
    for (int i = 0; i < size; i++)
        arr[i] = left_bor + rand() % right_bor;
    writeArr(filename_a, arr, size);

    srand(time(nullptr));
    left_bor = 1000000000, right_bor = 1500000000;
    for (int i = 0; i < size; i++)
        arr[i] = left_bor + rand() % right_bor;
    writeArr(filename_b, arr, size);

    srand(time(nullptr));
    left_bor = 500000000, right_bor = 1000000000;
    for (int i = 0; i < size; i++)
        arr[i] = left_bor + rand() % right_bor;
    writeArr(filename_c, arr, size);

    srand(time(nullptr));
    left_bor = 0, right_bor = 500000000;
    for (int i = 0; i < size; i++)
        arr[i] = left_bor + rand() % right_bor;
    writeArr(filename_d, arr, size);

    auto start = chrono::high_resolution_clock::now();
    quickSort(arr, 0, size - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_d = end - start;
    writeResult(filename, arr, size);

    readFile(filename_c, arr, size);
    start = chrono::high_resolution_clock::now();
    quickSort(arr, 0, size - 1);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_c = end - start;
    writeResult(filename, arr, size);

    readFile(filename_b, arr, size);
    start = chrono::high_resolution_clock::now();
    quickSort(arr, 0, size - 1);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_b = end - start;
    writeResult(filename, arr, size);

    readFile(filename_a, arr, size);
    start = chrono::high_resolution_clock::now();
    quickSort(arr, 0, size - 1);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_a = end - start;
    writeResult(filename, arr, size);

    cout << "Sort done in: " << elapsed_a.count() + elapsed_b.count() + elapsed_c.count() + elapsed_d.count() << " seconds";

    return 0;
}