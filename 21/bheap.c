#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_N 100000

typedef struct Node
{
    int data, deg;
    struct Node *par, *ch, *sbl;
} Node;

typedef struct Tree
{
    struct Node *main, *exc;
} Tree;

Tree *table[MAX_N];
int size = 1;

void init()
{
    Tree *tmp;

    for (int i = 0; i < MAX_N; ++i)
    {
        tmp = (Tree *)malloc(sizeof(Tree));
        tmp->main = NULL;
        tmp->exc = NULL;
        table[i] = tmp;
    }
}

Node *new_node(int x)
{
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->data = x;
    tmp->deg = 0;
    tmp->ch = tmp->par = tmp->sbl = NULL;
    return tmp;
}

Node *merge(Node *b1, Node *b2)
{
    //make the par smaller
    if (b1->data > b2->data)
    {
        b1->par = b2, b1->sbl = b2->ch;
        b2->ch = b1, b2->deg++;
        return b2;
    }
    else
    {
        b2->par = b1, b2->sbl = b1->ch;
        b1->ch = b2, b1->deg++;
        return b1;
    }
}

void adjust()
{
    Node *tmp;
    for (int i = size - 1; i >= 0; --i)
    {
        if (table[i]->main != NULL && table[i]->exc != NULL)
        {
            tmp = merge(table[i]->main, table[i]->exc);
            table[i]->main = table[i]->exc = NULL;
            if (!table[i + 1]->main)
                table[i + 1]->main = tmp;
            else
                table[i + 1]->exc = tmp;
            if ((i + 1) == size)
                ++size;
        }
    }
    for (int i = 0; i < size; ++i)
    {
        if (table[i]->main != NULL && table[i]->exc != NULL)
        {
            tmp = merge(table[i]->main, table[i]->exc);
            table[i]->main = table[i]->exc = NULL;
            if (!table[i + 1]->main)
            {
                table[i + 1]->main = tmp;
            }
            else
            {
                table[i + 1]->exc = tmp;
            }
            if ((i + 1) == size)
                ++size;
        }
    }
}

void insert_node(int x)
{
    Node *tmp = new_node(x);
    if (!table[0]->main)
    {
        table[0]->main = tmp;
    }
    else
    {
        table[0]->exc = tmp;
    }
    adjust();
}

Node *get_min()
{
    Node *tmp = NULL;
    for (int i = 0; i < size; ++i)
    {
        if (table[i]->main)
        {
            if (!tmp)
                tmp = table[i]->main;
            else
            {
                if (table[i]->main->data < tmp->data)
                    tmp = table[i]->main;
            }
        }
    }
    return tmp;
}

int pop_min()
{
    Node *pop = get_min();
    Node *tmp;
    for (Node *ptr = pop->ch; ptr != NULL; ptr = tmp)
    {
        if (!table[ptr->deg]->main)
            table[ptr->deg]->main = ptr;
        else
            table[ptr->deg]->exc = ptr;
        tmp = ptr->sbl;
        ptr->sbl = NULL;
    }
    table[pop->deg]->main = NULL;
    adjust();
    return pop->data;
}
