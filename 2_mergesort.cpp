/*
    Problem Statement:
        Write a program to implement Parallel Bubble Sort and Merge sort using OpenMP.
        Use existing algorithms and measure the performance of sequential and parallel algorithms.
*/

#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

void displayArray(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Merge two sorted subarrays arr[low...mid] and arr[mid+1...high]
void merge(vector<int> &arr, int low, int mid, int high)
{
    // aux is used to temporary store the vector obtained by merging elements from [low to mid] and [mid+1 to high] in arr
    vector<int> aux; // auxillary array

    int i = low;
    int j = mid + 1;

    // while there are elements in the both subarrays
    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
        {
            aux.push_back(arr[i]);
            i++;
        }
        else
        {
            aux.push_back(arr[j]);
            j++;
        }
    }

    // copy remaining elements
    while (i <= mid)
    {
        aux.push_back(arr[i]);
        i++;
    }

    // copy remaining elements
    while (j <= high)
    {
        aux.push_back(arr[j]);
        j++;
    }

    // copy back to the original array to reflect sorted order
    for (int i = low; i <= high; i++)
    {
        arr[i] = aux[i - low];
    }
}

void sequentialMergeSort(vector<int> &arr, int low, int high)
{
    if (low >= high)
        return;

    int mid = (low + high) / 2;
    sequentialMergeSort(arr, low, mid);
    sequentialMergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

void parallelMergeSort(vector<int> &arr, int low, int high)
{
    if (low >= high)
        return;

    int mid = (low + high) / 2;
#pragma omp parallel sections
    {
#pragma omp section
        {
            parallelMergeSort(arr, low, mid);
        }

#pragma omp section
        {
            parallelMergeSort(arr, mid + 1, high);
        }
    }
    merge(arr, low, mid, high);
}

int main()
{
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> arr(n);
   
    // Random generating elements and storing in arr
    srand(time(0));
    for (int i = 0; i < n; ++i)
    {
        arr[i] = rand() % 100;
    }

    cout << "Displaying the array: " << endl;
    displayArray(arr);
    cout << endl;

    // Sequential Merge Sort
    vector<int> arr1 = arr;
    double start_time = omp_get_wtime(); // start timer for sequential algorithm
    sequentialMergeSort(arr1, 0, n - 1);
    double end_time = omp_get_wtime(); // end timer for sequential algorithm
    cout << "Time taken by Sequential MergeSort Algorithm: " << (end_time - start_time) << " seconds" << endl;

    cout << "Displaying the Sequential Sorted array: " << endl;
    displayArray(arr1);
    cout << endl;

    // Parallel Merge Sort
    vector<int> arr2 = arr;
    start_time = omp_get_wtime(); // start timer for parallel algorithm
    parallelMergeSort(arr2, 0, n - 1);
    end_time = omp_get_wtime(); // end timer for parallel algorithm
    cout << "Time taken by Parallel MergeSort Algorithm: " << (end_time - start_time) << " seconds" << endl;

    cout << "Displaying the Parallel Sorted array: " << endl;
    displayArray(arr2);
    cout << endl;

    return 0;
}