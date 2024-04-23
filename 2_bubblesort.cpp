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

void sequentialBubbleSort(vector<int> &arr)
{
    int n = arr.size();
    bool isSwapped;

    for (int i = 0; i < n; i++)
    {
        isSwapped = false;
        for (int j = 0; j < n - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                isSwapped = true;
            }
        }

        if (!isSwapped)
            break;
    }
}

void parallelBubbleSort(vector<int> &arr)
{
    int n = arr.size();
    bool isSwapped;

    for (int i = 0; i < n; i++)
    {
        isSwapped = false;
        int first = i % 2;
        #pragma omp parallel for shared(arr, first)
        for (int j = first; j < n - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                isSwapped = true;
            }
        }

        if (!isSwapped)
            break;
    }
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

    cout<<"Displaying the array: "<<endl;
    displayArray(arr);
    cout<<endl;

    // Sequential Bubble Sort
    vector<int> arr1 = arr;
    double start_time = omp_get_wtime(); // start timer for sequential algorithm
    sequentialBubbleSort(arr1);
    double end_time = omp_get_wtime(); // end timer for sequential algorithm
    cout << "Time taken by Sequential BubbleSort Algorithm: " << (end_time - start_time) << " seconds" << endl;

    cout<<"Displaying the Sequential Sorted array: "<<endl;
    displayArray(arr1);
    cout<<endl;


    // Parallel Bubble Sort
    vector<int> arr2 = arr;
    start_time = omp_get_wtime(); // start timer for parallel algorithm
    parallelBubbleSort(arr2);
    end_time = omp_get_wtime(); // end timer for parallel algorithm
    cout << "Time taken by Parallel BubbleSort Algorithm: " << (end_time - start_time) << " seconds" << endl;

    cout<<"Displaying the Parallel Sorted array: "<<endl;
    displayArray(arr2);
    cout<<endl;

    return 0;
}