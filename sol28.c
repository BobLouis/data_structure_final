#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DIV 17

int arr[DIV];

int insert(int x)
{
    int key = x % DIV;
    int ptr = key;
    if (!~arr[key])
    {
        arr[key] = x;
        return 1;
    }
    else
    {
        ptr++;
        while (ptr != key)
        {
            if (ptr == DIV)
                ptr = 0;
            if (arr[ptr] == -1)
            {
                arr[ptr] = x;
                return 1;
            }
            ptr++;
        }
    }
    return -1; //array full
}

int search(int x)
{
    int key = x % DIV;
    int ptr = key;
    if (arr[key] == x)
        return key;
    else
    {
        ptr++;
        while (ptr != key)
        {
            if (ptr == DIV)
                ptr = 0;
            if (arr[ptr] == x)
                return ptr;
            ptr++;
        }
    }
    return -1;
}

int dis(int ptr, int des)
{
    if (ptr >= des)
        return ptr - des;
    else
        return DIV - des + ptr;
}

int delete (int x)
{
    int key = search(x);
    if (key == -1)
        return -1; //key not found
    int ptr = key;
    int ety, des;
    arr[ptr] = -1;
    ety = ptr;
    ptr++;
    while (ptr != key)
    {
        des = arr[ptr] % DIV;
        if (arr[ptr] != -1 && des != ptr && dis(ptr, des) > dis(ety, des))
        {
            arr[ety] = arr[ptr];
            arr[ptr] = -1;
            ety = ptr;
            ptr++;
        }
        else
            ptr++;
        if (ptr == DIV)
            ptr = 0;
    }
    return 1;
}

int main()
{

    int input[] = {6, 12, 34, 29, 28, 11, 23, 7, 0, 33, 30, 45};
    memset(arr, -1, DIV * sizeof(int));
    print();
    for (int i = 0; i < sizeof(input) / sizeof(int); i++)
    {
        insert(input[i]);
        print();
    }
    for (int i = 0; i < sizeof(input) / sizeof(int); i++)
    {
        printf("%d ", search(input[i]));
    }
    printf("\n");
    print();
    delete (29);
    print();
    return 0;
}