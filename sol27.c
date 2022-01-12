#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define maxN 11000

//insertion
void InsertSort(int *arr, int len)
{
    int tmp;
    for (int i = 2; i <= len; i++)
    {
        tmp = arr[i];
        for (int j = i - 1; j >= 0; j--)
            if (tmp < arr[j])
                arr[j + 1] = arr[j];
            else
            {
                arr[j + 1] = tmp;
                break;
            }
    }
}
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
//quicksort
int part(int arr[], int L, int R)
{
    // median(&arr[L], &arr[(R + L) >> 1], &arr[R]);
    int pivot = arr[R];
    int i = (L - 1);
    for (int j = L; j <= R - 1; j++)
        if (arr[j] < pivot)
            i++, swap(&arr[i], &arr[j]);
    swap(&arr[i + 1], &arr[R]);
    return (i + 1);
}

void quickSort(int arr[], int L, int R)
{
    if (L < R)
    {
        int pi = part(arr, L, R);
        quickSort(arr, L, pi - 1);
        quickSort(arr, pi + 1, R);
    }
}

void MergeSort(int *arr, int L, int R)
{
    int mid, *tmp = (int *)malloc(sizeof(int) * (R - L + 1));
    if (L < R)
    {
        mid = (L + R) >> 1;
        MergeSort(arr, L, mid);
        MergeSort(arr, mid + 1, R);

        int idx = 0, p1 = L, p2 = mid + 1;
        while (p1 <= mid && p2 <= R)
            tmp[idx++] = (arr[p1] < arr[p2] ? arr[p1++] : arr[p2++]);
        while (p1 <= mid)
            tmp[idx++] = arr[p1++];
        while (p2 <= R)
            tmp[idx++] = arr[p2++];
        for (int i = 0; i < idx; i++)
            arr[L + i] = tmp[i];
    }
}

void Heapfy(int *arr, int idx, int len)
{
    if (idx << 1 <= len)
    {
        while ((idx <<= 1) <= len)
        {
            if (idx + 1 <= len && arr[idx + 1] > arr[idx])
                idx += 1;
            if (arr[idx >> 1] < arr[idx])
                swap(&arr[idx], &arr[idx >> 1]);
            else
                break;
        }
    }
}

void HeapSort(int *arr, int len)
{
    for (int i = len >> 1; i >= 1; i--)
        Heapfy(arr, i, len);
    for (int i = len; i > 1; i--)
        swap(&arr[1], &arr[i]), Heapfy(arr, 1, i - 1);
}
