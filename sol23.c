#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100000

int h[MAX_N];
int last = 1;

void insert(int x)
{
    int cur, done = 0, gp, lcgp, rcgp;

    cur = ++last;
    //swap if right is bigger than left
    if (last % 2 == 1 && x < h[last - 1])
    {
        h[last] = h[last - 1];
        cur--;
    }
    while (!done && cur >= 4)
    {
        gp = cur / 4;    //grandparent
        lcgp = 2 * gp;   //left child of gp (smallest)
        rcgp = lcgp + 1; //right child of gp (biggest) of the feild
        if (x < h[lcgp])
        {
            h[cur] = h[lcgp];
            ;
            cur = lcgp;
        }
        else if (x > h[rcgp])
        {
            h[cur] = h[rcgp];
            cur = rcgp;
        }
        else
        {
            done = 1; //p2 p3 complete
        }
    }
    h[cur] = x;
}

void adjust()
{
    int idx = last;
    int tmp;
    if (idx < 16 && idx > 7)
    {
        if (idx % 2 == 0)
            idx--;
        for (int i = idx; idx > 7; idx -= 2)
        {
            if (h[i] < h[i - 1])
            {
                tmp = h[i];
                h[i] = h[i - 1];
                h[i - 1] = tmp;
            }
        }
    }
    else if (idx < 8 && idx > 3)
    {
        if (idx % 2 == 0)
            idx--;
        for (int i = idx; idx > 3; idx -= 2)
        {
            if (h[i] < h[i - 1])
            {
                tmp = h[i];
                h[i] = h[i - 1];
                h[i - 1] = tmp;
            }
        }
    }
}

void delete_min()
{
    int done = 0, cur = 2, tmp = h[last--], ch_l, ch_r;
    while (!done && cur <= last)
    {
        ch_l = cur * 2;
        ch_r = ch_l + 2;
        if ((ch_l <= last && tmp > h[ch_l]) || (ch_r <= last && tmp > h[ch_r]))
        {
            if (h[ch_l] < h[ch_r])
                h[cur] = h[ch_l], cur = ch_l;
            else
                h[cur] = h[ch_r], cur = ch_r;
        }
        else
            done = 1;
    }
    h[cur] = tmp;
    adjust();
}

void delete_max()
{
    int done = 0, cur = 3, tmp = h[last--], ch_l, ch_r;
    while (!done && cur <= last)
    {
        ch_l = cur * 2 - 1;
        ch_r = ch_l + 2;
        if ((ch_l <= last && tmp < h[ch_l]) || (ch_r <= last && tmp < h[ch_r]))
        {
            if (h[ch_l] > h[ch_r])
                h[cur] = h[ch_l], cur = ch_l;
            else
                h[cur] = h[ch_r], cur = ch_r;
        }
        else
            done = 1;
    }
    h[cur] = tmp;
    adjust();
}

void show()
{
    printf("NULL\n");
    for (int i = 2; i <= last; ++i)
    {
        if (i == 3 || i == 7 || i == last)
            printf("%d\n", h[i]);
        else
            printf("%d ", h[i]);
    }
}

int main()
{
    char str[15] = {'\0'};
    int x;
    while (*str != 'q')
    {
        scanf("%s", str);
        if (*str == 'i')
        {
            scanf("%d", &x);
            insert(x);
        }
        else if (*str == 'd')
        {
            scanf("%s", str);
            if (*(str + 1) == 'i')
                delete_min();
            else
                delete_max();
        }
        else if (*str == 's')
        {
            show();
        }
    }
}