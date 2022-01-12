#include <stdio.h>
#include <stdlib.h>
//leftist
typedef struct Node
{
    int val, npl; //null path length
    struct Node *l, *r;
} Node;

Node *new_node(int x)
{
    Node *tmp = (Node *)malloc(sizeof(struct Node));
    tmp->val = x;
    tmp->npl = 0;
    tmp->l = tmp->r = NULL;
    return tmp;
}

void swap(Node *x, Node *y)
{
    Node tmp = *x; //the content of x
    *x = *y;
    *y = tmp;
}

Node *merge_sub(Node *, Node *);
Node *merge(Node *, Node *);

Node *merge_sub(Node *root, Node *child)
{
    if (root->l == NULL)
        root->l = child; //leftist first
    else
    {
        root->r = merge(root->r, child);
        if (root->r->npl > root->l->npl) //check if the npl right is larger than npl left
            swap(root->l, root->r);
        root->npl = root->r->npl + 1;
    }
    return root;
}

Node *merge(Node *x, Node *y)
{
    if (x == NULL)
        return y;
    if (y == NULL)
        return x;
    return (x->val < y->val) ? merge_sub(x, y) : merge_sub(y, x);
}

Node *insert(Node *root, int x)
{
    Node *tmp = new_node(x);
    root = merge(root, tmp);
    return root;
}

Node *pop_min(Node *root)
{
    // printf("%d ", root->val);
    root = merge(root->r, root->l);
    return root;
}
