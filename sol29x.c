
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

/*
M = 100000
N = 10000
U = 10000
*/
typedef struct bitmap
{
    int *bits, range;
} Bitmap;

int _h;

Bitmap *tmpapInit(int range)
{
    Bitmap *tmp = (Bitmap *)malloc(sizeof(Bitmap));
    tmp->bits = (int *)malloc(sizeof(int) * range + 1);
    tmp->range = range;
    memset(tmp->bits, 0, sizeof(tmp->range));
    return tmp;
}

int hash(char *key, int seed)
{
    return (*key - 'A') * 0x123 + seed;
}

void tmpapSet(Bitmap *tmp, int x)
{
    tmp->bits[(x % tmp->range)] |= (1 << (x % 32));
}

int tmpapExist(Bitmap *tmp, int x)
{
    return (tmp->bits[(x % tmp->range)] & (1 << (x % 32))) != 0;
}

void BFilterSet(Bitmap *tmp, char *str)
{
    for (int i = 1; i <= _h; i++)
    {
        tmpapSet(tmp, (hash(str, 1 << i)));
    }
}

int BFilterExist(Bitmap *tmp, char *str)
{
    for (int i = 1; i <= _h; i++)
    {
        if (!tmpapExist(tmp, (hash(str, 1 << i))))
            return 0;
    }
    return 1;
}

int main()
{
    int n, m;
    scanf("%d%d%d", &n, &m, &_h);
    char *str = (char *)malloc(sizeof(char) * 100);
    Bitmap *tmp = tmpapInit(m);
    for (int i = 1; i <= n; i++)
        scanf("%s", str), BFilterSet(tmp, str);
    for (int i = 1; i <= n; i++)
        scanf("%s", str), printf("%d\n", BFilterExist(tmp, str));
}